#include "../../../include/Encryption/Decode/TelegramDecoder.hpp"

bool Encryption::decodeTelegram(unsigned char* telegramCharArray, unsigned int telegramLength, DatapointTypes::DATAPOINT_TYPES dpt)
{
    switch ((SUBSERVICES)telegramCharArray[1])
    {
    case GetServerItemRes:
        if (decodeGetServerItemRes(telegramCharArray, telegramLength))
        {
			return true;
            break;
        }
        return false;
        break;
    case SetServerItemRes:
        if (decodeSetServerItemRes(telegramCharArray, telegramLength))
        {
            return true;
            break;
        }
        return false;
        break;
    case GetDatapointDescriptionRes:
        if (decodeGetDatapointDescriptionRes(telegramCharArray, telegramLength))
        {
            return true;
            break;
        }
        return false;
        break;
    case GetDescriptionStringRes:
        if (decodeGetDescriptionStringRes(telegramCharArray, telegramLength))
        {
            return true;
            break;
        }
        return false;
        break;
    case GetDatapointValueRes:
        if (decodeGetDatapointValueRes(telegramCharArray, telegramLength, dpt))
        {
            return true;
            break;
        }
        return false;
        break;
    case SetDatapointValueRes:
        if (decodeSetDatapointValueRes(telegramCharArray, telegramLength))
        {
            return true;
            break;
        }
        return false;
        break;
    case GetParameterByteRes:
        if (decodeGetParameterByteRes(telegramCharArray, telegramLength))
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