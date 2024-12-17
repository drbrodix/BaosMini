#include "../../include/Services/SetServerItem.hpp"

SetServerItem::SetServerItem(
	SerialConnection* serialConnection)
	: BaosTelegram(serialConnection)
{
	*(baosTelegram + BAOS_SUBSERVICE_CODE_INDEX) = SetServerItemReq;
}

SetServerItem::~SetServerItem()
{
}

bool SetServerItem::checkForError()
{
	bool hasNoError = true;
	const unsigned char ERROR_CODE = *(responseTelegram + ERROR_CODE_OFFSET);

	// Error route
	if (ERROR_CODE)
	{
		getErrorDescription(ERROR_CODE);
		hasNoError = false;
	}

	return hasNoError;
}

template <typename T>
bool SetServerItem::setValue(T itemValue, SERVER_ITEMS serverItem, unsigned char itemLength, bool decode)
{
	clearTelegram();
	*(unsigned short*)(baosTelegram + SET_SERVER_ITEM_START_ITEM_ID_OFFSET)	= swap2((unsigned short)serverItem);
	// Number of items hard set to 1, since the concurrent
	// setting of multiple server items will not be supported
	*(unsigned short*)(baosTelegram + SET_SERVER_ITEM_NR_OF_ITEMS_OFFSET)	= swap2((unsigned short)0x01);
	*(unsigned short*)(baosTelegram + SET_SERVER_ITEM_FIRST_ITEM_ID_OFFSET)	= swap2((unsigned short)serverItem);
	*(baosTelegram + SET_SERVER_ITEM_FIRST_ITEM_LENGTH_OFFSET)				= itemLength;
	*(T*)(baosTelegram + SET_SERVER_ITEM_FIRST_ITEM_DATA_OFFSET)			= itemValue;
	// Member variable set to BAOS telegram length (header + data).
	// It is calculated by adding the length of the fixed parts, and the 
	// dynamic length of the server items together, passed as a parameter.
	telegramLength = 9 + itemLength;

	serialConnection->sendTelegram(baosTelegram, telegramLength);
	getAnswer();
	hasValidResponse = checkForError();
	if (hasValidResponse && decode)
	{
		decodeSetServerItemRes();
	}
	return hasValidResponse;
}

bool SetServerItem::setBaudrate(BAUDRATES baudrate, bool decode)
{
	return setValue<unsigned char>(baudrate, BAUDRATE, 1, decode);
}

bool SetServerItem::setCurrentBufferSize(unsigned short bufferSize, bool decode)
{
	return setValue<unsigned short>(swap2(bufferSize), CURRENT_BUFFER_SIZE, 2, decode);
}

bool SetServerItem::setProgrammingMode(bool enable, bool decode)
{
	return setValue<unsigned char>(enable, PROGRAMMING_MODE, 1, decode);
}

bool SetServerItem::setIndicationSending(bool enable, bool decode)
{
	return setValue<unsigned char>(enable, INDICATION_SENDING, 1, decode);
}

void SetServerItem::decodeSetServerItemRes()
{
	unsigned short serverItemID = swap2(*(unsigned short*)(responseTelegram + SET_SERVER_ITEM_RES_ITEM_ID_OFFSET));

	switch ((SERVER_ITEMS)serverItemID)
	{
	case SERVER_ITEMS::BAUDRATE:
		printf("Baudrate has been successfully set\n");
		break;
	case SERVER_ITEMS::CURRENT_BUFFER_SIZE:
		printf("Current buffer size has been successfully set\n");
		break;
	case SERVER_ITEMS::PROGRAMMING_MODE:
		printf("Programming mode has been successfully set\n");
		break;
	case SERVER_ITEMS::INDICATION_SENDING:
		printf("Indication sending has been successfully set\n");
		break;
	default:
		printf("Unknown server item has been set\n");
		break;
	}
}