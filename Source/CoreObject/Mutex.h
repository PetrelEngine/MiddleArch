//
// Created by liuqian8 on 2019/6/3.
//
#pragma once

class Mutex
{
public:
    /// 构造方法
    Mutex();
    /// 析构方法
    ~Mutex();

    /// 获得互斥锁。
    void Acquire();
    /// 尝试在不锁定的情况下获得互斥锁。如果成功返回true
    bool TryAcquire();
    /// 析构释放互斥锁。Release the mutex.
    void Release();

private:
    ///互斥锁的句柄
    void* handle_;
};

class MutexLock
{
public:
    ///构造并获取呼哧锁
    MutexLock(Mutex& mutex);
    /// 析构并释放互斥锁
    ~MutexLock();

private:
    /// 防止复制构造,重载这些操作符是防止非法的进行构造一个互斥量造成不可预料的结果
    MutexLock(const MutexLock& rhs);
    /// 防止重载运算符=复制构造
    MutexLock& operator =(const MutexLock& rhs);

    ///互斥锁指针
    Mutex& mutex_;
};
