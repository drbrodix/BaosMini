#include "../../Include/Utility/DecodeServerItemRes.hpp"

namespace
{
    inline void formatServerItemKNXAddress(unsigned char* pDataStartAddress)
    {
    
        printf("%hu.%hu.%hu \n",
            *(pDataStartAddress) >> 4,
            (*(pDataStartAddress) & 0x0F),
            *(pDataStartAddress + 1));
    }

    inline void formatServerItemIsEnabled(unsigned char* pDataStartAddress)
    {
        printf("%s\n", *pDataStartAddress ? "true" : "false");
    }

    inline void formatServerItemSize(unsigned char* pDataStartAddress)
    {
        printf("%hu Byte(s)\n", swap2(*(unsigned short*)pDataStartAddress));
    }

    inline void formatServerItemBaudrate(unsigned char* pDataStartAddress)
    {
        switch ((BAUDRATES)*pDataStartAddress)
        {
        case BAUDRATE_19200:
            printf("Baudrate: 19200 Baud \n");
            break;
        case BAUDRATE_115200:
            printf("Baudrate: 115200 Baud \n");
            break;
        default:
            printf("Baudrate: unknown \n");
            break;
        }
    }

    inline void formatServerItemHex(unsigned char* pDataStartAddress, unsigned char itemLength)
    {
        for (unsigned char i = 0; i < itemLength; i++)
        {
            printf("%02X ", *(pDataStartAddress + i));
        }
        printf("\n");
    }

    inline void formatServerItemVersion(unsigned char* pDataStartAddress)
    {
        printf("%hu.%hu \n",
            *(pDataStartAddress) >> 4,
            *(pDataStartAddress) & 0x0F);
    }

    inline void formatServerItemTime(unsigned char* pDataStartAddress, unsigned char itemLength)
    {
        unsigned int    timeMs  = swap4(*((int*)(pDataStartAddress)));
        unsigned char    timeSec = timeMs / 1000;
        unsigned char    timeHr  = timeSec / 3600;
        unsigned char    timeMin = (timeSec % 3600) / 60;
                        timeSec = timeSec % 60;
        printf("Time since reset: %dHr %dMin %dSec\n", timeHr, timeMin, timeSec);
    }

    // Decode server item according to passed
    // server item ID and return index of next item
    unsigned short decodeServerItem(unsigned char* telegramCharArray, unsigned short currentIndex, unsigned short itemId)
    {
        unsigned char itemLength = 0;
        unsigned char* pDataStartAddress = (telegramCharArray + currentIndex + SERVER_ITEM_OFFSET_FROM_ID);
        switch ((SERVER_ITEMS)itemId)
        {
        case HARDWARE_TYPE:
            itemLength = 6;
            printf("Hardware type: ");
            formatServerItemHex(pDataStartAddress, itemLength);
            return currentIndex + itemLength + SERVER_ITEM_OFFSET_FROM_ID;
            break;
        case HARDWARE_VERSION:
            itemLength = 1;
            printf("Hardware version: ");
            formatServerItemVersion(pDataStartAddress);
            return currentIndex + itemLength + SERVER_ITEM_OFFSET_FROM_ID;
            break;
        case FIRMWARE_VERSION:
            itemLength = 1;
            printf("Firmware version: ");
            formatServerItemVersion(pDataStartAddress);
            return currentIndex + itemLength + SERVER_ITEM_OFFSET_FROM_ID;
            break;
        case KNX_MANUFACTURER_CODE_DEV:
            itemLength = 2;
            printf("KNX manufacturer code of device: ");
            formatServerItemHex(pDataStartAddress, itemLength);
            return currentIndex + itemLength + SERVER_ITEM_OFFSET_FROM_ID;
            break;
        case KNX_MANUFACTURER_CODE_APP:
            itemLength = 2;
            printf("KNX manufacturer code loaded by ETS: ");
            formatServerItemHex(pDataStartAddress, itemLength);
            return currentIndex + itemLength + SERVER_ITEM_OFFSET_FROM_ID;
            break;
        case APPLICATION_ID:
            itemLength = 2;
            printf("ID of application loaded by ETS: ");
            formatServerItemHex(pDataStartAddress, itemLength);
            return currentIndex + itemLength + SERVER_ITEM_OFFSET_FROM_ID;
            break;
        case APPLICATION_VERSION:
            itemLength = 1;
            printf("Version of application loaded by ETS: ");
            formatServerItemVersion(pDataStartAddress);
            return currentIndex + itemLength + SERVER_ITEM_OFFSET_FROM_ID;
            break;
        case SERIAL_NUMBER:
            itemLength = 6;
            printf("Serial number of device: ");
            formatServerItemHex(pDataStartAddress, itemLength);
            return currentIndex + itemLength + SERVER_ITEM_OFFSET_FROM_ID;
            break;
        case TIME_SINCE_RESET:
            itemLength = 4;
            formatServerItemTime(pDataStartAddress, itemLength);
            return currentIndex + itemLength + SERVER_ITEM_OFFSET_FROM_ID;
            break;
        case BUS_CONNECTION_STATE:
            itemLength = 1;
            printf("Bus connection active: ");
            formatServerItemIsEnabled(pDataStartAddress);
            return currentIndex + itemLength + SERVER_ITEM_OFFSET_FROM_ID;
            break;
        case MAX_BUFFER_SIZE:
            itemLength = 2;
            printf("Max buffer size: ");
            formatServerItemSize(pDataStartAddress);
            return currentIndex + itemLength + SERVER_ITEM_OFFSET_FROM_ID;
            break;
        case LENGTH_OF_DESC_STRING:
            itemLength = 2;
            printf("Length of description string: ");
            formatServerItemSize(pDataStartAddress);
            return currentIndex + itemLength + SERVER_ITEM_OFFSET_FROM_ID;
            break;
        case BAUDRATE:
            itemLength = 1;
            formatServerItemBaudrate(pDataStartAddress);
            return currentIndex + itemLength + SERVER_ITEM_OFFSET_FROM_ID;
            break;
        case CURRENT_BUFFER_SIZE:
            itemLength = 2;
            printf("Current buffer size: ");
            formatServerItemSize(pDataStartAddress);
            return currentIndex + itemLength + SERVER_ITEM_OFFSET_FROM_ID;
            break;
        case PROGRAMMING_MODE:
            itemLength = 1;
            printf("Programming mode active: ");
            formatServerItemIsEnabled(pDataStartAddress);
            return currentIndex + itemLength + SERVER_ITEM_OFFSET_FROM_ID;
            break;
        case PROTOCOL_VERSION_BINARY:
            itemLength = 1;
            printf("Version of the ObjectServer binary protocol: ");
            formatServerItemVersion(pDataStartAddress);
            return currentIndex + itemLength + SERVER_ITEM_OFFSET_FROM_ID;
            break;
        case INDICATION_SENDING:
            itemLength = 1;
            printf("Indication sending active: ");
            formatServerItemIsEnabled(pDataStartAddress);
            return currentIndex + itemLength + SERVER_ITEM_OFFSET_FROM_ID;
            break;
        case INDIVIDUAL_ADDRESS:
            itemLength = 2;
            printf("Individual KNX address of the device: ");
            formatServerItemKNXAddress(pDataStartAddress);
            return currentIndex + itemLength + SERVER_ITEM_OFFSET_FROM_ID;
            break;
        case PROTOCOL_VERSION_WEB:
            itemLength = 1;
            printf("Version of the ObjectServer protocol via web services: ");
            formatServerItemVersion(pDataStartAddress);
            return currentIndex + itemLength + SERVER_ITEM_OFFSET_FROM_ID;
            break;
        case PROTOCOL_VERSION_REST:
            itemLength = 1;
            printf("Version of the ObjectServer protocol via rest services: ");
            formatServerItemVersion(pDataStartAddress);
            return currentIndex + itemLength + SERVER_ITEM_OFFSET_FROM_ID;
            break;
        default:
            return 0xff'ff; // Unknown server item ID
            break;
        }
    }
}

bool decodeServerItemRes(unsigned char* telegramCharArray, unsigned int telegramLength)
{
    unsigned short numberOfItems =  swap2(*((unsigned short*)(telegramCharArray + 4)));

    // Error route
    if (!numberOfItems)
    {
        getErrorDescription(*(telegramCharArray + ERROR_CODE_OFFSET)); // telegramCharArray[6] == Error code

        return false;
    }
    else
    {
        // ID of first server item starts at
        // index 6 in the response telegram
        unsigned short index = 6;

        while (index < telegramLength)
        {
            unsigned short itemId = swap2(*((unsigned short*)(telegramCharArray + index)));

            index = decodeServerItem(telegramCharArray, index, itemId);
        }

        return true;
    }
}