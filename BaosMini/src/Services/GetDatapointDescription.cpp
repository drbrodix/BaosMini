#include "../../include/Services/GetDatapointDescription.hpp"

GetDatapointDescription::GetDatapointDescription(
	unsigned short datapointId,
	SerialConnection* serialConnection)
	: BaosTelegram(serialConnection)
{
	*(baosTelegram + (BAOS_HEADER_FIRST_INDEX + 1)) = GetDatapointDescriptionReq;
	
	*(unsigned short*)(baosTelegram + (BAOS_DATA_FIRST_INDEX))		= swap2(datapointId);
	
	*(unsigned short*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 2))	= swap2(0x01);

	telegramLength = 6;

	serialConnection->sendTelegram(baosTelegram, telegramLength);
}

GetDatapointDescription::~GetDatapointDescription()
{
}