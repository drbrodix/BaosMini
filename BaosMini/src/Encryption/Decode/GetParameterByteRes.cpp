#include "../../../include/Encryption/Decode/GetParameterByteRes.hpp"

bool decodeGetParameterByteRes(unsigned char* telegramCharArray, unsigned int telegramLength)
{
    unsigned short numberOfBytes = swap2(*((unsigned short*)(telegramCharArray + NR_OF_BYTES_OFFSET_FROM_MAIN_SERVICE)));

    // Error route
    if (numberOfBytes == 0)
    {
        getErrorDescription(*(telegramCharArray + ERROR_CODE_OFFSET_FROM_MAIN_SERVICE));

        return false;
    }
    else
    {
        if (telegramLength != (numberOfBytes + 6) /* Number of bytes + service codes + start byte index + number of bytes field */)
        {
            printf("Telegram length incorrect\n");
            return false;
        }
        else
        {
            unsigned short byteIndex = swap2(*((unsigned short*)(telegramCharArray + START_BYTE_INDEX_OFFSET_FROM_MAIN_SERVICE)));
            for(unsigned char i = 0; i < numberOfBytes; i++)
            {
                printf("Parameter byte #%hu: %hhu\n",
                    byteIndex,
                    *(telegramCharArray + FIRST_BYTE_OFFSET_FROM_MAIN_SERVICE + i));
                ++byteIndex;
            }

            return true;
        }

    }
}