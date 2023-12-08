
#include <iostream>

using namespace std;

class Singleton{
    public:
    
        Singleton(const Singleton&)=delete; //Delete Copy constructor
        Singleton(Singleton&&) = delete;  // Delete move constructor
        Singleton& operator=(const Singleton&) = delete;
        static Singleton& Get(){
            static Singleton instance;
            return instance;
        }
        

        static void Print(){
           return Get().PrintImpl();
        }
        
        ~Singleton(){
            cout<<"DTR";
        }

    private: 
        void PrintImpl(){
            std::cout << "HELLO" << std::endl;
        }
        Singleton(){}
};


int main()
{

    Singleton& s = Singleton::Get() ;
    s.Print();
    
    Singleton::Print() ;
    

}
