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

HANDLE SerialConnection::getHandle() const
{
    return serialHandle;
}

bool SerialConnection::switchControlByteState()
{
    isOddFrame = !isOddFrame;
    return isOddFrame;
}

unsigned char SerialConnection::getControlByte() const
{
    return CONTROL_BYTE[isOddFrame];
}