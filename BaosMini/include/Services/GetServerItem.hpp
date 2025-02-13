#ifndef GET_SERVER_ITEM_HPP
#define GET_SERVER_ITEM_HPP

/// <summary>
/// Index of the ID of the server item, whose value is to be fetched,
/// offset from the BAOS main service code in the baosTelegram array.
/// </summary>
#define  GET_SERVER_ITEM_SERVER_ITEM_ID_OFFSET BAOS_DATA_FIRST_INDEX

/// <summary>
/// Index of the number of server items to be fetched, offset
/// from the BAOS main service code in the baosTelegram array.
/// </summary>
#define GET_SERVER_ITEM_NR_OF_ITEMS_OFFSET (BAOS_DATA_FIRST_INDEX + 2)

/// <summary>
/// Index of the number of server items requested, offset from the BAOS
/// main service code in the ObjectsServer's response telegram array.
/// </summary>
#define GET_SERVER_ITEM_RES_NR_OF_ITEMS_OFFSET 4

/// <summary>
/// Index of the first byte of the data related to the
/// server item requested, offset from the BAOS main
/// service code in the ObjectsServer's response telegram array.
/// </summary>
#define GET_SERVER_ITEM_RES_SERVER_ITEM_DATA_OFFSET 9

#include "BaosTelegram.hpp"
#include "../Utility/DecodeServerItemRes.hpp"
#include "../Enums/ServerItemEnum.hpp"

/// <summary>
/// A bitfield structure to store the KNX-Address
/// of the device in a clear and efficient way.
/// </summary>
typedef struct
{
	unsigned char area		: 4;
	unsigned char line		: 4;
	unsigned char device	: 8;
} KnxDeviceAddress;

/// <summary>
/// An unsigned char structure allowing a clear
/// and easy way to store and access time data.
/// </summary>
typedef struct
{
	unsigned char hours;
	unsigned char minutes;
	unsigned char seconds;
} BaosTime;

/// <summary>
/// A bitfield structure to store version
/// numbers in a clear and efficient way.
/// </summary>
typedef struct
{
	unsigned char mainVersion	: 4;
	unsigned char minorVersion	: 4;
} BaosVersion;

/// <summary>
/// A 6 byte unsigned char structure,
/// used to store a BAOS hardware type.
/// </summary>
typedef struct
{
	unsigned char byte1;
	unsigned char byte2;
	unsigned char byte3;
	unsigned char byte4;
	unsigned char byte5;
	unsigned char byte6;
} BaosHardwareType;

/// <summary>
/// A 6 byte unsigned char structure,
/// used to store a BAOS serial number.
/// </summary>
typedef BaosHardwareType BaosSerialNumber;

/// <summary>
/// A BAOS service, allowing the retrieval of
/// various data about the connected BAOS device.
/// </summary>
class GetServerItem : public BaosTelegram
{
public:
	/// <summary>
	/// The constructor function calls the base class
	/// BaosTelegram constructor function, thus initializing
	/// the basic data members, and sets the BAOS subservice code.
	/// </summary>
	/// <param name="serialConnection">A pointer to the SerialConnection object.</param>
	GetServerItem(SerialConnection* serialConnection);

	/// <summary>
	/// The default destructor calls the parent function,
	/// which frees up the dynamically allocated
	/// memory of the baosTelegram and responseTelegram arrays.
	/// </summary>
	~GetServerItem();

	/// <summary>
	/// Requests the server items specified in the parameters,
	/// and prints the retrieved data in a formatted way in the
	/// standard output stream if the received telegram contains
	/// no error code. Decodes and prints the received error code
	/// in the standard output stream otherwise.
	/// </summary>
	/// <param name="firstItemId">ID of the first server item that should be fetched.</param>
	/// 
	/// <param name="nrOfItems">Number of the server items that should be fetched.</param>
	/// 
	/// <returns>Returns true if fetched telegram contains no error code, false otherwise.</returns>
	bool printServerItems(SERVER_ITEMS firstItemId, unsigned short nrOfItems);

	/// <summary>
	/// Retrieves the hardware type of the connected BAOS device.
	/// </summary>
	/// <returns>
	/// Returns the hardware type of the connected BAOS device, 
	/// if result of error check is positive. Returns 0 otherwise.
	/// </returns>
	BaosHardwareType getHardwareType();

	/// <summary>
	/// Retrieves the hardware version of the connected BAOS device.
	/// </summary>
	/// <returns>
	/// Returns the hardware version of the connected BAOS device, 
	/// if result of error check is positive. Returns 0 otherwise.
	/// </returns>
	BaosVersion getHardwareVersion();

	/// <summary>
	/// Retrieves the firmware version of the connected BAOS device.
	/// </summary>
	/// <returns>
	/// Returns the firmware version of the connected BAOS device, 
	/// if result of error check is positive. Returns 0 otherwise.
	/// </returns>
	BaosVersion getFirmwareVersion();

	/// <summary>
	/// Retrieves the KNX manufacturer code of the connected BAOS device.
	/// </summary>
	/// <returns>
	/// Returns the KNX manufacturer code of the connected BAOS device, 
	/// if result of error check is positive. Returns 0 otherwise.
	/// </returns>
	unsigned short getKnxDeviceManufacturerCode();

	/// <summary>
	/// Retrieves the KNX manufacturer code loaded by ETS.
	/// </summary>
	/// <returns>
	/// Returns the KNX manufacturer code loaded by ETS, 
	/// if result of error check is positive. Returns 0 otherwise.
	/// </returns>
	unsigned short getKnxAppManufacturerCode();

	/// <summary>
	/// Retrieves the ID of the application loaded by ETS.
	/// </summary>
	/// <returns>
	/// Returns the ID of the application loaded by ETS, 
	/// if result of error check is positive. Returns 0 otherwise.
	/// </returns>
	unsigned short getApplicationId();

	/// <summary>
	/// Retrieves the version of the application loaded by ETS.
	/// </summary>
	/// <returns>
	/// Returns the version of the application loaded by ETS, 
	/// if result of error check is positive. Returns 0 otherwise.
	/// </returns>
	BaosVersion getApplicationVersion();

	/// <summary>
	/// Retrieves the serial number of the connected BAOS device.
	/// </summary>
	/// <returns>
	/// Returns the serial number of the connected BAOS device, 
	/// if result of error check is positive. Returns 0 otherwise.
	/// </returns>
	BaosSerialNumber getSerialNumber();

	/// <summary>
	/// Retrieves the time passed since the last
	/// time the connected BAOS device was reset.
	/// </summary>
	/// <returns>
	/// Returns the time passed since the last time the connected BAOS device 
	/// was reset, if result of error check is positive. Returns 0 otherwise.
	/// </returns>
	BaosTime getTimeSinceReset();

	/// <summary>
	/// Retrieves the bus connection state of the connected BAOS device.
	/// </summary>
	/// <returns>
	/// Returns the bus connection state of the connected BAOS device,
	/// if result of error check is positive. Returns 0 otherwise.
	/// </returns>
	bool getBusConnectionState();

	/// <summary>
	/// Retrieves the maximum buffer size of the connected BAOS device.
	/// </summary>
	/// <returns>
	/// Returns the maximum buffer size of the connected BAOS device,
	/// if result of error check is positive. Returns 0 otherwise.
	/// </returns>
	unsigned short getMaxBufferSize();

	/// <summary>
	/// Retrieves the length of description string of the connected BAOS device.
	/// </summary>
	/// <returns>
	/// Returns the length of description string of the connected BAOS device,
	/// if result of error check is positive. Returns 0 otherwise.
	/// </returns>
	unsigned short getLengthOfDescString();

	/// <summary>
	/// Retrieves the baudrate of the connected BAOS device.
	/// </summary>
	/// <returns>
	/// Returns the baudrate of the connected BAOS device,
	/// if result of error check is positive. Returns 0 otherwise.
	/// </returns>
	BAUDRATES getBaudrate();

	/// <summary>
	/// Retrieves the currently set buffer size of the connected BAOS device.
	/// </summary>
	/// <returns>
	/// Returns the currently set buffer size of the connected BAOS device,
	/// if result of error check is positive. Returns 0 otherwise.
	/// </returns>
	unsigned short getCurrentBufferSize();

	/// <summary>
	/// Retrieves the current state of programming
	/// mode of the connected BAOS device.
	/// </summary>
	/// <returns>
	/// Returns the current state of programming mode of the connected
	/// BAOS device, if result of error check is positive. Returns 0 otherwise.
	/// </returns>
	bool getProgrammingMode();

	/// <summary>
	/// Retrieves the version of the ObjectServer binary protocol.
	/// </summary>
	/// <returns>
	/// Returns the version of the ObjectServer binary protocol,
	/// if result of error check is positive. Returns 0 otherwise.
	/// </returns>
	BaosVersion getProtocolVersionBinary();

	/// <summary>
	/// Retrieves the current state of indication
	/// sending of the connected BAOS device.
	/// </summary>
	/// <returns>
	/// Returns the current state of indication sending of the connected
	/// BAOS device, if result of error check is positive. Returns 0 otherwise.
	/// </returns>
	bool getIndicationSending();

	/// <summary>
	/// Retrieves the version of the ObjectServer protocol via web services.
	/// </summary>
	/// <returns>
	/// Returns the version of the ObjectServer protocol via web services,
	/// if result of error check is positive. Returns 0 otherwise.
	/// </returns>
	BaosVersion getProtocolVersionWeb();

	/// <summary>
	/// Retrieves the version of the ObjectServer protocol via rest services.
	/// </summary>
	/// <returns>
	/// Returns the version of the ObjectServer protocol via rest services,
	/// if result of error check is positive. Returns 0 otherwise.
	/// </returns>
	BaosVersion getProtocolVersionRest();

	/// <summary>
	/// Retrieves the individual KNX address of the connected BAOS device.
	/// </summary>
	/// <returns>
	/// Returns the individual KNX address of the connected BAOS device,
	/// if result of error check is positive. Returns 0 otherwise.
	/// </returns>
	KnxDeviceAddress getKnxIndividualAddress();

private:
	/// <summary>
	/// Checks if ObjectServer response is an error telegram. Returns false
	/// if an error code has been detected, which then will be decoded and
	/// a respective error message printed in the terminal.
	/// Returns true if the ObjectServer response contains no error code.
	/// </summary>
	bool checkForError();

	/// <summary>
	/// This function is used to retrieve a server item from the
	/// ObjectServer. It sets up and sends the telegram to the ObjectServer
	/// with the passed parameters, then retrieves and stores the answer.
	/// An error check will be done, and the result stored for further use.
	/// Depending on the state of the decode flag, data about the fetched
	/// server items will be printed in the terminal.
	/// </summary>
	bool getItem(SERVER_ITEMS firstItemId, unsigned short nrOfItems = 1, bool decode = false);

	/// <summary>
	/// A helper function used to retrieve and return a 1 byte
	/// server item. Will be called by some public functions.
	/// </summary>
	inline unsigned char get1ByteItem(SERVER_ITEMS serverItem);
	
	/// <summary>
	/// A helper function used to retrieve and return a 2 byte
	/// server item. Will be called by some public functions.
	/// </summary>
	inline unsigned short get2ByteItem(SERVER_ITEMS serverItem);

	/// <summary>
	/// A helper function used to retrieve and return a 6 byte
	/// server item. Will be called by some public functions.
	/// </summary>
	template<typename T> T get6BByteItem(SERVER_ITEMS serverItem);

	/// <summary>
	/// A helper function used to retrieve, format, and return a
	/// version server item. Will be called by some public functions.
	/// </summary>
	inline BaosVersion getVersionItem(SERVER_ITEMS serverItem);
};

#endif // GET_SERVER_ITEM_HPP
