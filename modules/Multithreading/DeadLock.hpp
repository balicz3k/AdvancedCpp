#pragma once

#include <chrono>
#include <mutex>
#include <print>
#include <thread>

class DeadLock
{
    mutable std::mutex m1, m2;

    void task1() const
    {
        std::lock_guard g1(m1);
        std::this_thread::sleep_for(std::chrono::milliseconds(25u));
        std::lock_guard g2(m2);
        std::println("Task 1 done!");
    }
    void task2() const
    {
        std::lock_guard g1(m2);
        std::this_thread::sleep_for(std::chrono::milliseconds(25u));
        std::lock_guard g2(m1);
        std::println("Task 2 done!");
    }

public:
    void demo()
    {
        std::thread t1(&DeadLock::task1, this);
        std::thread t2(&DeadLock::task2, this);
        t1.join();
        t2.join();
    }
};