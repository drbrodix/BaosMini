#ifndef FRAME_FORMATTER_HPP
#define FRAME_FORMATTER_HPP

#include <iostream>

namespace FrameFormatter
{
	bool formatFt12Frame(
		unsigned char* ft12Frame,
		unsigned char* baosTelegram,
		unsigned char telegramLength,
		unsigned char controlByte,
		unsigned char checksum
	);
}

#endif // FRAME_FORMATTER_HPP