#pragma once

#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include "ThostFtdcMdApi.h"
#include "QOperator.h"
#include "QAccount.h"

namespace QUtility
{
    class QAnalyst
    {
    private:
        CThostFtdcMdApi *_api;
        CThostFtdcMdSpi *_spi;
        QOperatorMsg *_pOperaterMsg;
        QAccount *_pAccount;
        unsigned int requestId;

    public:
        QAnalyst(QOperatorMsg *pOperaterMsg, CThostFtdcMdSpi *spi, QAccount *pAccount);
        void go();
        void thread_quit();
        void thread_main();
        int process_api_state(ApiState s);
        void init();
        void reqConnect();
        void reqReConnect();
        void reqLogIn();
        void reqSubscribe();
        void record(CThostFtdcDepthMarketDataField *pDmd);
        void reqRelease();
    };

}