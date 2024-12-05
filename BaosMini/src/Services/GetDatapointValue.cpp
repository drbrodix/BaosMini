#include "../../include/Services/GetDatapointValue.hpp"

GetDatapointValue::GetDatapointValue(
	unsigned short datapointId,
	DatapointTypes::DATAPOINT_TYPES dpt,
	SerialConnection* serialConnection)
	: BaosTelegram(serialConnection)
	, dpt(dpt)
{
	*(baosTelegram + (BAOS_HEADER_FIRST_INDEX + 1)) = GetDatapointValueReq;
	
	*(unsigned short*)(baosTelegram + (BAOS_DATA_FIRST_INDEX))		= swap2(datapointId);
	
	*(unsigned short*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 2))	= swap2(0x01);

	*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 4))					= FILTER_CODES::GetAllDatapointValues; // Filter, which datapoints should be retrieved

	telegramLength = 7;

	serialConnection->sendTelegram(baosTelegram, telegramLength, dpt);
	if (getAnswer())
	{
		hasValidResponse = true;
	}
	if (checkForError(datapointId))
	{
		hasValidResponse = false;
	}
}

GetDatapointValue::~GetDatapointValue()
{
}

bool GetDatapointValue::checkForError(unsigned short datapointId)
{
	bool hasError = false;
	unsigned short nrOfDps = swap2(*((unsigned short*)(responseTelegram + NR_OF_DPS_OFFSET_FROM_MAINSERVICE)));
	unsigned char dpValueSize = DatapointTypes::getDatapointSize(dpt);
	unsigned char responseDpValueSize = *(responseTelegram + DP_LENGTH_OFFSET_FROM_MAINSERVICE);

	// Error sent by ObjectServer
	if (!nrOfDps)
	{
		getErrorDescription(*(responseTelegram + ERROR_CODE_OFFSET_FROM_MAINSERVICE));
		hasError = true;
	}
	// Datapoint length doesn't match the expected length
	if (dpValueSize != responseDpValueSize)
	{
		printf("Incorrect datapoint length while fetching datapoint %hu\n", datapointId);
		hasError = true;
	}
	return hasError;
}

bool GetDatapointValue::getBooleanValue()
{
	if (!hasValidResponse)
	{
		return 0;
	}
	if (dpt != DatapointTypes::BOOLEAN)
	{
		printf("Datapoint type is not boolean\n");
		return 0;
	}
	return *(responseTelegram + DP_VALUE_OFFSET_FROM_MAINSERVICE);
}

unsigned char GetDatapointValue::getUnsignedValue1Byte()
{
	if (!hasValidResponse)
	{
		return 0;
	}
	if (dpt != DatapointTypes::UNSIGNED_VALUE_1BYTE)
	{
		printf("Datapoint type is not 1 byte unsigned\n");
		return 0;
	}
	return *(responseTelegram + DP_VALUE_OFFSET_FROM_MAINSERVICE);
}

char GetDatapointValue::getSignedValue1Byte()
{
	if (!hasValidResponse)
	{
		return 0;
	}
	if (dpt != DatapointTypes::SIGNED_VALUE_1BYTE)
	{
		printf("Datapoint type is not 1 byte signed\n");
		return 0;
	}
	return *(responseTelegram + DP_VALUE_OFFSET_FROM_MAINSERVICE);
}

unsigned short GetDatapointValue::getUnsignedValue2Byte()
{
	if (!hasValidResponse)
	{
		return 0;
	}
	if (dpt != DatapointTypes::UNSIGNED_VALUE_2BYTE)
	{
		printf("Datapoint type is not 2 byte unsigned\n");
		return 0;
	}
	return swap2(*(unsigned short*)(responseTelegram + DP_VALUE_OFFSET_FROM_MAINSERVICE));
}

short GetDatapointValue::getSignedValue2Byte()
{
	if (!hasValidResponse)
	{
		return 0;
	}
	if (dpt != DatapointTypes::SIGNED_VALUE_2BYTE)
	{
		printf("Datapoint type is not 2 byte signed\n");
		return 0;
	}
	return swap2(*(short*)(responseTelegram + DP_VALUE_OFFSET_FROM_MAINSERVICE));
}

float GetDatapointValue::getFloatValue2Byte()
{
	if (!hasValidResponse)
	{
		return 0;
	}
	if (dpt != DatapointTypes::FLOAT_VALUE_2BYTE)
	{
		printf("Datapoint type is not 2 byte float\n");
		return 0;
	}
	return floatConverter::decode2byteFloat(
		*(responseTelegram + DP_VALUE_OFFSET_FROM_MAINSERVICE),
		*(responseTelegram + DP_VALUE_OFFSET_FROM_MAINSERVICE + 1));
}

unsigned int GetDatapointValue::getUnsignedValue4Byte()
{
	if (!hasValidResponse)
	{
		return 0;
	}
	if (dpt != DatapointTypes::UNSIGNED_VALUE_4BYTE)
	{
		printf("Datapoint type is not 4 byte unsigned\n");
		return 0;
	}
	return swap4(*(unsigned int*)(responseTelegram + DP_VALUE_OFFSET_FROM_MAINSERVICE));
}

int GetDatapointValue::getSignedValue4Byte()
{
	if (!hasValidResponse)
	{
		return 0;
	}
	if (dpt != DatapointTypes::SIGNED_VALUE_4BYTE)
	{
		printf("Datapoint type is not 4 byte signed\n");
		return 0;
	}
	return swap4(*(int*)(responseTelegram + DP_VALUE_OFFSET_FROM_MAINSERVICE));
}

float GetDatapointValue::getFloatValue4Byte()
{
	if (!hasValidResponse)
	{
		return 0;
	}
	if (dpt != DatapointTypes::FLOAT_VALUE_4BYTE)
	{
		printf("Datapoint type is not 4 byte float\n");
		return 0;
	}
	float dpValueSwapped = 0.0f;
	*((char*)&dpValueSwapped)		= *((char*)responseTelegram + DP_VALUE_OFFSET_FROM_MAINSERVICE + 3);
	*((char*)&dpValueSwapped + 1)	= *((char*)responseTelegram + DP_VALUE_OFFSET_FROM_MAINSERVICE + 2);
	*((char*)&dpValueSwapped + 2)	= *((char*)responseTelegram + DP_VALUE_OFFSET_FROM_MAINSERVICE + 1);
	*((char*)&dpValueSwapped + 3)	= *((char*)responseTelegram + DP_VALUE_OFFSET_FROM_MAINSERVICE);
	return dpValueSwapped;
}
