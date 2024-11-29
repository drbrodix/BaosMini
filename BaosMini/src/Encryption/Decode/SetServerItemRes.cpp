#include "../../../include/Encryption/Decode/SetServerItemRes.hpp"

bool decodeSetServerItemRes(unsigned char* telegramCharArray, unsigned int telegramLength)
{
    const unsigned char ERROR_CODE = telegramCharArray[6];

    if (ERROR_CODE == 0x00)
    {
        unsigned short serverItemID = swap2(*(unsigned short*)(telegramCharArray + 2));

        switch ((SERVER_ITEMS)serverItemID)
        {
        case SERVER_ITEMS::BAUDRATE:
            printf("Baudrate has been successfully set\n");
            return true;
            break;
        case SERVER_ITEMS::CURRENT_BUFFER_SIZE:
            printf("Current buffer size has been successfully set\n");
            return true;
            break;
        case SERVER_ITEMS::PROGRAMMING_MODE:
            printf("Programming mode has been successfully set\n");
            return true;
            break;
        case SERVER_ITEMS::INDICATION_SENDING:
            printf("Indication sending has been successfully set\n");
            return true;
            break;
        default:
            printf("Unknown server item has been set\n");
            return false;
            break;
        }
    }
    // Error route
    else
    {
        getErrorDescription(ERROR_CODE);

        return false;
    }
}