#ifndef GET_DATAPOINT_VALUE_HPP
#define GET_DATAPOINT_VALUE_HPP

#include "BaosTelegram.hpp"
#include "../Utility/FormatterFunctions.hpp"

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
       unsigned short nrOfDatapoints);
	~GetDatapointValue();

private:

};

#endif // GET_DATAPOINT_VALUE_HPP
