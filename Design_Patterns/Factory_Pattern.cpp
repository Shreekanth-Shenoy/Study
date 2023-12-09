#include <iostream>
#include <memory>
#include <vector>
#include <cstdlib> // for rand()

// Abstract Product
class Animal {
public:
    virtual void speak() const = 0;
    virtual void move() const = 0;
    virtual ~Animal() {}
};

// Concrete Products
class Lion : public Animal {
public:
    void speak() const override {
        std::cout << "Lion says Roar!\n";
    }

    void move() const override {
        std::cout << "Lion is running.\n";
    }
};

class Elephant : public Animal {
public:
    void speak() const override {
        std::cout << "Elephant says Trumpet!\n";
    }

    void move() const override {
        std::cout << "Elephant is walking.\n";
    }
};

class Penguin : public Animal {
public:
    void speak() const override {
        std::cout << "Penguin says Honk!\n";
    }

    void move() const override {
        std::cout << "Penguin is waddling.\n";
    }
};

// Factory Interface
class AnimalFactory {
public:
    virtual std::unique_ptr<Animal> createAnimal() = 0;
    virtual ~AnimalFactory() {}
};

// Concrete Factories
class LionFactory : public AnimalFactory {
public:
    std::unique_ptr<Animal> createAnimal() override {
        return std::make_unique<Lion>();
    }
};

class ElephantFactory : public AnimalFactory {
public:
    std::unique_ptr<Animal> createAnimal() override {
        return std::make_unique<Elephant>();
    }
};

class PenguinFactory : public AnimalFactory {
public:
    std::unique_ptr<Animal> createAnimal() override {
        return std::make_unique<Penguin>();
    }
};

// Balanced Animal Factory (Creates animals in a balanced manner)
class BalancedAnimalFactory : public AnimalFactory {
private:
    size_t currentIndex = 0;
public:
    std::unique_ptr<Animal> createAnimal() override {
        currentIndex = (currentIndex + 1) % 3;
        switch (currentIndex) {
            case 0:
                return std::make_unique<Lion>();
            case 1:
                return std::make_unique<Elephant>();
            case 2:
                return std::make_unique<Penguin>();
            default:
                // This should not happen, but handle it by creating a default animal.
                return std::make_unique<Lion>();
        }
    }
};

// Random Animal Factory (Creates animals randomly)
class RandomAnimalFactory : public AnimalFactory {
public:
    std::unique_ptr<Animal> createAnimal() override {
        int randomAnimal = rand() % 3; // 0: Lion, 1: Elephant, 2: Penguin

        switch (randomAnimal) {
            case 0:
                return std::make_unique<Lion>();
            case 1:
                return std::make_unique<Elephant>();
            case 2:
                return std::make_unique<Penguin>();
            default:
                // This should not happen, but handle it by creating a default animal.
                return std::make_unique<Lion>();
        }
    }
};

// Client using the Factories
int main() {
    std::unique_ptr<AnimalFactory> lionFactory = std::make_unique<LionFactory>();
    std::unique_ptr<AnimalFactory> elephantFactory = std::make_unique<ElephantFactory>();
    std::unique_ptr<AnimalFactory> penguinFactory = std::make_unique<PenguinFactory>();
    std::unique_ptr<AnimalFactory> balancedFactory = std::make_unique<BalancedAnimalFactory>();
    std::unique_ptr<AnimalFactory> randomFactory = std::make_unique<RandomAnimalFactory>();

    std::unique_ptr<Animal> lion = lionFactory->createAnimal();
    std::unique_ptr<Animal> elephant = elephantFactory->createAnimal();
    std::unique_ptr<Animal> penguin = penguinFactory->createAnimal();
    
    std::unique_ptr<Animal> balancedAnimal1 = balancedFactory->createAnimal();
    std::unique_ptr<Animal> balancedAnimal2 = balancedFactory->createAnimal();
    std::unique_ptr<Animal> balancedAnimal3 = balancedFactory->createAnimal();
    std::unique_ptr<Animal> balancedAnimal4 = balancedFactory->createAnimal();
    std::unique_ptr<Animal> balancedAnimal5 = balancedFactory->createAnimal();
    std::unique_ptr<Animal> balancedAnimal6 = balancedFactory->createAnimal();
    std::unique_ptr<Animal> balancedAnimal7 = balancedFactory->createAnimal();
    std::unique_ptr<Animal> balancedAnimal8 = balancedFactory->createAnimal();

    std::unique_ptr<Animal> randomAnimal1 = randomFactory->createAnimal();
    std::unique_ptr<Animal> randomAnimal2 = randomFactory->createAnimal();

    lion->speak();
    lion->move();

    elephant->speak();
    elephant->move();

    penguin->speak();
    penguin->move();

    std::cout<<std::endl;
    std::cout<<"----------Balaced Animals-------------"<<std::endl;
    balancedAnimal1->speak();
    balancedAnimal1->move();

    balancedAnimal2->speak();
    balancedAnimal2->move();

    balancedAnimal3->speak();
    balancedAnimal3->move();

    balancedAnimal4->speak();
    balancedAnimal4->move();

    balancedAnimal5->speak();
    balancedAnimal5->move();

    balancedAnimal6->speak();
    balancedAnimal6->move();

    balancedAnimal7->speak();
    balancedAnimal7->move();

    balancedAnimal8->speak();
    balancedAnimal8->move();

    std::cout<<std::endl;
    std::cout<<"----------Random Animals-------------"<<std::endl;

    randomAnimal1->speak();
    randomAnimal1->move();

    randomAnimal2->speak();
    randomAnimal2->move();

    return 0;
}
