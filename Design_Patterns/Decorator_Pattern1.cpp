#include <iostream>
#include <memory>

// Component interface
class Bread {
public:
    virtual ~Bread() = default;
    virtual void addTopping() const = 0;
};

// Concrete component
class PlainBread : public Bread {
public:
    void addTopping() const override {
        std::cout << "Plain Bread" << std::endl;
    }
};

// Decorator base class
class BreadDecorator : public Bread {
protected:
    std::unique_ptr<Bread> bread;

public:
    BreadDecorator(std::unique_ptr<Bread> bread) : bread(std::move(bread)) {}

    void addTopping() const override {
        bread->addTopping();
    }
};

// Concrete decorator 1: GarlicBreadDecorator
class GarlicBreadDecorator : public BreadDecorator {
public:
    GarlicBreadDecorator(std::unique_ptr<Bread> bread) : BreadDecorator(std::move(bread)) {}

    void addTopping() const override {
        BreadDecorator::addTopping();
        addGarlic();
    }

private:
    void addGarlic() const {
        std::cout << " + Garlic" << std::endl;
    }
};

// Concrete decorator 2: ButterBreadDecorator
class ButterBreadDecorator : public BreadDecorator {
public:
    ButterBreadDecorator(std::unique_ptr<Bread> bread) : BreadDecorator(std::move(bread)) {}

    void addTopping() const override {
        BreadDecorator::addTopping();
        addButter();
    }

private:
    void addButter() const {
        std::cout << " + Butter" << std::endl;
    }
};

// Concrete decorator 3: JamBreadDecorator
class JamBreadDecorator : public BreadDecorator {
public:
    JamBreadDecorator(std::unique_ptr<Bread> bread) : BreadDecorator(std::move(bread)) {}

    void addTopping() const override {
        BreadDecorator::addTopping();
        addJam();
    }

private:
    void addJam() const {
        std::cout << " + Jam" << std::endl;
    }
};

// Concrete decorator 4: CheeseBreadDecorator
class CheeseBreadDecorator : public BreadDecorator {
public:
    CheeseBreadDecorator(std::unique_ptr<Bread> bread) : BreadDecorator(std::move(bread)) {}

    void addTopping() const override {
        BreadDecorator::addTopping();
        addCheese();
    }

private:
    void addCheese() const {
        std::cout << " + Cheese" << std::endl;
    }
};

int main() {
    // Creating plain bread
    std::unique_ptr<Bread> plainBread = std::make_unique<PlainBread>();
    plainBread->addTopping();
    // Output: Plain Bread

    // Decorating with garlic
    std::unique_ptr<Bread> garlicBread = std::make_unique<GarlicBreadDecorator>(std::make_unique<PlainBread>());
    garlicBread->addTopping();
    // Output: Plain Bread + Garlic

    // Decorating with butter and jam
    std::unique_ptr<Bread> butterJamBread = std::make_unique<ButterBreadDecorator>(
        std::make_unique<JamBreadDecorator>(std::make_unique<PlainBread>())
    );
    butterJamBread->addTopping();
    // Output: Plain Bread + Jam + Butter

    // Decorating with cheese
    std::unique_ptr<Bread> cheeseBread = std::make_unique<CheeseBreadDecorator>(std::make_unique<PlainBread>());
    cheeseBread->addTopping();
    // Output: Plain Bread + Cheese

    return 0;
}

/*


Yes, the provided example is indeed an illustration of the decorator pattern. Let's break down the key components:

Component Interface (Bread):

Bread is the component interface, defining the common interface for all concrete components (in this case, types of bread).
Concrete Component (PlainBread):

PlainBread is a concrete component that implements the Bread interface. It represents the basic bread without any additional toppings.
Decorator Base Class (BreadDecorator):

BreadDecorator is the decorator base class, also implementing the Bread interface. It has a member variable of type Bread and delegates the addTopping method to the wrapped Bread object.
Concrete Decorators (GarlicBreadDecorator, ButterBreadDecorator, JamBreadDecorator, CheeseBreadDecorator):

These are concrete decorators that extend the behavior of the base BreadDecorator. Each decorator adds its own topping (garlic, butter, jam, cheese) to the bread.
Client Code (main function):

The client code demonstrates creating instances of plain bread and decorating them with various toppings. This allows for flexible combinations of toppings without modifying the underlying bread classes.
In summary, the example follows the structure of the decorator pattern, where decorators add additional responsibilities to the core component (Bread) without altering its structure.*/