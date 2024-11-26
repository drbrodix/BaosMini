
#ifndef FLOAT_CONVERTER_HPP
#define FLOAT_CONVERTER_HPP

namespace floatConverter
{
	bool encode2byteFloat(float f, unsigned char* resultArray);
	float decode2byteFloat(unsigned char firstByte, unsigned char secondByte);
}

#endif // FLOAT_CONVERTER_HPP

