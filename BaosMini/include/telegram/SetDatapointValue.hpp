#ifndef SET_DATAPOINT_VALUE_HPP
#define SET_DATAPOINT_VALUE_HPP

#include "telegram/BaosTelegram.hpp"

class SetDatapointValue : public BaosTelegram
{
public:
	SetDatapointValue(
        int datapointId,
        bool datapointValue);
	~SetDatapointValue();

private:

};

#endif // SET_DATAPOINT_VALUE_HPP
