#include <iostream>
#include <string>
#include <memory>
// Abstract Product A
class Pizza {
public:
    virtual ~Pizza() {}
};

// Concrete Product A1
class MargheritaPizza : public Pizza {};

// Concrete Product A2
class PepperoniPizza : public Pizza {};

// Concrete Product A3
class VegetarianPizza : public Pizza {};

// Abstract Product B
class Topping {
public:
    virtual std::string getType() const = 0;
    virtual ~Topping() {}
};

// Concrete Product B1
class Cheese : public Topping {
public:
    std::string getType() const override {
        return "Cheese";
    }
};

// Concrete Product B2
class Pepperoni : public Topping {
public:
    std::string getType() const override {
        return "Pepperoni";
    }
};

// Concrete Product B3
class Vegetables : public Topping {
public:
    std::string getType() const override {
        return "Vegetables";
    }
};

// Abstract Factory
class PizzaFactory {
public:
    virtual std::unique_ptr<Pizza> createPizza() const = 0;
    virtual std::unique_ptr<Topping> createTopping() const = 0;
    virtual ~PizzaFactory() {}
};

// Concrete Factory 1
class MargheritaPizzaFactory : public PizzaFactory {
public:
    std::unique_ptr<Pizza> createPizza() const override {
        return std::make_unique<MargheritaPizza>();
    }

    std::unique_ptr<Topping> createTopping() const override {
        return std::make_unique<Cheese>();
    }
};

// Concrete Factory 2
class PepperoniPizzaFactory : public PizzaFactory {
public:
    std::unique_ptr<Pizza> createPizza() const override {
        return std::make_unique<PepperoniPizza>();
    }

    std::unique_ptr<Topping> createTopping() const override {
        return std::make_unique<Pepperoni>();
    }
};

// Concrete Factory 3
class VegetarianPizzaFactory : public PizzaFactory {
public:
    std::unique_ptr<Pizza> createPizza() const override {
        return std::make_unique<VegetarianPizza>();
    }

    std::unique_ptr<Topping> createTopping() const override {
        return std::make_unique<Vegetables>();
    }
};

int main() {
    // Using Abstract Factory Pattern in a pizzeria scenario
    std::cout << "Welcome to the Pizzeria!\n";

    // Margherita Pizza
    std::unique_ptr<PizzaFactory> margheritaFactory = std::make_unique<MargheritaPizzaFactory>();
    std::unique_ptr<Pizza> margheritaPizza = margheritaFactory->createPizza();
    std::unique_ptr<Topping> margheritaTopping = margheritaFactory->createTopping();

    std::cout << "Topping: " << margheritaTopping->getType() << "\n\n";

    // Pepperoni Pizza
    std::unique_ptr<PizzaFactory> pepperoniFactory = std::make_unique<PepperoniPizzaFactory>();
    std::unique_ptr<Pizza> pepperoniPizza = pepperoniFactory->createPizza();
    std::unique_ptr<Topping> pepperoniTopping = pepperoniFactory->createTopping();

    std::cout << "Topping: " << pepperoniTopping->getType() << "\n\n";

    // Vegetarian Pizza
    std::unique_ptr<PizzaFactory> vegetarianFactory = std::make_unique<VegetarianPizzaFactory>();
    std::unique_ptr<Pizza> vegetarianPizza = vegetarianFactory->createPizza();
    std::unique_ptr<Topping> vegetarianTopping = vegetarianFactory->createTopping();

    std::cout << "Topping: " << vegetarianTopping->getType() << "\n\n";

    std::cout << "Thank you for ordering from the Pizzeria!\n";

    return 0;
}
