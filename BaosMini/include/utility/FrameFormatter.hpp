#ifndef FRAME_FORMATTER_HPP
#define FRAME_FORMATTER_HPP

/// <summary>
/// FT1.2 start byte constant
/// </summary>
#define FT12_START_BYTE		0x68

/// <summary>
/// FT1.2 end byte constant
/// </summary>
#define FT12_END_BYTE		0x16

/// <summary>
/// Fixed number of bytes of the FT1.2 frame:
/// header bytes + checksum + end byte
/// </summary>
#define FRAME_BYTES_NR	7

#include <exception>
#include <cstdio>
#include <wtypes.h>


/// <summary>
/// Wraps the passed baosTelegram array in an FT1.2 frame. 
/// The function deals only with the formatting. The control byte
/// and checksum need to be calculated and passed as parameters.
/// </summary>
unsigned short formatFt12Frame(
	unsigned char* baosTelegram,
	DWORD telegramLength,
	unsigned char controlByte,
	unsigned char checksum
);

#endif // FRAME_FORMATTER_HPP