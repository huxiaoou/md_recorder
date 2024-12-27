#include "QOperator.h"

namespace QUtility
{
    QOperatorMsg::QOperatorMsg(const char *label)
    {
        strcpy(_label, label);
        _pQueue = new std::queue<QUtility::MsgNode *>;
    }

    void QOperatorMsg::Push(QUtility::MsgNode *pNode)
    {
        std::unique_lock<std::mutex> lck(_mutex);
        _pQueue->push(pNode);
        _cv.notify_all();
    }

    void QOperatorMsg::GetFrontAndPop(QUtility::MsgNode *pNode)
    {
        std::unique_lock<std::mutex> lck(_mutex);
        pNode = _pQueue->front();
        _pQueue->pop();
    }

    void QOperatorMsg::Wait()
    {
        std::unique_lock<std::mutex> lck(_mutex);
        _cv.wait(lck);
    }
}