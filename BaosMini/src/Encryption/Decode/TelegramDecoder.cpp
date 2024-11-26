#include "../../../include/Encryption/Decode/TelegramDecoder.hpp"

bool Encryption::decodeTelegram(unsigned char* telegramCharArray, unsigned int telegramLength)
{
    /*
    GetServerItemRes = 0x81,
    SetServerItemRes = 0x82,
    GetDatapointDescriptionRes = 0x83,
    GetDescriptionStringRes = 0x84,
    GetDatapointValueRes = 0x85,
    SetDatapointValueRes = 0x86,
    GetParameterByteRes = 0x87,
    SetParameterByteRes = 0x88,
    DatapointValueind = 0xC1,
    ServerItemInd = 0xC2
    */

    switch (telegramCharArray[1])
    {
    case 0x81:
        if (decodeGetServerItemRes(telegramCharArray, telegramLength))
        {
			return true;
            break;
        }
        return false;
        break;
    case 0x82:
        if (decodeSetServerItemRes(telegramCharArray, telegramLength))
        {
            return true;
            break;
        }
        return false;
        break;
    case 0x83:
        if (decodeGetDatapointDescriptionRes(telegramCharArray, telegramLength))
        {
            return true;
            break;
        }
        return false;
        break;
    case 0x84:
        if (decodeGetDescriptionStringRes(telegramCharArray, telegramLength))
        {
            return true;
            break;
        }
        return false;
        break;
    case 0x85:
        if (decodeGetDatapointValueRes(telegramCharArray, telegramLength))
        {
            return true;
            break;
        }
        return false;
        break;
    case 0x86:
        if (decodeSetDatapointValueRes(telegramCharArray, telegramLength))
        {
            return true;
            break;
        }
        return false;
        break;
    case 0x87:
        if (decodeGetParameterByteRes(telegramCharArray, telegramLength))
        {
            return true;
            break;
        }
        return false;
        break;
    case 0x88:
        if (decodeSetParameterByteRes(telegramCharArray, telegramLength))
        {
            return true;
            break;
        }
        return false;
        break;
    default:
        return false;
        break;
    }
}