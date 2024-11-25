#ifndef BASE_FRAME_FORMATTER_HPP
#define BASE_FRAME_FORMATTER_HPP

#define START_BYTE 0x68
#define END_BYTE 0x16

#include <iostream>

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