#include "telegram/SetDatapointValue.hpp"

SetDatapointValue::SetDatapointValue(
    int datapointId,
    bool datapointValue,
    SerialConnection* pSerialConnection)
    : pSerialConnection(pSerialConnection)
    , handle (pSerialConnection->getHandle())

    // BAOS telegram data member init
    , setDatapointValueTelegram{
        BaosTelegram::BAOS_MAIN_SERVICE,
        BaosSubServices::SetDatapointValueReq,
        0x00, unsigned char(datapointId), // ID of first datapoint to set
        0x00, 0x01, // Number of datapoints to set
        0x00, unsigned char(datapointId), // ID of first datapoint
        0x03, // Command byte of first datapoint - 0b0011 == Set value and send on bus
        0x01, // Length byte of first datapoint
        datapointValue // Value of first datapoint
    }
    , dataLength(
        sizeof(setDatapointValueTelegram) / sizeof(setDatapointValueTelegram[0]) // Data length
    )
    , controlByte(pSerialConnection->getControlByte()) // Control byte
    , checksum(calculateChecksum()) // Checksum
{
    
}

SetDatapointValue::~SetDatapointValue()
{
}

bool SetDatapointValue::sendTelegram() const
{
    // Complete frame with BAOS payload
    const unsigned char SET_BOOL_DP_VALUE[] = {
        // START FT1.2 HEADER
        0x68,
        (dataLength + 1),
        (dataLength + 1),
        0x68,
        controlByte,
        // START  BAOS TELEGRAM
        setDatapointValueTelegram[0],
        setDatapointValueTelegram[1],
        setDatapointValueTelegram[2],
        setDatapointValueTelegram[3],
        setDatapointValueTelegram[4],
        setDatapointValueTelegram[5],
        setDatapointValueTelegram[6],
        setDatapointValueTelegram[7],
        setDatapointValueTelegram[8],
        setDatapointValueTelegram[9],
        setDatapointValueTelegram[10],
        // START FT1.2 FOOTER
        checksum,
        0x16
    };

    // Reset request frame
    const unsigned char RESET_REQUEST[] = {
        0x10,
        0x40,
        0x40,
        0x16
    };

    // Write reset request
    DWORD dwBytesWrittenRR = 0;
    if (!WriteFile(
        handle,
        RESET_REQUEST,
        sizeof(RESET_REQUEST),
        &dwBytesWrittenRR,
        nullptr
    )) {
        std::cerr << "Error while writing to COM port." << '\n';
    }

    // Write data
    DWORD dwBytesWritten = 0;
    if (!WriteFile(
        handle,
        SET_BOOL_DP_VALUE,
        sizeof(SET_BOOL_DP_VALUE),
        &dwBytesWritten,
        nullptr
    )) {
        std::cerr << "Error while writing to COM port." << '\n';
    }

    return true;
}

unsigned char SetDatapointValue::calculateChecksum()
{
    // Checksum is the sum all the data in the telegram
    // plus the control byte, so we can as well initialize
    // the sum variable with the current control byte
    unsigned int sum = pSerialConnection->getControlByte();
    for (int i : setDatapointValueTelegram)
    {
        sum += i;
    }
    return unsigned char(sum % 256);
}