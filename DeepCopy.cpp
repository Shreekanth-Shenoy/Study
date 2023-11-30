#include<iostream>
#include <cstring>

using namespace std;


class String{
    
    private: 
      char* m_Buffer;
      unsigned int m_Size;
    public:
      String(const char* string){
        m_Size = strlen(string);
        m_Buffer = new char[m_Size+1];
        memcpy(m_Buffer,string,m_Size); 
        m_Buffer[m_Size]=0;
      }
      String(const String& string):m_Size(string.m_Size){
        m_Buffer = new char[m_Size+1];
        memcpy(m_Buffer,string.m_Buffer,m_Size+1); 

      }
      
      ~String(){
        delete[] m_Buffer;
      }
      
      char& operator[](unsigned index){
        
        return m_Buffer[index];
      }
      
      friend ostream& operator<<(ostream& stream, const String& string);
};

ostream& operator<<(ostream& stream, const String& string){
  stream<<string.m_Buffer;
  return stream;
}

int main(){

  String string = "Cherno";
  String second = string;
  
  second[2] ='W';
  cout<<string<<endl;
  cout<<second<<endl;
}
