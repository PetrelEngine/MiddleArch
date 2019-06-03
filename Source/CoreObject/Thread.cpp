//
// Created by liuqian8 on 2019/6/3.
//
#include "Thread.h"
static void* threadFunctionStatic(void* data)
{
    Thread* thread = static_cast<Thread*>(data);
    thread->threadFunction();
    pthread_exit((void*)0);
    return 0;
}

ThreadID Thread::mainThreadID;

Thread::Thread():
        handle_(NULL),
        shouldRun_(false)
{

}

Thread::~Thread()
{
    stop();
}

bool Thread::run()
{
    if(handle_)
        return false;
    shouldRun_ = true;

    handle_ = new pthread_t;
    pthread_attr_t type;
    pthread_attr_init(&type);
    /*
     *设置线程属性
     * 设置为PTHREAD_CREATE_DETACHED，以分离转台启动线程，一旦设置为该状态，则切换不回设置为PTHREAD_CREATE_JOINABLE状态
     * 设置为PTHREAD_CREATE_JOINABLE，正常启动线程。
     */
    pthread_attr_setdetachstate(&type, PTHREAD_CREATE_JOINABLE);
    //创建线程，创建成功则返回0，创建失败常见的错误代码为 #define   EAGAIN    35 （资源暂时不可用）
    //#define   EINVAL     22 参数无效
    //第一个参数为指向线程标识符的指针
    //第二个参数用来指定线程属性
    //第三个参数是线程运行函数的起始地址
    //第三个参数是运行函数的参数
    pthread_create((pthread_t*)handle_, &type, threadFunctionStatic,this);
    return  handle_ != nullptr;
}

void Thread::stop()
{
    if(!handle_)
        return;
    shouldRun_ = false;
    //拿到线程指针的句柄
    pthread_t* thread = (pthread_t*)handle_;
    //判空，防止出现不可预料结果
    if (thread)
    {
        /*
         * 线程创建为非分离状态，这种情况下啊，原油的线程等待创建的线程结束。只有当pthread_join()函数返回时，创建的线程才算终止，才能释放自己占用
         * 系统资源。
         * 而分离线程则 不是这个样子，它没有被其他的线程所等待，自己运行结束了，线程也就终止了，马上释放系统资源。
         */
        pthread_join(*thread, 0);//线程等待
    }

    delete thread;
    handle_ = nullptr;
}

void Thread::setPriority(int priority)
{
    pthread_t* thread = (pthread_t*)handle_;
    struct sched_param sched;
    if (thread){
        /*
         * 线程调度参数，pthread_attr_getschedparam和pthread_attr_setschedparam分别用来
         * 设置和得到线程的调度参数
         * 参数atter  线程属性变量
         * 参数param sched_param结构
         * 这两个函数具有两个参数，第一个参数是指向属性对象的指针，第二个参数是sched_param结构或指向该结构的指针。
         * sched_param在文件/usr/include/bits/sched.h中定义如下：
         * struct sched_param
         * {
         *    intsched_priority;
         * };
         * 结构sched_param的子成员sched_priority控制一个优先权值，大的优先权值对应高的优先权。系统支持的
         * 最大和最小的优先权值可以用sched_get_priority_max函数和sched_get_priority_min函数分别得到。
         * 注意：如果不是编写实时程序，不建议修改线程的优先级。因为，调度策略是一件非常复杂的事情，如果不正确使用会导致程序错误，从而导致死锁
         * 等问题。如：在多线程应用程序中为线程设置不用的优先级别，有可能因为共享资源而导致优先级倒置。
         *
         */
        pthread_setschedparam(*thread,priority,&sched);
    }

}

void Thread::setMainThread()
{
    mainThreadID = getCurrentThreadID();
}

ThreadID Thread::getCurrentThreadID()
{
    //获取线程的指针句柄id
    return pthread_self();
}

bool Thread::isMainThread()
{
    //判断是否是主线程，线程的指针句柄id对比
    return getCurrentThreadID() == mainThreadID;
}

void Thread::sleep(int sec, int nsec)
{
    struct timespec sleepTime;
    struct timespec returnTime;
    sleepTime.tv_sec = sec;
    sleepTime.tv_nsec = nsec;
    /*
     * sleep()是以秒为单位
     * usleep()是以微妙为单位
     * nanosleep(const struct timespec *req, struct timespec *rem)以纳秒为单位
     * struct timespec
     * {
     *   time_t  tv_sec;          秒seconds
     *   long    tv_nsec;         纳秒nanoseconds
     * }
     * 这个函数功能是暂停某个进程直到你规定的时间后回复，参数req就是你要暂停的时间，其中req->tv_sec是以秒为单位，
     * 而tv_nsec纳秒为单位。由于调用nanosleep是进程进入到TASK_INTERRUPTIBLE，这中状态是会相应信号而进入TASK_RUNNING状态的，
     * 这就意味着有可能会没有等到你规定的时间就因为其他信号而唤醒，此时函数返回-1，且还剩余的时间会被记录在rem中。
     * return：若进程暂停到参数*req所指定的时间，成功则返回0，若有幸好终端则返回-1，并且将余微妙记录在*rem中。
     */
    nanosleep(&sleepTime, &returnTime);
}

long long Thread::getCurrentTime()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (long long)tv.tv_sec * 1000 + (long long)tv.tv_usec / 1000;
}
