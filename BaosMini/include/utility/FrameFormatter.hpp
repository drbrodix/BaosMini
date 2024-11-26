#ifndef BASE_FRAME_FORMATTER_HPP
#define BASE_FRAME_FORMATTER_HPP

#define START_BYTE		0x68	// FT1.2 start byte is fixed value
#define END_BYTE		0x16	// FT1.2 end byte is fixed value
#define FRAME_BYTES_NR	7		// Number of FT1.2 header bytes + end byte + checksum should never change

#include <exception>
#include <cstdio>

namespace FrameFormatter
{
	unsigned short formatFt12Frame(
		unsigned char* baosTelegram,
		unsigned char telegramLength,
		unsigned char controlByte,
		unsigned char checksum
	);
}

#endif // BASE_FRAME_FORMATTER_HPP