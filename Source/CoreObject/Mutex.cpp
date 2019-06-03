//
// Created by liuqian8 on 2019/6/3.
//
#include <pthread.h>
#include "Mutex.h"
Mutex::Mutex() :
        handle_(new pthread_mutex_t)
{
    pthread_mutex_t* mutex = (pthread_mutex_t*)handle_;
    //互斥锁的属性
    pthread_mutexattr_t attr;
    //函数成功完成后会返回0，其他任何返回值都表示出现了错误。函数成功执行后，互斥锁被初始化为未锁住状态
    pthread_mutexattr_init(&attr);
    //修改类型互斥量属性
    /*
     * PTHREAD_MUTEX_NORMAL
     *   这种类型的互斥锁不会自动检测死锁，如果一个线程试图对一个互斥锁重复锁定，将会引起这个线程的死锁，如果试图解锁一个由别的线程锁定的
     *   互斥锁会引发不可预料的结果。如果一个线程试图解锁已经被解锁的互斥锁也会发生不可预料的结果
     * PTHREAD_MUTEX_ERRORCHECK
     *   这种类型的互斥锁会自动检测死锁，如果一个线程试图对一个互斥锁重复锁定，将会返回一个错误代码。如果试图解锁一个由别的线程锁定的
     *   互斥锁将会返回一个错误代码。如果一个线程试图解锁已经被解锁的互斥锁也将会返回一个错误代码。
     * PTHREAD_MUTEX_RECURSIVE
     *   如果一个线程对这种类型的互斥锁重复上锁，不会引起死锁。一个线程对这种互斥锁多次重复上锁必须由这个线程来重复相同数量的解锁，这样
     *   才会解开这个互斥锁。别的线程才能得到这个互斥锁。如果试图解锁一个由别的线程锁定的互斥锁将会返回一个错误码。如果一个线程试图解锁
     *   已经被解锁的互斥锁也将会返回一个错误代码。这种类型的呼哧锁只能是进程私有的（作用域属性为PTHREAD_PROCESS_PRIVATE）
     * PTHREAD_MUTEX_DEFAULT
     *   这种类型的互斥锁不会自动检测死锁。如果一个线程试图对一个互斥锁重复锁定，将会引起不可预料的结果。如果试图解锁一个由别的线程锁定的互斥锁会
     *   引发不可预料的结果。如果一个线程试图解锁已经被解锁的互斥锁也会引发不可预料的结果。POSIX标准规定，对于某一具体的实现，可以把这种类型的
     *   互斥锁定义为其他类型的互斥锁
     */
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    //函数是以动态方式创建互斥锁的，参数atter指定了新建互斥锁的属性，如果为空，则使用默认的互斥锁属性，默认属性为快速互斥锁，window是迭代互斥锁。
    pthread_mutex_init(mutex, &attr);
    /*
     * 互斥锁需要注意的几点：
     * 1。互斥量需要时间来枷锁和解锁。锁住较少互斥量的程序通常运行的更快。所以，互斥量应该尽量少，够用即可，每个互斥量保护的区域应则尽量大。
     * 2。互斥量的本质是串行执行，如果很多线程需要频繁的加锁同一个互斥量，则线程大部分时间就会在等待，这对性能是由害的。如果互斥量保护的数据（或代码）
     * 包含彼此无关的片段，则可以特大的互斥量分解为几个小的互斥量来提高性能。这样，任意时刻需要小互斥量的线程减少，线程等待的时间就会减少。所以，互斥量应该足够多
     * （到有意义的地步），每个互斥量保护的区域则应尽量的少。
     */
}

Mutex::~Mutex()
{
    pthread_mutex_t* mutex = (pthread_mutex_t*)handle_;
    pthread_mutex_destroy(mutex);
    delete mutex;
    handle_ = 0;
}

void Mutex::Acquire()
{
    //互斥锁上锁，也就是获得互斥锁
    pthread_mutex_lock((pthread_mutex_t*)handle_);
}

bool Mutex::TryAcquire()
{
    //函数成功返回0。任何其他返回值都表示错误。函数pthread_mutex_trylock是pthread_mutex_lock的非阻塞版本。
    //如果mutex参数所指定的互斥锁已经被锁定的话，调用pthread_mutex_trylock函数不会阻塞当前线程，而是立即返回一个值来描述互斥锁的状况。
    return pthread_mutex_trylock((pthread_mutex_t*)handle_) == 0;
}

void Mutex::Release()
{
    //互斥锁解锁，也就是释放互斥锁
    pthread_mutex_unlock((pthread_mutex_t*)handle_);
}

MutexLock::MutexLock(Mutex& mutex) :
        mutex_(mutex)
{
    //互斥锁加锁，也就是获取互斥锁
    mutex_.Acquire();
}

MutexLock::~MutexLock()
{
    //互斥锁解锁，也就是释放互斥锁
    mutex_.Release();
}