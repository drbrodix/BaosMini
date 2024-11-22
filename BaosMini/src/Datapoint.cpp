#include "Datapoint.hpp"

Datapoint::Datapoint(
	unsigned short dpId,
	SerialConnection* serialConnection
)
	: BaosTelegram(serialConnection)
	, dpId(dpId)
{
	baosTelegram[BAOS_HEADER_FIRST_INDEX + 1] = BaosSubServices::SetDatapointValueReq;
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
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 6)) = commandByte; // 3rd byte set to command byte
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 7)) = 0x01; // 4th byte set to datapoint value size
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 8)) = dpValue; // 5th byte set to actual value to set the datapoint to

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
		setDpIdAndNr(); // 1st and 2nd byte are set to datapoint ID, 3rd and 4th byte are set to number of datapoints
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 6)) = commandByte; // 3rd byte set to command byte
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 7)) = getDatapointSize(DatapointTypes::SignedValue1Byte); // 4th byte set to datapoint value size
		*(char*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 8)) = dpValue; // 5th byte set to actual value to set the datapoint to

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
		clearTelegram();
		setDpIdAndNr(); // 1st and 2nd byte are set to datapoint ID, 3rd and 4th byte are set to number of datapoints
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 6)) = commandByte; // 3rd byte set to command byte
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 7)) = getDatapointSize(DatapointTypes::UnsignedValue2Byte); // 4th byte set to datapoint value size
		*(unsigned short*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 8)) = _byteswap_ushort(dpValue); // 5th byte set to actual value to set the datapoint to
		
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

	// -300 in binary is 0000 0001 0010 1100 -> 1|111 1110 1101 0100 

	try
	{
		clearTelegram();
		setDpIdAndNr(); // 1st and 2nd byte are set to datapoint ID, 3rd and 4th byte are set to number of datapoints
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 6)) = commandByte; // 3rd byte set to command byte
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 7)) = getDatapointSize(DatapointTypes::SignedValue2Byte); // 4th byte set to datapoint value size
		*(short*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 8)) = _byteswap_ushort(dpValue); // 5th byte set to actual value to set the datapoint to

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
	float testFloat = 0b1100'1001'0100'1000 << 8;
	// Octet nr: 2 MSB 1 LSB
	// encoding M E E E  E M M M		M M M M  M M M M M

	// 2.56 = 0,01 * 8 * 2^5 = 0010 1000 0000 1000

	// 0000 1000 0010 1000

	try
	{
		clearTelegram();
		setDpIdAndNr(); // 1st and 2nd byte are set to datapoint ID, 3rd and 4th byte are set to number of datapoints
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 6)) = commandByte; // 3rd byte set to command byte
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 7)) = getDatapointSize(DatapointTypes::FloatValue2Byte); // 4th byte set to datapoint value size
		//*(float*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 8)) = (dpValue);
		*(float*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 8)) = testFloat; // 5th byte set to actual value to set the datapoint to
		//*(char*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 9)) = byte2;
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

bool Datapoint::setFloatValue4Byte(float dpValue, CommandByte commandByte)
{
	float reverseFloat = 0;
	unsigned char i = 0;
	unsigned char j = 3;
	while(i < 4)
	{
		*((char*)&reverseFloat + i) = *((char*)&dpValue + j);
		++i;
		--j;
	}

	// 0A D7 23 40 = 0000 1010 1101 0111 0010 0011 0100 0000
	// Byte order switch =	0100 0000 0010 0011 1101 0111 0000 1010
	// From converter:		0100 0000 0010 0011 1101 0111 0000 1010
	// Exponent = 128 - 127
	// Mantissa = 2 348 810

	try
	{
		clearTelegram();
		setDpIdAndNr(); // 1st and 2nd byte are set to datapoint ID, 3rd and 4th byte are set to number of datapoints
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 6)) = commandByte; // 3rd byte set to command byte
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 7)) = getDatapointSize(DatapointTypes::FloatValue4Byte); // 4th byte set to datapoint value size
		*(float*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 8)) = (reverseFloat); // 5th byte set to actual value to set the datapoint to

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
		unsigned char dpIdB1;
		unsigned char dpIdB2;
		unsigned char nrOfDpsB1;
		unsigned char nrOfDpsB2;
		FormatterFunctions::formatValueInTwoBytes(0x01, &nrOfDpsB1, &nrOfDpsB2);
		FormatterFunctions::formatValueInTwoBytes(dpId, &dpIdB1, &dpIdB2);
		baosTelegram[BAOS_DATA_FIRST_INDEX]		= dpIdB1;
		baosTelegram[BAOS_DATA_FIRST_INDEX + 1] = dpIdB2;
		baosTelegram[BAOS_DATA_FIRST_INDEX + 2] = nrOfDpsB1;
		baosTelegram[BAOS_DATA_FIRST_INDEX + 3] = nrOfDpsB2;
		baosTelegram[BAOS_DATA_FIRST_INDEX + 4] = dpIdB1;
		baosTelegram[BAOS_DATA_FIRST_INDEX + 5] = dpIdB2;
		
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