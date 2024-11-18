#ifndef FORMATTER_FUNCTIONS_HPP
#define FORMATTER_FUNCTIONS_HPP

#include <utility>
#include <exception>

namespace FormatterFunctions
{
	bool formatValueInTwoBytes(
		int value,
		unsigned char* firstByteVar,
		unsigned char* secondByteVar
	);
}

#endif // FORMATTER_FUNCTIONS_HPP