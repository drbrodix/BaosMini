#include "../../include/Services/GetServerItem.hpp"

GetServerItem::GetServerItem(
	SerialConnection* serialConnection)
	: BaosTelegram(serialConnection)
{
	*(baosTelegram + (BAOS_HEADER_FIRST_INDEX + 1)) = GetServerItemReq;
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

inline void GetServerItem::clearTelegram()
{
	memset((baosTelegram + BAOS_DATA_FIRST_INDEX), 0, BAOS_BYTES_IN_ARR);
}

bool GetServerItem::printServerItems(SERVER_ITEMS firstItemId, unsigned short nrOfItems)
{
	clearTelegram();

	*(unsigned short*)(baosTelegram + (BAOS_DATA_FIRST_INDEX)) = swap2((unsigned short)firstItemId);

	*(unsigned short*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 2)) = swap2(nrOfItems);

	telegramLength = 6;

	serialConnection->sendTelegram(baosTelegram, telegramLength);
	getAnswer();
	if (checkForError())
	{
		decodeServerItemRes(responseTelegram, responseLength);
		return true;
	}
	return false;
}

bool GetServerItem::getSingleServerItem(SERVER_ITEMS firstItemId)
{
	clearTelegram();

	*(unsigned short*)(baosTelegram + (BAOS_DATA_FIRST_INDEX)) = swap2((unsigned short)firstItemId);

	*(unsigned short*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 2)) = swap2(0x00'01);

	telegramLength = 6;

	serialConnection->sendTelegram(baosTelegram, telegramLength);
	getAnswer();
	if (checkForError())
	{
		return true;
	}
	return false;
}

inline unsigned char GetServerItem::get1ByteItem(SERVER_ITEMS serverItem)
{
	getSingleServerItem(serverItem);
	return *(responseTelegram + SERVER_ITEM_DATA_OFFSET_FROM_MAIN_SERVICE);
}

inline unsigned short GetServerItem::get2ByteItem(SERVER_ITEMS serverItem)
{
	getSingleServerItem(serverItem);
	return swap2(*((unsigned short*)(responseTelegram + SERVER_ITEM_DATA_OFFSET_FROM_MAIN_SERVICE)));
}

inline BaosVersion GetServerItem::getVersionItem(SERVER_ITEMS serverItem)
{
	unsigned char versionByte = get1ByteItem(serverItem);
	BaosVersion baosVersion =
	{
		*(responseTelegram + SERVER_ITEM_DATA_OFFSET_FROM_MAIN_SERVICE) >> 4,
		*(responseTelegram + SERVER_ITEM_DATA_OFFSET_FROM_MAIN_SERVICE) & 0x0F
	};
	return baosVersion;
}

template<typename T>
T GetServerItem::get6BByteItem(SERVER_ITEMS serverItem)
{
	getSingleServerItem(serverItem);

	T baosHardwareType =
	{
		*(responseTelegram + SERVER_ITEM_DATA_OFFSET_FROM_MAIN_SERVICE),
		*(responseTelegram + SERVER_ITEM_DATA_OFFSET_FROM_MAIN_SERVICE + 1),
		*(responseTelegram + SERVER_ITEM_DATA_OFFSET_FROM_MAIN_SERVICE + 2),
		*(responseTelegram + SERVER_ITEM_DATA_OFFSET_FROM_MAIN_SERVICE + 3),
		*(responseTelegram + SERVER_ITEM_DATA_OFFSET_FROM_MAIN_SERVICE + 4),
		*(responseTelegram + SERVER_ITEM_DATA_OFFSET_FROM_MAIN_SERVICE + 5)
	};

	return baosHardwareType;
}

BaosHardwareType GetServerItem::getHardwareType()
{
	return get6BByteItem<BaosHardwareType>(HARDWARE_TYPE);
}

BaosVersion GetServerItem::getHardwareVersion()
{
	return getVersionItem(HARDWARE_VERSION);
}

BaosVersion GetServerItem::getFirmwareVersion()
{
	return getVersionItem(FIRMWARE_VERSION);
}

unsigned short GetServerItem::getKnxDeviceManufacturerCode()
{
	return get2ByteItem(KNX_MANUFACTURER_CODE_DEV);
}

unsigned short GetServerItem::getKnxAppManufacturerCode()
{
	return get2ByteItem(KNX_MANUFACTURER_CODE_APP);
}

unsigned short GetServerItem::getApplicationId()
{
	return get2ByteItem(APPLICATION_ID);
}

BaosVersion GetServerItem::getApplicationVersion()
{
	return getVersionItem(APPLICATION_VERSION);
}

BaosSerialNumber GetServerItem::getSerialNumber()
{
	return get6BByteItem<BaosSerialNumber>(SERIAL_NUMBER);
}