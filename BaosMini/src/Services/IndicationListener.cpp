#include "../../include/Services/IndicationListener.hpp"

IndicationListener::IndicationListener(
	SerialConnection* serialConnection)
	: BaosTelegram(serialConnection)
{
}

IndicationListener::~IndicationListener()
{
}

DWORD WINAPI IndicationListener::InputThread(LPVOID lpParameter) {
	getchar();
	return 0;
}

bool IndicationListener::startListening()
{
	// Create a thread to handle user input.
	DWORD threadId;
	HANDLE hThread = CreateThread(NULL, 0, InputThread, NULL, 0, &threadId);
	if (hThread == NULL) {
		fprintf(stderr, "Error creating input thread\n");
		CloseHandle(serialConnection);
		return false;
	}

    fprintf(stdout, "Listening for incoming telegram...\n");
	fprintf(stdout, "Press [Enter] to stop listening...\n");

	unsigned short dpId = 0x00;
	GetDatapointDescription* gdd = nullptr;

    while (true)
    {
		if (responseTelegram != nullptr)
		{
			memset(responseTelegram, 0, RESPONSE_ARR_SIZE);

			responseLength = serialConnection->receiveTelegram(responseTelegram, hThread);
		}

		if (responseLength == -1)
			break;

		if (responseTelegram)
		{
			switch ((SUBSERVICES) * (responseTelegram + 1))
			{
			case SUBSERVICES::DatapointValueind:
				// Extract ID of indication datapoint
				dpId = swap2(*(unsigned short*)(responseTelegram + 2));

				//// Fetch info about the datapoint
				gdd = new GetDatapointDescription(dpId, serialConnection);

				decodeDatapointIndication(responseTelegram, gdd->getDpDpt());
				break;

			case SUBSERVICES::ServerItemInd:
				decodeServerItemRes(responseTelegram, responseLength);
				break;

			default:
				break;
			}
		}
    }
	CloseHandle(hThread);

	delete gdd;
}

float IndicationListener::decode4ByteFloat(unsigned char* pValueStartAddress)
{
	float dpValueSwapped = 0.0f;
	*((char*)&dpValueSwapped)		= *((char*)pValueStartAddress + 3);
	*((char*)&dpValueSwapped + 1)	= *((char*)pValueStartAddress + 2);
	*((char*)&dpValueSwapped + 2)	= *((char*)pValueStartAddress + 1);
	*((char*)&dpValueSwapped + 3)	= *((char*)pValueStartAddress);
	return dpValueSwapped;
}

bool IndicationListener::decodeDatapointIndication(unsigned char* responseTelegram, DatapointTypes::DATAPOINT_TYPES dpt)
{
	unsigned short nrOfDps = swap2(*(unsigned short*)(responseTelegram + GET_DP_DESC_RES_NR_OF_DPS_OFFSET));
	// Error route
	if (!nrOfDps)
	{
		getErrorDescription(*(responseTelegram + ERROR_CODE_OFFSET));
		return false;
	}
	// Successful datapoint value fetch
	else
	{
		unsigned char dpValueLength = DatapointTypes::getDatapointSize(dpt);
		unsigned char dpValueSize = *(responseTelegram + IND_LISTEN_DP_LENGTH_OFFSET);
		unsigned short dpId = swap2(*(unsigned short*)(responseTelegram + GET_DP_DESC_RES_DP_ID_OFFSET));
		unsigned char* pValueStartAddress = (responseTelegram + IND_LISTEN_DP_VALUE_OFFSET);

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