//
// Created by liuqian8 on 2019/6/4.
//
#pragma once
#include "Common.h"
#include "Thread.h"
#include "Mutex.h"
#include <iostream>
#include <queue>

class TestWorkerThread;
enum ThreadType
{
    Producer,
    Consumer
};

struct WorkItem
{
    queue<int>      buffer;
    Mutex*          wimutex;
    TestWorkerThread*   wiproducer;
    TestWorkerThread*   wiconsumer;
};

class TestWorkerThread:public Thread
{
public:
    TestWorkerThread(ThreadType type);

    virtual ~TestWorkerThread();

    virtual void threadFunction() override;

    void producer();

    void consumer();

    void setWorkItem(WorkItem workItem);
private:
    unsigned index_;
    ThreadType threadType_;
    WorkItem workItem_;
};

