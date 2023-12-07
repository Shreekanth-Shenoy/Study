#include <iostream>

using namespace std;
template<typename T , size_t S>
class Array{

    public:
        int Size() const{
            return S;
        }

        T& operator[](size_t index){
            return m_Data[index];
        }

        const T& operator[](size_t index) const {
            return m_Data[index];
        }
    private:
    T m_Data[S];
};


int main(){

    Array<int,5> data;
    cout<< data.Size()<<endl;

    for(int i=0;i<data.Size();i++){
        data[i]=i;
    }
    data[3]=100;
 

    const auto& constData = data; 
    for(int i=0;i<constData.Size();i++){
        cout<<constData[i]<<endl;
    }    
}