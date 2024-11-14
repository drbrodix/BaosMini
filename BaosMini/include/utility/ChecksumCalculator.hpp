#ifndef CHECKSUM_CALCULATOR_HPP
#define CHECKSUM_CALCULATOR_HPP

#include <vector>
#include <numeric>

namespace ChecksumCalculator
{
	unsigned char calculateChecksum(
		std::vector<unsigned char>* pTelegramDataVector,
		unsigned char controlByte);
}

#endif // CHECKSUM_CALCULATOR_HPP