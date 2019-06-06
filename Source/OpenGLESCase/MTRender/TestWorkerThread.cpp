//
// Created by liuqian8 on 2019/6/4.
//
#include "TestWorkerThread.h"
TestWorkerThread::TestWorkerThread(ThreadType type)
{
    threadType_ = type;
}

TestWorkerThread::~TestWorkerThread()
{

}

void TestWorkerThread::threadFunction()
{
    if(threadType_ == Producer)
        producer();
    else
        consumer();
}

void TestWorkerThread::setWorkItem(WorkItem workItem)
{
    workItem_ = workItem;
}

void TestWorkerThread::consumer()
{
    while(true)
    {
        sleep(1,1);
        workItem_.wimutex->Acquire();
        LOGE("=> consumer 消费 开始:%d",workItem_.buffer.size());
        if(workItem_.buffer.size() > 0)
            workItem_.buffer.pop();
        LOGE("=> consumer 消费 结束:%d",workItem_.buffer.size());
        workItem_.wiproducer->setWorkItem(workItem_);
        workItem_.wimutex->Release();
    }
}

void TestWorkerThread::producer()
{
    while(true)
    {
        sleep(1,1);
        workItem_.wimutex->Acquire();
        LOGE("=> producer 生产 开始:%d",workItem_.buffer.size());
        workItem_.buffer.push(1);
        workItem_.wiconsumer->setWorkItem(workItem_);
        LOGE("=> producer 生产 结束:%d",workItem_.buffer.size());
        workItem_.wimutex->Release();
    }
}
