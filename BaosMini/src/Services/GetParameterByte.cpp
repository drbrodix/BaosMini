#include "../../include/Services/GetParameterByte.hpp"

GetParameterByte::GetParameterByte(
	unsigned short indexOfFirstByte,
	unsigned short numberOfBytes,
	SerialConnection* serialConnection)
	: BaosTelegram(serialConnection)
{
	*(baosTelegram + (BAOS_HEADER_FIRST_INDEX + 1)) = GetParameterByteReq;
	
	*(unsigned short*)(baosTelegram + (BAOS_DATA_FIRST_INDEX))		= swap2(indexOfFirstByte);
	
	*(unsigned short*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 2))	= swap2(numberOfBytes);

	telegramLength = 6;

	serialConnection->sendTelegram(baosTelegram, telegramLength);
	getAnswer();
}

GetParameterByte::~GetParameterByte()
{
}