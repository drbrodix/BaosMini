#include "../../../include/Encryption/Decode/SetDatapointValueRes.hpp"

bool decodeSetDatapointValueRes(unsigned char* telegramCharArray, unsigned int telegramLength)
{
    const unsigned char ERROR_CODE = telegramCharArray[6];

    if(ERROR_CODE == 0x00)
	{
        unsigned short datapointID = 0;
        // Bytes are swapped to convert from big endian to little endian
        *((char*)&datapointID)      = telegramCharArray[3];
        *((char*)&datapointID + 1)  = telegramCharArray[2];

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