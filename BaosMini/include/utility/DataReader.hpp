#ifndef DATA_READER_HPP
#define DATA_READER_HPP

#include <Windows.h>
#include "ChecksumCalculator.hpp"

namespace DataReader
{
	size_t recieveTelegram(HANDLE serialHandle, unsigned char *telegramCharArray);
}

#endif // DATA_READER_HPP