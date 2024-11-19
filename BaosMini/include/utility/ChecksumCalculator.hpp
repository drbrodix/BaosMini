#ifndef CHECKSUM_CALCULATOR_HPP
#define CHECKSUM_CALCULATOR_HPP

#include <numeric>

namespace ChecksumCalculator
{
	unsigned char calculateChecksum(
		unsigned char* telegramData,
		unsigned char telegramLength,
		unsigned char controlByte
	);
}

#endif // CHECKSUM_CALCULATOR_HPP