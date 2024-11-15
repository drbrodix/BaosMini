#include "telegram/GetServerItem.hpp"

GetServerItem::GetServerItem(
	int firstItemId,
	int nrOfItems)
{
	const unsigned char FIRST_ITEM_ID_BYTEONE = firstItemId / 256;
	const unsigned char FIRST_ITEM_ID_BYTETWO = firstItemId % 256;

	const unsigned char NR_OF_ITEMS_BYTEONE = nrOfItems / 256;
	const unsigned char NR_OF_ITEMS_BYTETWO = nrOfItems % 256;

	baosTelegram.push_back(BaosTelegram::BAOS_MAIN_SERVICE);
	baosTelegram.push_back(BaosSubServices::GetServerItemReq);
	baosTelegram.push_back(FIRST_ITEM_ID_BYTEONE);
	baosTelegram.push_back(FIRST_ITEM_ID_BYTETWO); // ID of first datapoint to set
	baosTelegram.push_back(NR_OF_ITEMS_BYTEONE);
	baosTelegram.push_back(NR_OF_ITEMS_BYTETWO); // Maximum number of datapoints to get
}

GetServerItem::~GetServerItem()
{
}