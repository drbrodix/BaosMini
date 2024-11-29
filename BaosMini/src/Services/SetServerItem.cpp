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

void SetServerItem::SetBaudrate(BAUDRATE baudrate)
{
	*(unsigned short*)(baosTelegram + (START_ITEM_OFFSET_FROM_MAINSERVICE))		= swap2((unsigned short)SERVER_ITEMS::BAUDRATE);
	*(unsigned short*)(baosTelegram + (FIRST_ITEM_ID_OFFSET_FROM_MAINSERVICE))	= swap2((unsigned short)SERVER_ITEMS::BAUDRATE);
	*(baosTelegram + (FIRST_ITEM_LENGTH_OFFSET_FROM_MAINSERVICE))				= 0x01;
	*(baosTelegram + (FIRST_ITEM_DATA_OFFSET_FROM_MAINSERVICE))					= baudrate;
	telegramLength = 10;
	serialConnection->sendTelegram(baosTelegram, telegramLength);
}

void SetServerItem::SetCurrentBufferSize(unsigned short bufferSize)
{
	*(unsigned short*)(baosTelegram + (START_ITEM_OFFSET_FROM_MAINSERVICE))			= swap2((unsigned short)SERVER_ITEMS::CURRENT_BUFFER_SIZE);
	*(unsigned short*)(baosTelegram + (FIRST_ITEM_ID_OFFSET_FROM_MAINSERVICE))		= swap2((unsigned short)SERVER_ITEMS::CURRENT_BUFFER_SIZE);
	*(baosTelegram + (FIRST_ITEM_LENGTH_OFFSET_FROM_MAINSERVICE))					= 0x02;
	*(unsigned short*)(baosTelegram + (FIRST_ITEM_DATA_OFFSET_FROM_MAINSERVICE))	= swap2(bufferSize);
	telegramLength = 11;
	serialConnection->sendTelegram(baosTelegram, telegramLength);
}

void SetServerItem::SetProgrammingMode(bool enable)
{
	*(unsigned short*)(baosTelegram + (START_ITEM_OFFSET_FROM_MAINSERVICE))		= swap2((unsigned short)SERVER_ITEMS::PROGRAMMING_MODE);
	*(unsigned short*)(baosTelegram + (FIRST_ITEM_ID_OFFSET_FROM_MAINSERVICE))	= swap2((unsigned short)SERVER_ITEMS::PROGRAMMING_MODE);
	*(baosTelegram + (FIRST_ITEM_LENGTH_OFFSET_FROM_MAINSERVICE))				= 0x01;
	*(baosTelegram + (FIRST_ITEM_DATA_OFFSET_FROM_MAINSERVICE))					= enable;
	telegramLength = 10;
	serialConnection->sendTelegram(baosTelegram, telegramLength);
}

void SetServerItem::SetIndicationSending(bool enable)
{
	*(unsigned short*)(baosTelegram + (START_ITEM_OFFSET_FROM_MAINSERVICE))		= swap2((unsigned short)SERVER_ITEMS::INDICATION_SENDING);
	*(unsigned short*)(baosTelegram + (FIRST_ITEM_ID_OFFSET_FROM_MAINSERVICE))	= swap2((unsigned short)SERVER_ITEMS::INDICATION_SENDING);
	*(baosTelegram + (FIRST_ITEM_LENGTH_OFFSET_FROM_MAINSERVICE))				= 0x01;
	*(baosTelegram + (FIRST_ITEM_DATA_OFFSET_FROM_MAINSERVICE))					= enable;
	telegramLength = 10;
	serialConnection->sendTelegram(baosTelegram, telegramLength);
}