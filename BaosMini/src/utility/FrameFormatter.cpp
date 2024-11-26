#include "../../include/utility/FrameFormatter.hpp"

unsigned short FrameFormatter::formatFt12Frame(
	unsigned char* baosTelegram,
	unsigned char telegramLength,
	unsigned char controlByte,
	unsigned char checksum
)
{
	try
	{
		// START FT1.2 HEADER
		*(baosTelegram)= START_BYTE;
		*(baosTelegram + 1) = (telegramLength + 1);
		*(baosTelegram + 2) = (telegramLength + 1);
		*(baosTelegram + 3) = START_BYTE;
		*(baosTelegram + 4) = controlByte;

		// START FT1.2 FOOTER
		*(baosTelegram + telegramLength + 5) = checksum;
		*(baosTelegram + telegramLength + 6) = END_BYTE;

		return FRAME_BYTES_NR + telegramLength;
	}
	catch (const std::exception& e)
	{
		printf("%s \n", e.what());
		return false;
	}
}