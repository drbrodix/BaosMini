#include "utility/FrameFormatter.hpp"

namespace FrameFormatter
{
	bool FrameFormatter::formatFt12Frame(
		unsigned char* ft12Frame,
		unsigned char* baosTelegram,
		unsigned char telegramLength,
		unsigned char controlByte,
		unsigned char checksum
	)
	{
		try
		{
			const unsigned char START_BYTE = 0x68;
			const unsigned char END_BYTE = 0x16;
		
			// Complete frame with BAOS payload

			// START FT1.2 HEADER
			ft12Frame[0] = START_BYTE;
			for (unsigned char i = 1; i < 3; i++)
			{
				ft12Frame[i] = (telegramLength + 1);
			}
			ft12Frame[3] = START_BYTE;
			ft12Frame[4] = controlByte;

			// START  BAOS TELEGRAM
			for (unsigned char i = 0; i < telegramLength; i++)
			{
				ft12Frame[i + 5] = baosTelegram[i];
			}

			// START FT1.2 FOOTER
			ft12Frame[telegramLength + 5] = checksum;
			ft12Frame[telegramLength + 6] = END_BYTE;

			return true;
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << '\n';
			return false;
		}
	}
}