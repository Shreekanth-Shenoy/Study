/*

#include<iostream>
using namespace std;

class FlyingStrategy{
public:
    virtual void fly() const = 0;

};

class QuackingStrategy{
public:
    virtual void quack() const =0;

};

class SimpleFlyingStrategy: public FlyingStrategy{
public:
    void fly() const override{
        cout<<"SimpleFlyingStrategy"<<endl;
    }
};

class NoFlyingStrategy : public FlyingStrategy{
public:
    void fly() const override{
        cout<<"NoFlyingStrategy"<<endl;
    }
};

class SimpleQuackingStrategy: public QuackingStrategy{
public:
    void quack() const override{
        cout<<"SimpleFlyingStrategy"<<endl;
    }
};

class MuteQuackingStrategy: public QuackingStrategy{
public:
    void quack() const override{
        cout<<"MuteQuackingStrategy"<<endl;
    }
};

class Duck{
private:
    FlyingStrategy* _flyingStrategy;
    QuackingStrategy* _quackingStrategy;

public:
    Duck(FlyingStrategy* flyingStrategy ,QuackingStrategy* quackingStrategy ):_flyingStrategy(flyingStrategy),_quackingStrategy(quackingStrategy){};
    void performFly() const{
        _flyingStrategy->fly();
    }
    void performQuack() const{
        _quackingStrategy->quack();
    }
    ~Duck() {                         //Need to b eexplicit to avoid memory leak
        delete _flyingStrategy;
        delete _quackingStrategy;
    }
};


int main(){
    Duck wildDuck(new SimpleFlyingStrategy(), new SimpleQuackingStrategy());
    Duck domesticDuck(new NoFlyingStrategy(), new MuteQuackingStrategy());
   
    wildDuck.performFly();
    wildDuck.performQuack();


    domesticDuck.performFly();
    domesticDuck.performQuack();
}

*/

//using unique pointer to avoid explict destructors 


#include<iostream>
#include <memory>
using namespace std;

class FlyingStrategy{
public:
    virtual void fly() const = 0;

};

class QuackingStrategy{
public:
    virtual void quack() const =0;

};

class SimpleFlyingStrategy: public FlyingStrategy{
public:
    void fly() const override{
        cout<<"SimpleFlyingStrategy"<<endl;
    }
};

class NoFlyingStrategy : public FlyingStrategy{
public:
    void fly() const override{
        cout<<"NoFlyingStrategy"<<endl;
    }
};

class SimpleQuackingStrategy: public QuackingStrategy{
public:
    void quack() const override{
        cout<<"SimpleFlyingStrategy"<<endl;
    }
};

class MuteQuackingStrategy: public QuackingStrategy{
public:
    void quack() const override{
        cout<<"MuteQuackingStrategy"<<endl;
    }
};

class Duck{
private:
    std::unique_ptr<FlyingStrategy> _flyingStrategy;
    std::unique_ptr<QuackingStrategy> _quackingStrategy;

public:
    Duck(std::unique_ptr<FlyingStrategy> flyingStrategy ,std::unique_ptr<QuackingStrategy> quackingStrategy ):
                    _flyingStrategy((std::move(flyingStrategy))),_quackingStrategy(std::move(quackingStrategy)){};
    void performFly() const{
        _flyingStrategy->fly();
    }
    void performQuack() const{
        _quackingStrategy->quack();
    }

    //~Duck() {                         //Not needed as we use smart pointers
    //    delete _flyingStrategy;
    //    delete _quackingStrategy;
    //}
};


int main(){

    Duck wildDuck(std::make_unique<SimpleFlyingStrategy>(), std::make_unique<SimpleQuackingStrategy>());
    Duck domesticDuck(std::make_unique<NoFlyingStrategy>(), std::make_unique<MuteQuackingStrategy>());

    wildDuck.performFly();
    wildDuck.performQuack();

    domesticDuck.performFly();
    domesticDuck.performQuack();
}




//using shared ptr, we need not use move

/*
#include<iostream>
#include<memory>
using namespace std;

class FlyingStrategy {
public:
    virtual void fly() const = 0;
};

class QuackingStrategy {
public:
    virtual void quack() const = 0;
};

class SimpleFlyingStrategy : public FlyingStrategy {
public:
    void fly() const override {
        cout << "SimpleFlyingStrategy" << endl;
    }
};

class NoFlyingStrategy : public FlyingStrategy {
public:
    void fly() const override {
        cout << "NoFlyingStrategy" << endl;
    }
};

class SimpleQuackingStrategy : public QuackingStrategy {
public:
    void quack() const override {
        cout << "SimpleQuackingStrategy" << endl;
    }
};

class MuteQuackingStrategy : public QuackingStrategy {
public:
    void quack() const override {
        cout << "MuteQuackingStrategy" << endl;
    }
};

class Duck {
private:
    std::shared_ptr<FlyingStrategy> _flyingStrategy;
    std::shared_ptr<QuackingStrategy> _quackingStrategy;

public:
    Duck(std::shared_ptr<FlyingStrategy> flyingStrategy, std::shared_ptr<QuackingStrategy> quackingStrategy)
        : _flyingStrategy(flyingStrategy), _quackingStrategy(quackingStrategy) {}

    void performFly() const {
        _flyingStrategy->fly();
    }

    void performQuack() const {
        _quackingStrategy->quack();
    }
};

int main() {
    Duck wildDuck(std::make_shared<SimpleFlyingStrategy>(), std::make_shared<SimpleQuackingStrategy>());
    Duck domesticDuck(std::make_shared<NoFlyingStrategy>(), std::make_shared<MuteQuackingStrategy>());

    wildDuck.performFly();
    wildDuck.performQuack();

    domesticDuck.performFly();
    domesticDuck.performQuack();

    return 0;
}

*/




/* CHATGPT SUMMARY

The Strategy Pattern is a behavioral design pattern that defines a family of algorithms, encapsulates each algorithm, and makes them interchangeable. It allows the client to choose the appropriate algorithm at runtime.

In this example:

FlyingStrategy and QuackingStrategy are the strategies:

FlyingStrategy is an interface that defines the fly method, which is then implemented by concrete classes like SimpleFlyingStrategy and NoFlyingStrategy.
QuackingStrategy is an interface that defines the quack method, implemented by SimpleQuackingStrategy and MuteQuackingStrategy.
Duck class uses strategies:

The Duck class has two private member variables, _flyingStrategy and _quackingStrategy, which are pointers to the FlyingStrategy and QuackingStrategy interfaces, respectively.
The Duck constructor allows the client to pass different strategies at runtime.
The performFly and performQuack methods of the Duck class delegate the corresponding behavior to the associated strategies.
Client code creates instances of Duck with different strategies:

In the main function, you create instances of Duck (wildDuck and domesticDuck) with different combinations of flying and quacking strategies.
This adheres to the principles of the Strategy Pattern, allowing you to encapsulate and interchange strategies dynamically. It promotes flexibility and makes it easy to extend or modify the behavior of a class without altering its source code.


*/