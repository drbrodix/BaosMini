#include "../../include/Services/GetServerItem.hpp"

GetServerItem::GetServerItem(
	SerialConnection* serialConnection)
	: BaosTelegram(serialConnection)
{
	*(baosTelegram + BAOS_SUBSERVICE_CODE_INDEX) = GetServerItemReq;
}

GetServerItem::~GetServerItem()
{
}

bool GetServerItem::checkForError()
{
	bool hasNoError = true;
	unsigned short nrOfItems = swap2(*((unsigned short*)(responseTelegram + GET_SERVER_ITEM_RES_NR_OF_ITEMS_OFFSET)));

	// Error route
	if (!nrOfItems)
	{
		getErrorDescription(*(responseTelegram + ERROR_CODE_OFFSET));
		hasNoError = false;
	}

	return hasNoError;
}

bool GetServerItem::getItem(SERVER_ITEMS firstItemId, unsigned short nrOfItems, bool decode)
{
	clearTelegram();

	*(unsigned short*)(baosTelegram + GET_SERVER_ITEM_SERVER_ITEM_ID_OFFSET)	= swap2((unsigned short)firstItemId);

	*(unsigned short*)(baosTelegram + GET_SERVER_ITEM_NR_OF_ITEMS_OFFSET)		= swap2(0x00'01);

	telegramLength = 6;

	serialConnection->sendTelegram(baosTelegram, telegramLength);

	//for (unsigned char i = 0; i < 4; i++)
	//{
	//	serialConnection->sendTelegram(baosTelegram, telegramLength);
	//	if (serialConnection->readAck())
	//		break;
	//}

	serialConnection->switchControlByteState();
	
	getAnswer();

	hasValidResponse = checkForError();

	if (hasValidResponse && decode)
	{
		decodeServerItemRes(responseTelegram, responseLength);
	}

	return hasValidResponse;
}

bool GetServerItem::printServerItems(SERVER_ITEMS firstItemId, unsigned short nrOfItems)
{
	return getItem(firstItemId, nrOfItems, true);
}

inline unsigned char GetServerItem::get1ByteItem(SERVER_ITEMS serverItem)
{
	if (getItem(serverItem))
	{
		return *(responseTelegram + GET_SERVER_ITEM_RES_SERVER_ITEM_DATA_OFFSET);
	}
	else
	{
		return 0;
	}
}

inline unsigned short GetServerItem::get2ByteItem(SERVER_ITEMS serverItem)
{
	if (getItem(serverItem))
	{
		return swap2(*((unsigned short*)(responseTelegram + GET_SERVER_ITEM_RES_SERVER_ITEM_DATA_OFFSET)));
	}
	else
	{
		return 0;
	}
}

template<typename T>
T GetServerItem::get6BByteItem(SERVER_ITEMS serverItem)
{
	T itemStruct = { 0 };
	if (getItem(serverItem))
	{
		itemStruct =
		{
			*(responseTelegram + GET_SERVER_ITEM_RES_SERVER_ITEM_DATA_OFFSET),
			*(responseTelegram + GET_SERVER_ITEM_RES_SERVER_ITEM_DATA_OFFSET + 1),
			*(responseTelegram + GET_SERVER_ITEM_RES_SERVER_ITEM_DATA_OFFSET + 2),
			*(responseTelegram + GET_SERVER_ITEM_RES_SERVER_ITEM_DATA_OFFSET + 3),
			*(responseTelegram + GET_SERVER_ITEM_RES_SERVER_ITEM_DATA_OFFSET + 4),
			*(responseTelegram + GET_SERVER_ITEM_RES_SERVER_ITEM_DATA_OFFSET + 5)
		};
	}
	return itemStruct;
}

inline BaosVersion GetServerItem::getVersionItem(SERVER_ITEMS serverItem)
{
	unsigned char versionByte = get1ByteItem(serverItem);
	BaosVersion baosVersion =
	{
		versionByte >> 4,
		versionByte & 0x0F
	};
	return baosVersion;
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

BaosTime GetServerItem::getTimeSinceReset()
{
	getItem(TIME_SINCE_RESET);

	unsigned int    timeMs = swap4(*((int*)(responseTelegram + GET_SERVER_ITEM_RES_SERVER_ITEM_DATA_OFFSET)));
	unsigned char    timeSec = timeMs / 1000;
	unsigned char    timeHr = timeSec / 3600;
	unsigned char    timeMin = (timeSec % 3600) / 60;
	timeSec = timeSec % 60;
	return BaosTime{ timeHr, timeMin, timeSec };
}

bool GetServerItem::getBusConnectionState()
{
	return get1ByteItem(BUS_CONNECTION_STATE);
}

unsigned short GetServerItem::getMaxBufferSize()
{
	return get2ByteItem(MAX_BUFFER_SIZE);
}

unsigned short GetServerItem::getLengthOfDescString()
{
	return get2ByteItem(LENGTH_OF_DESC_STRING);
}

BAUDRATES GetServerItem::getBaudrate()
{
	return (BAUDRATES)get1ByteItem(BAUDRATE);
}

unsigned short GetServerItem::getCurrentBufferSize()
{
	return get2ByteItem(CURRENT_BUFFER_SIZE);
}

bool GetServerItem::getProgrammingMode()
{
	return get1ByteItem(PROGRAMMING_MODE);
}

BaosVersion GetServerItem::getProtocolVersionBinary()
{
	return getVersionItem(PROTOCOL_VERSION_BINARY);
}

bool GetServerItem::getIndicationSending()
{
	return get1ByteItem(INDICATION_SENDING);
}

BaosVersion GetServerItem::getProtocolVersionWeb()
{
	return getVersionItem(PROTOCOL_VERSION_WEB);
}

BaosVersion GetServerItem::getProtocolVersionRest()
{
	return getVersionItem(PROTOCOL_VERSION_REST);
}

KnxDeviceAddress GetServerItem::getKnxIndividualAddress()
{
	// A = Area | L = Line | B = Bus Device
	// AAAA LLLL BBBB BBBB
	KnxDeviceAddress knxDeviceAddress = { 0 };
	if (getItem(INDIVIDUAL_ADDRESS))
	{
		knxDeviceAddress.area	= *(responseTelegram + GET_SERVER_ITEM_RES_SERVER_ITEM_DATA_OFFSET) >> 4;
		knxDeviceAddress.line	= *(responseTelegram + GET_SERVER_ITEM_RES_SERVER_ITEM_DATA_OFFSET) & 0x0F;
		knxDeviceAddress.device = *(responseTelegram + GET_SERVER_ITEM_RES_SERVER_ITEM_DATA_OFFSET + 1);
	}
	return knxDeviceAddress;
}