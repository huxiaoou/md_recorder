#pragma once
#include <string.h>
#include <mutex>
#include <condition_variable>
#include "QNode.h"

namespace QUtility
{
    class QOperatorMsg
    {
    private:
        char _label[60];
        QueueMsg *_pQueue;
        std::mutex _mutex;
        std::condition_variable _cv;

    public:
        QOperatorMsg(const char* label);
        size_t GetSize() const { return _pQueue->size(); }
        void Push(QUtility::MsgNode *pNode);
        QUtility::MsgNode * GetFrontAndPop();
        void Wait();
    };
}