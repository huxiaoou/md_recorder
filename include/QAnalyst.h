#pragma once
#include <iostream>
#include <iomanip>
#include "ThostFtdcMdApi.h"
#include "QOperator.h"
#include "QAccount.h"

namespace QUtility
{
    class QAnalyst
    {
    private:
        CThostFtdcMdApi *_api;
        QOperatorMsg *_pOperaterMsg;
        QAccount* _pAccount;
        unsigned int requestId;

    public:
        QAnalyst(QOperatorMsg *pOperaterMsg, CThostFtdcMdSpi *spi, QAccount *pAccount);
        void init();
        void thread_main();
        void process_api_state(ApiState s);
        void reqConnect();
        void reqReConnect();
        void reqLogIn();
        void reqSubscribe();
        void record(CThostFtdcDepthMarketDataField *pDmd);
    };

}