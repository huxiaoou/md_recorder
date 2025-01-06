#include "QAnalyst.h"

namespace QUtility
{
    QAnalyst::QAnalyst(
        QOperatorMsg *pOperaterMsg,
        CThostFtdcMdSpi *spi,
        QAccount *pAccount,
        const QSection *pSection)
    {
        _pAccount = pAccount;
        _api = CThostFtdcMdApi::CreateFtdcMdApi(_pAccount->GetConsPath());
        _api->RegisterSpi(spi);
        _spi = spi;
        _pOperaterMsg = pOperaterMsg;
        _section = pSection;
        requestId = 0;
    }

    void QAnalyst::go()
    {
        std::thread tMain(&QAnalyst::thread_main, this);
        std::thread tQuit(&QAnalyst::thread_quit, this);
        tMain.join();
        tQuit.join();
    }

    void QAnalyst::thread_quit()
    {
        while (true)
        {
            QTimestamp tp;
            std::cout << "... " << tp << ": check for quit" << std::endl;
            if (tp >= *_section->GetEnd())
            {
                MsgNode *x = new MsgNode(ApiState::QUIT);
                _pOperaterMsg->Push(x);
                return;
            }
            std::this_thread::sleep_for(std::chrono::seconds(180));
        }
    }

    void QAnalyst::thread_main()
    {
        init();
        while (true)
        {
            if (_pOperaterMsg->GetSize() == 0)
                _pOperaterMsg->Wait();
            if (_pOperaterMsg->GetSize() > 0)
            {
                MsgNode *x = _pOperaterMsg->GetFrontAndPop();
                if (std::holds_alternative<ApiState>(*x))
                {
                    ApiState s = std::get<ApiState>(*x);
                    if (process_api_state(s) == -1)
                        break;
                }
                else if (std::holds_alternative<FrtSessId>(*x))
                {
                    std::cout << "holds front and session id" << std::endl;
                }
                else if (std::holds_alternative<CThostFtdcDepthMarketDataField *>(*x))
                {
                    CThostFtdcDepthMarketDataField *pDmd = std::get<CThostFtdcDepthMarketDataField *>(*x);
                    record(pDmd);
                }
                else
                {
                    std::cout << "invalid type of MsgNode" << std::endl;
                }
                delete x;
            }
        }
        _api->Join();
    }

    int QAnalyst::process_api_state(ApiState s)
    {
        switch (s)
        {
        case ApiState::DISCONNECTED:
            reqReConnect();
            return 0;
        case ApiState::CONNECTED:
            reqLogIn();
            return 0;
        case ApiState::LOGGED_IN:
            reqSubscribe();
            return 0;
        case ApiState::QUIT:
            reqRelease();
            return -1;
        default:
            return 0;
        }
    }

    void QAnalyst::init()
    {
        reqConnect();
        _api->Init();
    }

    void QAnalyst::reqConnect()
    {
        _api->RegisterFront(_pAccount->GetFrntAddr());
        std::cout << "... req to connect" << std::endl;
    }

    void QAnalyst::reqReConnect()
    {
        std::cout << "... disconnected from front, md-api will try to reconnect automatically" << std::endl;
    }

    void QAnalyst::reqLogIn()
    {
        CThostFtdcReqUserLoginField req;
        memset(&req, 0, sizeof(req));
        strcpy(req.BrokerID, _pAccount->GetBrokerID());
        strcpy(req.UserID, _pAccount->GetInvstrID());
        strcpy(req.Password, _pAccount->GetPassword());
        _api->ReqUserLogin(&req, requestId++);
        std::cout << "... req to log in" << std::endl;
    }

    void QAnalyst::reqSubscribe()
    {
        char *contracts[9] = {
            (char *)"rb2505",
            (char *)"hc2505",
            (char *)"ru2505",
            (char *)"CF505",
            (char *)"SR505",
            (char *)"TA505",
            (char *)"y2505",
            (char *)"m2505",
            (char *)"p2505",
        };
        _api->SubscribeMarketData(contracts, 9);
        std::cout << "... req to subscribe" << std::endl;
    }

    void QAnalyst::record(CThostFtdcDepthMarketDataField *pDmd)
    {
        // std::cout << "| "
        //           << pDmd->ActionDay << " | "
        //           << pDmd->TradingDay << " | "
        //           << pDmd->UpdateTime << " | "
        //           << std::setw(3) << pDmd->UpdateMillisec << " | "
        //           << std::setw(6) << pDmd->InstrumentID << " | "
        //           << std::setw(8) << pDmd->LastPrice << " |"
        //           << std::endl;
    }

    void QAnalyst::reqRelease()
    {
        if (_api)
        {
            _api->RegisterSpi(NULL);
            _api->Release();
            _api = NULL;
        }
        if (_spi)
        {
            delete _spi;
            _spi = NULL;
        }
        std::cout << "... req to release" << std::endl;
    }
}
