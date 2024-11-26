#include "../../../include/Encryption/Decode/GetServerItemRes.hpp"

bool decodeGetServerItemRes(unsigned char* telegramCharArray, unsigned int telegramLength)
{
    unsigned short numberOfItems = 0;
    // Bytes are swapped to convert from big endian to little endian
    *((char*)&numberOfItems)        = telegramCharArray[5];
    *((char*)&numberOfItems + 1)    = telegramCharArray[4];

    // Error route
    if (numberOfItems == 0)
    {
        getErrorDescription(telegramCharArray[6]); // telegramCharArray[6] == Error code

        return false;
    }
    else
    {
        printf("Number of items: %hu\n", numberOfItems);
        return true;
    }
}