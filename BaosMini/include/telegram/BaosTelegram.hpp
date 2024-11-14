#ifndef BAOS_TELEGRAM_HPP
#define BAOS_TELEGRAM_HPP

#include <vector>

enum BaosSubServices
{
    GetServerItemReq            = 0x01,
    SetServerItemReq            = 0x02,
    GetDatapointDescriptionReq  = 0x03,
    GetDescriptionStringReq     = 0x04,
    GetDatapointValueReq        = 0x05,
    SetDatapointValueReq        = 0x06,
    GetParameterByteReq         = 0x07,
    SetParameterByteReq         = 0x08,
    GetServerItemRes            = 0x81,
    SetServerItemRes            = 0x82,
    GetDatapointDescriptionRes  = 0x83,
    GetDescriptionStringRes     = 0x84,
    GetDatapointValueRes        = 0x85,
    SetDatapointValueRes        = 0x86,
    GetParameterByteRes         = 0x87,
    SetParameterByteRes         = 0x88,
    DatapointValueind           = 0xC1,
    ServerItemInd               = 0xC2
};

class BaosTelegram
{
public:
    std::vector<unsigned char>* getTelegramData()
    {
        return &baosTelegram;
    }

protected:
    // BAOS telegram data members
    static const unsigned char BAOS_MAIN_SERVICE = 0xF0;
    std::vector<unsigned char> baosTelegram;
};

#endif // BAOS_TELEGRAM_HPP
