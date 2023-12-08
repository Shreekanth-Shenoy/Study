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