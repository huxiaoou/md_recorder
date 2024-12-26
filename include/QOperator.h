#include <string.h>
#include <mutex>
#include <condition_variable>
#include <queue>
#include "QNode.h"

namespace QUtility
{
    class TOperator
    {
    private:
        char m_queue_label[60];
        std::queue<QUtility::MsgNode *> *m_pQueue;
        std::mutex m_mutex;
        std::condition_variable m_cond_var;

    public:
        void Init(const char *t_queue_label);
        size_t GetQueueSize() const { return m_pQueue->size(); }
        void PushState(QUtility::MsgNode *t_pNode);
        void GetFrontAndPop(QUtility::MsgNode *t_pNode);
        void Wait();
    };

    void TOperator::Init(const char *t_queue_label)
    {
        strcpy(m_queue_label, t_queue_label);
        m_pQueue = new std::queue<QUtility::MsgNode *>;
    }

    void TOperator::PushState(QUtility::MsgNode *t_pNode)
    {
        std::unique_lock<std::mutex> lck(m_mutex);
        m_pQueue->push(t_pNode);
        m_cond_var.notify_all();
    }

    void TOperator::GetFrontAndPop(QUtility::MsgNode *t_pNode)
    {
        std::unique_lock<std::mutex> lck(m_mutex);
        t_pNode = m_pQueue->front();
        m_pQueue->pop();
    }

    void TOperator::Wait()
    {
        std::unique_lock<std::mutex> lck(m_mutex);
        m_cond_var.wait(lck);
    }
}