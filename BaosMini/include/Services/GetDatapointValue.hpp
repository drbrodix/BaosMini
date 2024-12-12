#ifndef GET_DATAPOINT_VALUE_HPP
#define GET_DATAPOINT_VALUE_HPP

#include "BaosTelegram.hpp"
#include "../Utility/FloatConverter.hpp"
#include "../Utility/DatapointTypes.hpp"
#include "../Utility/Macros.hpp"

enum FILTER_CODES
{
        GetAllDatapointValues = 0x00,
        GetOnlyValidDatapointValues = 0x01,
        GetOnlyUpdatedDatapointValues = 0x02
};

class GetDatapointValue : public BaosTelegram
{
public:
	GetDatapointValue(
        unsigned short datapointId,
        DatapointTypes::DATAPOINT_TYPES dpt,
        SerialConnection* serialConnection);
	~GetDatapointValue();

    // Returns 0 if no valid value has been fetched from ObjectServer
    bool getBooleanValue();
    // Returns 0 if no valid value has been fetched from ObjectServer
    unsigned char getUnsignedValue1Byte();
    // Returns 0 if no valid value has been fetched from ObjectServer
    signed char getSignedValue1Byte();
    // Returns 0 if no valid value has been fetched from ObjectServer
    unsigned short getUnsignedValue2Byte();
    // Returns 0 if no valid value has been fetched from ObjectServer
    signed short getSignedValue2Byte();
    // Returns 0 if no valid value has been fetched from ObjectServer
    float getFloatValue2Byte();
    // Returns 0 if no valid value has been fetched from ObjectServer
    unsigned int getUnsignedValue4Byte();
    // Returns 0 if no valid value has been fetched from ObjectServer
    signed int getSignedValue4Byte();
    // Returns 0 if no valid value has been fetched from ObjectServer
    float getFloatValue4Byte();

private:
    DatapointTypes::DATAPOINT_TYPES dpt;
    // Returns true if no errors have been encountered
    // while fetching datapoint value, false otherwise
    bool checkForError(unsigned short datapointId);
    template <typename T> T getValue(DatapointTypes::DATAPOINT_TYPES expectedDpt, const char* dptString);
};

#endif // GET_DATAPOINT_VALUE_HPP
