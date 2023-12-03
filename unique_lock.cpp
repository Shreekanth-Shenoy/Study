#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>

using namespace std;

condition_variable cv;
mutex m;
long balance=0;

void addMoney(int money){
    m.lock();
    balance+=money;
    cout<<"amount added "<<balance<<endl;
    m.unlock();

    cv.notify_all();
}

void withDrawMoney(int money){
    unique_lock<mutex> ul(m);
    cv.wait(ul,[]{return (balance!=0)?true:false;});
    if(balance>=money){
        balance-=money;
        cout<<"amount deducted "<<money<<endl;
    }
    else{
        cout<< " Amount connot be deducted current balance less than "<<money<<endl;
    }
    cout<<"Current balance is "<<balance<<endl;
}


int main(){
    thread t1(withDrawMoney,500);
    thread t2(addMoney,500);

    thread t3(withDrawMoney,500);
    thread t4(addMoney,500);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

}



/*

Comparison:
notify_one: Wakes up one randomly selected thread that is currently waiting on the condition variable.

notify_all: Wakes up all threads currently waiting on the condition variable.

Choosing Between notify_one and notify_all:

Use notify_one when you know that only one waiting thread needs to be notified, and waking up one thread is sufficient.

Use notify_all when multiple threads may need to proceed, and waking up all waiting threads is necessary (for example, in a broadcast scenario).

Note: Overusing notify_all can lead to performance issues, as it can potentially wake up more threads than necessary. It's generally more efficient to use notify_one unless there's a specific reason to wake up all waiting threads.

*/

