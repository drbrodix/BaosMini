#ifndef FRAME_FORMATTER_HPP
#define FRAME_FORMATTER_HPP

#include <iostream>
#include <vector>

namespace FrameFormatter
{
	bool formatFt12Frame(
		std::vector<unsigned char>* ft12Frame,
		std::vector<unsigned char>* setDatapointValueTelegram,
		unsigned char controlByte,
		unsigned char checksum
	);
}

#endif // FRAME_FORMATTER_HPP