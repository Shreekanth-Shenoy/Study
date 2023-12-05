#include <iostream>
#include <thread>
#include <mutex>
#include <deque>
#include <condition_variable>

class Buffer {
public:
    Buffer() : maxBufferSize(50) {}

    void produce(int val) {
        while (val) {
            std::unique_lock<std::mutex> locker(mu);
            cond.wait(locker, [this](){return buffer.size() < maxBufferSize;});
            buffer.push_back(val);
            std::cout << "Produced: " << val << std::endl;
            val--;
            locker.unlock();
            cond.notify_one();
        }
    }

    void consume() {
        while (true) {
            std::unique_lock<std::mutex> locker(mu);
            cond.wait(locker, [this](){return buffer.size() > 0;});
            int val = buffer.back();
            buffer.pop_back();
            std::cout << "Consumed: " << val << std::endl;
            locker.unlock();
            cond.notify_one();
        }
    }

private:
    std::mutex mu;
    std::condition_variable cond;
    std::deque<int> buffer;
    const unsigned int maxBufferSize;
};

int main() {
    Buffer bufferObj;

    std::thread t1(&Buffer::produce, &bufferObj, 100);
    std::thread t2(&Buffer::consume, &bufferObj);

    t1.join();
    t2.join();

    return 0;
}
