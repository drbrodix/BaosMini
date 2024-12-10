#ifndef CHECKSUM_CALCULATOR_HPP
#define CHECKSUM_CALCULATOR_HPP

#ifndef BAOS_HEADER_FIRST_INDEX
#define BAOS_HEADER_FIRST_INDEX 5
#endif // !BAOS_HEADER_FIRST_INDEX

#ifndef BAOS_DATA_FIRST_INDEX
#define BAOS_DATA_FIRST_INDEX BAOS_HEADER_FIRST_INDEX + 2
#endif // !BAOS_DATA_FIRST_INDEX

namespace ChecksumCalculator
{
	unsigned char calculateChecksumSent(
		unsigned char* telegramData,
		unsigned char telegramLength,
		unsigned char controlByte
	);

	unsigned char calculateChecksumRecieved(
		unsigned char* telegramData,
		unsigned char telegramLength,
		unsigned char controlByte
	);
}

#endif // CHECKSUM_CALCULATOR_HPP