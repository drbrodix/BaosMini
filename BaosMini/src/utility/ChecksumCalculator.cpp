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
        for (unsigned char i = BAOS_HEADER_FIRST_INDEX; i < BAOS_HEADER_FIRST_INDEX + telegramLength; i++)
        {
			sum += *(telegramData + i);
        }
        return unsigned char(sum % 256);
    }
}