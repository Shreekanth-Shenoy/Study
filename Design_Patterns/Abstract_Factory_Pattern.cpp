#include <iostream>
#include <string>
#include <memory>
// Abstract Product A
class Bread {
public:
    Bread(const std::string& type) : type(type) {
        std::cout << "Freshly baked " << type << " is ready.\n";
    }

    std::string getType() const {
        return type;
    }

private:
    std::string type;
};

// Concrete Product A1
class Baguette : public Bread {
public:
    Baguette() : Bread("Baguette") {}
};

// Concrete Product A2
class WholeGrain : public Bread {
public:
    WholeGrain() : Bread("Whole Grain") {}
};

// Abstract Product B
class Spread {
public:
    Spread(const std::string& type) : type(type) {
        std::cout << "Delicious " << type << " spread is ready.\n";
    }

    std::string getType() const {
        return type;
    }

private:
    std::string type;
};

// Concrete Product B1
class Butter : public Spread {
public:
    Butter() : Spread("Butter") {}
};

// Concrete Product B2
class Jam : public Spread {
public:
    Jam() : Spread("Jam") {}
};

// Abstract Factory
class BreadFactory {
public:
    virtual std::unique_ptr<Bread> createBread() const = 0;
    virtual std::unique_ptr<Spread> createSpread() const = 0;
};

// Concrete Factory 1
class FrenchBakery : public BreadFactory {
public:
    std::unique_ptr<Bread> createBread() const override {
        return std::make_unique<Baguette>();
    }

    std::unique_ptr<Spread> createSpread() const override {
        return std::make_unique<Butter>();
    }
};

// Concrete Factory 2
class HealthFoodBakery : public BreadFactory {
public:
    std::unique_ptr<Bread> createBread() const override {
        return std::make_unique<WholeGrain>();
    }

    std::unique_ptr<Spread> createSpread() const override {
        return std::make_unique<Jam>();
    }
};

int main() {
    // Using Abstract Factory Pattern in a bakery scenario
    std::cout << "Welcome to the Bakeries!\n";

    std::unique_ptr<BreadFactory> frenchBakery = std::make_unique<FrenchBakery>();
    std::unique_ptr<Bread> baguette = frenchBakery->createBread();
    std::unique_ptr<Spread> butter = frenchBakery->createSpread();

    std::cout << "\n";

    std::unique_ptr<BreadFactory> healthFoodBakery = std::make_unique<HealthFoodBakery>();
    std::unique_ptr<Bread> wholeGrain = healthFoodBakery->createBread();
    std::unique_ptr<Spread> jam = healthFoodBakery->createSpread();

    std::cout << "\nThank you for visiting the Bakeries!\n";

    return 0;
}
