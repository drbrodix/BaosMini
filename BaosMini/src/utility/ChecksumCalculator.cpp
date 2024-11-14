#include "utility/ChecksumCalculator.hpp"

namespace ChecksumCalculator
{
    unsigned char ChecksumCalculator::calculateChecksum(
        std::vector<unsigned char> *pTelegramDataVector,
        unsigned char controlByte)
    {
        unsigned int sum =
            std::accumulate(
                pTelegramDataVector->begin(),
                pTelegramDataVector->end(),
                controlByte
            );
        return unsigned char(sum % 256);
    }
}