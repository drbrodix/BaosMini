#include "../../include/utility/FrameFormatter.hpp"

unsigned short formatFt12Frame(
	unsigned char* baosTelegram,
	unsigned char telegramLength,
	unsigned char controlByte,
	unsigned char checksum
)
{
	// START FT1.2 HEADER
	*(baosTelegram)		= FT12_START_BYTE;
	*(baosTelegram + 1) = (telegramLength + 1);
	*(baosTelegram + 2) = (telegramLength + 1);
	*(baosTelegram + 3) = FT12_START_BYTE;
	*(baosTelegram + 4) = controlByte;

	// START FT1.2 FOOTER
	*(baosTelegram + telegramLength + 5) = checksum;
	*(baosTelegram + telegramLength + 6) = FT12_END_BYTE;

	return FRAME_BYTES_NR + telegramLength;
}