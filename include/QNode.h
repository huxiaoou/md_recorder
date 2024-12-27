#pragma once
#include <queue>
#include "ThostFtdcUserApiStruct.h"

namespace QUtility
{
    class MsgNode
    {
    public:
        virtual ~MsgNode() = default;
    };

    //  ------ Node definition 0: API state for trader-api and md-api ------
    enum class ValApiState
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
    class MsgNodeApiState : public MsgNode
    {
    private:
        ValApiState _valApiState;

    public:
        MsgNodeApiState(ValApiState valApiState) : _valApiState(valApiState) {}
    };

    //  ------ Node definition 1: frontId and sessionId ------
    class MsgNodeFrtSessId : public MsgNode
    {
    private:
        TThostFtdcFrontIDType _frontId;
        TThostFtdcSessionIDType _sessionId;

    public:
        MsgNodeFrtSessId(TThostFtdcFrontIDType frontId, TThostFtdcSessionIDType sessionId) : _frontId(frontId), _sessionId(sessionId) {}
        void SetValue(TThostFtdcFrontIDType frontId, TThostFtdcSessionIDType sessionId);
        const TThostFtdcFrontIDType GetFrontId() const { return _frontId; }
        const TThostFtdcSessionIDType GetSessionId() const { return _sessionId; }
    };

    typedef std::queue<MsgNode *> QueueMsg;
}
