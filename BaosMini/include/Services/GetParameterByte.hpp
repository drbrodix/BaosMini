#ifndef GET_PARAMETER_BYTE_HPP
#define GET_PARAMETER_BYTE_HPP

#ifndef NR_OF_BYTES_OFFSET_FROM_MAIN_SERVICE
#define NR_OF_BYTES_OFFSET_FROM_MAIN_SERVICE 4
#endif // !NR_OF_BYTES_OFFSET_FROM_MAIN_SERVICE

#ifndef FIRST_BYTE_OFFSET_FROM_MAIN_SERVICE
#define FIRST_BYTE_OFFSET_FROM_MAIN_SERVICE 6
#endif // !FIRST_BYTE_OFFSET_FROM_MAIN_SERVICE

#include "BaosTelegram.hpp"

class GetParameterByte : public BaosTelegram
{
public:
    GetParameterByte(
        unsigned short indexOfFirstByte,
        SerialConnection* serialConnection);
	~GetParameterByte();
    unsigned char getByte();

private:
    // Returns true if no errors have been encountered
    // while fetching datapoint value, false otherwise
    bool checkForError();
};

#endif // GET_PARAMETER_BYTE_HPP