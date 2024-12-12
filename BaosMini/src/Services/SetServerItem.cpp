#include "../../include/Services/SetServerItem.hpp"

SetServerItem::SetServerItem(
	SerialConnection* serialConnection)
	: BaosTelegram(serialConnection)
{
	*(baosTelegram + (BAOS_HEADER_FIRST_INDEX + 1)) = SetServerItemReq;

	// Number of items hard set to 1, since the concurrent
	// setting of multiple server items will not be supported
	*(unsigned short*)(baosTelegram + (NR_OF_ITEMS_OFFSET_FROM_MAINSERVICE)) = swap2((unsigned short)0x01);
	
}

SetServerItem::~SetServerItem()
{
}

// Set decode to "true" to print ObjectServer answer in terminal
void SetServerItem::setBaudrate(BAUDRATES baudrate, bool decode)
{
	*(unsigned short*)(baosTelegram + (START_ITEM_OFFSET_FROM_MAINSERVICE))		= swap2((unsigned short)SERVER_ITEMS::BAUDRATE);
	*(unsigned short*)(baosTelegram + (FIRST_ITEM_ID_OFFSET_FROM_MAINSERVICE))	= swap2((unsigned short)SERVER_ITEMS::BAUDRATE);
	*(baosTelegram + (FIRST_ITEM_LENGTH_OFFSET_FROM_MAINSERVICE))				= 0x01;
	*(baosTelegram + (FIRST_ITEM_DATA_OFFSET_FROM_MAINSERVICE))					= baudrate;
	telegramLength = 10;
	serialConnection->sendTelegram(baosTelegram, telegramLength);
	getAnswer();
	if (decode)
	{
		decodeSetServerItemRes();
	}
}

// Set decode to "true" to print ObjectServer answer in terminal
void SetServerItem::setCurrentBufferSize(unsigned short bufferSize, bool decode)
{
	*(unsigned short*)(baosTelegram + (START_ITEM_OFFSET_FROM_MAINSERVICE))			= swap2((unsigned short)SERVER_ITEMS::CURRENT_BUFFER_SIZE);
	*(unsigned short*)(baosTelegram + (FIRST_ITEM_ID_OFFSET_FROM_MAINSERVICE))		= swap2((unsigned short)SERVER_ITEMS::CURRENT_BUFFER_SIZE);
	*(baosTelegram + (FIRST_ITEM_LENGTH_OFFSET_FROM_MAINSERVICE))					= 0x02;
	*(unsigned short*)(baosTelegram + (FIRST_ITEM_DATA_OFFSET_FROM_MAINSERVICE))	= swap2(bufferSize);
	telegramLength = 11;
	serialConnection->sendTelegram(baosTelegram, telegramLength);
	getAnswer();
	if (decode)
	{
		decodeSetServerItemRes();
	}
}

void SetServerItem::setBool(bool enable, bool decode, SERVER_ITEMS serverItem)
{
	*(unsigned short*)(baosTelegram + (START_ITEM_OFFSET_FROM_MAINSERVICE)) = swap2((unsigned short)serverItem);
	*(unsigned short*)(baosTelegram + (FIRST_ITEM_ID_OFFSET_FROM_MAINSERVICE)) = swap2((unsigned short)serverItem);
	*(baosTelegram + (FIRST_ITEM_LENGTH_OFFSET_FROM_MAINSERVICE)) = 0x01;
	*(baosTelegram + (FIRST_ITEM_DATA_OFFSET_FROM_MAINSERVICE)) = enable;
	telegramLength = 10;
	serialConnection->sendTelegram(baosTelegram, telegramLength);
	getAnswer();
	if (decode)
	{
		decodeSetServerItemRes();
	}
}

// Set decode to "true" to print ObjectServer answer in terminal
void SetServerItem::setProgrammingMode(bool enable, bool decode)
{
	setBool(enable, decode, SERVER_ITEMS::PROGRAMMING_MODE);
}

// Set decode to "true" to print ObjectServer answer in terminal
void SetServerItem::setIndicationSending(bool enable, bool decode)
{
	setBool(enable, decode, SERVER_ITEMS::INDICATION_SENDING);
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