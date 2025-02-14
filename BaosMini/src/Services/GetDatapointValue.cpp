#include "../../include/Services/GetDatapointValue.hpp"

GetDatapointValue::GetDatapointValue(
	unsigned short datapointId,
	DatapointTypes::DATAPOINT_TYPES dpt,
	SerialConnection* serialConnection)
	: BaosTelegram(serialConnection)
	, dpt(dpt)
{
	*(baosTelegram + BAOS_SUBSERVICE_CODE_INDEX)						= GetDatapointValueReq;
	
	*(unsigned short*)(baosTelegram + GET_DP_VALUE_DP_ID_OFFSET)		= swap2(datapointId);
	// Number of datapoints hard set to 1, since the concurrent
	// fetching of multiple datapoint values will not be supported
	*(unsigned short*)(baosTelegram + GET_DP_VALUE_NR_OF_DPS_OFFSET)	= swap2(0x01);

	*(baosTelegram + GET_DP_VALUE_FILTER_CODE_OFFSET)					= FILTER_CODES::GetAllDatapointValues;

	telegramLength = 7;

	serialConnection->sendTelegram(baosTelegram, telegramLength);

	//for (unsigned char i = 0; i < 4; i++)
	//{
	//	serialConnection->sendTelegram(baosTelegram, telegramLength);
	//	if (serialConnection->readAck())
	//		break;
	//}

	serialConnection->switchControlByteState();

	getAnswer();

	hasValidResponse = checkForError(datapointId);
}

GetDatapointValue::~GetDatapointValue()
{
}

bool GetDatapointValue::checkForError(unsigned short datapointId)
{
	bool hasNoError = true;
	unsigned short nrOfDps = swap2(*((unsigned short*)(responseTelegram + GET_DP_VALUE_RES_NR_OF_DPS_OFFSET)));
	unsigned char dpValueSize = DatapointTypes::getDatapointSize(dpt);
	unsigned char responseDpValueSize = *(responseTelegram + GET_DP_VALUE_RES_DP_LENGTH_OFFSET);

	// Error sent by ObjectServer
	if (!nrOfDps)
	{
		getErrorDescription(*(responseTelegram + ERROR_CODE_OFFSET));
		hasNoError = false;
	}
	// Datapoint length doesn't match the expected length
	if (dpValueSize != responseDpValueSize)
	{
		printf("Incorrect datapoint length while fetching datapoint %hu\n", datapointId);
		hasNoError = false;
	}
	return hasNoError;
}

template <typename T>
T GetDatapointValue::getValue(DatapointTypes::DATAPOINT_TYPES expectedDpt, const char* dptString)
{
	if (!hasValidResponse)
	{
		return 0;
	}
	if (dpt != expectedDpt)
	{
		printf("Datapoint type is not %s\n", dptString);
		return 0;
	}

	float floatValueSwapped = 0.0f;
	switch (expectedDpt)
	{
	case DatapointTypes::FLOAT_VALUE_2BYTE:
		return floatConverter::decode2byteFloat(
			*(responseTelegram + GET_DP_VALUE_RES_DP_VALUE_OFFSET),
			*(responseTelegram + GET_DP_VALUE_RES_DP_VALUE_OFFSET + 1));
		break;
	case DatapointTypes::FLOAT_VALUE_4BYTE:
		*((char*)&floatValueSwapped)		= *((char*)responseTelegram + GET_DP_VALUE_RES_DP_VALUE_OFFSET + 3);
		*((char*)&floatValueSwapped + 1)	= *((char*)responseTelegram + GET_DP_VALUE_RES_DP_VALUE_OFFSET + 2);
		*((char*)&floatValueSwapped + 2)	= *((char*)responseTelegram + GET_DP_VALUE_RES_DP_VALUE_OFFSET + 1);
		*((char*)&floatValueSwapped + 3)	= *((char*)responseTelegram + GET_DP_VALUE_RES_DP_VALUE_OFFSET);
		return floatValueSwapped;
		break;
	default:
		return *(T*)(responseTelegram + GET_DP_VALUE_RES_DP_VALUE_OFFSET);
		break;
	}
}

bool GetDatapointValue::getBooleanValue()
{
	return getValue<bool>(DatapointTypes::BOOLEAN, "boolean");
}

unsigned char GetDatapointValue::getUnsignedValue1Byte()
{
	return getValue<unsigned char>(DatapointTypes::UNSIGNED_VALUE_1BYTE, "1 byte unsigned");
}

signed char GetDatapointValue::getSignedValue1Byte()
{
	return getValue<signed char>(DatapointTypes::SIGNED_VALUE_1BYTE, "1 byte signed");
}

unsigned short GetDatapointValue::getUnsignedValue2Byte()
{
	return swap2(getValue<unsigned short>(DatapointTypes::UNSIGNED_VALUE_2BYTE, "2 byte unsigned"));
}

signed short GetDatapointValue::getSignedValue2Byte()
{
	return swap2(getValue<signed short>(DatapointTypes::SIGNED_VALUE_2BYTE, "2 byte signed"));
}

unsigned int GetDatapointValue::getUnsignedValue4Byte()
{
	return swap4(getValue<unsigned int>(DatapointTypes::UNSIGNED_VALUE_4BYTE, "4 byte unsigned"));
}

signed int GetDatapointValue::getSignedValue4Byte()
{
	return swap4(getValue<signed int>(DatapointTypes::SIGNED_VALUE_4BYTE, "4 byte signed"));
}

float GetDatapointValue::getFloatValue2Byte()
{
	return getValue<float>(DatapointTypes::FLOAT_VALUE_2BYTE, "2 byte float");
}

float GetDatapointValue::getFloatValue4Byte()
{
	return getValue<float>(DatapointTypes::FLOAT_VALUE_4BYTE, "4 byte float");
}
