
#ifndef SERVER_ITEM_ENUM_HPP
#define SERVER_ITEM_ENUM_HPP

enum SERVER_ITEMS
{
	HARDWARE_TYPE				= 1,
	HARDWARE_VERSION			= 2,
	FIRMWARE_VERSION			= 3,
	KNX_MANUFACTURER_CODE_DEV	= 4,
	KNX_MANUFACTURER_CODE_APP	= 5,
	APPLICATION_ID				= 6,
	APPLICATION_VERSION			= 7,
	SERIAL_NUMBER				= 8,
	TIME_SINCE_RESET			= 9,
	BUS_CONNECTION_STATE		= 10,
	MAX_BUFFER_SIZE				= 11,
	LENGTH_OF_DESC_STRING		= 12,
	BAUDRATE					= 13,
	CURRENT_BUFFER_SIZE			= 14,
	PROGRAMMING_MODE			= 15,
	PROTOCOL_VERSION_BINARY		= 16,
	INDICATION_SENDING			= 17,
	PROTOCOL_VERSION_WEB		= 18,
	PROTOCOL_VERSION_REST		= 19,
	INDIVIDUAL_ADDRESS			= 20
};

#endif // SERVER_ITEM_ENUM_HPP

