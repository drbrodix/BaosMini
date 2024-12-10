#ifndef GET_SERVER_ITEM_HPP
#define GET_SERVER_ITEM_HPP

#include "BaosTelegram.hpp"
#include "../Utility/DecodeServerItemRes.hpp"
#include "../Enums/ServerItemEnum.hpp"

typedef struct
{
	unsigned char mainVersion;
	unsigned char minorVersion;
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

private:
	// Returns true if no errors have been encountered
	// while fetching datapoint value, false otherwise
	bool checkForError();
	inline void clearTelegram();
	bool getSingleServerItem(SERVER_ITEMS firstItemId);
	inline unsigned char get1ByteItem(SERVER_ITEMS serverItem);
	inline unsigned short get2ByteItem(SERVER_ITEMS serverItem);
	template<typename T> T get6BByteItem(SERVER_ITEMS serverItem);
	inline BaosVersion getVersionItem(SERVER_ITEMS serverItem);
};

#endif // GET_SERVER_ITEM_HPP
