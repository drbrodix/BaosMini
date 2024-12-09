#include "../../include/Services/GetServerItem.hpp"

GetServerItem::GetServerItem(
	SERVER_ITEMS firstItemId,
	unsigned short nrOfItems,
	SerialConnection* serialConnection)
	: BaosTelegram(serialConnection)
{
	*(baosTelegram + (BAOS_HEADER_FIRST_INDEX + 1)) = GetServerItemReq;

	*(unsigned short*)(baosTelegram + (BAOS_DATA_FIRST_INDEX)) = swap2((unsigned short)firstItemId);

	*(unsigned short*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 2)) = swap2(nrOfItems);

	telegramLength = 6;

	serialConnection->sendTelegram(baosTelegram, telegramLength);
	getAnswer();
	if (checkForError())
	{
		decodeServerItemRes(responseTelegram, responseLength);
	}
}

GetServerItem::~GetServerItem()
{
}

bool GetServerItem::checkForError()
{
	bool hasNoError = true;
	unsigned short nrOfItems = swap2(*((unsigned short*)(responseTelegram + NR_OF_DPS_OFFSET_FROM_MAINSERVICE)));

	// Error route
	if (!nrOfItems)
	{
		getErrorDescription(*(responseTelegram + ERROR_CODE_OFFSET_FROM_MAINSERVICE));
		hasNoError = false;
	}

	return hasNoError;
}