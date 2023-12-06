#include <iostream>
using namespace std;

void getValue(int& num){
    cout<<num<<endl;
    return;
}
void getValue(int&& num){   //ravlue
    cout<<num<<endl;
    return;
}

int main()
{
    int a =10;
    getValue(a);
    getValue(10);  //rvalue
    return 0;
}
