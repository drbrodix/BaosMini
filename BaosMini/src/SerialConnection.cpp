#include "SerialConnection.hpp"

SerialConnection::SerialConnection(std::string connectString)
	: connectionName(connectString)
	, serialHandle(nullptr)
    , dcbSerialParam{0}
    , timeout{0}
    , isOddFrame(true)
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
    const unsigned char controlByte = getControlByte();
    const unsigned char checksum = ChecksumCalculator::calculateChecksum(telegramData, controlByte);

    sendResetRequest();
    FrameFormatter::formatFt12Frame(
        &ft12Frame,
        telegramData,
        controlByte,
        checksum
    );

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

    recieveTelegram();

    return true;
}

bool SerialConnection::recieveTelegram() const
{
    const unsigned short BUFFER_SIZE = 250;
    unsigned char readBuffer[BUFFER_SIZE + 1] = { 0 };

    // Write data
    DWORD drBytesRead = 0;
    if (!ReadFile(
        serialHandle,
        readBuffer,
        250,
        &drBytesRead,
        nullptr
    )) {
        std::cerr << "Error while writing to COM port." << '\n';
        return false;
    }
    else {
        sendAck();
    }

    std::ostringstream oss;

    for (DWORD i = 0; i < drBytesRead; i++)
    {
        std::cout << std::hex << (unsigned int)readBuffer[i] << " ";
    }

    std::cout << '\n';

    return true;
}

bool SerialConnection::sendAck() const
{
    const unsigned char ACK_BYTE[] = { 0xe5 }; // Acknowledgement byte

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