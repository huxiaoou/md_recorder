#include "QListener.h"

namespace QUtility
{
    void QListenerMd::OnFrontConnected()
    {
        std::cout << "... front address connected" << std::endl;
        MsgNodeApiState *s = new MsgNodeApiState(ValApiState::CONNECTED);
        _pOperatorMsg->Push(s);
    }

    void QListenerMd::OnFrontDisconnected(int nReason)
    {
        std::cout << "... front address disconnected" << std::endl;
        MsgNodeApiState *s = new MsgNodeApiState(ValApiState::DISCONNECTED);
        _pOperatorMsg->Push(s);
    }

    void QListenerMd::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
    {
        std::cout << "... logged in" << std::endl;
        MsgNodeApiState *s = new MsgNodeApiState(ValApiState::LOGGED_IN);
        _pOperatorMsg->Push(s);
    }

    void QListenerMd::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
    {
        if (pRspInfo != NULL && pRspInfo->ErrorID == 0)
            std::cout << "| " << std::setw(6) << pSpecificInstrument->InstrumentID << " | subscribed |" << std::endl;

        if (bIsLast)
            std::cout << "===============" << std::endl;
    }

    void QListenerMd::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
    {
        std::cout << pDepthMarketData->ActionDay << " "
                  << pDepthMarketData->InstrumentID << " "
                  << pDepthMarketData->LastPrice
                  << std::endl;
    }
}
