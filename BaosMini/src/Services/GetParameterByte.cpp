#include "../../include/Services/GetParameterByte.hpp"

GetParameterByte::GetParameterByte(
	unsigned short parameterByteId,
	SerialConnection* serialConnection)
	: BaosTelegram(serialConnection)
{
	*(baosTelegram + BAOS_SUBSERVICE_CODE_INDEX) = GetParameterByteReq;
	
	*(unsigned short*)(baosTelegram + GET_PARAM_BYTE_PARAM_BYTE_ID_OFFSET)	= swap2(parameterByteId);
	// Number of parameter bytes hard set to 1, since the concurrent
	// fetching of multiple parameter bytes will not be supported
	*(unsigned short*)(baosTelegram + GET_PARAM_BYTE_NR_OF_BYTES_OFFSET)	= swap2(0x01);

	telegramLength = 6;

	serialConnection->sendTelegram(baosTelegram, telegramLength);

	//for (unsigned char i = 0; i < 4; i++)
	//{
	//	serialConnection->sendTelegram(baosTelegram, telegramLength);
	//	if (serialConnection->readAck())
	//		break;
	//}

	serialConnection->switchControlByteState();

	getAnswer();

	hasValidResponse = checkForError();
}

GetParameterByte::~GetParameterByte()
{
}

unsigned char GetParameterByte::getByte()
{
	if (hasValidResponse)
	{
		return *(responseTelegram + GET_PARAM_BYTE_RES_FIRST_BYTE_OFFSET);
	}
	else
	{
		return 0;
	}
}

bool GetParameterByte::checkForError()
{
	bool hasNoError = true;
	unsigned short nrOfBytes = swap2(*((unsigned short*)(responseTelegram + GET_PARAM_BYTE_RES_NR_OF_BYTES_OFFSET)));
	
	// Error route
	if (!nrOfBytes)
	{
		getErrorDescription(*(responseTelegram + ERROR_CODE_OFFSET));
		hasNoError = false;
	}

	return hasNoError;
}