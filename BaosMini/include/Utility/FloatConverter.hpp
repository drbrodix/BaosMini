
#ifndef FLOAT_CONVERTER_HPP
#define FLOAT_CONVERTER_HPP

/// <summary>
/// Functions for encoding and decoding 2byte floats.
/// </summary>
namespace floatConverter
{
	/// <summary>
	/// An entry point to a line of 2byte float encoding functions.
	/// A regular 4byte float will be passed as a parameter, which
	/// will be converted into a 2byte float. A pointer to an
	/// unsigned char array will be passed as a second parameter, in
	/// which the resulting 2 bytes of the conversion will be stored.
	/// </summary>
	bool encode2byteFloat(float f, unsigned char* resultArray);
	
	/// <summary>
	/// An entry point to a line of 2byte float decoding functions.
	/// The two bytes of the float will be passed as two separate
	/// parameters, which will be converted into a 4byte float, which
	/// will then be returned.
	/// </summary>
	float decode2byteFloat(unsigned char firstByte, unsigned char secondByte);
}

#endif // FLOAT_CONVERTER_HPP

