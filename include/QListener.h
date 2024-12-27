#include <iostream>
#include <cstring>
#include <iomanip>
#include "ThostFtdcMdApi.h"
#include "ThostFtdcUserApiStruct.h"
#include "QOperator.h"

namespace QUtility
{
    class QListenerMd : public CThostFtdcMdSpi
    {
    private:
        QOperatorMsg *_pOperatorMsg;

    public:
        QListenerMd(QOperatorMsg *pOperatorMsg) : _pOperatorMsg(pOperatorMsg) {}
        void OnFrontConnected();
        void OnFrontDisconnected(int nReason);
        void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
        void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
        void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);
    };
}