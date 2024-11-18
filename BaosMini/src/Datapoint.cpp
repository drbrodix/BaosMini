#include "Datapoint.hpp"

Datapoint::Datapoint(int dpId)
	: dpId(dpId)
{
	unsigned char dpIdB1;
	unsigned char dpIdB2;
	FormatterFunctions::formatValueInTwoBytes(dpId, &dpIdB1, &dpIdB2);
	dpData.push_back(dpIdB1);
	dpData.push_back(dpIdB2);
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
	dpData.push_back(commandByte);
	dpData.push_back(
		getDatapointSize(DatapointTypes::Boolean)
	);
	dpData.push_back(dpValue);
}

const std::vector<unsigned char>* const Datapoint::getDpData()
{
	return &dpData;
}