#include "../../include/Services/SetServerItem.hpp"

SetServerItem::SetServerItem(
	SerialConnection* serialConnection)
	: BaosTelegram(serialConnection)
{
	*(baosTelegram + (BAOS_HEADER_FIRST_INDEX + 1)) = SetServerItemReq;	
}

SetServerItem::~SetServerItem()
{
}

template <typename T>
bool SetServerItem::setValue(T itemValue, SERVER_ITEMS serverItem, unsigned char itemLength, bool decode)
{
	clearTelegram();
	// Number of items hard set to 1, since the concurrent
	// setting of multiple server items will not be supported
	*(unsigned short*)(baosTelegram + (NR_OF_ITEMS_OFFSET_FROM_MAINSERVICE))	= swap2((unsigned short)0x01);
	*(unsigned short*)(baosTelegram + (START_ITEM_OFFSET_FROM_MAINSERVICE))		= swap2((unsigned short)serverItem);
	*(unsigned short*)(baosTelegram + (FIRST_ITEM_ID_OFFSET_FROM_MAINSERVICE))	= swap2((unsigned short)serverItem);
	*(baosTelegram + (FIRST_ITEM_LENGTH_OFFSET_FROM_MAINSERVICE))				= itemLength;
	*(T*)(baosTelegram + (FIRST_ITEM_DATA_OFFSET_FROM_MAINSERVICE))				= itemValue;
	// Member variable set to BAOS telegram length (header + data)
	telegramLength = 9 + itemLength;

	serialConnection->sendTelegram(baosTelegram, telegramLength);
	const bool serverResponse = getAnswer();
	if (decode)
	{
		decodeSetServerItemRes();
	}
	return serverResponse;
}

// Set decode to "true" to print ObjectServer answer in terminal
bool SetServerItem::setBaudrate(BAUDRATES baudrate, bool decode)
{
	return setValue<unsigned char>(baudrate, BAUDRATE, 1, decode);
}

// Set decode to "true" to print ObjectServer answer in terminal
bool SetServerItem::setCurrentBufferSize(unsigned short bufferSize, bool decode)
{
	return setValue<unsigned short>(swap2(bufferSize), CURRENT_BUFFER_SIZE, 2, decode);
}

// Set decode to "true" to print ObjectServer answer in terminal
bool SetServerItem::setProgrammingMode(bool enable, bool decode)
{
	return setValue<unsigned char>(enable, PROGRAMMING_MODE, 1, decode);
}

// Set decode to "true" to print ObjectServer answer in terminal
bool SetServerItem::setIndicationSending(bool enable, bool decode)
{
	return setValue<unsigned char>(enable, INDICATION_SENDING, 1, decode);
}

bool SetServerItem::decodeSetServerItemRes()
{
	const unsigned char ERROR_CODE = *(responseTelegram + ERROR_CODE_OFFSET_FROM_MAINSERVICE);

	if (ERROR_CODE == 0x00)
	{
		unsigned short serverItemID = swap2(*(unsigned short*)(responseTelegram + 2));

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