#ifndef SET_DATAPOINT_VALUE_HPP
#define SET_DATAPOINT_VALUE_HPP

#include "telegram/BaosTelegram.hpp"
#include "Datapoint.hpp"

class SetDatapointValue : public BaosTelegram
{
public:
	SetDatapointValue();
	SetDatapointValue(Datapoint *datapoint);
	~SetDatapointValue();

	bool addDatapoint(Datapoint *datapoint);
private:
	unsigned short nrOfDps;
};

#endif // SET_DATAPOINT_VALUE_HPP
