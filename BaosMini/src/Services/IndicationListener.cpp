#include "../../include/Services/IndicationListener.hpp"

IndicationListener::IndicationListener(
	SerialConnection* serialConnection)
	: BaosTelegram(serialConnection)
{
	std::thread listenerThread(startListening, responseTelegram, &responseLength, serialConnection);
	listenerThread.detach();
	printf("Press [Enter] to stop listening...\n");
	getchar();
}

IndicationListener::~IndicationListener()
{
}

void IndicationListener::startListening(unsigned char* responseTelegram, unsigned int* responseLength, SerialConnection* serialConnection)
{
    printf("Listening for incoming telegram...\n");

	unsigned short dpId = 0x00;
	GetDatapointDescription* gdd = nullptr;

    while (true)
    {
		if (responseTelegram != nullptr)
		{
			memset(responseTelegram, 0, RESPONSE_ARR_SIZE);

			*responseLength = serialConnection->recieveTelegram(responseTelegram);

			if (*responseLength > 0)
			{
				serialConnection->sendAck();
			}
		}

		switch ((SUBSERVICES)*(responseTelegram + 1))
		{
		case SUBSERVICES::DatapointValueind:
			// Extract ID of indication datapoint
			dpId = swap2(*(unsigned short*)(responseTelegram + 2));

			//// Fetch info about the datapoint
			gdd = new GetDatapointDescription(dpId, serialConnection);

			decodeDatapointIndication(responseTelegram, (DatapointTypes::DATAPOINT_TYPES)gdd->getDpDpt());
			break;
		
		case SUBSERVICES::ServerItemInd:
			decodeServerItemRes(responseTelegram, *responseLength);
			break;

		default:
			break;
		}
    }

	delete gdd;
}

float IndicationListener::decode4ByteFloat(unsigned char* pValueStartAddress)
{
	float dpValueSwapped = 0.0f;
	*((char*)&dpValueSwapped) = *((char*)pValueStartAddress + 3);
	*((char*)&dpValueSwapped + 1) = *((char*)pValueStartAddress + 2);
	*((char*)&dpValueSwapped + 2) = *((char*)pValueStartAddress + 1);
	*((char*)&dpValueSwapped + 3) = *((char*)pValueStartAddress);
	return dpValueSwapped;
}

bool IndicationListener::decodeDatapointIndication(unsigned char* responseTelegram, DatapointTypes::DATAPOINT_TYPES dpt)
{
	unsigned short nrOfDps = swap2(*(unsigned short*)(responseTelegram + NR_OF_DPS_OFFSET_FROM_MAINSERVICE));
	// Error route
	if (!nrOfDps)
	{
		getErrorDescription(*(responseTelegram + ERROR_CODE_OFFSET_FROM_MAINSERVICE));
		return false;
	}
	// Successful datapoint value fetch
	else
	{
		unsigned char dpValueLength = DatapointTypes::getDatapointSize(dpt);
		unsigned char dpValueSize = *(responseTelegram + DP_LENGTH_OFFSET_FROM_MAINSERVICE);
		unsigned short dpId = swap2(*(unsigned short*)(responseTelegram + DP_ID_OFFSET_FROM_MAINSERVICE));
		unsigned char* pValueStartAddress = (responseTelegram + DP_VALUE_OFFSET_FROM_MAINSERVICE);

		if (dpValueLength != dpValueSize)
		{
			printf("Incorrect datapoint length while fetching datapoint %hu\n", dpId);
			return false;
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
				printf("Datapoint %hu of DPT%hu: %.2f\n",
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