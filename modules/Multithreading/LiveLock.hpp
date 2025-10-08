#pragma once
#include <atomic>
#include <chrono>
#include <mutex>
#include <print>
#include <thread>

class LiveLock
{
    mutable std::mutex m1, m2;
    int numOfTask{0};

    void worker1()
    {
        while (numOfTask > 0)
        {
            m1.lock();
            if (not m2.try_lock())
            {
                m1.unlock();
                std::this_thread::yield();
            }
            else
            {
                m2.unlock();
                m1.unlock();

                if (numOfTask > 0)
                {
                    std::println("Worker 1 done task: {}", numOfTask--);
                }
            }
        }
    }
    void worker2()
    {
        while (numOfTask > 0)
        {
            m2.lock();
            if (not m1.try_lock())
            {
                m2.unlock();
                std::this_thread::yield();
            }
            else
            {
                std::println("Worker 2 done task: {}", numOfTask--);
                m1.unlock();
                m2.unlock();
            }
        }
    }

public:
    void demo(const int taskToDo)
    {
        numOfTask = taskToDo;
        std::thread w1([this]() { worker1(); });
        std::thread w2([this]() { worker2(); });
        w1.join();
        w2.join();
    }
};