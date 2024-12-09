#include "../../include/Services/SetDatapointValue.hpp"

SetDatapointValue::SetDatapointValue(
	unsigned short dpId,
	SerialConnection* serialConnection
)
	: BaosTelegram(serialConnection)
	, dpId(dpId)
{
	*(baosTelegram + (BAOS_HEADER_FIRST_INDEX + 1)) = SetDatapointValueReq;
	setDpIdAndNr(); // 1st and 2nd, 5th and	6th byte are set to datapoint ID, 3rd and 4th byte are set to number of datapoints
}

SetDatapointValue::~SetDatapointValue()
{
}

bool SetDatapointValue::setBoolean(bool dpValue, CommandByte commandByte, bool decode)
{
	if (setOneByteDp(dpValue, commandByte, decode))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool SetDatapointValue::setUnsignedValue1Byte(unsigned char dpValue, CommandByte commandByte, bool decode)
{
	if(setOneByteDp(dpValue, commandByte, decode))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool SetDatapointValue::setOneByteDp(unsigned char dpValue, CommandByte commandByte, bool decode)
{
	try
	{
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 6)) = commandByte; // 7th byte set to command byte
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 7)) = 0x01; // 8th byte set to datapoint value size
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 8)) = dpValue; // 9th byte set to actual value to set the datapoint to

		telegramLength = 11; // Member variable set to BAOS telegram length (header + data)

		serialConnection->sendTelegram(baosTelegram, telegramLength);
		getAnswer();
		if (decode)
		{
			decodeSetDatapointValueRes();
		}
		return true;
	}
	catch (const std::exception& e)
	{
		printf("Error while setting datapoint to one byte unsigned value: %s\n", e.what());
		return false;
	}
}

bool SetDatapointValue::setSignedValue1Byte(char dpValue, CommandByte commandByte, bool decode)
{
	try
	{
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 6)) = commandByte; // 7rd byte set to command byte
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 7)) = getDatapointSize(DatapointTypes::SIGNED_VALUE_1BYTE); // 8th byte set to datapoint value size
		*(char*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 8)) = dpValue; // 9th byte set to actual value to set the datapoint to

		telegramLength = 11; // Member variable set to BAOS telegram length (header + data)

		serialConnection->sendTelegram(baosTelegram, telegramLength);
		getAnswer();
		if (decode)
		{
			decodeSetDatapointValueRes();
		}
		return true;
	}
	catch (const std::exception& e)
	{
		printf("Error while setting datapoint to one byte signed value: %s\n", e.what());
		return false;
	}
}

bool SetDatapointValue::setUnsignedValue2Byte(unsigned short dpValue, CommandByte commandByte, bool decode)
{
	try
	{
		unsigned short swappedDpValue = swap2(dpValue);
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 6)) = commandByte; // 7rd byte set to command byte
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 7)) = getDatapointSize(DatapointTypes::UNSIGNED_VALUE_2BYTE); // 8th byte set to datapoint value size
		*(unsigned short*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 8)) = swappedDpValue; // 9th and 10th byte set to actual value to set the datapoint to
		
		telegramLength = 12; // Member variable set to BAOS telegram length (header + data)

		serialConnection->sendTelegram(baosTelegram, telegramLength);
		getAnswer();
		if (decode)
		{
			decodeSetDatapointValueRes();
		}
		return true;
	}
	catch (const std::exception& e)
	{
		printf("Error while setting datapoint to two byte unsigned value: %s\n", e.what());
		return false;
	}
}

bool SetDatapointValue::setSignedValue2Byte(short dpValue, CommandByte commandByte, bool decode)
{
	try
	{
		short swappedDpValue = swap2(dpValue);
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 6)) = commandByte; // 7rd byte set to command byte
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 7)) = getDatapointSize(DatapointTypes::SIGNED_VALUE_2BYTE); // 8th byte set to datapoint value size
		*(short*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 8)) = swappedDpValue; // 9th and 10th byte set to actual value to set the datapoint to

		telegramLength = 12; // Member variable set to BAOS telegram length (header + data)

		serialConnection->sendTelegram(baosTelegram, telegramLength);
		getAnswer();
		if (decode)
		{
			decodeSetDatapointValueRes();
		}
		return true;
	}
	catch (const std::exception& e)
	{
		printf("Error while setting datapoint to two byte signed value: %s\n", e.what());
		return false;
	}
}

bool SetDatapointValue::setFloatValue2Byte(float dpValue, CommandByte commandByte, bool decode)
{
	try
	{
		unsigned char floatBytesArr[2] = { 0, 0 };
		floatConverter::encode2byteFloat(dpValue, floatBytesArr);

		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 6)) = commandByte; // 7rd byte set to command byte
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 7)) = getDatapointSize(DatapointTypes::FLOAT_VALUE_2BYTE); // 8th byte set to datapoint value size
		*(unsigned char*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 8)) = floatBytesArr[0]; // 9th byte set to actual value to set the datapoint to
		*(unsigned char*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 9)) = floatBytesArr[1]; // 10th byte set to actual value to set the datapoint to
		telegramLength = 12; // Member variable set to BAOS telegram length (header + data)

		serialConnection->sendTelegram(baosTelegram, telegramLength);
		getAnswer();
		if (decode)
		{
			decodeSetDatapointValueRes();
		}
		return true;
	}
	catch (const std::exception& e)
	{
		printf("Error while setting datapoint to two byte signed value: %s\n", e.what());
		return false;
	}
}

bool SetDatapointValue::setUnsignedValue4Byte(unsigned int dpValue, CommandByte commandByte, bool decode)
{
	try
	{
		unsigned int swappedDpValue = swap4(dpValue);

		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 6)) = commandByte; // 7rd byte set to command byte
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 7)) = getDatapointSize(DatapointTypes::UNSIGNED_VALUE_4BYTE); // 8th byte set to datapoint value size
		*(unsigned int*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 8)) = swappedDpValue; // 9th till 12th bytes set to actual value to set the datapoint to

		telegramLength = 14; // Member variable set to BAOS telegram length (header + data)

		serialConnection->sendTelegram(baosTelegram, telegramLength);
		getAnswer();
		if (decode)
		{
			decodeSetDatapointValueRes();
		}
		return true;
	}
	catch (const std::exception& e)
	{
		printf("Error while setting datapoint to two byte unsigned value: %s\n", e.what());
		return false;
	}
}

bool SetDatapointValue::setSignedValue4Byte(int dpValue, CommandByte commandByte, bool decode)
{
	try
	{
		int swappedDpValue = swap4(dpValue);
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 6)) = commandByte; // 7rd byte set to command byte
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 7)) = getDatapointSize(DatapointTypes::SIGNED_VALUE_4BYTE); // 8th byte set to datapoint value size
		*(int*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 8)) = swappedDpValue; // 9th till 12th bytes set to actual value to set the datapoint to

		telegramLength = 14; // Member variable set to BAOS telegram length (header + data)

		serialConnection->sendTelegram(baosTelegram, telegramLength);
		getAnswer();
		if (decode)
		{
			decodeSetDatapointValueRes();
		}
		return true;
	}
	catch (const std::exception& e)
	{
		printf("Error while setting datapoint to two byte signed value: %s\n", e.what());
		return false;
	}
}

bool SetDatapointValue::setFloatValue4Byte(float dpValue, CommandByte commandByte, bool decode)
{
	try
	{	
		// Byte swapper macro doesn't work with floats,
		// hence we have to swap the bytes manually
		float dpValueSwapped = 0.0f;
		*((char*)&dpValueSwapped + 0) = *((char*)&dpValue + 3);
		*((char*)&dpValueSwapped + 1) = *((char*)&dpValue + 2);
		*((char*)&dpValueSwapped + 2) = *((char*)&dpValue + 1);
		*((char*)&dpValueSwapped + 3) = *((char*)&dpValue + 0);

		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 6)) = commandByte; // 7rd byte set to command byte
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 7)) = getDatapointSize(DatapointTypes::FLOAT_VALUE_4BYTE); // 8th byte set to datapoint value size
		*(float*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 8)) = dpValueSwapped; // 9th till 12th bytes set to actual value to set the datapoint to

		telegramLength = 14; // Member variable set to BAOS telegram length (header + data)

		serialConnection->sendTelegram(baosTelegram, telegramLength);
		getAnswer();
		if (decode)
		{
			decodeSetDatapointValueRes();
		}
		return true;
	}
	catch (const std::exception& e)
	{
		printf("Error while setting datapoint to two byte signed value: %s\n", e.what());
		return false;
	}
}

bool SetDatapointValue::setDpIdAndNr()
{
	try
	{
		*((unsigned short*)(baosTelegram + BAOS_DATA_FIRST_INDEX))	= swap2(dpId);

		*((unsigned short*)(baosTelegram + BAOS_DATA_FIRST_INDEX + 2)) = swap2(0x00'01);

		*((unsigned short*)(baosTelegram + BAOS_DATA_FIRST_INDEX + 4)) = swap2(dpId);
		
		return true;
	}
	catch (const std::exception& e)
	{
		printf("Error while setting datapoint ID: %s\n", e.what());
		return false;
	}
}

bool SetDatapointValue::decodeSetDatapointValueRes()
{
	const unsigned char ERROR_CODE = *(responseTelegram + ERROR_CODE_OFFSET_FROM_MAINSERVICE);
	
	if (ERROR_CODE == 0x00)
	{
		unsigned short datapointID = swap2(*(unsigned short*)(responseTelegram + 2));

		printf("Datapoint %hu has been successfully set\n", datapointID);
		return true;
	}
	// Error route
	else
	{
		getErrorDescription(ERROR_CODE);

		return false;
	}
}