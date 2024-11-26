#include "../include/Services/SetDatapointValue.hpp"

Datapoint::Datapoint(
	unsigned short dpId,
	SerialConnection* serialConnection
)
	: BaosTelegram(serialConnection)
	, dpId(dpId)
{
	*(baosTelegram + (BAOS_HEADER_FIRST_INDEX + 1)) = BaosSubServices::SetDatapointValueReq;
}

Datapoint::~Datapoint()
{
	
}

unsigned char Datapoint::getDatapointSize(DatapointTypes dpt)
{
	switch (dpt)
	{
	case Boolean:
	case Control:
	case Dimming_Blinds:
	case CharacterSet:
	case UnsignedValue1Byte:
	case SignedValue1Byte:
	case SceneNumber:
	case SceneControl:
	case HVACMode:
		return 0x01;
		break;
	case UnsignedValue2Byte:
	case SignedValue2Byte:
	case FloatValue2Byte:
		return 0x02;
		break;
	case Time:
	case Date:
	case ColorRGB:
		return 0x03;
		break;
	case UnsignedValue4Byte:
	case SignedValue4Byte:
	case FloatValue4Byte:
	case Access:
		return 0x04;
		break;
	case ColorRGBW:
		return 0x06;
		break;
	case DateTime:
		return 0x08;
		break;
	case String:
		return 0x0E;
		break;
	default:
		return 0x00;
		break;
	}
}

bool Datapoint::setBoolean(bool dpValue, CommandByte commandByte)
{
	if (setOneByteDp(dpValue, commandByte))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Datapoint::setUnsignedValue1Byte(unsigned char dpValue, CommandByte commandByte)
{
	if(setOneByteDp(dpValue, commandByte))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Datapoint::setOneByteDp(unsigned char dpValue, CommandByte commandByte)
{
	try
	{
		clearTelegram();
		setDpIdAndNr(); // 1st and 2nd, 5th and	6th byte are set to datapoint ID, 3rd and 4th byte are set to number of datapoints
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 6)) = commandByte; // 7th byte set to command byte
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 7)) = 0x01; // 8th byte set to datapoint value size
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 8)) = dpValue; // 9th byte set to actual value to set the datapoint to

		telegramLength = 11; // Member variable set to BAOS telegram length (header + data)

		serialConnection->sendTelegram(baosTelegram, telegramLength);
		return true;
	}
	catch (const std::exception& e)
	{
		printf("Error while setting datapoint to one byte unsigned value: %s\n", e.what());
		return false;
	}
}

bool Datapoint::setSignedValue1Byte(char dpValue, CommandByte commandByte)
{
	try
	{
		clearTelegram();
		setDpIdAndNr(); // 1st and 2nd, 5th and	6th byte are set to datapoint ID, 3rd and 4th byte are set to number of datapoints
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 6)) = commandByte; // 7rd byte set to command byte
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 7)) = getDatapointSize(DatapointTypes::SignedValue1Byte); // 8th byte set to datapoint value size
		*(char*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 8)) = dpValue; // 9th byte set to actual value to set the datapoint to

		telegramLength = 11; // Member variable set to BAOS telegram length (header + data)

		serialConnection->sendTelegram(baosTelegram, telegramLength);

		return true;
	}
	catch (const std::exception& e)
	{
		printf("Error while setting datapoint to one byte signed value: %s\n", e.what());
		return false;
	}
}

bool Datapoint::setUnsignedValue2Byte(unsigned short dpValue, CommandByte commandByte)
{
	try
	{
		unsigned short swappedDpValue = swap2(dpValue);
		clearTelegram();
		setDpIdAndNr(); // 1st and 2nd, 5th and	6th byte are set to datapoint ID, 3rd and 4th byte are set to number of datapoints
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 6)) = commandByte; // 7rd byte set to command byte
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 7)) = getDatapointSize(DatapointTypes::UnsignedValue2Byte); // 8th byte set to datapoint value size
		*(unsigned short*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 8)) = swappedDpValue; // 9th and 10th byte set to actual value to set the datapoint to
		
		telegramLength = 12; // Member variable set to BAOS telegram length (header + data)

		serialConnection->sendTelegram(baosTelegram, telegramLength);

		return true;
	}
	catch (const std::exception& e)
	{
		printf("Error while setting datapoint to two byte unsigned value: %s\n", e.what());
		return false;
	}
}

bool Datapoint::setSignedValue2Byte(short dpValue, CommandByte commandByte)
{
	try
	{
		short swappedDpValue = swap2(dpValue);
		clearTelegram();
		setDpIdAndNr(); // 1st and 2nd, 5th and	6th byte are set to datapoint ID, 3rd and 4th byte are set to number of datapoints
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 6)) = commandByte; // 7rd byte set to command byte
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 7)) = getDatapointSize(DatapointTypes::SignedValue2Byte); // 8th byte set to datapoint value size
		*(short*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 8)) = swappedDpValue; // 9th and 10th byte set to actual value to set the datapoint to

		telegramLength = 12; // Member variable set to BAOS telegram length (header + data)

		serialConnection->sendTelegram(baosTelegram, telegramLength);

		return true;
	}
	catch (const std::exception& e)
	{
		printf("Error while setting datapoint to two byte signed value: %s\n", e.what());
		return false;
	}
}

bool Datapoint::setFloatValue2Byte(float dpValue, CommandByte commandByte)
{
	try
	{
		unsigned char floatBytesArr[2] = { 0, 0 };
		floatConverter::encode2byteFloat(dpValue, floatBytesArr);
		clearTelegram();
		setDpIdAndNr(); // 1st and 2nd, 5th and	6th byte are set to datapoint ID, 3rd and 4th byte are set to number of datapoints
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 6)) = commandByte; // 7rd byte set to command byte
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 7)) = getDatapointSize(DatapointTypes::FloatValue2Byte); // 8th byte set to datapoint value size
		*(unsigned char*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 8)) = floatBytesArr[0]; // 9th byte set to actual value to set the datapoint to
		*(unsigned char*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 9)) = floatBytesArr[1]; // 10th byte set to actual value to set the datapoint to
		telegramLength = 12; // Member variable set to BAOS telegram length (header + data)

		serialConnection->sendTelegram(baosTelegram, telegramLength);

		return true;
	}
	catch (const std::exception& e)
	{
		printf("Error while setting datapoint to two byte signed value: %s\n", e.what());
		return false;
	}
}

bool Datapoint::setUnsignedValue4Byte(unsigned int dpValue, CommandByte commandByte)
{
	try
	{
		unsigned int swappedDpValue = swap4(dpValue);
		clearTelegram();
		setDpIdAndNr(); // 1st and 2nd, 5th and	6th byte are set to datapoint ID, 3rd and 4th byte are set to number of datapoints
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 6)) = commandByte; // 7rd byte set to command byte
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 7)) = getDatapointSize(DatapointTypes::UnsignedValue4Byte); // 8th byte set to datapoint value size
		*(unsigned int*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 8)) = swappedDpValue; // 9th till 12th bytes set to actual value to set the datapoint to

		telegramLength = 14; // Member variable set to BAOS telegram length (header + data)

		serialConnection->sendTelegram(baosTelegram, telegramLength);

		return true;
	}
	catch (const std::exception& e)
	{
		printf("Error while setting datapoint to two byte unsigned value: %s\n", e.what());
		return false;
	}
}

bool Datapoint::setSignedValue4Byte(int dpValue, CommandByte commandByte)
{
	try
	{
		int swappedDpValue = swap4(dpValue);
		clearTelegram();
		setDpIdAndNr(); // 1st and 2nd, 5th and	6th byte are set to datapoint ID, 3rd and 4th byte are set to number of datapoints
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 6)) = commandByte; // 7rd byte set to command byte
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 7)) = getDatapointSize(DatapointTypes::SignedValue4Byte); // 8th byte set to datapoint value size
		*(int*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 8)) = swappedDpValue; // 9th till 12th bytes set to actual value to set the datapoint to

		telegramLength = 14; // Member variable set to BAOS telegram length (header + data)

		serialConnection->sendTelegram(baosTelegram, telegramLength);

		return true;
	}
	catch (const std::exception& e)
	{
		printf("Error while setting datapoint to two byte signed value: %s\n", e.what());
		return false;
	}
}

bool Datapoint::setFloatValue4Byte(float dpValue, CommandByte commandByte)
{
	try
	{
		// Byte swapper macro doesn't work for floats,
		// hence we have to swap the bytes manually
		float dpValueSwapped = 0.0f;
		*((char*)&dpValueSwapped + 0) = *((char*)&dpValue + 3);
		*((char*)&dpValueSwapped + 1) = *((char*)&dpValue + 2);
		*((char*)&dpValueSwapped + 2) = *((char*)&dpValue + 1);
		*((char*)&dpValueSwapped + 3) = *((char*)&dpValue + 0);
		clearTelegram();
		setDpIdAndNr(); // 1st and 2nd, 5th and	6th byte are set to datapoint ID, 3rd and 4th byte are set to number of datapoints
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 6)) = commandByte; // 7rd byte set to command byte
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 7)) = getDatapointSize(DatapointTypes::FloatValue4Byte); // 8th byte set to datapoint value size
		*(float*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 8)) = dpValueSwapped; // 9th till 12th bytes set to actual value to set the datapoint to

		telegramLength = 14; // Member variable set to BAOS telegram length (header + data)

		serialConnection->sendTelegram(baosTelegram, telegramLength);

		return true;
	}
	catch (const std::exception& e)
	{
		printf("Error while setting datapoint to two byte signed value: %s\n", e.what());
		return false;
	}
}

bool Datapoint::setDpIdAndNr()
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

bool Datapoint::clearTelegram()
{
	try
	{
		for (unsigned char i = BAOS_DATA_FIRST_INDEX; i < TELEGRAM_ARR_SIZE; i++)
		{
			baosTelegram[i] = 0x00;
		}
		return true;
	}
	catch (const std::exception& e)
	{
		printf("Error while clearing telegram: %s\n", e.what());
		return false;
	}
}