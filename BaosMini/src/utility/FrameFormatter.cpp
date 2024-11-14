#include "utility/FrameFormatter.hpp"

namespace FrameFormatter
{
	bool FrameFormatter::formatFt12Frame(
		std::vector<unsigned char>* ft12Frame,
		std::vector<unsigned char>* setDatapointValueTelegram,
		unsigned char controlByte,
		unsigned char checksum
		)
	{
		try
		{
			const unsigned char START_BYTE = 0x68;
			const unsigned char END_BYTE = 0x16;
			const unsigned char DATA_LENGTH = setDatapointValueTelegram->size();
		
			// Complete frame with BAOS payload

			// START FT1.2 HEADER
			ft12Frame->push_back(START_BYTE);
			for (int i = 0; i < 2; i++)
			{
				ft12Frame->push_back(DATA_LENGTH + 1);
			}
			ft12Frame->push_back(START_BYTE);
			ft12Frame->push_back(controlByte);
			// START  BAOS TELEGRAM
			for (unsigned char c : *setDatapointValueTelegram)
			{
				ft12Frame->push_back(c);
			}
			// START FT1.2 FOOTER
			ft12Frame->push_back(checksum);
			ft12Frame->push_back(END_BYTE);

			return true;
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << '\n';
			return false;
		}
	}
}