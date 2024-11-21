#ifndef CHECKSUM_CALCULATOR_HPP
#define CHECKSUM_CALCULATOR_HPP

#define BAOS_HEADER_FIRST_INDEX 5
#define BAOS_DATA_FIRST_INDEX BAOS_HEADER_FIRST_INDEX + 2

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