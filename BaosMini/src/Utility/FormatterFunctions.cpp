#include "utility/FormatterFunctions.hpp"

namespace FormatterFunctions
{
	bool FormatterFunctions::formatValueInTwoBytes(
		int value,
		unsigned char *firstByteVar,
		unsigned char *secondByteVar
	)
	{
		try
		{
			*firstByteVar	= value / 256;
			*secondByteVar	= value % 256;
			return true;
		}
		catch (const std::exception& e)
		{
			return false;
		}
	}
}