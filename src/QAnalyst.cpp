#include "QAnalyst.h"

namespace QUtility
{
    QAnalyst::QAnalyst(QOperatorMsg *pOperaterMsg, CThostFtdcMdSpi *spi, Account *pAccount)
    {
        _pAccount = pAccount;
        _api = CThostFtdcMdApi::CreateFtdcMdApi(_pAccount->GetConsPath());
        _api->RegisterSpi(spi);
        _pOperaterMsg = pOperaterMsg;
        requestId = 0;
    }

    void QAnalyst::init()
    {
        reqConnect();
        _api->Init();
    }

    void QAnalyst::thread_main()
    {
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
                    process_api_state(s);
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

    void QAnalyst::process_api_state(ApiState s)
    {
        switch (s)
        {
        case ApiState::DISCONNECTED:
            reqReConnect();
            break;
        case ApiState::CONNECTED:
            reqLogIn();
            break;
        case ApiState::LOGGED_IN:
            reqSubscribe();
            break;
        default:
            break;
        }
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
        std::cout << "| "
                  << pDmd->ActionDay << " | "
                  << pDmd->TradingDay << " | "
                  << pDmd->UpdateTime << " | "
                  << std::setw(3) << pDmd->UpdateMillisec << " | "
                  << std::setw(6) << pDmd->InstrumentID << " | "
                  << std::setw(8) << pDmd->LastPrice << " |"
                  << std::endl;
    }
}
