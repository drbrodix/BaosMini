#include "../../include/Services/GetParameterByte.hpp"

GetParameterByte::GetParameterByte(
	unsigned short indexOfFirstByte,
	SerialConnection* serialConnection)
	: BaosTelegram(serialConnection)
{
	*(baosTelegram + (BAOS_HEADER_FIRST_INDEX + 1)) = GetParameterByteReq;
	
	*(unsigned short*)(baosTelegram + (BAOS_DATA_FIRST_INDEX))		= swap2(indexOfFirstByte);
	
	*(unsigned short*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 2))	= swap2(0x01);

	telegramLength = 6;

	serialConnection->sendTelegram(baosTelegram, telegramLength);
	getAnswer();
	checkForError();
}

GetParameterByte::~GetParameterByte()
{
}

unsigned char GetParameterByte::getByte()
{
	return *(responseTelegram + FIRST_BYTE_OFFSET_FROM_MAIN_SERVICE);
}

bool GetParameterByte::checkForError()
{
	bool hasError = false;
	unsigned short nrOfBytes = swap2(*((unsigned short*)(responseTelegram + NR_OF_BYTES_OFFSET_FROM_MAIN_SERVICE)));
	
	// Error route
	if (!nrOfBytes)
	{
		getErrorDescription(*(responseTelegram + ERROR_CODE_OFFSET_FROM_MAINSERVICE));
		hasError = true;
	}

	return hasError;
}