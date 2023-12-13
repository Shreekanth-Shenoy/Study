#include <iostream>

// Abstract class defining the template algorithm
class BakeryTemplate {
public:
    // Template method for baking pastries
    void bakePastry() {
        prepareBatter();
        pourIntoPan();
        bake();
        cool();
    }

    // Primitive operations to be overridden by subclasses
    virtual void prepareBatter() = 0;
    virtual void pourIntoPan() = 0;
    virtual void bake() = 0;
    virtual void cool() {
        std::cout << "Cooling the pastry\n";
    }
};

// Concrete class for baking cakes
class CakeBakery : public BakeryTemplate {
public:
    // Override primitive operations
    void prepareBatter() override {
        std::cout << "Preparing cake batter\n";
    }

    void pourIntoPan() override {
        std::cout << "Pouring cake batter into the pan\n";
    }

    void bake() override {
        std::cout << "Baking the cake\n";
    }

    // No need to override cool(), as the default implementation is used
};

// Concrete class for baking donuts
class DonutBakery : public BakeryTemplate {
public:
    // Override primitive operations
    void prepareBatter() override {
        std::cout << "Preparing donut batter\n";
    }

    void pourIntoPan() override {
        std::cout << "Pouring donut batter into the donut mold\n";
    }

    void bake() override {
        std::cout << "Baking the donuts\n";
    }

    // Custom cool() implementation for donuts
    void cool() override {
        std::cout << "Cooling donuts and dipping them in sugar glaze\n";
    }
};

int main() {
    // Creating CakeBakery object on the stack
    CakeBakery cakeBakery;
    cakeBakery.bakePastry();

    std::cout << "\n";

    // Creating DonutBakery object on the stack
    DonutBakery donutBakery;
    donutBakery.bakePastry();

    return 0;
}
