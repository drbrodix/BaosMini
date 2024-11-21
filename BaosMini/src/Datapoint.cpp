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
		printf("Error while setting datapoint to boolean: %s\n", e.what());
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
		printf("Error while setting datapoint to boolean: %s\n", e.what());
		return false;
	}
}

bool Datapoint::setSignedValue2Byte(short dpValue, CommandByte commandByte)
{

	// 2 Byte float
	// M = Mantissa	E = Exponent
	// M E E E E M M M		M M M M M M M M M
	try
	{
		clearTelegram();
		setDpIdAndNr(); // 1st and 2nd byte are set to datapoint ID, 3rd and 4th byte are set to number of datapoints
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 6)) = commandByte; // 3rd byte set to command byte
		*(baosTelegram + (BAOS_DATA_FIRST_INDEX + 7)) = getDatapointSize(DatapointTypes::SignedValue2Byte); // 4th byte set to datapoint value size
		*(short*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 8)) = dpValue; // 5th byte set to actual value to set the datapoint to
		//*(char*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 8)) = 0b10000000; // 5th byte set to actual value to set the datapoint to
		//*(char*)(baosTelegram + (BAOS_DATA_FIRST_INDEX + 9)) = 0b10001011; // 5th byte set to actual value to set the datapoint to

		telegramLength = 12; // Member variable set to BAOS telegram length (header + data)

		serialConnection->sendTelegram(baosTelegram, telegramLength);

		return true;
	}
	catch (const std::exception& e)
	{
		printf("Error while setting datapoint to boolean: %s\n", e.what());
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