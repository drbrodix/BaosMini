#include "../../include/utility/DatapointTypes.hpp"

unsigned char DatapointTypes::getDatapointSize(DATAPOINT_TYPES dpt)
{
	switch (dpt)
	{
	case BOOLEAN:
		//case CONTROL:
		//case DIMMING_BLINDS:
		//case CHARACTERSET:
	case UNSIGNED_VALUE_1BYTE:
	case SIGNED_VALUE_1BYTE:
		//case SCENE_NUMBER:
		//case SCENE_CONTROL:
		//case HVAC_MODE:
		return 0x01;
		break;
	case UNSIGNED_VALUE_2BYTE:
	case SIGNED_VALUE_2BYTE:
	case FLOAT_VALUE_2BYTE:
		return 0x02;
		break;
		//case TIME:
		//case DATE:
		//case COLOR_RGB:
			//return 0x03;
			//break;
	case UNSIGNED_VALUE_4BYTE:
	case SIGNED_VALUE_4BYTE:
	case FLOAT_VALUE_4BYTE:
		//case ACCESS:
		return 0x04;
		break;
		//case COLOR_RGBW:
			//return 0x06;
			//break;
		//case DATE_TIME:
			//return 0x08;
			//break;
		//case STRING:
			//return 0x0E;
			//break;
	default:
		return 0x00;
		break;
	}
}