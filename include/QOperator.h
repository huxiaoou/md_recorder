#include <string.h>
#include <mutex>
#include <condition_variable>
#include <queue>
#include "QNode.h"

namespace QUtility
{
    class OperatorMsg
    {
    private:
        char _label[60];
        std::queue<QUtility::MsgNode *> *_pQueue;
        std::mutex _mutex;
        std::condition_variable _cv;

    public:
        void Init(const char *label);
        size_t GetQueueSize() const { return _pQueue->size(); }
        void Push(QUtility::MsgNode *pNode);
        void GetFrontAndPop(QUtility::MsgNode *pNode);
        void Wait();
    };
}