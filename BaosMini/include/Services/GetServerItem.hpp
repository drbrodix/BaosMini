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
	GetServerItem(SerialConnection* serialConnection);

	/// <summary>
	/// The default destructor calls the parent function,
	/// which frees up the dynamically allocated
	/// memory of the baosTelegram and responseTelegram arrays.
	/// </summary>
	~GetServerItem();

	/// <summary>
	/// Requests the server items specified in the parameters,
	/// prints the retrieved data in a formatted way in the
	/// terminal if the recieved telegram contains no error code,
	/// and returns true. Decodes and prints the recieved error code
	/// in the terminal, and returns false otherwise.
	/// </summary>
	bool printServerItems(SERVER_ITEMS firstItemId, unsigned short nrOfItems);

	/// <summary>
	/// Retrieves and returns the hardware type of the
	/// connected BAOS device, if result of error check
	/// is positive. Returns 0 otherwise.
	/// </summary>
	BaosHardwareType getHardwareType();

	/// <summary>
	/// Retrieves and returns the hardware version of the
	/// connected BAOS device, if result of error check
	/// is positive. Returns 0 otherwise.
	/// </summary>
	BaosVersion getHardwareVersion();

	/// <summary>
	/// Retrieves and returns the firmware version of the
	/// connected BAOS device, if result of error check
	/// is positive. Returns 0 otherwise.
	/// </summary>
	BaosVersion getFirmwareVersion();

	/// <summary>
	/// Retrieves and returns the KNX manufacturer code
	/// of the connected BAOS device, if result of
	/// error check is positive. Returns 0 otherwise.
	/// </summary>
	unsigned short getKnxDeviceManufacturerCode();

	/// <summary>
	/// Retrieves and returns the KNX manufacturer
	/// code loaded by ETS, if result of error check 
	/// is positive. Returns 0 otherwise.
	/// </summary>
	unsigned short getKnxAppManufacturerCode();

	/// <summary>
	/// Retrieves and returns the ID of the application
	/// loaded by ETS, if result of error check 
	/// is positive. Returns 0 otherwise.
	/// </summary>
	unsigned short getApplicationId();

	/// <summary>
	/// Retrieves and returns the version of the
	/// application loaded by ETS, if result of
	/// error check is positive. Returns 0 otherwise.
	/// </summary>
	BaosVersion getApplicationVersion();

	/// <summary>
	/// Retrieves and returns the serial number of the
	/// connected BAOS device, if result of error check 
	/// is positive. Returns 0 otherwise.
	/// </summary>
	BaosSerialNumber getSerialNumber();

	/// <summary>
	/// Retrieves and returns the time passed since the
	/// last time the connected BAOS device was reset, 
	/// if result of error check is positive.
	/// Returns 0 otherwise.
	/// </summary>
	BaosTime getTimeSinceReset();

	/// <summary>
	/// Retrieves and returns bus connection state
	/// of the connected BAOS device, if result of
	/// error check is positive. Returns 0 otherwise.
	/// </summary>
	bool getBusConnectionState();

	/// <summary>
	/// Retrieves and returns maximum buffer size
	/// of the connected BAOS device, if result of
	/// error check is positive. Returns 0 otherwise.
	/// </summary>
	unsigned short getMaxBufferSize();

	/// <summary>
	/// Retrieves and returns length of description
	/// string of the connected BAOS device, if result
	/// of error check is positive. Returns 0 otherwise.
	/// </summary>
	unsigned short getLengthOfDescString();

	/// <summary>
	/// Retrieves and returns baudrate of the connected
	/// BAOS device, if result of error check is positive.
	/// Returns 0 otherwise.
	/// </summary>
	BAUDRATES getBaudrate();

	/// <summary>
	/// Retrieves and returns currently set buffer
	/// size of the connected BAOS device, if result of
	/// error check is positive. Returns 0 otherwise.
	/// </summary>
	unsigned short getCurrentBufferSize();

	/// <summary>
	/// Retrieves and returns current state of programming
	/// mode of the connected BAOS device, if result of
	/// error check is positive. Returns 0 otherwise.
	/// </summary>
	bool getProgrammingMode();

	/// <summary>
	/// Retrieves and returns the version of the
	/// ObjectServer binary protocol, if result of
	/// error check is positive. Returns 0 otherwise.
	/// </summary>
	BaosVersion getProtocolVersionBinary();

	/// <summary>
	/// Retrieves and returns current state of indication
	/// sending of the connected BAOS device, if result of
	/// error check is positive. Returns 0 otherwise.
	/// </summary>
	bool getIndicationSending();

	/// <summary>
	/// Retrieves and returns the version of the
	/// ObjectServer protocol via web services, if result
	/// of error check is positive. Returns 0 otherwise.
	/// </summary>
	BaosVersion getProtocolVersionWeb();

	/// <summary>
	/// Retrieves and returns the version of the
	/// ObjectServer protocol via rest services, if result
	/// of error check is positive. Returns 0 otherwise.
	/// </summary>
	BaosVersion getProtocolVersionRest();

	/// <summary>
	/// Retrieves and returns the individual KNX address
	/// of the connected BAOS device, if result of
	/// error check is positive. Returns 0 otherwise.
	/// </summary>
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
