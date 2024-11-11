#include "BaosMini.hpp"

int main(int argc, char* argv[])
{

    // Create COM Port Handle Object
    const HANDLE serial_handle = CreateFile(
        L"COM3",
        GENERIC_READ | GENERIC_WRITE,
        0,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr);

    if (serial_handle == INVALID_HANDLE_VALUE)
    {
        if(GetLastError() == ERROR_FILE_NOT_FOUND)
        {
            std::cerr << "COM3 not found" << '\n';
        }
        else
        {
            std::cerr << "Error opening serial port." << '\n';
        }
    }

    // "The FT1.2 transmission protocol is based on the international standard IEC 870-5-1 and IEC 870-
    // 5-2 (DIN 19244). The used hardware interface for the transmission is the Universal Asynchronous
    // Receiver Transmitter (UART). The frame format of the FT1.2 protocol is fixed to 8 data bits, 1 stop
    // bit and even parity bit. The default communication speed is 19200 Baud."
    // Source: Weinzierl KNX BAOS Binary Protocol v2

    // Create properties object and set basic properties
    DCB dcb_serial_param = {0};
    dcb_serial_param.DCBlength = sizeof(dcb_serial_param);
    if (!GetCommState(serial_handle, &dcb_serial_param))
    {
        std::cerr << "Error while fetching COM properties." << '\n';
    }

    dcb_serial_param.BaudRate   = CBR_19200;
    dcb_serial_param.ByteSize   = 8;
    dcb_serial_param.StopBits   = ONESTOPBIT;
    dcb_serial_param.Parity     = EVENPARITY;

    if (!SetCommState(serial_handle, &dcb_serial_param))
    {
        std::cerr << "Error while setting serial port properties." << '\n';
    }

    // Setting timeout

    //COMMTIMEOUTS cto;
	//cto.ReadIntervalTimeout         = CHARACTER_TIMEOUT;
	//cto.ReadTotalTimeoutConstant    = MAXDWORD;
	//cto.ReadTotalTimeoutMultiplier  = 0;
	//cto.WriteTotalTimeoutConstant   = MAXDWORD;
	//cto.WriteTotalTimeoutMultiplier = 0;

    COMMTIMEOUTS timeout                = {0};
    timeout.ReadIntervalTimeout         = 100; // specifies the time that must pass between receiving characters before timing out (in milliseconds).
    timeout.ReadTotalTimeoutConstant    = MAXDWORD; // provides the amount of time to wait before returning (in milliseconds).
    timeout.ReadTotalTimeoutMultiplier  = 0; // specifies the length of time to wait before responding for each byte requested in the read operation (in milliseconds).
    timeout.WriteTotalTimeoutConstant   = MAXDWORD; // same as in case of reading, but for writing
    timeout.WriteTotalTimeoutMultiplier = 0; // same as in case of reading, but for writing

    if(!SetCommTimeouts(serial_handle, &timeout))
    {
        std::cerr << "Error while setting timeout properties." << '\n';
    }

    // FT1.2 frame configuration
    const unsigned char DATA_LENGTH     = 0x0C;
    const unsigned char CONTROL_BYTE    = 0x73;
    const unsigned char CHECKSUM        = 0x71;

    // Build a "Set new DP value and send on bus" BAOS request telegram
    const unsigned char BAOS_MAIN_ROUTINE               = 0xF0;
    const unsigned char BAOS_SET_DATAPOINT_VALUE_REQ    = 0x06;
    const unsigned char START_DP[2]                     = { 0x00, 0x01 };
    const unsigned char NR_OF_DP[2]                     = { 0x00, 0x01 };
    const unsigned char FIRST_DP_ID[2]                  = { 0x00, 0x01 };
    const unsigned char FIRST_DP_CMD                    = 0x03; // 0011 -> Set new value and send on bus
    const unsigned char FIRST_DP_LENGTH                 = 0x01;
    const unsigned char FIRST_DP_VALUE                  = 0x01;

    // Complete frame with BAOS payload
    const unsigned char SET_BOOL_DP_VALUE[] = {
        // START FT1.2 HEADER
        0x68,
        DATA_LENGTH,
        DATA_LENGTH,
        0x68,
        CONTROL_BYTE,
        // START  BAOS TELEGRAM
        BAOS_MAIN_ROUTINE,
        BAOS_SET_DATAPOINT_VALUE_REQ,
        START_DP[0],
        START_DP[1],
        NR_OF_DP[0],
        NR_OF_DP[1],
        FIRST_DP_ID[0],
        FIRST_DP_ID[1],
        FIRST_DP_CMD,
        FIRST_DP_LENGTH,
        FIRST_DP_VALUE,
        // START FT1.2 FOOTER
        CHECKSUM,
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
        serial_handle,
        RESET_REQUEST,
        sizeof(RESET_REQUEST),
        &dwBytesWrittenRR,
        nullptr
    )) {
        std::cerr << "Error while writing to COM port." << '\n';
    }

    // Write data
    DWORD dwBytesWritten = 0;
    if(!WriteFile(
        serial_handle,
        SET_BOOL_DP_VALUE,
        sizeof(SET_BOOL_DP_VALUE),
        &dwBytesWritten,
        nullptr
    )) { std::cerr << "Error while writing to COM port." << '\n'; }

    // Close port
    if (!CloseHandle(serial_handle))
    {
        std::cerr << "Error while closing COM port." << '\n';
    }

    return EXIT_SUCCESS;
}
