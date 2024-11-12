#ifndef SET_DATAPOINT_VALUE_REQ_HPP
#define SET_DATAPOINT_VALUE_REQ_HPP

#include "telegram/BaosTelegram.hpp"

class SetDatapointValue : public BaosTelegram
{
public:
	SetDatapointValue(int datapointId, bool datapointValue, HANDLE handle);
	~SetDatapointValue();

    bool sendTelegram() const;

private:
    HANDLE handle;
    unsigned char baosMainService;
    unsigned char startDp[2];
    unsigned char nrOfDp[2];
    unsigned char firstDpId[2];
    unsigned char firstDpCmd;
    unsigned char firstDpLength;
    unsigned char firstDpValue;
};

#endif // SET_DATAPOINT_VALUE_REQ_HPP
