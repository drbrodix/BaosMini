#include "SerialConnection.hpp"

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
    timeout.ReadTotalTimeoutConstant    = MAXDWORD; // provides the amount of time to wait before returning (in milliseconds).
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

bool SerialConnection::sendTelegram(std::vector<unsigned char>* telegramData)
{
    std::vector<unsigned char> ft12Frame;
    
    // Initialize some variables for readability
    const unsigned char controlByte = getControlByte();
    const unsigned char checksum = ChecksumCalculator::calculateChecksum(telegramData, controlByte);
    const unsigned char subServiceCode = telegramData->at(1);
    const bool isReadAnswerReq = checkIsReadAnswerReq(subServiceCode);

    // Serial communication needs a reset request before the actual BAOS telegram
    //sendResetRequest();

    // Format the final FT1.2 frame
    FrameFormatter::formatFt12Frame(
        &ft12Frame,
        telegramData,
        controlByte,
        checksum
    );

    // Windows serial API function requires an array, so
    // thanks Microsoft for these ugly 3 lines of code...
    size_t buffSize = ft12Frame.size();
    unsigned char* pBuff = new unsigned char[buffSize];
    std::copy(ft12Frame.begin(), ft12Frame.end(), pBuff);

    // Write data
    DWORD dwBytesWritten = 0;
    if (!WriteFile(
        serialHandle,
        pBuff,
        buffSize,
        &dwBytesWritten,
        nullptr
    )) {
        std::cerr << "Error while writing to COM port." << '\n';
    }

    delete[] pBuff;

    const unsigned short READ_TELEGRAM_BUFF_SIZE = 200;
    unsigned char *pReadTelegram = new unsigned char[READ_TELEGRAM_BUFF_SIZE];

    const size_t READ_TELEGRAM_LENGTH = DataReader::recieveTelegram(serialHandle, pReadTelegram);

    if (READ_TELEGRAM_LENGTH > 0)
    {
        sendAck();

        std::ostringstream oss;

        for (int i = 0; i < READ_TELEGRAM_LENGTH; i++)
        {
            std::cout << std::hex << (unsigned int)pReadTelegram[i] << " ";
        }

        std::cout << '\n';
    }
    else
    {
        std::cerr << "Error while reading from COM port." << '\n';
    }

    delete[] pReadTelegram;

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

bool SerialConnection::checkIsReadAnswerReq(unsigned char subServiceCode) const
{
    switch (subServiceCode)
    {
    case 0x01:
    case 0x03:
    case 0x04:
    case 0x05:
    case 0x07:
        return true;
        break;
    default:
        return false;
        break;
    }
}