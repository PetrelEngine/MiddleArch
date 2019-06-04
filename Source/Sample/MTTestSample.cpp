//
// Created by liuqian8 on 2019/6/3.
//
#include "MTTestSample.h"
MTTestSample::MTTestSample()
{

}

MTTestSample::~MTTestSample()
{

}

void MTTestSample::CreateScence(Context *context, int width, int height)
{
    queue<int> buffer;
    producer = new WorkerThread(Producer);
    consumer = new WorkerThread(Consumer);
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
