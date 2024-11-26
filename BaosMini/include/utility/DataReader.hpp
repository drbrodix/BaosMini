#ifndef DATA_READER_HPP
#define DATA_READER_HPP

#include <Windows.h>
#include <string>
#include "ChecksumCalculator.hpp"

namespace DataReader
{
	unsigned int recieveTelegram(HANDLE serialHandle, unsigned char *telegramCharArray);
}

#endif // DATA_READER_HPP