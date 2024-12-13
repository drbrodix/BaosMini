#ifndef GET_SERVER_ITEM_HPP
#define GET_SERVER_ITEM_HPP

#ifndef NR_OF_ITEMS_OFFSET_FROM_MAINSERVICE
#define NR_OF_ITEMS_OFFSET_FROM_MAINSERVICE 4
#endif // !NR_OF_ITEMS_OFFSET_FROM_MAINSERVICE

#ifndef SERVER_ITEM_DATA_OFFSET_FROM_MAIN_SERVICE
#define SERVER_ITEM_DATA_OFFSET_FROM_MAIN_SERVICE 9
#endif // !SERVER_ITEM_DATA_OFFSET_FROM_MAIN_SERVICE

#include "BaosTelegram.hpp"
#include "../Utility/DecodeServerItemRes.hpp"
#include "../Enums/ServerItemEnum.hpp"

typedef struct
{
	unsigned char area		: 4;
	unsigned char line		: 4;
	unsigned char device	: 8;
} KnxDeviceAddress;

typedef struct
{
	unsigned char hours;
	unsigned char minutes;
	unsigned char seconds;
} BaosTime;

typedef struct
{
	unsigned char mainVersion	: 4;
	unsigned char minorVersion	: 4;
} BaosVersion;

typedef struct
{
	unsigned char byte1;
	unsigned char byte2;
	unsigned char byte3;
	unsigned char byte4;
	unsigned char byte5;
	unsigned char byte6;
} BaosHardwareType;

typedef BaosHardwareType BaosSerialNumber;

class GetServerItem : public BaosTelegram
{
public:
	GetServerItem(SerialConnection* serialConnection);
	~GetServerItem();
	bool printServerItems(SERVER_ITEMS firstItemId, unsigned short nrOfItems);
	BaosHardwareType getHardwareType();
	BaosVersion getHardwareVersion();
	BaosVersion getFirmwareVersion();
	unsigned short getKnxDeviceManufacturerCode();
	unsigned short getKnxAppManufacturerCode();
	unsigned short getApplicationId();
	BaosVersion getApplicationVersion();
	BaosSerialNumber getSerialNumber();
	BaosTime getTimeSinceReset();
	bool getBusConnectionState();
	unsigned short getMaxBufferSize();
	unsigned short getLengthOfDescString();
	BAUDRATES getBaudrate();
	unsigned short getCurrentBufferSize();
	bool getProgrammingMode();
	BaosVersion getProtocolVersionBinary();
	bool getIndicationSending();
	BaosVersion getProtocolVersionWeb();
	BaosVersion getProtocolVersionRest();
	KnxDeviceAddress getKnxIndividualAddress();

private:
	// Returns true if no errors have been encountered
	// while fetching datapoint value, false otherwise
	bool checkForError();
	bool getSingleServerItem(SERVER_ITEMS firstItemId);
	inline unsigned char get1ByteItem(SERVER_ITEMS serverItem);
	inline unsigned short get2ByteItem(SERVER_ITEMS serverItem);
	template<typename T> T get6BByteItem(SERVER_ITEMS serverItem);
	inline BaosVersion getVersionItem(SERVER_ITEMS serverItem);
};

#endif // GET_SERVER_ITEM_HPP
