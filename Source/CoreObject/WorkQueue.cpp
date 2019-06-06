//
// Created by liuqian8 on 2019/6/6.
//
#include "WorkQueue.h"

WorkerThread::WorkerThread(WorkQueue *owner, unsigned index):
    owner_(owner),
    index_(index)
{

}

void WorkerThread::threadFunction()
{

}

ThreadID WorkerThread::getIndex()
{
    return index_;
}
