#ifndef GET_DATAPOINT_DESCRIPTION_RES_HPP
#define GET_DATAPOINT_DESCRIPTION_RES_HPP

#ifndef NR_OF_DPS_OFFSET_FROM_MAINSERVICE
#define NR_OF_DPS_OFFSET_FROM_MAINSERVICE 4
#endif // !NR_OF_DPS_OFFSET_FROM_MAINSERVICE

#ifndef DP_ID_OFFSET_FROM_MAINSERVICE
#define DP_ID_OFFSET_FROM_MAINSERVICE 6
#endif // !DP_ID_OFFSET_FROM_MAINSERVICE

#ifndef DP_VALUE_TYPE_OFFSET_FROM_MAINSERVICE
#define DP_VALUE_TYPE_OFFSET_FROM_MAINSERVICE 8
#endif // !DP_VALUE_TYPE_OFFSET_FROM_MAINSERVICE

#ifndef DP_CONFIG_FLAGS_OFFSET_FROM_MAINSERVICE
#define DP_CONFIG_FLAGS_OFFSET_FROM_MAINSERVICE 9
#endif // !DP_CONFIG_FLAGS_OFFSET_FROM_MAINSERVICE

#ifndef DP_DPT_OFFSET_FROM_MAINSERVICE
#define DP_DPT_OFFSET_FROM_MAINSERVICE 10
#endif // !DP_DPT_OFFSET_FROM_MAINSERVICE

#ifndef ERROR_CODE_OFFSET_FROM_MAINSERVICE
#define ERROR_CODE_OFFSET_FROM_MAINSERVICE 6
#endif // !ERROR_CODE_OFFSET_FROM_MAINSERVICE

#include "../Utility/GetErrorDescription.hpp"
#include "../../Utility/Macros.hpp"
#include "../../Utility/DatapointTypes.hpp"

bool decodeGetDatapointDescriptionRes(unsigned char* telegramCharArray, unsigned int telegramLength);

inline void decodeDpId(unsigned char* startAddress);
void decodeDpValueType(unsigned char* startAddress);
void decodeDpConfigFlags(unsigned char* startAddress);
void decodeDpDpt(unsigned char* startAddress);

#endif // GET_DATAPOINT_DESCRIPTION_RES_HPP