#ifndef DATAPOINT_TYPES_HPP
#define DATAPOINT_TYPES_HPP

namespace DatapointTypes
{
	enum DATAPOINT_TYPES
	{
		// Datapoint Type (DPT)			// DPT Code, DPT Size

		NO_DATAPOINT_TYPE		= 0x00, // ONLY FOR INTERNAL USAGE
		BOOLEAN					= 0x01, // DPT 1,	1 Bit
		//CONTROL				= 0x02, // DPT 2,	2 Bits
		//DIMMING_BLINDS		= 0x03, // DPT 3,	4 Bits
		//CHARACTERSET			= 0x04, // DPT 4,	8 Bits
		UNSIGNED_VALUE_1BYTE	= 0x05, // DPT 5,	8 Bits
		SIGNED_VALUE_1BYTE		= 0x06, // DPT 6,	8 Bits
		UNSIGNED_VALUE_2BYTE	= 0x07, // DPT 7,	2 Bytes
		SIGNED_VALUE_2BYTE		= 0x08, // DPT 8,	2 Bytes
		FLOAT_VALUE_2BYTE		= 0x09, // DPT 9,	2 Bytes
		//TIME					= 0x0A, // DPT 10,	3 Bytes
		//DATE					= 0x0B, // DPT 11,	3 Bytes
		UNSIGNED_VALUE_4BYTE	= 0x0C, // DPT 12,	4 Bytes
		SIGNED_VALUE_4BYTE		= 0x0D, // DPT 13,	4 Bytes
		FLOAT_VALUE_4BYTE		= 0x0E, // DPT 14,	4 Bytes
		//ACCESS				= 0x0F, // DPT 15,	4 Bytes
		//STRING				= 0x10, // DPT 16,	14 Bytes
		//SCENE_NUMBER			= 0x11, // DPT 17,	1 Byte
		//SCENE_CONTROL			= 0x12, // DPT 18,	1 Byte
		//DATE_TIME				= 0x13, // DPT 19,	8 Bytes
		//HVAC_MODE				= 0x14, // DPT 20,	1 Byte
		//COLOR_RGB				= 0xE8, // DPT 232, 3 Bytes
		//COLOR_RGBW			= 0xFB  // DPT 251, 6 Bytes
	};

	unsigned char getDatapointSize(DATAPOINT_TYPES dpt);
}

#endif // DATAPOINT_TYPES_HPP