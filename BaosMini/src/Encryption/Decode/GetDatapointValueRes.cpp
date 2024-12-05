#include "../../../include/Encryption/Decode/GetDatapointValueRes.hpp"

float decode4ByteFloat(unsigned char* pValueStartAddress)
{
	float dpValueSwapped = 0.0f;
	*((char*)&dpValueSwapped)		= *((char*)pValueStartAddress + 3);
	*((char*)&dpValueSwapped + 1)	= *((char*)pValueStartAddress + 2);
	*((char*)&dpValueSwapped + 2)	= *((char*)pValueStartAddress + 1);
	*((char*)&dpValueSwapped + 3)	= *((char*)pValueStartAddress);
	return dpValueSwapped;
}

bool decodeGetDatapointValueRes(unsigned char* telegramCharArray, unsigned int telegramLength, DatapointTypes::DATAPOINT_TYPES dpt)
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
		unsigned char dpValueLength = DatapointTypes::getDatapointSize(dpt);
		unsigned char dpValueSize = *(telegramCharArray + DP_LENGTH_OFFSET_FROM_MAINSERVICE);
		unsigned short dpId = swap2(*(unsigned short*)(telegramCharArray + DP_ID_OFFSET_FROM_MAINSERVICE));
		unsigned char* pValueStartAddress = (telegramCharArray + DP_VALUE_OFFSET_FROM_MAINSERVICE);

		if (dpValueLength != dpValueSize)
		{
			printf("Incorrect datapoint length while fetching datapoint %hu\n", dpId);
		}
		else
		{
			switch ((DatapointTypes::DATAPOINT_TYPES)dpt)
			{
			case DatapointTypes::BOOLEAN:
				printf("Datapoint %hu of DPT%hu: %s\n",
					dpId, dpt,
					*pValueStartAddress ? "true" : "false");
				return true;
				break;
			case DatapointTypes::UNSIGNED_VALUE_1BYTE:
				printf("Datapoint %hu of DPT%hu: %hhu\n",
					dpId, dpt,
					*pValueStartAddress);
				return true;
				break;
			case DatapointTypes::SIGNED_VALUE_1BYTE:
				printf("Datapoint %hu of DPT%hu: %hhd\n",
					dpId, dpt,
					*pValueStartAddress);
				return true;
				break;
			case DatapointTypes::UNSIGNED_VALUE_2BYTE:
				printf("Datapoint %hu of DPT%hu: %hu\n",
					dpId, dpt,
					swap2(*(unsigned short*)(pValueStartAddress)));
				return true;
				break;
			case DatapointTypes::SIGNED_VALUE_2BYTE:
				printf("Datapoint %hu of DPT%hu: %hd\n",
					dpId, dpt,
					swap2(*(short*)(pValueStartAddress)));
				return true;
				break;
			case DatapointTypes::FLOAT_VALUE_2BYTE:
				printf("Datapoint %hu of DPT%hu: %.2hf\n",
					dpId, dpt,
					floatConverter::decode2byteFloat(
						*pValueStartAddress, *(pValueStartAddress + 1)));
				return true;
				break;
			case DatapointTypes::UNSIGNED_VALUE_4BYTE:
				printf("Datapoint %hu of DPT%hu: %u\n",
					dpId, dpt,
					swap4(*(unsigned int*)(pValueStartAddress)));
				return true;
				break;
			case DatapointTypes::SIGNED_VALUE_4BYTE:
				printf("Datapoint %hu of DPT%hu: %d\n",
					dpId, dpt,
					swap4(*(int*)(pValueStartAddress)));
				return true;
				break;
			case DatapointTypes::FLOAT_VALUE_4BYTE:
				printf("Datapoint %hu of DPT%hu: %.2f\n",
					dpId, dpt,
					decode4ByteFloat(pValueStartAddress));
				return true;
				break;
			default:
				return false; // Unknown / unsupported datatype
				break;
			}
		}
	}
}