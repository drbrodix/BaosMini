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

    dcb_serial_param.BaudRate = CBR_19200;
    dcb_serial_param.ByteSize = 8;
    dcb_serial_param.StopBits = ONESTOPBIT;
    dcb_serial_param.Parity = EVENPARITY;

    if (!SetCommState(serial_handle, &dcb_serial_param))
    {
        std::cerr << "Error while setting serial port properties." << '\n';
    }

    // Setting timeout
    COMMTIMEOUTS timeout = {0};
    timeout.ReadIntervalTimeout = 60; // specifies the time that must pass between receiving characters before timing out (in milliseconds).
    timeout.ReadTotalTimeoutConstant = 60; // provides the amount of time to wait before returning (in milliseconds).
    timeout.ReadTotalTimeoutMultiplier = 15; // specifies the length of time to wait before responding for each byte requested in the read operation (in milliseconds).
    timeout.WriteTotalTimeoutConstant = 60; // same as in case of reading, but for writing
    timeout.WriteTotalTimeoutMultiplier = 8; // same as in case of reading, but for writing

    if(!SetCommTimeouts(serial_handle, &timeout))
    {
        std::cerr << "Error while setting timeout properties." << '\n';
    }

    // Build a "Set new DP value and send on bus" BAOS request telegram

    const int BAOS_MAIN_ROUTINE =               0xF0;
    const int BAOS_SET_DATAPOINT_VALUE_REQ =    0x06;
    const int START_DP[2] =                    {0x00, 0x01};
    const int NR_OF_DP[2] =                    {0x00, 0x01};
    const int FIRST_DP_ID[2] =                 {0x00, 0x01};
    const int FIRST_DP_CMD =                    0x03; // 0011 -> Set new value and send on bus
    const int FIRST_DP_LENGTH =                 0x01;
    const int FIRST_DP_VALUE =                  0x01;


    int set_bool_dp_value[] = {
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
        FIRST_DP_VALUE
    };

    // Write data
    DWORD dwBytesWritten = 0;
    if(!WriteFile(
        serial_handle
        set_bool_dp_value,
        sizeof(set_bool_dp_value),
        &dwBytesWritten,
        NULL
    )) { std::cerr << "Error while writing to COM port." << '\n'; }

    // Close port
    CloseHandle(serial_handle);

    return EXIT_SUCCESS;
}
