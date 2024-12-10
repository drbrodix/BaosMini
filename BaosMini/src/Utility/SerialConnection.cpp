#include "../../include/Utility/SerialConnection.hpp"

SerialConnection::SerialConnection(std::string connectString)
	: connectionName(connectString)
	, serialHandle(nullptr)
    , dcbSerialParam{0}
    , timeout{0}
    , isOddFrame(true)
    , isFirstTelegram(true)
{
	serialHandle = createSerialHandle();
    if (serialHandle == INVALID_HANDLE_VALUE)
    {
        if (GetLastError() == ERROR_FILE_NOT_FOUND)
        {
            std::cerr << "COM3 not found" << '\n';
        }
        else
        {
            std::cerr << "Error opening serial port." << '\n';
        }
    }

    configureConnect();
    configureTimeout();
    sendResetRequest();
}

SerialConnection::~SerialConnection()
{
    // Close port
    if (!CloseHandle(serialHandle))
    {
        std::cerr << "Error while closing COM port." << '\n';
    }
}

HANDLE SerialConnection::createSerialHandle() const
{
	return CreateFile(
        // std::string -> LPCWSTR conversion needs to be done locally,
        // so that we won't end up with a dangling pointer
        (std::wstring(connectionName.begin(), connectionName.end()).c_str()),
        GENERIC_READ | GENERIC_WRITE,
        0,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );
}

bool SerialConnection::configureConnect()
{
    dcbSerialParam.DCBlength = sizeof(dcbSerialParam);
    if (!GetCommState(serialHandle, &dcbSerialParam))
    {
        std::cerr << "Error while fetching COM properties." << '\n';
    }

    dcbSerialParam.BaudRate = CBR_19200;
    dcbSerialParam.ByteSize = 8;
    dcbSerialParam.StopBits = ONESTOPBIT;
    dcbSerialParam.Parity   = EVENPARITY;

    if (!SetCommState(serialHandle, &dcbSerialParam))
    {
        std::cerr << "Error while setting serial port properties." << '\n';
    }
    
    return true;
}

bool SerialConnection::configureTimeout()
{
    timeout.ReadIntervalTimeout         = 100; // specifies the time that must pass between receiving characters before timing out (in milliseconds).
    timeout.ReadTotalTimeoutConstant    = 100; // provides the amount of time to wait before returning (in milliseconds).
    timeout.ReadTotalTimeoutMultiplier  = 0; // specifies the length of time to wait before responding for each byte requested in the read operation (in milliseconds).
    timeout.WriteTotalTimeoutConstant   = MAXDWORD; // same as in case of reading, but for writing
    timeout.WriteTotalTimeoutMultiplier = 0; // same as in case of reading, but for writing

    if (!SetCommTimeouts(serialHandle, &timeout))
    {
        std::cerr << "Error while setting timeout properties." << '\n';
    }
    return true;
}

unsigned char SerialConnection::getControlByte()
{
    const unsigned char currentControlByte = CONTROL_BYTE[isOddFrame];
    isOddFrame = !isOddFrame;
    return currentControlByte;
}

bool SerialConnection::sendTelegram(unsigned char* baosTelegram, unsigned char telegramLength, DatapointTypes::DATAPOINT_TYPES dpt)
{
    // Initialize some variables for readability
    const unsigned char controlByte = getControlByte();
    const unsigned char checksum = ChecksumCalculator::calculateChecksumSent(baosTelegram, telegramLength, controlByte);
    // const bool isReadAnswerReq = checkIsReadAnswerReq(subServiceCode);

    // Format the final FT1.2 frame
    unsigned short bytesToWrite = FrameFormatter::formatFt12Frame(
        baosTelegram,
        telegramLength,
        controlByte,
        checksum
    );

    // Write data
    DWORD dwBytesWritten = 0;
    if (!WriteFile(
        serialHandle,
        baosTelegram,
        bytesToWrite,
        &dwBytesWritten,
        nullptr
    )) {
        std::cerr << "Error while writing to COM port." << '\n';
        return false;
    }
    return true;
}

bool SerialConnection::sendAck() const
{
    const unsigned char ACK_BYTE[1] = { 0xe5 }; // Acknowledgement byte

    // Write data
    DWORD dwBytesWritten = 0;
    if (!WriteFile(
        serialHandle,
        ACK_BYTE,
        sizeof(ACK_BYTE),
        &dwBytesWritten,
        nullptr
    )) {
        std::cerr << "Error while writing to COM port." << '\n';
        return false;
    }
    else
    {
        return true;
    }
}

bool SerialConnection::sendResetRequest() const
{
    // Reset request frame
    const unsigned char RESET_REQUEST[] = {
        0x10,
        0x40,
        0x40,
        0x16
    };

    // Write reset request
    DWORD dwBytesWrittenRR = 0;
    if (!WriteFile(
        serialHandle,
        RESET_REQUEST,
        sizeof(RESET_REQUEST),
        &dwBytesWrittenRR,
        nullptr
    )) {
        std::cerr << "Error while writing to COM port." << '\n';
    }

    return true;
}

//                                  //
//  Reader Functions Section Below  //
//                                  //

// Return true if parameter char is found
bool SerialConnection::isCharFound(unsigned char charToFind) const
{
    unsigned char c = 0;

    // Looking for starter byte of FT1.2 frame
    DWORD drBytesRead = 0;
    if (!ReadFile(
        serialHandle,
        &c,
        sizeof(c),
        &drBytesRead,
        nullptr
    ))
    {
        return false;
    }

    return c == charToFind;
}

// Return telegram length, or 0 if reading failed
unsigned int SerialConnection::readHeader(unsigned char* ft12Header) const
{
    // Reading FT1.2 header
    for (int i = 1; i < FT12_HEADER_SIZE; i++)  // Loop start index at 1, because
        // index 0 will be set manually to 0x68
    {
        DWORD headerBytesRead = 0;
        if (!ReadFile(
            serialHandle,
            ft12Header + i,
            1,
            &headerBytesRead,
            nullptr
        )) {
            return 0;
        }
    }

    ft12Header[0] = FT12_START_BYTE; // Index 0 of FT1.2 header set to start byte 0x68

    if (ft12Header[0] != ft12Header[3])
    {
        return 0;
    }
    else
    {
        return ft12Header[1] - 1; // (Data length plus control byte) minus control byte;
    }
}

bool SerialConnection::readData(unsigned char* buffer) const
{
    DWORD bytesRead = 0;
    if (!ReadFile(
        serialHandle,
        buffer,
        1,
        &bytesRead,
        nullptr
    ))
    {
        return false;
    }
    return true;
}

// Recieve Telegram
// I know it's terrible... I'm just an intern, don't judge me...
unsigned int SerialConnection::recieveTelegram(unsigned char* telegramCharArray)
{
    //const unsigned short MAX_TRIES_COUNT        = 30;       // Caps number of tries looking for FT1.2 start byte
    //unsigned int readTries                      = 0;        // Keeps count of number of tries looking for FT1.2 start byte
    unsigned int telegramLength = 0;        // Variable to save BAOS telegram length after reading FT1.2 header
    unsigned char ft12Header[FT12_HEADER_SIZE] = { 0 };    // { (0) 0x68 , (1) Length, (2) Length, (3) 0x68, (4) ControlByte }
    unsigned char checksum = 0;
    unsigned char endByte = 0;

    while (!isCharFound(FT12_START_BYTE));

    telegramLength = readHeader(ft12Header);

    for (unsigned int i = 0; i < telegramLength; i++)
    {
        readData(telegramCharArray + i);
    }

    readData(&checksum);

    readData(&endByte);

    if (checksum !=
        ChecksumCalculator::calculateChecksumRecieved(telegramCharArray, telegramLength, ft12Header[4]))
    {
        printf("Checksum error\n");
        return 0;
    }

    return telegramLength;
}