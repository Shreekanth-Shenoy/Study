/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <cstring>
using namespace std;


class String
{

    public:
        String() = default;
        String(const char* string){
            cout<<"Created"<<endl;
            m_Size = strlen(string);
            m_Buffer = new char[m_Size];
            memcpy(m_Buffer,string,m_Size);
        }
        String(const String& other){
            cout<<"Copy"<<endl;
            m_Size = other.m_Size;
            m_Buffer = new char[m_Size];
            memcpy(m_Buffer,other.m_Buffer,m_Size);
        }
        String(String&& other){
            cout<<"Moved"<<endl;
            m_Buffer = other.m_Buffer;
            m_Size = other.m_Size;
            other.m_Buffer =nullptr;
            other.m_Size = 0;
        }
        ~String(){
            delete m_Buffer;
        }
        
        void print(){
        for(int i =0; i<m_Size;i++){
            cout<<m_Buffer[i];
        }
    }
    
    private:
        char* m_Buffer;
        int m_Size;
};


class Entity{
public:
    Entity()=default;
    Entity(const String& string):string(string){};
    Entity(String&& string):string(std::move(string)){};

    void print(){
        string.print();
    }

    private:
        String string;
};

int main()
{

    Entity e("Hello");
    e.print();
    return 0;
}
