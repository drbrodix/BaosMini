#ifndef CHECKSUM_CALCULATOR_HPP
#define CHECKSUM_CALCULATOR_HPP

/// <summary>
/// Index of the first byte in the baosTelegram array
/// reserved for the BAOS telegram header part.
/// This stands after the 5 bytes of the FT1.2 header.
/// </summary>
#define BAOS_HEADER_FIRST_INDEX 5

/// <summary>
/// Index of the first byte in the baosTelegram array
/// reserved for the BAOS telegram data part.
/// This stands after the 2 bytes of the BAOS header.
/// </summary>
#define BAOS_DATA_FIRST_INDEX (BAOS_HEADER_FIRST_INDEX + 2)

/// <summary>
/// In the ChecksumCalculator two separate public functions are available.
/// One to calculate the checksum of the telegram to be sent, and one to
/// calculate the checksum of the received telegram. They both call a
/// central private function, but with different arguments.
/// </summary>
namespace ChecksumCalculator
{
	/// <summary>
	/// Function to calculate the checksum of outbound telegrams.
	/// It calls a central private function with the passed
	/// arguments and preset configuration for outbound telegrams.
	/// </summary>
	unsigned char calculateChecksumSent(
		unsigned char* telegramData,
		unsigned char telegramLength,
		unsigned char controlByte
	);
	/// <summary>
	/// Function to calculate the checksum of inbound telegrams.
	/// It calls a central private function with the passed
	/// arguments and preset configuration for inbound telegrams.
	/// </summary>
	unsigned char calculateChecksumReceived(
		unsigned char* telegramData,
		unsigned char telegramLength,
		unsigned char controlByte
	);
}

#endif // CHECKSUM_CALCULATOR_HPP