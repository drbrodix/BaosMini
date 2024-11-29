#include "../../../include/Encryption/Decode/GetDatapointDescriptionRes.hpp"

void decodeDpId(unsigned char* startAddress)
{
	printf("Datapoint %hu:\n", 
		swap2(*(unsigned short*)(startAddress)));
}
void decodeDpValueType(unsigned char* startAddress)
{
	printf("\tValue size: ");
	switch (*startAddress)
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
void decodeDpConfigFlags(unsigned char* startAddress)
{
	printf("\tTransmit priority: ");
	switch (*startAddress & 0b0000'0011)
	{
	case 0x00:
		printf("System priority\n");
		break;
	case 0x01:
		printf("High priority\n");
		break;
	case 0x02:
		printf("Alarm priority\n");
		break;
	case 0x03:
		printf("Low priority\n");
		break;
	default:
		printf("unknown\n");
		break;
	}

	printf("\tDatapoint communication: %s\n",
		(*startAddress & 0b0000'0100) == 0b0000'0100 ?
		"Enabled" : "Disabled");

	printf("\tRead from bus: %s\n",
		(*startAddress & 0b0000'1000) == 0b0000'1000 ?
		"Enabled" : "Disabled");

	printf("\tWrite from bus: %s\n",
		(*startAddress & 0b0001'0000) == 0b0001'0000 ?
		"Enabled" : "Disabled");

	printf("\tRead on init: %s\n",
		(*startAddress & 0b0010'0000) == 0b0010'0000 ?
		"Enabled" : "Disabled");

	printf("\tTransmit to bus: %s\n",
		(*startAddress & 0b0100'0100) == 0b0100'0000 ? "Enabled" : "Disabled");

	printf("\tUpdate on response: %s\n",
		(*startAddress & 0b1000'0000) == 0b1000'0000 ?
		"Enabled" : "Disabled");
}
void decodeDpDpt(unsigned char* startAddress)
{
	printf("\tDatapoint type: ");
	switch (*startAddress)
	{
	case DatapointTypes::NO_DATAPOINT_TYPE:
		printf("Datapoint disabled\n");
		break;
	case DatapointTypes::BOOLEAN:
		printf("DPT%hhu, Boolean\n", *startAddress);
		break;
	case DatapointTypes::UNSIGNED_VALUE_1BYTE:
		printf("DPT%hhu, Unsigned value, 1 byte\n", *startAddress);
		break;
	case DatapointTypes::SIGNED_VALUE_1BYTE:
		printf("DPT%hhu, Signed value, 1 byte\n", *startAddress);
		break;
	case DatapointTypes::UNSIGNED_VALUE_2BYTE:
		printf("DPT%hhu, Unsigned value, 2 bytes\n", *startAddress);
		break;
	case DatapointTypes::SIGNED_VALUE_2BYTE:
		printf("DPT%hhu, Signed value, 2 bytes\n", *startAddress);
		break;
	case DatapointTypes::FLOAT_VALUE_2BYTE:
		printf("DPT%hhu, Float value, 2 bytes\n", *startAddress);
		break;
	case DatapointTypes::UNSIGNED_VALUE_4BYTE:
		printf("DPT%hhu, Unsigned value, 4 bytes\n", *startAddress);
		break;
	case DatapointTypes::SIGNED_VALUE_4BYTE:
		printf("DPT%hhu, Signed value, 4 bytes\n", *startAddress);
		break;
	case DatapointTypes::FLOAT_VALUE_4BYTE:
		printf("DPT%hhu, Float value, 4 bytes\n", *startAddress);
		break;
	default:
		printf("unknown\n");
		break;
	}
}

bool decodeGetDatapointDescriptionRes(unsigned char* telegramCharArray, unsigned int telegramLength)
{
	unsigned short nrOfDps = swap2(*(unsigned short*)(telegramCharArray + NR_OF_DPS_OFFSET_FROM_MAINSERVICE));
	// Error route
	if (!nrOfDps)
	{
		getErrorDescription(*(telegramCharArray + ERROR_CODE_OFFSET_FROM_MAINSERVICE));
		return false;
	}
	// Successful datapoint value fetch
	else
	{
		decodeDpId((telegramCharArray + DP_ID_OFFSET_FROM_MAINSERVICE));
		decodeDpDpt((telegramCharArray + DP_DPT_OFFSET_FROM_MAINSERVICE));
		decodeDpValueType((telegramCharArray + DP_VALUE_TYPE_OFFSET_FROM_MAINSERVICE));
		decodeDpConfigFlags((telegramCharArray + DP_CONFIG_FLAGS_OFFSET_FROM_MAINSERVICE));

		/*unsigned char dpValueSize = *(telegramCharArray + DP_LENGTH_OFFSET_FROM_MAINSERVICE);
		unsigned short dpId = swap2(*(unsigned short*)(telegramCharArray + DP_ID_OFFSET_FROM_MAINSERVICE));
		unsigned char* pValueStartAddress = (telegramCharArray + DP_VALUE_OFFSET_FROM_MAINSERVICE);*/
	}
}