#include "utility/ChecksumCalculator.hpp"

namespace ChecksumCalculator
{
    unsigned char ChecksumCalculator::calculateChecksum(
        unsigned char* telegramData,
        unsigned char telegramLength,
        unsigned char controlByte
    )
    {
        unsigned int sum = controlByte;
        for (unsigned char i = 0; i < telegramLength; i++)
        {
			sum += telegramData[i];
        }
        return unsigned char(sum % 256);
    }
}