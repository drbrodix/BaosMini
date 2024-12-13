#include "../../include/Utility/GetErrorDescription.hpp"

bool getErrorDescription(unsigned char errorCode)
{
    char* errorString = new char[ERROR_STRING_SIZE];
    bool isErrorKnown = true;

    switch (errorCode)
    {
    case 0x01:
        strcpy_s(errorString, ERROR_STRING_SIZE, "Internal error");
        break;
    case 0x02:
        strcpy_s(errorString, ERROR_STRING_SIZE, "No element found");
        break;
    case 0x03:
        strcpy_s(errorString, ERROR_STRING_SIZE, "Buffer is too small");
        break;
    case 0x04:
        strcpy_s(errorString, ERROR_STRING_SIZE, "Item is not writable");
        break;
    case 0x05:
        strcpy_s(errorString, ERROR_STRING_SIZE, "Service is not supported");
        break;
    case 0x06:
        strcpy_s(errorString, ERROR_STRING_SIZE, "Bad service parameter");
        break;
    case 0x07:
        strcpy_s(errorString, ERROR_STRING_SIZE, "Bad ID");
        break;
    case 0x08:
        strcpy_s(errorString, ERROR_STRING_SIZE, "Bad command / value");
        break;
    case 0x09:
        strcpy_s(errorString, ERROR_STRING_SIZE, "Bad length");
        break;
    case 0x0A:
        strcpy_s(errorString, ERROR_STRING_SIZE, "Message inconsistent");
        break;
    case 0x0B:
        strcpy_s(errorString, ERROR_STRING_SIZE, "Object server is busy");
        break;
    default:
        strcpy_s(errorString, ERROR_STRING_SIZE, "Unknown error");
        isErrorKnown = false;
        break;
    }

    printf("Error code %hu: %s\n", errorCode, errorString);

    return isErrorKnown;
}