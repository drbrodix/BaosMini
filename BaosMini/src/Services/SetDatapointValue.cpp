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
	*(baosTelegram + BAOS_SUBSERVICE_CODE_INDEX)							= SetDatapointValueReq;
	*((unsigned short*)(baosTelegram + SET_DP_VALUE_START_DP_ID_OFFSET))	= swap2(dpId);
	// Number of items hard set to 1, since the concurrent
	// setting of multiple server items will not be supported
	*((unsigned short*)(baosTelegram + SET_DP_VALUE_NR_OF_DPS_OFFSET))		= swap2(0x00'01);
	*((unsigned short*)(baosTelegram + SET_DP_VALUE_FIRST_DP_ID_OFFSET))	= swap2(dpId);
}

bool SetDatapointValue::checkForError()
{
	bool hasNoError = true;
	const unsigned char ERROR_CODE = *(responseTelegram + ERROR_CODE_OFFSET);

	// Error route
	if (ERROR_CODE)
	{
		getErrorDescription(ERROR_CODE);
		hasNoError = false;
	}

	return hasNoError;
}

template <typename T>
bool SetDatapointValue::setValue(T dpValue, DatapointTypes::DATAPOINT_TYPES dpt, CommandByte commandByte, bool decode)
{
	const unsigned char dptSize = getDatapointSize(dpt);
	// Member variable set to BAOS telegram length (header + data).
	// It is calculated by adding the length of the fixed parts, and the 
	// dynamic length of the datapoint values together, passed as a parameter.
	telegramLength = 10 + dptSize;
	
	*(baosTelegram + SET_DP_VALUE_COMMAND_BYTE_OFFSET)	= commandByte;
	*(baosTelegram + SET_DP_VALUE_DP_VALUE_SIZE_OFFSET)	= dptSize;
	*(T*)(baosTelegram + SET_DP_VALUE_DP_VALUE_OFFSET)	= dpValue;
	
	serialConnection->sendTelegram(baosTelegram, telegramLength);
	getAnswer();
	hasValidResponse = checkForError();
	if (decode && hasValidResponse)
	{
		unsigned short datapointID = swap2(*(unsigned short*)(responseTelegram + SET_DP_VALUE_RES_DP_ID_OFFSET));
		printf("Datapoint %hu has been successfully set\n", datapointID);
	}
	return hasValidResponse;
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