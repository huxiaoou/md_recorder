#include "QAnalyst.h"

namespace QUtility
{
    QAnalyst::QAnalyst(QOperatorMsg *pOperaterMsg, CThostFtdcMdSpi *spi)
    {
        _api = CThostFtdcMdApi::CreateFtdcMdApi("../cons/");
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
                    std::cout << "ApiState = " << static_cast<unsigned>(s) << std::endl;
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
        char front_address[] = "tcp://116.236.253.145:42213";
        _api->RegisterFront(front_address);
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
        strcpy(req.BrokerID, "95533");
        strcpy(req.UserID, "51710159");
        strcpy(req.Password, "*******");
        _api->ReqUserLogin(&req, requestId++);
        std::cout << "... req to log in" << std::endl;
    }

    void QAnalyst::reqSubscribe()
    {
        char *contracts[3] = {(char *)"rb2505", (char *)"CF505", (char *)"m2405"};
        _api->SubscribeMarketData(contracts, 3);
        std::cout << "... req to subscribe" << std::endl;
    }

    void QAnalyst::record(CThostFtdcDepthMarketDataField *pDmd)
    {
        std::cout << pDmd->ActionDay << " "
                  << pDmd->InstrumentID << " "
                  << pDmd->LastPrice
                  << std::endl;
    }
}
