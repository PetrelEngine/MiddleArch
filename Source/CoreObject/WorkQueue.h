//
// Created by liuqian8 on 2019/6/5.
//
#pragma once
#include "Object.h"
#include <vector>
#include "Thread.h"
#include "Mutex.h"

class WorkQueue;
class WorkerThread:public Thread
{
public:
    WorkerThread(WorkQueue* owner, unsigned index);

    virtual void threadFunction();

    unsigned getIndex();

private:
    WorkQueue* owner_;
    unsigned index_;
};
struct WorkItem
{
    friend class WorkQueue;
public:
    WorkItem():
            priority_(0),
            sendEvent_(false),
            completed_(false),
            pooled_(false)
    {
    }
    void (* workFunction_)(const WorkItem*, unsigned);
    void* start_;
    void* end_;
    void* aux_;
    unsigned priority_;
    bool sendEvent_;
    volatile bool completed_;
private:
    bool pooled_;
};


//class WorkQueue:public Object
//{
//    ENGINE_OBJECT(WorkQueue,Object);
//public:
//    WorkQueue(Context* context);
//
//    virtual ~WorkQueue();
//
//    void createThreads(unsigned numThreads);
//
//    WorkItem getFreeItem();
//
//    void addWorkItem(WorkItem item);
//
//    bool removeWorkItem(WorkItem item);
//
//    unsigned removeWorkItems(const std::vector<WorkItem> item);
//
//    void pause();
//
//    void resume();
//
//    void complete(unsigned priority);

//private:
//    void processItems(unsigned threadIndex);
//
//    void purgeCompleted(unsigned priority);
//
//    void purgePool();
//
//    void returnToPool(WorkItem item);
//
//    std::vector<WorkerThread> threads_;
//    std::vector<WorkItem>   poolItems_;
//    std::vector<WorkItem*>  queue_;
//    Mutex                   queueMutex_;
//    volatile bool sutDown_;
//    volatile bool pausing_;
//    bool paused_;
//    bool completing_;
//    int tolerance_;
//    unsigned lastSize_;
//    int maxNonThreadWorkMs_;
//};
