#include "telegram/SetDatapointValueReq.hpp"

SetDatapointValue::SetDatapointValue(int datapointId, bool datapointValue, HANDLE handle)
    : handle (handle)

    // BAOS telegram data member init
    , baosMainService (BAOS_MAIN_SERVICE) // Main service code
    , startDp { 0x00, unsigned char(datapointId)} // ID of first datapoint to set
    , nrOfDp { 0x00, 0x01 } // Number of datapoints to set
    , firstDpId {0x00, unsigned char(datapointId) } // ID of first datapoint - Byte 1
    , firstDpCmd (0x03) // Command byte of first datapoint - 0b0011 == Set value and send on bus
    , firstDpLength (0x01) // Length byte of first datapoint
    , firstDpValue (datapointValue) // Value of first datapoint
    , BaosTelegram(BaosSubServices::SetDatapointValueReq, 0x0C, 0x73, 0x71)
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
        dataLength,
        dataLength,
        0x68,
        controlByte,
        // START  BAOS TELEGRAM
        BAOS_MAIN_SERVICE,
        subServiceCode,
        startDp[0],
        startDp[1],
        nrOfDp[0],
        nrOfDp[1],
        firstDpId[0],
        firstDpId[1],
        firstDpCmd,
        firstDpLength,
        firstDpValue,
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