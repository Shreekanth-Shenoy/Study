#include<iostream>
#include <cstring>
#include <vector>
using namespace std;



/* using pointer
class Entity{
  static Entity* instance;
  
public:

  static Entity* getInstance() {
        if (!instance) {
            instance = new Entity();
        }
        return instance;
    }
};
Entity* Entity::instance = nullptr;

int main(){
    Entity* entity1 = Entity::getInstance();
    Entity* entity2 = Entity::getInstance();
    cout<< entity1 <<endl;
    cout<< entity2 <<endl;

}
*/



/* using reference
class Entity{
  static Entity* instance;
  
public:
 static Entity& getInstance() {
        if (!instance) {
            instance = new Entity();
        }
        return *instance;
    }
};
Entity* Entity::instance = nullptr;

int main(){
    Entity& entity1 = Entity::getInstance();
    Entity& entity2 = Entity::getInstance();
    cout<< &entity1 <<endl;
    cout<< &entity2 <<endl;

}
*/


//using static member
class Entity{
public:
 static Entity& getInstance() {
        static Entity instance;
        return instance;
    }
};

int main(){
    Entity& entity1 = Entity::getInstance();
    Entity& entity2 = Entity::getInstance();
    cout<< &entity1 <<endl;
    cout<< &entity2 <<endl;

}

