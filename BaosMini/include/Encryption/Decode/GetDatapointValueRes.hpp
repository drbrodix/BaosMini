#ifndef GET_DATAPOINT_VALUE_RES_HPP
#define GET_DATAPOINT_VALUE_RES_HPP

#ifndef DP_VALUE_OFFSET_FROM_MAINSERVICE
#define DP_VALUE_OFFSET_FROM_MAINSERVICE 10
#endif // !DP_VALUE_OFFSET_FROM_MAINSERVICE

#ifndef DP_ID_OFFSET_FROM_MAINSERVICE
#define DP_ID_OFFSET_FROM_MAINSERVICE 6
#endif // !DP_ID_OFFSET_FROM_MAINSERVICE

#ifndef NR_OF_DPS_OFFSET_FROM_MAINSERVICE
#define NR_OF_DPS_OFFSET_FROM_MAINSERVICE 4
#endif // !NR_OF_DPS_OFFSET_FROM_MAINSERVICE

#ifndef DP_LENGTH_OFFSET_FROM_MAINSERVICE
#define DP_LENGTH_OFFSET_FROM_MAINSERVICE 9
#endif // !DP_LENGTH_OFFSET_FROM_MAINSERVICE

#ifndef ERROR_CODE_OFFSET_FROM_MAINSERVICE
#define ERROR_CODE_OFFSET_FROM_MAINSERVICE 6
#endif // !ERROR_CODE_OFFSET_FROM_MAINSERVICE

#include "../Utility/GetErrorDescription.hpp"
#include "../../Utility/DatapointTypes.hpp"
#include "../../Utility/FloatConverter.hpp"
#include "../../Utility/Macros.hpp"

bool decodeGetDatapointValueRes(unsigned char* telegramCharArray, unsigned int telegramLength, DatapointTypes::DATAPOINT_TYPES dpt);
inline float decode4ByteFloat(unsigned char* pValueStartAddress);

#endif // GET_DATAPOINT_VALUE_RES_HPP