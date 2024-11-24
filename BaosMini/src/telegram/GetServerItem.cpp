#include "../../include/telegram/GetServerItem.hpp"

GetServerItem::GetServerItem(
	unsigned short firstItemId,
	unsigned short nrOfItems)
	: BaosTelegram()
{
	unsigned char FIRST_ITEM_ID_BYTEONE = 0;
	unsigned char FIRST_ITEM_ID_BYTETWO = 0;

	unsigned char NR_OF_ITEMS_BYTEONE = 0;
	unsigned char NR_OF_ITEMS_BYTETWO = 0;

	FormatterFunctions::formatValueInTwoBytes(firstItemId, &FIRST_ITEM_ID_BYTEONE, &FIRST_ITEM_ID_BYTETWO);
	FormatterFunctions::formatValueInTwoBytes(nrOfItems, &NR_OF_ITEMS_BYTEONE, &NR_OF_ITEMS_BYTETWO);

	baosTelegram[1] = BaosSubServices::GetServerItemReq;
	baosTelegram[2] = FIRST_ITEM_ID_BYTEONE;
	baosTelegram[3] = FIRST_ITEM_ID_BYTETWO; // ID of first datapoint to set
	baosTelegram[4] = NR_OF_ITEMS_BYTEONE;
	baosTelegram[5] = NR_OF_ITEMS_BYTETWO; // Maximum number of datapoints to get

	telegramLength = 6;
}

GetServerItem::~GetServerItem()
{
}