#ifndef TELEGRAM_DECODER_HPP
#define TELEGRAM_DECODER_HPP

#include "GetDatapointDescriptionRes.hpp"
#include "GetDatapointValueRes.hpp"
#include "GetDescriptionStringRes.hpp"
#include "GetParameterByteRes.hpp"
#include "GetServerItemRes.hpp"
#include "SetDatapointValueRes.hpp"
#include "SetParameterByteRes.hpp"
#include "SetServerItemRes.hpp"
#include "../../Utility/DatapointTypes.hpp"
#include "../Utility/GetErrorDescription.hpp"

namespace Encryption
{
	bool decodeTelegram(unsigned char* telegramCharArray, unsigned int telegramLength, DatapointTypes::DATAPOINT_TYPES dpt);
}

#endif // TELEGRAM_DECODER_HPP