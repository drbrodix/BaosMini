#include "../../include/Utility/SerialConnection.hpp"

SerialConnection::SerialConnection(LPCWSTR connectString)
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
            printf("COM3 not found\n");
        }
        else
        {
            printf("Error opening serial port.\n");
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
        printf("Error while closing COM port.\n");
    }
}

HANDLE SerialConnection::createSerialHandle() const
{
	return CreateFile(
                        connectionName,
                        GENERIC_READ | GENERIC_WRITE,
                        0,
                        nullptr,
                        OPEN_EXISTING,
                        FILE_FLAG_OVERLAPPED,
                        nullptr
                     );
}

bool SerialConnection::configureConnect()
{
    dcbSerialParam.DCBlength = sizeof(dcbSerialParam);
    if (!GetCommState(serialHandle, &dcbSerialParam))
    {
        printf("Error while fetching COM properties.\n");
    }

    dcbSerialParam.BaudRate = CBR_19200;
    dcbSerialParam.ByteSize = 8;
    dcbSerialParam.StopBits = ONESTOPBIT;
    dcbSerialParam.Parity   = EVENPARITY;

    if (!SetCommState(serialHandle, &dcbSerialParam))
    {
        printf("Error while setting serial port properties.\n");
    }
    
    return true;
}

bool SerialConnection::configureTimeout()
{
    timeout.ReadIntervalTimeout         = MAXDWORD; // specifies the time that must pass between receiving characters before timing out (in milliseconds).
    timeout.ReadTotalTimeoutConstant    = 50;       // provides the amount of time to wait before returning (in milliseconds).
    timeout.ReadTotalTimeoutMultiplier  = MAXDWORD; // specifies the length of time to wait before responding for each byte requested in the read operation (in milliseconds).
    timeout.WriteTotalTimeoutConstant   = 0;        // same as in case of reading, but for writing
    timeout.WriteTotalTimeoutMultiplier = 0;        // same as in case of reading, but for writing

    if (!SetCommTimeouts(serialHandle, &timeout))
    {
        fprintf(stderr, "Error while setting timeout properties.\n");
    }
    return true;
}

unsigned char SerialConnection::getControlByte()
{
    return CONTROL_BYTE[isOddFrame];
}

bool SerialConnection::switchControlByteState()
{
    isOddFrame = !isOddFrame;
    return isOddFrame;
}

bool SerialConnection::writeToSerial(LPCVOID buffToWrite, DWORD nrOfBytesToWrite) const
{
    OVERLAPPED osWrite = { 0 };
    osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

    if (osWrite.hEvent == NULL)
    {
        fprintf(stderr, "Error creating overlapped event for write\n");
        CloseHandle(serialHandle);
        return 0;
    }

    // Write data
    DWORD dwBytesWritten = 0;
    if (!WriteFile(
                    serialHandle,
                    buffToWrite,
                    nrOfBytesToWrite,
                    &dwBytesWritten,
                    &osWrite
                  ))
    {
        if (GetLastError() == ERROR_IO_PENDING)
        {
            // The operation is in progress; wait for it to complete.
            if (WaitForSingleObject(osWrite.hEvent, INFINITE) == WAIT_OBJECT_0)
            {
                if (!GetOverlappedResult(serialHandle, &osWrite, &dwBytesWritten, FALSE))
                {
                    fprintf(stderr, "Error in GetOverlappedResult for write\n");
                }
            }
            else
            {
                fprintf(stderr, "Error waiting for write completion\n");
            }
        }
        else
        {
            fprintf(stderr, "Error writing to serial port\n");
        }
    }
    CloseHandle(osWrite.hEvent);
    return true;
}

bool SerialConnection::sendTelegram(unsigned char* baosTelegram, DWORD telegramLength, DatapointTypes::DATAPOINT_TYPES dpt)
{
    // Initialize some variables for readability
    const unsigned char controlByte = getControlByte();
    const unsigned char checksum = ChecksumCalculator::calculateChecksumSent(baosTelegram, telegramLength, controlByte);

    // Format the final FT1.2 frame
    unsigned short nrOfBytesToWrite = formatFt12Frame(
                                                      baosTelegram,
                                                      telegramLength,
                                                      controlByte,
                                                      checksum
                                                     );
    
    return writeToSerial(baosTelegram, nrOfBytesToWrite);
}

bool SerialConnection::sendAck() const
{
    const unsigned char ACK_BYTE[1] = { BAOS_ACK_BYTE };

    return writeToSerial(ACK_BYTE, sizeof(ACK_BYTE));
}

bool SerialConnection::sendResetRequest() const
{
    const unsigned char RESET_REQUEST[] = { 0x10, 0x40, 0x40, 0x16 };

    return writeToSerial(RESET_REQUEST, sizeof(RESET_REQUEST));
}

STATES SerialConnection::readFrame(unsigned char* pBuff, const DWORD bytesRead, unsigned char* destBuff, ReaderInfo* ri)
{
    // typedef enum {
    //     SEARCHING_START_BYTE        = 0,
    //     CHECKING_FIRST_LENGTH       = 1,
    //     CHECKING_SECOND_LENGTH      = 2,
    //     CHECKING_SECOND_START_BYTE  = 3,
    //     CHECKING_CONTROL_BYTE       = 4,
    //     CHECKING_BAOS_PAYLOAD       = 5,
    //     CHECKING_CHECKSUM           = 6,
    //     CHECKING_END_BYTE           = 7,
    // } STATES;
    //
    // typedef struct {
    //     STATES currentState;
    //     DWORD currentInputIndex;
    //     DWORD currentOutputIndex;
    //     unsigned char payloadLength;
    //     int checksumSum;
    //     bool doStartBytesMatch;
    //     bool doLengthBytesMatch;
    //     bool doesChecksumMatch;
    //     bool isEndByteFound;
    // } ReaderInfo;

    while (ri->currentInputIndex < bytesRead)
    {
        switch (ri->currentState)
        {
            case SEARCHING_START_BYTE:
                while (ri->currentInputIndex < bytesRead) {
                    if (pBuff[ri->currentInputIndex] == FT12_START_BYTE) {
                        destBuff[ri->currentOutputIndex] = pBuff[ri->currentInputIndex];
                        ri->currentState = CHECKING_FIRST_LENGTH;
                        ri->currentInputIndex++;
                        ri->currentOutputIndex++;
                        break;
                    }
                    ri->currentInputIndex++;
                }
                break;

            case CHECKING_FIRST_LENGTH:
                destBuff[ri->currentOutputIndex] = pBuff[ri->currentInputIndex];
                ri->payloadLength = pBuff[ri->currentInputIndex];
                ri->currentState = CHECKING_SECOND_LENGTH;
                ri->currentInputIndex++;
                ri->currentOutputIndex++;
                break;

            case CHECKING_SECOND_LENGTH:
                destBuff[ri->currentOutputIndex] = pBuff[ri->currentInputIndex];
                ri->doLengthBytesMatch = destBuff[ri->currentOutputIndex] == destBuff[ri->currentOutputIndex - 1];
                ri->currentState = CHECKING_SECOND_START_BYTE;
                ri->currentInputIndex++;
                ri->currentOutputIndex++;
                break;

            case CHECKING_SECOND_START_BYTE:
                destBuff[ri->currentOutputIndex] = pBuff[ri->currentInputIndex];
                ri->doStartBytesMatch = destBuff[ri->currentOutputIndex] == destBuff[ri->currentOutputIndex - 3];
                ri->currentState = CHECKING_CONTROL_BYTE;
                ri->currentInputIndex++;
                ri->currentOutputIndex++;
                break;

            case CHECKING_CONTROL_BYTE:
                destBuff[ri->currentOutputIndex] = pBuff[ri->currentInputIndex];
                ri->checksumSum = destBuff[ri->currentOutputIndex];
                ri->currentState = CHECKING_BAOS_PAYLOAD;
                ri->currentInputIndex++;
                ri->currentOutputIndex++;
                break;

            case CHECKING_BAOS_PAYLOAD:
                // It must be checked, that we don't try to access empty elements in the array,
                // and it is also necessary to ensure that we only access the payload part of the frame.
                while ((ri->currentInputIndex < bytesRead) &&
                    (ri->currentOutputIndex <= GET_PAYLOAD_END_INDEX(ri->payloadLength))) {

                    destBuff[ri->currentOutputIndex] = pBuff[ri->currentInputIndex];
                    ri->checksumSum += destBuff[ri->currentOutputIndex];
                    ri->currentInputIndex++;
                    ri->currentOutputIndex++;
                }

                if (ri->currentOutputIndex > GET_PAYLOAD_END_INDEX(ri->payloadLength))
                    ri->currentState = CHECKING_CHECKSUM;
                break;

            case CHECKING_CHECKSUM:
                destBuff[ri->currentOutputIndex] = pBuff[ri->currentInputIndex];
                ri->doesChecksumMatch = (ri->checksumSum % 256) == destBuff[ri->currentOutputIndex];
                ri->currentState = CHECKING_END_BYTE;
                ri->currentInputIndex++;
                ri->currentOutputIndex++;
                break;

            case CHECKING_END_BYTE:
                destBuff[ri->currentOutputIndex] = pBuff[ri->currentInputIndex];
                ri->isEndByteFound = (destBuff[ri->currentOutputIndex] == FT12_END_BYTE);
                ri->currentState = RECEPTION_COMPLETE;
                ri->currentInputIndex++;
                ri->currentOutputIndex++;
                return ri->currentState;
                break;

            default:
                break;
        }
    }
    return ri->currentState;
}

DWORD SerialConnection::readBuffer(unsigned char* pBuff, const DWORD bytesRead, unsigned char* destBuff, ReaderInfo* ri)
{
    while (ri->currentInputIndex < bytesRead)
    {
        readFrame(pBuff, bytesRead, destBuff, ri);

        // If the frame has been completely read
        if (ri->currentState == RECEPTION_COMPLETE)
        {
            return ri->payloadLength;
            /*const DWORD currentInputIndex = ri->currentInputIndex;
            memset(destBuff, 0, FT12_ARRAY_LENGTH);
            memset(ri, 0, sizeof(*ri));
            ri->currentInputIndex = currentInputIndex;*/
        }
    }
    // Reset buffer and reader struct if buffer has been completely read
    memset(pBuff, 0, INPUT_ARRAY_LENGTH);
    ri->currentInputIndex = 0;
    return 0;
}

void SerialConnection::parseTelegram(unsigned char* ft12Buff, DWORD telegramLength, unsigned char* telegramCharArray)
{
    for (DWORD i = 0; i < telegramLength - 1; i++)
    {
        telegramCharArray[i] = ft12Buff[i + 5];
    }
}

bool SerialConnection::readAck() const
{
    unsigned char buff[1] = { 0 };
    DWORD bytesRead = 0;
    bool isAckFound = false;

    OVERLAPPED osRead = { 0 };
    osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (osRead.hEvent == NULL)
    {
        fprintf(stderr, "Error creating event for read\n");
        CloseHandle(serialHandle);
        return 0;
    }

    while (true)
    {
        // Initiate an asynchronous read.
        BOOL readResult = ReadFile(
                                    serialHandle,
                                    buff,
                                    1,
                                    &bytesRead,
                                    &osRead
                                  );
        // If the read routine doesn't complete immediately...
        if (!readResult)
        {
            // The reading is being completed asynchronously...
            if (GetLastError() == ERROR_IO_PENDING)
            {
                // Wait for the read routine to signal completion...
                // The I/O handle is configured to return as soon as
                // ANYTHING has been read into the buffer.
                // This means, the read function should normally
                // return with 1 byte in buffer.
                DWORD waitRes = WaitForSingleObject(osRead.hEvent, INFINITE);

                if (!GetOverlappedResult(serialHandle, &osRead, &bytesRead, FALSE))
                {
                    fprintf(stderr, "Error in GetOverlappedResult for read\n");
                    break;
                }
            }
            else
            {
                fprintf(stderr, "Error in ReadFile\n");
                break;
            }
        }

        // If actual data has been received
        if (bytesRead > 0)
        {
            isAckFound = buff[0] == BAOS_ACK_BYTE;
            break;
        }
        // Reset the event for the next read.
        ResetEvent(osRead.hEvent);
    }
    CloseHandle(osRead.hEvent);
    return isAckFound;
}

unsigned int SerialConnection::receiveTelegram(unsigned char* telegramCharArray, HANDLE inputThreadHandle)
{
    DWORD telegramLength = 0;
    DWORD bytesRead = 0;
    unsigned char buff[INPUT_ARRAY_LENGTH] = { 0 };
    unsigned char ft12Buff[FT12_ARRAY_LENGTH] = { 0 };

    OVERLAPPED osRead = { 0 };
    osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (osRead.hEvent == NULL)
    {
        fprintf(stderr, "Error creating event for read\n");
        CloseHandle(serialHandle);
        return 0;
    }

    // Structure containing relevant infos to reading through buffer.
    // Will be initialised with all 0's
    ReaderInfo ri = {SEARCHING_START_BYTE};

    while (true)
    {
        // This block will be used for the IndicationListener
        if (inputThreadHandle != nullptr)
        {
            // Check if the input thread is still active.
            if (WaitForSingleObject(inputThreadHandle, 0) == WAIT_OBJECT_0)
            {
                // Input thread ended, exit the loop.
                return -1;
            }
        }
        // Initiate an asynchronous read.
        BOOL readResult = ReadFile(
                                    serialHandle,
                                    buff,
                                    INPUT_ARRAY_LENGTH,
                                    &bytesRead,
                                    &osRead
                                  );
        // If the read routine doesn't complete immediately...
        if (!readResult)
        {
            // The reading is being completed asynchronously...
            if (GetLastError() == ERROR_IO_PENDING)
            {
                // Wait for the read routine to signal completion...
                // The I/O handle is configured to return as soon as
                // ANYTHING has been read into the buffer.
                // This means, the read function should normally
                // return with 1 byte in buffer.
                DWORD waitRes = WaitForSingleObject(osRead.hEvent, INFINITE);

                if (!GetOverlappedResult(serialHandle, &osRead, &bytesRead, FALSE))
                {
                    fprintf(stderr, "Error in GetOverlappedResult for read\n");
                    break;
                }
            }
            else
            {
                fprintf(stderr, "Error in ReadFile\n");
                break;
            }
        }

        // If actual data has been received
        if (bytesRead > 0)
        {
            telegramLength = readBuffer(buff, bytesRead, ft12Buff, &ri);

            // The telegram length will only be returned,
            // once "Reception Complete" state has been reached.
            // This occurs if a complete FT 1.2 frame,
            // including the end byte has been read.
            if (telegramLength > 0)
            {
                // Send acknowledgement as soon as a complete frame has been read!
                // Important so that the BAOS device shuts up.
                sendAck();

                if (!ri.doesChecksumMatch)
                    fprintf(stderr, "Checksum mismatch!\n");

                parseTelegram(ft12Buff, telegramLength, telegramCharArray);
                CloseHandle(osRead.hEvent);
                return telegramLength;
            }
        }
        // Reset the event for the next read.
        ResetEvent(osRead.hEvent);
    }
    CloseHandle(osRead.hEvent);
    return telegramLength;
}