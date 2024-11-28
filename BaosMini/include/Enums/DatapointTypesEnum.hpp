#ifndef DATAPOINT_TYPES_ENUM_HPP
#define DATAPOINT_TYPES_ENUM_HPP

enum DATAPOINT_TYPES
{
	// Datapoint Type (DPT)     // DPT Code, DPT Size

	NO_DATAPOINT_TYPE	= 0x00, // ONLY FOR INTERNAL USAGE
	Boolean				= 0x01, // DPT 1,	1 Bit		RELEVANT
	//Control			= 0x02, // DPT 2,	2 Bits
	//Dimming_Blinds	= 0x03, // DPT 3,	4 Bits
	//CharacterSet		= 0x04, // DPT 4,	8 Bits
	UnsignedValue1Byte	= 0x05, // DPT 5,	8 Bits		RELEVANT
	SignedValue1Byte	= 0x06, // DPT 6,	8 Bits		RELEVANT
	UnsignedValue2Byte	= 0x07, // DPT 7,	2 Bytes		RELEVANT
	SignedValue2Byte	= 0x08, // DPT 8,	2 Bytes		RELEVANT
	FloatValue2Byte		= 0x09, // DPT 9,	2 Bytes		RELEVANT
	//Time				= 0x0A, // DPT 10,	3 Bytes
	//Date				= 0x0B, // DPT 11,	3 Bytes
	UnsignedValue4Byte	= 0x0C, // DPT 12,	4 Bytes		RELEVANT
	SignedValue4Byte	= 0x0D, // DPT 13,	4 Bytes		RELEVANT
	FloatValue4Byte		= 0x0E, // DPT 14,	4 Bytes		RELEVANT
	//Access			= 0x0F, // DPT 15,	4 Bytes
	//String			= 0x10, // DPT 16,	14 Bytes
	//SceneNumber		= 0x11, // DPT 17,	1 Byte
	//SceneControl		= 0x12, // DPT 18,	1 Byte
	//DateTime			= 0x13, // DPT 19,	8 Bytes
	//HVACMode			= 0x14, // DPT 20,	1 Byte
	//ColorRGB			= 0xE8, // DPT 232, 3 Bytes
	//ColorRGBW			= 0xFB  // DPT 251, 6 Bytes
};

#endif // DATAPOINT_TYPES_ENUM_HPP

