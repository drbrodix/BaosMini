#ifndef SET_DATAPOINT_VALUE_HPP
#define SET_DATAPOINT_VALUE_HPP

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

class SetDatapointValue : BaosTelegram
{
public:
	SetDatapointValue(
		unsigned short dpId,
		SerialConnection* serialConnection
	);
	~SetDatapointValue();

	//                         Generic structure of BAOS Datapoint
	// 
	//          ID of DP          Command byte of DP    Length byte of DP         Value of DP
	// 
	//         0x00 0x00        |        0x00        |        0x00        |         0x00 ...

	// Returns true if a response has been recieved
	// from the object server, false otherwise
	bool setBoolean(bool dpValue, CommandByte commandByte, bool decode = false);
	// Returns true if a response has been recieved
	// from the object server, false otherwise
	bool setUnsignedValue1Byte(unsigned char dpValue, CommandByte commandByte, bool decode = false);
	// Returns true if a response has been recieved
	// from the object server, false otherwise
	bool setSignedValue1Byte(signed char dpValue, CommandByte commandByte, bool decode = false);
	// Returns true if a response has been recieved
	// from the object server, false otherwise
	bool setUnsignedValue2Byte(unsigned short dpValue, CommandByte commandByte, bool decode = false);
	// Returns true if a response has been recieved
	// from the object server, false otherwise
	bool setSignedValue2Byte(signed short dpValue, CommandByte commandByte, bool decode = false);
	// Returns true if a response has been recieved
	// from the object server, false otherwise
	bool setFloatValue2Byte(float dpValue, CommandByte commandByte, bool decode = false);
	// Returns true if a response has been recieved
	// from the object server, false otherwise
	bool setUnsignedValue4Byte(unsigned int dpValue, CommandByte commandByte, bool decode = false);
	// Returns true if a response has been recieved
	// from the object server, false otherwise
	bool setSignedValue4Byte(signed int dpValue, CommandByte commandByte, bool decode = false);
	// Returns true if a response has been recieved
	// from the object server, false otherwise
	bool setFloatValue4Byte(float dpValue, CommandByte commandByte, bool decode = false);

private:
	unsigned short dpId;
	// Setup basic parts of telegram
	inline void initTelegram();
	// The ObjectServer's answer will be decoded,
	// and the result will be printed in the terminal
	bool decodeSetDatapointValueRes();
	// Returns true if a response has been recieved
	// from the object server, false otherwise
	template <typename T> bool setValue(T dpValue, DatapointTypes::DATAPOINT_TYPES dpt, CommandByte commandByte, bool decode);
};

#endif // SET_DATAPOINT_VALUE_HPP
