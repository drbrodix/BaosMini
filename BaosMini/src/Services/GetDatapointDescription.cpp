#include "../../include/Services/GetDatapointDescription.hpp"

GetDatapointDescription::GetDatapointDescription(
	unsigned short datapointId,
	SerialConnection* serialConnection)
	: BaosTelegram(serialConnection)
{
	*(baosTelegram + (BAOS_HEADER_FIRST_INDEX + 1))					= GetDatapointDescriptionReq;
	
	*(unsigned short*)(baosTelegram + (BAOS_DATA_FIRST_INDEX))		= swap2(datapointId);
	
	*(unsigned short*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 2))	= swap2(0x01);

	telegramLength = 6;

	serialConnection->sendTelegram(baosTelegram, telegramLength);

	hasValidResponse = getAnswer();

	hasValidResponse = checkForError();
}

GetDatapointDescription::~GetDatapointDescription()
{
}

DatapointTypes::DATAPOINT_TYPES GetDatapointDescription::getDpDpt()
{
	if (!hasValidResponse)
	{
		return DatapointTypes::NO_DATAPOINT_TYPE;
	}
	return (DatapointTypes::DATAPOINT_TYPES)*(responseTelegram + DP_DPT_OFFSET_FROM_MAINSERVICE);
}

DatapointTypes::DATAPOINT_VALUE_TYPES GetDatapointDescription::getDpValueType()
{
	if (!hasValidResponse)
	{
		return DatapointTypes::INVALID_SIZE;
	}
	return (DatapointTypes::DATAPOINT_VALUE_TYPES)*(responseTelegram + DP_VALUE_TYPE_OFFSET_FROM_MAINSERVICE);
}

ConfigFlags GetDatapointDescription::getDpConfigFlags()
{
	if (!hasValidResponse)
	{
		return ConfigFlags{0};
	}
	ConfigFlags configFlag = { 0 };
	configFlag.transmitPriority			= *(responseTelegram + DP_CONFIG_FLAGS_OFFSET_FROM_MAINSERVICE) & 0b0000'0011;
	configFlag.datapointCommunication	= (*(responseTelegram + DP_CONFIG_FLAGS_OFFSET_FROM_MAINSERVICE) & 0b0000'0100) >> 2;
	configFlag.readFromBus				= (*(responseTelegram + DP_CONFIG_FLAGS_OFFSET_FROM_MAINSERVICE) & 0b0000'1000) >> 3;
	configFlag.writeFromBus				= (*(responseTelegram + DP_CONFIG_FLAGS_OFFSET_FROM_MAINSERVICE) & 0b0001'0000) >> 4;
	configFlag.readOnInit				= (*(responseTelegram + DP_CONFIG_FLAGS_OFFSET_FROM_MAINSERVICE) & 0b0010'0000) >> 5;
	configFlag.transmitToBus			= (*(responseTelegram + DP_CONFIG_FLAGS_OFFSET_FROM_MAINSERVICE) & 0b0100'0000) >> 6;
	configFlag.updateOnResponse			= (*(responseTelegram + DP_CONFIG_FLAGS_OFFSET_FROM_MAINSERVICE) & 0b1000'0000) >> 7;
	return configFlag;
}

bool GetDatapointDescription::checkForError()
{
	bool hasNoError = true;
	unsigned short nrOfDps = swap2(*((unsigned short*)(responseTelegram + NR_OF_DPS_OFFSET_FROM_MAINSERVICE)));
	
	// Error route
	if (!nrOfDps)
	{
		getErrorDescription(*(responseTelegram + ERROR_CODE_OFFSET_FROM_MAINSERVICE));
		hasNoError = false;
	}

	return hasNoError;
}

void GetDatapointDescription::decodeDpDpt(DatapointTypes::DATAPOINT_TYPES dpt)
{
	printf("\tDatapoint type: ");
	switch (dpt)
	{
	case DatapointTypes::NO_DATAPOINT_TYPE:
		printf("Datapoint disabled\n");
		break;
	case DatapointTypes::BOOLEAN:
		printf("DPT%hhu, Boolean\n", dpt);
		break;
	case DatapointTypes::UNSIGNED_VALUE_1BYTE:
		printf("DPT%hhu, Unsigned value, 1 byte\n", dpt);
		break;
	case DatapointTypes::SIGNED_VALUE_1BYTE:
		printf("DPT%hhu, Signed value, 1 byte\n", dpt);
		break;
	case DatapointTypes::UNSIGNED_VALUE_2BYTE:
		printf("DPT%hhu, Unsigned value, 2 bytes\n", dpt);
		break;
	case DatapointTypes::SIGNED_VALUE_2BYTE:
		printf("DPT%hhu, Signed value, 2 bytes\n", dpt);
		break;
	case DatapointTypes::FLOAT_VALUE_2BYTE:
		printf("DPT%hhu, Float value, 2 bytes\n", dpt);
		break;
	case DatapointTypes::UNSIGNED_VALUE_4BYTE:
		printf("DPT%hhu, Unsigned value, 4 bytes\n", dpt);
		break;
	case DatapointTypes::SIGNED_VALUE_4BYTE:
		printf("DPT%hhu, Signed value, 4 bytes\n", dpt);
		break;
	case DatapointTypes::FLOAT_VALUE_4BYTE:
		printf("DPT%hhu, Float value, 4 bytes\n", dpt);
		break;
	default:
		printf("unknown\n");
		break;
	}
}

void GetDatapointDescription::decodeDpConfigFlags(ConfigFlags configFlagByte)
{
	printf("\tTransmit priority: ");
	switch (configFlagByte.transmitPriority)
	{
	case 0b00:
		printf("System priority\n");
		break;
	case 0b01:
		printf("High priority\n");
		break;
	case 0b10:
		printf("Alarm priority\n");
		break;
	case 0b11:
		printf("Low priority\n");
		break;
	default:
		printf("unknown\n");
		break;
	}

	printf("\tDatapoint communication: %s\n",
		configFlagByte.datapointCommunication ? "Enabled" : "Disabled");

	printf("\tRead from bus: %s\n",
		configFlagByte.readFromBus ? "Enabled" : "Disabled");

	printf("\tWrite from bus: %s\n",
		configFlagByte.writeFromBus ? "Enabled" : "Disabled");

	printf("\tRead on init: %s\n",
		configFlagByte.readOnInit ? "Enabled" : "Disabled");

	printf("\tTransmit to bus: %s\n",
		configFlagByte.transmitToBus ? "Enabled" : "Disabled");

	printf("\tUpdate on response: %s\n",
		configFlagByte.updateOnResponse ? "Enabled" : "Disabled");
}

void GetDatapointDescription::decodeDpValueType(DatapointTypes::DATAPOINT_VALUE_TYPES dpValueType)
{
	printf("\tValue size: ");
	switch (dpValueType)
	{
	case DatapointTypes::SIZE_1_BIT:
		printf("1 bit\n");
		break;
	case DatapointTypes::SIZE_2_BIT:
		printf("2 bits\n");
		break;
	case DatapointTypes::SIZE_3_BIT:
		printf("3 bits\n");
		break;
	case DatapointTypes::SIZE_4_BIT:
		printf("4 bits\n");
		break;
	case DatapointTypes::SIZE_5_BIT:
		printf("5 bits\n");
		break;
	case DatapointTypes::SIZE_6_BIT:
		printf("6 bits\n");
		break;
	case DatapointTypes::SIZE_7_BIT:
		printf("7 bits\n");
		break;
	case DatapointTypes::SIZE_1_BYTE:
		printf("1 byte\n");
		break;
	case DatapointTypes::SIZE_2_BYTE:
		printf("2 bytes\n");
		break;
	case DatapointTypes::SIZE_3_BYTE:
		printf("3 bytes\n");
		break;
	case DatapointTypes::SIZE_4_BYTE:
		printf("4 bytes\n");
		break;
	case DatapointTypes::SIZE_6_BYTE:
		printf("6 bytes\n");
		break;
	case DatapointTypes::SIZE_8_BYTE:
		printf("8 bytes\n");
		break;
	case DatapointTypes::SIZE_10_BYTE:
		printf("10 bytes\n");
		break;
	case DatapointTypes::SIZE_14_BYTE:
		printf("14 bytes\n");
		break;
	default:
		printf("unknown\n");
		break;
	}
}

bool GetDatapointDescription::printDpDescription(
	bool datapointDpt,
	bool datapointValueType,
	bool datapointConfigFlag)
{
	if (!hasValidResponse)
	{
		return false;
	}
	printf("Datapoint %hu:\n",
		swap2(*(unsigned short*)(responseTelegram + DP_ID_OFFSET_FROM_MAINSERVICE)));
	if (datapointDpt)
	{
		decodeDpDpt(getDpDpt());
	}
	
	if (datapointValueType)
	{
		decodeDpValueType(getDpValueType());
	}
	
	if (datapointConfigFlag)
	{
		decodeDpConfigFlags(getDpConfigFlags());
	}
	return true;
}