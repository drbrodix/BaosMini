#include "../../include/Services/SetDatapointValue.hpp"

SetDatapointValue::SetDatapointValue(
	unsigned short dpId,
	SerialConnection* serialConnection
)
	: BaosTelegram(serialConnection)
	, dpId(dpId)
{
	initTelegram();
}

SetDatapointValue::~SetDatapointValue()
{
}

inline void SetDatapointValue::initTelegram()
{
	*(baosTelegram + (BAOS_HEADER_FIRST_INDEX + 1))					= SetDatapointValueReq;
	*((unsigned short*)(baosTelegram + BAOS_DATA_FIRST_INDEX))		= swap2(dpId);
	*((unsigned short*)(baosTelegram + BAOS_DATA_FIRST_INDEX + 2))	= swap2(0x00'01);
	*((unsigned short*)(baosTelegram + BAOS_DATA_FIRST_INDEX + 4))	= swap2(dpId);
}

bool SetDatapointValue::decodeSetDatapointValueRes()
{
	const unsigned char ERROR_CODE = *(responseTelegram + ERROR_CODE_OFFSET_FROM_MAINSERVICE);

	if (!ERROR_CODE)
	{
		unsigned short datapointID = swap2(*(unsigned short*)(responseTelegram + 2));
		printf("Datapoint %hu has been successfully set\n", datapointID);
		return true;
	}
	// Error route
	else
	{
		getErrorDescription(ERROR_CODE);
		return false;
	}
}

template <typename T>
bool SetDatapointValue::setValue(T dpValue, DatapointTypes::DATAPOINT_TYPES dpt, CommandByte commandByte, bool decode)
{
	clearTelegram();
	const unsigned char dptSize = getDatapointSize(dpt);
	telegramLength = 10 + dptSize; // Member variable set to BAOS telegram length (header + data)
	
	*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 6)) = commandByte;	// 7rd byte set to command byte
	*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 7)) = dptSize;		// 8th byte set to datapoint value size
	*(T*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 8)) = dpValue;	// 9th and 10th byte set to actual value to set the datapoint to
	
	serialConnection->sendTelegram(baosTelegram, telegramLength);
	const bool serverResponse = getAnswer();
	if (decode)
	{
		decodeSetDatapointValueRes();
	}
	return serverResponse;
}

bool SetDatapointValue::setBoolean(bool dpValue, CommandByte commandByte, bool decode)
{
	return setValue<bool>(dpValue, DatapointTypes::BOOLEAN, commandByte, decode);
}

bool SetDatapointValue::setUnsignedValue1Byte(unsigned char dpValue, CommandByte commandByte, bool decode)
{
	return setValue<unsigned char>(dpValue, DatapointTypes::UNSIGNED_VALUE_1BYTE, commandByte, decode);
}

bool SetDatapointValue::setSignedValue1Byte(signed char dpValue, CommandByte commandByte, bool decode)
{
	return setValue<signed char>(dpValue, DatapointTypes::SIGNED_VALUE_1BYTE, commandByte, decode);
}

bool SetDatapointValue::setUnsignedValue2Byte(unsigned short dpValue, CommandByte commandByte, bool decode)
{
	return setValue<unsigned short>(swap2(dpValue), DatapointTypes::UNSIGNED_VALUE_2BYTE, commandByte, decode);
}

bool SetDatapointValue::setSignedValue2Byte(signed short dpValue, CommandByte commandByte, bool decode)
{
	return setValue<signed short>(swap2(dpValue), DatapointTypes::SIGNED_VALUE_2BYTE, commandByte, decode);
}

bool SetDatapointValue::setUnsignedValue4Byte(unsigned int dpValue, CommandByte commandByte, bool decode)
{
	return setValue<unsigned int>(swap4(dpValue), DatapointTypes::UNSIGNED_VALUE_4BYTE, commandByte, decode);
}

bool SetDatapointValue::setSignedValue4Byte(signed int dpValue, CommandByte commandByte, bool decode)
{
	return setValue<signed int>(swap4(dpValue), DatapointTypes::SIGNED_VALUE_4BYTE, commandByte, decode);
}

bool SetDatapointValue::setFloatValue2Byte(float dpValue, CommandByte commandByte, bool decode)
{
	unsigned char floatBytesArr[2] = { 0, 0 };
	float float2Byte = 0.0f;
	floatConverter::encode2byteFloat(dpValue, floatBytesArr);
	*((char*)&float2Byte)		= floatBytesArr[0];
	*((char*)&float2Byte + 1)	= floatBytesArr[1];

	return setValue<float>(float2Byte, DatapointTypes::FLOAT_VALUE_2BYTE, commandByte, decode);
}

bool SetDatapointValue::setFloatValue4Byte(float dpValue, CommandByte commandByte, bool decode)
{
	// Byte swapper macro doesn't work with floats,
	// hence we have to swap the bytes manually
	float floatValueSwapped = 0.0f;
	*((char*)&floatValueSwapped + 0) = *((char*)&dpValue + 3);
	*((char*)&floatValueSwapped + 1) = *((char*)&dpValue + 2);
	*((char*)&floatValueSwapped + 2) = *((char*)&dpValue + 1);
	*((char*)&floatValueSwapped + 3) = *((char*)&dpValue + 0);
	return setValue<float>(floatValueSwapped, DatapointTypes::FLOAT_VALUE_4BYTE, commandByte, decode);
}