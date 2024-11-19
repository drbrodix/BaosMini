#include "Datapoint.hpp"

Datapoint::Datapoint(unsigned short dpId)
	: dpId(dpId)
	, dpObjectSize(0)
{
	dpData = new unsigned char[DP_BUFF_BASE_SIZE];
	memset(dpData, 0, sizeof(*dpData));
}

Datapoint::~Datapoint()
{
	delete[] dpData;
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
	try
	{
		memset(dpData, 0, sizeof(*dpData));
		setDpId(); // 1st and 2nd byte are set to datapoint ID
		dpData[2] = commandByte; // 3rd byte set to command byte
		dpData[3] = getDatapointSize(DatapointTypes::Boolean); // 4th byte set to datapoint value size
		dpData[4] = dpValue; // 5th byte set to actual value to set the datapoint to

		dpObjectSize = 5; // Data member set to currently used range of datapoint buffer
		return true;
	}
	catch (const std::exception& e)
	{
		printf("Error while setting datapoint to boolean: %s\n", e.what());
		return false;
	}
}

bool Datapoint::setDpId()
{
	try
	{
		unsigned char dpIdB1;
		unsigned char dpIdB2;
		FormatterFunctions::formatValueInTwoBytes(dpId, &dpIdB1, &dpIdB2);
		dpData[0] = dpIdB1;
		dpData[1] = dpIdB2;
		
		return true;
	}
	catch (const std::exception& e)
	{
		printf("Error while setting datapoint ID: %s\n", e.what());
		return false;
	}
}

const unsigned char* const Datapoint::getDpData() const
{
	return dpData;
}

const unsigned char Datapoint::getDpObjectSize() const
{
	return dpObjectSize;
}