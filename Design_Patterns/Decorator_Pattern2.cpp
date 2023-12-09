#include <iostream>
#include <memory>

// Component interface
class Coffee {
public:
    virtual ~Coffee() = default;
    virtual void brew() const = 0;
};

// Concrete component
class SimpleCoffee : public Coffee {
public:
    void brew() const override {
        std::cout << "Brewing a simple coffee" << std::endl;
    }
};

// Decorator base class
class CoffeeDecorator : public Coffee {
protected:
    std::unique_ptr<Coffee> coffee;

public:
    CoffeeDecorator(std::unique_ptr<Coffee> coffee) : coffee(std::move(coffee)) {}
    void brew() const override {
        coffee->brew();
    }
};

// Concrete decorator 1
class MilkDecorator : public CoffeeDecorator {
public:
    MilkDecorator(std::unique_ptr<Coffee> coffee) : CoffeeDecorator(std::move(coffee)) {}
    void brew() const override {
        CoffeeDecorator::brew();
        addMilk();
    }

private:
    void addMilk() const {
        std::cout << "Adding milk" << std::endl;
    }
};

// Concrete decorator 2
class SugarDecorator : public CoffeeDecorator {
public:
    SugarDecorator(std::unique_ptr<Coffee> coffee) : CoffeeDecorator(std::move(coffee)) {}
    void brew() const override {
        CoffeeDecorator::brew();
        addSugar();
    }

private:
    void addSugar() const {
        std::cout << "Adding sugar" << std::endl;
    }
};

int main() {
    // Creating a simple coffee
    std::unique_ptr<Coffee> simpleCoffee = std::make_unique<SimpleCoffee>();
    simpleCoffee->brew(); // Output: Brewing a simple coffee

    // Decorating with milk
    std::unique_ptr<Coffee> milkCoffee = std::make_unique<MilkDecorator>(std::move(simpleCoffee));
    milkCoffee->brew();
    // Output:
    // Brewing a simple coffee
    // Adding milk

    // Decorating with sugar
    std::unique_ptr<Coffee> sweetCoffee = std::make_unique<SugarDecorator>(std::move(milkCoffee));
    sweetCoffee->brew();
    // Output:
    // Brewing a simple coffee
    // Adding milk
    // Adding sugar

    return 0;
}

/*

Yes, the provided code is indeed an example of the decorator pattern in C++. Let's break down the key components of the example:

Component Interface (Coffee):

Coffee is the component interface, defining the common interface for all concrete components (in this case, types of coffee).
Concrete Component (SimpleCoffee):

SimpleCoffee is a concrete component that implements the Coffee interface. It represents the basic coffee without any additional features.
Decorator Base Class (CoffeeDecorator):

CoffeeDecorator is the decorator base class, also implementing the Coffee interface. It has a member variable of type Coffee and delegates the brew method to the wrapped Coffee object.
Concrete Decorators (MilkDecorator, SugarDecorator):

These are concrete decorators that extend the behavior of the base CoffeeDecorator. Each decorator adds its own feature (milk or sugar) to the coffee.
Client Code (main function):

The client code demonstrates creating instances of a simple coffee and decorating it with various features (milk, sugar). This allows for flexible combinations of features without modifying the underlying coffee classes.
In summary, the example follows the structure of the decorator pattern, where decorators add additional features to the core component (Coffee) without altering its structure.

*/