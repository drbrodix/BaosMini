#ifndef DATA_READER_HPP
#define DATA_READER_HPP

#define FT12_HEADER_SIZE 5	// Fixed size of FT1.2 header; unless the protocol changes, this constant shouldn't be touched
#define FT12_START_BYTE 0x68

#include <Windows.h>
#include <string>
#include "ChecksumCalculator.hpp"

namespace DataReader
{
	unsigned int recieveTelegram(HANDLE serialHandle, unsigned char *telegramCharArray);
}

#endif // DATA_READER_HPP