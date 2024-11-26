#ifndef DATAPOINT_HPP
#define DATAPOINT_HPP

#include <cstring>
#include <cstdio>
#include "BaosTelegram.hpp"
#include "Utility/FloatConverter.hpp"

enum DatapointTypes
{
	// Datapoint Type (DPT)     // DPT Code, DPT Size

	Boolean             = 0x01, // DPT 1, 1 Bits        RELEVANT
	Control             = 0x02, // DPT 2, 2 Bits
	Dimming_Blinds      = 0x03, // DPT 3, 4 Bits
	CharacterSet        = 0x04, // DPT 4, 8 Bits
	UnsignedValue1Byte  = 0x05, // DPT 5, 8 Bits        RELEVANT
	SignedValue1Byte    = 0x06, // DPT 6, 8 Bits        RELEVANT
	UnsignedValue2Byte  = 0x07, // DPT 7, 2 Bytes       RELEVANT
	SignedValue2Byte    = 0x08, // DPT 8, 2 Bytes       RELEVANT
	FloatValue2Byte     = 0x09, // DPT 9, 2 Bytes       RELEVANT
	Time                = 0x0A, // DPT 10, 3 Bytes
	Date                = 0x0B, // DPT 11, 3 Bytes
	UnsignedValue4Byte  = 0x0C, // DPT 12, 4 Bytes      RELEVANT
	SignedValue4Byte    = 0x0D, // DPT 13, 4 Bytes      RELEVANT
	FloatValue4Byte     = 0x0E, // DPT 14, 4 Bytes      RELEVANT
	Access              = 0x0F, // DPT 15, 4 Bytes
	String              = 0x10, // DPT 16, 14 Bytes
	SceneNumber         = 0x11, // DPT 17, 1 Byte
	SceneControl        = 0x12, // DPT 18, 1 Byte
	DateTime            = 0x13, // DPT 19, 8 Bytes
	HVACMode            = 0x14, // DPT 20, 1 Byte
	ColorRGB            = 0xE8, // DPT 232, 3 Bytes
	ColorRGBW           = 0xFB  // DPT 251, 6 Bytes
};

enum CommandByte
{
	NoCommand                       = 0x00, // No Command
	SetNewValue                     = 0x01, // Set new value
	SendValueOnBus                  = 0x02, // Send value on bus
	SetNewValueAndSendOnBus         = 0x03, // Set new value and send on bus
	ReadNewValueViaBus              = 0x04, // Read new value via bus
	ClearDatapointTransmissionState = 0x05  // Clear datapoint transmission state
};

class Datapoint : BaosTelegram
{
public:
	Datapoint(
		unsigned short dpId,
		SerialConnection* serialConnection
	);
	~Datapoint();

	//                         Generic structure of BAOS Datapoint
	// 
	//          ID of DP          Command byte of DP    Length byte of DP         Value of DP
	// 
	//         0x00 0x00        |        0x00        |        0x00        |         0x00 ...

	// Functions to setup Datapoint
	bool setBoolean(bool dpValue, CommandByte commandByte);
	bool setUnsignedValue1Byte(unsigned char dpValue, CommandByte commandByte);
	bool setSignedValue1Byte(char dpValue, CommandByte commandByte);
	bool setUnsignedValue2Byte(unsigned short dpValue, CommandByte commandByte);
	bool setSignedValue2Byte(short dpValue, CommandByte commandByte);
	bool setFloatValue2Byte(float dpValue, CommandByte commandByte);
	bool setUnsignedValue4Byte(unsigned int dpValue, CommandByte commandByte);
	bool setSignedValue4Byte(int dpValue, CommandByte commandByte);
	bool setFloatValue4Byte(float dpValue, CommandByte commandByte);

	static unsigned char getDatapointSize(DatapointTypes dpt);

private:
	unsigned short dpId;
	
	bool setOneByteDp(unsigned char dpValue, CommandByte commandByte);
	bool setDpIdAndNr();
	bool clearTelegram();
};

#endif // DATAPOINT_HPP
