//
// Created by liuqian8 on 2019/6/4.
//
#pragma once
#include "Common.h"
#include "Thread.h"
#include "Mutex.h"
#include <iostream>
#include <queue>

struct WorkItem
{
    queue<int>      buffer;
    Mutex*          wimutex;
    WorkerThread*   wiproducer;
    WorkerThread*   wiconsumer;
};

enum ThreadType
{
    Producer,
    Consumer
};

class WorkerThread:public Thread
{
public:
    WorkerThread(ThreadType type);

    virtual ~WorkerThread();

    virtual void threadFunction() override;

    void producer();

    void consumer();

    void setWorkItem(WorkItem workItem);
private:
    unsigned index_;
    ThreadType threadType_;
    WorkItem workItem_;
};

