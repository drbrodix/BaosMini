#include "../../include/Services/GetDatapointValue.hpp"

GetDatapointValue::GetDatapointValue(
	unsigned short datapointId,
	unsigned short nrOfDatapoints,
	SerialConnection* serialConnection)
	: BaosTelegram(serialConnection)
{
	*(baosTelegram + (BAOS_HEADER_FIRST_INDEX + 1)) = GetDatapointValueReq;
	
	*(unsigned short*)(baosTelegram + (BAOS_DATA_FIRST_INDEX))		= swap2(datapointId);
	
	*(unsigned short*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 2))	= swap2(nrOfDatapoints);

	*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 4))					= FILTER_CODES::GetAllDatapointValues; // Filter, which datapoints should be retrieved

	telegramLength = 7;

	serialConnection->sendTelegram(baosTelegram, telegramLength);
}

GetDatapointValue::~GetDatapointValue()
{
}