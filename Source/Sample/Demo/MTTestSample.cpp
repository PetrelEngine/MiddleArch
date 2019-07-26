//
// Created by liuqian8 on 2019/6/3.
//
#include "MTTestSample.h"
MTTestSample::MTTestSample():
        producer(NULL),
        consumer(NULL),
        mutex_(NULL)
{

}

MTTestSample::~MTTestSample()
{
    if(producer)
    {
        delete producer;
        producer = NULL;
    }

    if(consumer)
    {
        delete consumer;
        consumer = NULL;
    }

    if(mutex_)
    {
        delete mutex_;
        mutex_ = NULL;
    }
}

void MTTestSample::CreateScence(Context *context, int width, int height)
{
    queue<int> buffer;
    producer = new TestWorkerThread(Producer);
    consumer = new TestWorkerThread(Consumer);
    mutex_ = new Mutex();

    WorkItem workItem;
    workItem.wimutex = mutex_;
    workItem.buffer = buffer;
    workItem.wiconsumer = consumer;
    workItem.wiproducer = producer;

    producer->setWorkItem(workItem);
    consumer->setWorkItem(workItem);

    producer->run();
    consumer->run();

    producer->stop();
    consumer->stop();
}

void MTTestSample::RenderOneFrame(Context *context)
{

}

void MTTestSample::Move()
{

}
