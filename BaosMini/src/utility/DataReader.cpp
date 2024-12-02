#include "../../include/utility/DataReader.hpp"

namespace
{
    // Return true if parameter char is found
    bool charFound(HANDLE serialHandle, unsigned char charToFind)
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
    unsigned int readHeader(HANDLE serialHandle, unsigned char *ft12Header)
    {
        unsigned char c = 0;
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

        ft12Header[0] = c; // Index 0 of FT1.2 header set to start byte 0x68

        if (ft12Header[0] != ft12Header[3])
        {
            return 0;
        }
        else
        {
            return ft12Header[1] - 1; // (Data length plus control byte) minus control byte;
        }
    }

    bool readData(HANDLE serialHandle, unsigned char* buffer)
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
}

// Recieve Telegram
// I know it's terrible... I'm just an intern, don't judge me...
unsigned int DataReader::recieveTelegram(HANDLE serialHandle, unsigned char* telegramCharArray)
{
    const unsigned short MAX_TRIES_COUNT        = 30;       // Caps number of tries looking for FT1.2 start byte
    unsigned int readTries                      = 0;        // Keeps count of number of tries looking for FT1.2 start byte
    unsigned int telegramLength                 = 0;        // Variable to save BAOS telegram length after reading FT1.2 header
    unsigned char ft12Header[FT12_HEADER_SIZE]  = { 0 };    // { (0) 0x68 , (1) Length, (2) Length, (3) 0x68, (4) ControlByte }
    unsigned char checksum                      = 0;
    unsigned char endByte                       = 0;

    while (!charFound(serialHandle, FT12_START_BYTE));

    telegramLength = readHeader(serialHandle, ft12Header);

    for (unsigned int i = 0; i < telegramLength; i++)
    {
        readData(serialHandle, telegramCharArray);
    }

    readData(serialHandle, &checksum);

    readData(serialHandle, &endByte);

    if (checksum !=
        ChecksumCalculator::calculateChecksumRecieved(telegramCharArray, telegramLength, ft12Header[4]))
    {
        printf("Checksum error\n");
        return 0;
    }

    return telegramLength;
}