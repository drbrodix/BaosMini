#ifndef TELEGRAM_DECODER_HPP
#define TELEGRAM_DECODER_HPP

#include "GetDatapointDescriptionRes.hpp"
#include "GetDatapointValueRes.hpp"
#include "GetParameterByteRes.hpp"
#include "GetServerItemRes.hpp"
#include "SetDatapointValueRes.hpp"
#include "SetServerItemRes.hpp"
#include "../../Enums/SubservicesEnum.hpp"
#include "../../Utility/DatapointTypes.hpp"
#include "../Utility/GetErrorDescription.hpp"

namespace Encryption
{
	bool decodeTelegram(unsigned char* telegramCharArray, unsigned int telegramLength, DatapointTypes::DATAPOINT_TYPES dpt = DatapointTypes::NO_DATAPOINT_TYPE);
}

#endif // TELEGRAM_DECODER_HPP