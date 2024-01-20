#include <iostream>

using namespace std;


class Base{
    
  public: 
        
        Base(){
            cout<<"Base CTR"<<endl;
        }
        
        virtual ~Base(){                     //any virtual function madatory for dynamic cast
            cout<<"Base DTR"<<endl;
        }
};


class Derived1:public Base{
    
    public:
        Derived1(){
            cout<<"Derived1 CTR"<<endl;
        }
        ~Derived1(){
            cout<<"Derived1 DTR"<<endl;
        }
};

class Derived2:public Base{
    
    public:
        Derived2(){
            cout<<"Derived2 CTR"<<endl;
        }
        ~Derived2(){
            cout<<"Derived2 DTR"<<endl;
        }
};


int main()
{

    Base* derived1 = new Derived1();
    Base* base = derived1;
    Derived2* derived2 = dynamic_cast<Derived2*>(derived1);
  
    if(derived2)
    {
        cout<<"casting Succesful";
    }

    if(!derived2)
    {
        cout<<"casting not Succesful";
    }

    return 0;
}


// casting is not Succesful

//NOTE: if we used static cast here, casting would be successful (wrong behaviour)
