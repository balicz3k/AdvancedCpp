#pragma once

#include <algorithm>
#include <functional>
#include <future>
#include <numeric>
#include <print>
#include <thread>
#include <vector>

class DataSharing
{
    static int calculateSum(const std::vector<int> &v, int &result)
    {
        result = std::accumulate(v.begin(), v.end(), result);
        return -1; // return value is never used
    }

public:
    static void dataSharedAsReferenceDemo()
    {
        std::vector<int> data = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        int sum{0};
        std::thread t1(&DataSharing::calculateSum, std::move(data), std::ref(sum));
        t1.join();
        std::println("Sum of data: {} is : {}", data, sum); // data is null  because of used move

        data = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        sum = 0;
        std::thread t2(&DataSharing::calculateSum, std::ref(data), std::ref(sum));
        t2.join();
        std::println("Sum of data: {} is : {}", data, sum);
    }
    static void dataSharedByFuturePromise()
    {
        std::vector<int> data = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

        std::promise<int> sum_promise;

        std::future<int> sum_future = sum_promise.get_future();

        std::thread t1(
            [](std::promise<int> p, const std::vector<int> &v) {
                try
                {
                    int sum = std::accumulate(v.begin(), v.end(), 0);
                    // auto doException{v.at(-1)}; to check  how handling exception by promise works
                    p.set_value(sum);
                }
                catch (...)
                {
                    p.set_exception(std::current_exception());
                }
            },
            std::move(sum_promise), data);

        try
        {
            int result = sum_future.get();
            std::println("Sum of data: {} is : {}", data, result);
        }
        catch (const std::exception &e)
        {
            std::println("Exception {}", e.what());
        }

        t1.join();
    }
};
