#include "../../include/utility/ChecksumCalculator.hpp"

namespace
{
    unsigned char calculateChecksum(
        unsigned char* telegramData,
        unsigned char telegramLength,
        unsigned char controlByte,
        unsigned char index,
		unsigned char loopEnd
    )
    {
        unsigned int sum = controlByte;
        for (index; index < loopEnd; index++)
        {
            sum += *(telegramData + index);
        }
        return unsigned char(sum % 256);
    }
}

unsigned char ChecksumCalculator::calculateChecksumSent(
    unsigned char* telegramData,
    unsigned char telegramLength,
    unsigned char controlByte
)
{
    return calculateChecksum(
        telegramData,
        telegramLength,
        controlByte,
        BAOS_HEADER_FIRST_INDEX,
        BAOS_HEADER_FIRST_INDEX + telegramLength
    );
}

unsigned char ChecksumCalculator::calculateChecksumRecieved(
    unsigned char* telegramData,
    unsigned char telegramLength,
    unsigned char controlByte
)
{
    return calculateChecksum(
        telegramData,
        telegramLength,
        controlByte,
        0,
        telegramLength
    );
}