/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <thread>
#include <mutex>
#include <deque>
#include <condition_variable>

using namespace std;



class Buffer{
public:    
    Buffer(int size):maxBufferSize(size){}
    
    void producer(int val){
        while(val){
            std::unique_lock<std::mutex> locker(mu); 
            cond.wait(locker,[this](){return buffer.size()<maxBufferSize;});
            buffer.push_back(101-val);
            cout<<"produced "<<(101-val)<<endl;
            val--;
            locker.unlock();
            cond.notify_one();
        }    
    }
    void consumer(){
        
        while(true){
            std::unique_lock<std::mutex> locker(mu);
            cond.wait(locker,[this](){return buffer.size()>0;});
            int val = buffer.front();
            buffer.pop_front();
            cout<<"Consumed "<<val<<endl;
            locker.unlock();
            cond.notify_one();
        }
    }
    
    
    private:
        std::mutex mu;
        std::condition_variable cond;
        std::deque<int> buffer;
        int maxBufferSize;
};



int main()
{
    Buffer bufferObj(10);
    
    std::thread t1(&Buffer::producer, &bufferObj,100);
    std::thread t2(&Buffer::consumer, &bufferObj);
    t1.join();
    t2.join();

    return 0;
}
