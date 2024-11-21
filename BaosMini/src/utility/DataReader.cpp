#include "utility/DataReader.hpp"

namespace DataReader
{
    // Recieve Telegram
    // I know it's terrible... I'm just an intern, don't judge me...
    size_t DataReader::recieveTelegram(HANDLE serialHandle, unsigned char* telegramCharArray)
    {
        const unsigned short MAX_TRIES_COUNT    = 100;      // Caps number of tries looking for FT1.2 start byte
        unsigned int readTries                  = 0;        // Keeps count of number of tries looking for FT1.2 start byte
        unsigned int telegramLength             = 0;        // Variable to save BAOS telegram length after reading FT1.2 header
        const unsigned short HEADER_SIZE        = 5;        // Fixed size of FT1.2 header; unless the protocol changes, this constant shouldn't be touched
        unsigned char ft12Header[HEADER_SIZE]   = { 0 };    // { (0) 0x68 , (1) Length, (2) Length, (3) 0x68, (4) ControlByte }

        while (MAX_TRIES_COUNT >= readTries)
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
            )) {
                return 0;
            }
            ++readTries;
            if (c == 0x68)  // If reader recognizes FT1.2 Start Byte,
                            // it should read the rest of the fixed sized header
            {
                for (int i = 1; i < HEADER_SIZE; i++)   // Loop start index at 1, because
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
                telegramLength = ft12Header[1] - 1;
                ft12Header[0] = c; // Index 0 of FT1.2 header set to start byte 0x68

                for (int i = 0; i < telegramLength; i++) // Now read the actual BAOS telegram

                {
                    DWORD telegramBytesRead = 0;
                    if (!ReadFile(
                        serialHandle,
                        telegramCharArray + i,
                        1,
                        &telegramBytesRead,
                        nullptr
                    )) {
                        return 0;
                    }
                }
                unsigned char endByte = 0;

                // Reading FT1.2 end byte
                DWORD endByteRead = 0;
                if (!ReadFile(
                    serialHandle,
                    &endByte,
                    sizeof(endByte),
                    &endByteRead,
                    nullptr
                )) {
                    return 0;
                }
            }
            if (telegramLength > 0)
            {
                return telegramLength;
            }
        }
        return 0;
    }
}