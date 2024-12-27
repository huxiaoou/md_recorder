#pragma once
#include <queue>
#include <variant>
#include "ThostFtdcUserApiStruct.h"

namespace QUtility
{
    //  ------ Node definition 0: API state for trader-api and md-api ------
    enum class ApiState
    {
        READY,
        CONNECTED,
        AUTHENTICATED,
        LOGGED_IN,
        SETTLEMENT_QUERIED,
        SETTLEMENT_CONFIRMED,
        TRADING_ACCOUNT_CONFIRMED,
        ALL_INQUIRED_CONTRACTS_RECEIVED,
        DISCONNECTED
    };

    //  ------ Node definition 1: frontId and sessionId ------
    class FrtSessId
    {
    private:
        TThostFtdcFrontIDType _frontId;
        TThostFtdcSessionIDType _sessionId;

    public:
        FrtSessId(TThostFtdcFrontIDType frontId, TThostFtdcSessionIDType sessionId) : _frontId(frontId), _sessionId(sessionId) {}
        const TThostFtdcFrontIDType GetFrontId() const { return _frontId; }
        const TThostFtdcSessionIDType GetSessionId() const { return _sessionId; }
    };

    // using std::variant
    typedef std::variant<ApiState, FrtSessId, CThostFtdcDepthMarketDataField*> MsgNode;
    typedef std::queue<MsgNode *> QueueMsg;
}
