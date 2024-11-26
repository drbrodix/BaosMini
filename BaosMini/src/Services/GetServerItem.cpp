#include "../../include/Services/GetServerItem.hpp"

GetServerItem::GetServerItem(
	unsigned short firstItemId,
	unsigned short nrOfItems,
	SerialConnection* serialConnection)
	: BaosTelegram(serialConnection)
{
	*(baosTelegram + (BAOS_HEADER_FIRST_INDEX + 1)) = BaosSubServices::GetServerItemReq;

	*(unsigned short*)(baosTelegram + (BAOS_DATA_FIRST_INDEX)) = swap2(firstItemId);

	*(unsigned short*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 2)) = swap2(nrOfItems);

	telegramLength = 6;

	serialConnection->sendTelegram(baosTelegram, telegramLength);
}

GetServerItem::~GetServerItem()
{
}