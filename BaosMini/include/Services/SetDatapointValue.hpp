#ifndef DATAPOINT_HPP
#define DATAPOINT_HPP

#include <cstring>
#include <cstdio>
#include "BaosTelegram.hpp"
#include "../Utility/FloatConverter.hpp"
#include "../Utility/DatapointTypes.hpp"

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

private:
	unsigned short dpId;
	
	bool setOneByteDp(unsigned char dpValue, CommandByte commandByte);
	bool setDpIdAndNr();
	bool clearTelegram();
};

#endif // DATAPOINT_HPP
