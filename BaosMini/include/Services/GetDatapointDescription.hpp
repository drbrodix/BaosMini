#ifndef GET_DATAPOINT_DESCRIPTION_HPP
#define GET_DATAPOINT_DESCRIPTION_HPP

#include "BaosTelegram.hpp"

class GetDatapointDescription : public BaosTelegram
{
public:
    GetDatapointDescription(
        unsigned short datapointId,
        SerialConnection* serialConnection);
	~GetDatapointDescription();

private:

};

#endif // GET_DATAPOINT_DESCRIPTION_HPP
