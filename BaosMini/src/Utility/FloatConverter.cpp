#include "../include/Utility/FloatConverter.hpp"
#ifndef LOBYTE
#define LOBYTE(w)   ((unsigned char)(w))
#endif
#ifndef HIBYTE
#define HIBYTE(w)   ((unsigned char)((unsigned short)(w) >> 8 & 255))
#endif
namespace
{
    enum
    {
        OneLeftShiftZero=(1 << 0), 
        OneLeftShiftSeven=(1 << 7)
    };

    inline unsigned short LeftShift8ThenBinOr(unsigned char ToLeftShift, unsigned char OrBy)
    {
        return(ToLeftShift << 8) | OrBy;
    }

    inline unsigned int LeftShiftByParam(unsigned int ToLeftShift, unsigned int LeftShiftBy)
    {
        return(ToLeftShift << LeftShiftBy);
    }

    inline unsigned int RightShiftByParam(unsigned int ToRightShift, unsigned int RightShiftBy)
    {
        return(ToRightShift >> RightShiftBy);
    }

    bool combineBytes(const unsigned char* inputBytes, int* outputInt)
    {
        unsigned short bytesCombined;
        unsigned short exponent;
        int mantissa;
        if((inputBytes[0] == 127) && (inputBytes[1] == 255))
        {
            return false;
        }
        bytesCombined = LeftShift8ThenBinOr(inputBytes[0], inputBytes[1]);
        mantissa = bytesCombined & 2047;
        exponent = LeftShiftByParam(OneLeftShiftZero,(RightShiftByParam(inputBytes[0], 3) & 15));
        if(inputBytes[0] & 128)
        {
            mantissa -= 2048;
        }
        *outputInt = (int)mantissa * exponent;
        return true;
    }

    // formatFloat(buffer, resultArray)
    bool formatFloat(int numToFloat, unsigned char* resultArray)
    {
        unsigned int buffer;
        unsigned short plusMinusSign;
        unsigned char mantissa;
        unsigned char exponent;

        // Set plus / minus sign
        if(numToFloat >= 0)
        {
            buffer = (unsigned int)numToFloat;
            plusMinusSign = 2047;
        }
        else
        {
            buffer = (unsigned int)-numToFloat;
            plusMinusSign = 2048;
        }
        mantissa = 0;
        exponent = 0;
        while((buffer + mantissa) > plusMinusSign)
        {
            mantissa = (unsigned char)(buffer & 1);
            buffer >>= 1;
            exponent++;
        }
        buffer += mantissa;
        if(exponent > 15)
        {
            resultArray[0] = 127;
            resultArray[1] = 255;
            return false;
        }
        if(numToFloat >= 0)
        {
            resultArray[0] = 0;
        }
        else
        {
            buffer = 2048 - buffer;
            resultArray[0] = OneLeftShiftSeven;
        }
        resultArray[0] |= (exponent << 3) & 120;
        resultArray[0] |= HIBYTE(buffer);
        resultArray[1] = LOBYTE(buffer);
        return true;
    }

    bool convertBytesToFloat(const unsigned char* arrayOfFloatBytes, float* resultFloat)
    {
        int outputInt;
        if(combineBytes(arrayOfFloatBytes, &outputInt))
        {
            *resultFloat = static_cast<float>(outputInt/100.0);
            return true;
        }
        return false;
    }

    bool roundFloat(float floatToConvert /* Float to convert */, unsigned char* resultArray /* UChar array for two bytes of 2-byte float */) // Second point
    {
        int buffer;
        floatToConvert *= 100.0;
        if(floatToConvert > 0)
        {
            buffer = (int)(floatToConvert +0.5); // Round up float if it has hundredth decimal place or bigger
        }
        else
        {
            buffer = (int)(floatToConvert -0.5); // Round down float if it has no hundredth decimal place or bigger
        }
        return formatFloat(buffer, resultArray);
    }
}

bool floatConverter::encode2byteFloat(float f, unsigned char* resultArray) // Start point
{
    if(!roundFloat(f, resultArray))
    {
        return false;
    }
    return true;
}

float floatConverter::decode2byteFloat(unsigned char firstByte,unsigned char secondByte)
{
    const unsigned char arrayOfFloatBytes[2] = {firstByte, secondByte};
    float resultFloat = 0;
    if(!convertBytesToFloat(arrayOfFloatBytes, &resultFloat))
    {
        return 0;
    }
    return resultFloat;
}
