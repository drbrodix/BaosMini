#ifndef SET_DATAPOINT_VALUE_HPP
#define SET_DATAPOINT_VALUE_HPP

#include "telegram/BaosTelegram.hpp"

class SetDatapointValue : public BaosTelegram
{
public:
	SetDatapointValue(
        int datapointId,
        bool datapointValue,
        SerialConnection *pSerialConnection);
	~SetDatapointValue();

    bool sendTelegram() const;

private:
    SerialConnection* pSerialConnection;
    HANDLE handle;
    unsigned char setDatapointValueTelegram[11];
    unsigned char controlByte;
    unsigned char checksum;
    int dataLength;


    unsigned char calculateChecksum();
};

#endif // SET_DATAPOINT_VALUE_HPP
