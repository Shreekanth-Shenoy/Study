#include <iostream>
#include <vector>

// Component
class BakeryItem {
public:
    virtual void bake() const = 0;
    virtual ~BakeryItem() = default;
};

// Leaf
class Cake : public BakeryItem {
public:
    void bake() const override {
        std::cout << "Baking a Cake" << std::endl;
    }
};

// Leaf
class Pastry : public BakeryItem {
public:
    void bake() const override {
        std::cout << "Baking a Pastry" << std::endl;
    }
};

// Leaf
class Cookie : public BakeryItem {
public:
    void bake() const override {
        std::cout << "Baking a Cookie" << std::endl;
    }
};

// Composite
class Assortment : public BakeryItem {
private:
    std::string assortmentName;
    std::vector<BakeryItem*> items;

public:
    Assortment(const std::string& name) : assortmentName(name) {}

    void addItem(BakeryItem* item) {
        items.push_back(item);
    }

    void bake() const override {
        std::cout << "Baking Assortment: " << assortmentName << std::endl;
        for (const auto& item : items) {
            item->bake();
        }
    }
};

int main() {
    // Create individual bakery items
    Cake cake;
    Pastry pastry;
    Cookie cookie;

    // Create composite assortment and add individual items
    Assortment specialAssortment("Special Assortment");
    specialAssortment.addItem(&cake);
    specialAssortment.addItem(&pastry);

    // Create another composite assortment and add an individual item
    Assortment holidayAssortment("Holiday Assortment");
    holidayAssortment.addItem(&cookie);

    // Add the holiday assortment to the special assortment
    specialAssortment.addItem(&holidayAssortment);

    // Bake the top-level assortment, which will recursively bake its items
    specialAssortment.bake();

    return 0;
}


/* Basic Structure

#include <iostream>
#include <vector>

// Component
class Component {
public:
    virtual void operation() const = 0;
    virtual ~Component() = default;
};

// Leaf
class Leaf : public Component {
public:
    void operation() const override {
        std::cout << "Leaf operation" << std::endl;
    }
};

// Composite
class Composite : public Component {
public:
    void add(Component* component) {
        components.push_back(component);
    }

    void operation() const override {
        std::cout << "Composite operation" << std::endl;
        for (const auto& component : components) {
            component->operation();
        }
    }

private:
    std::vector<Component*> components;
};

int main() {
    // Create leaf objects
    Leaf leaf1, leaf2, leaf3;

    // Create composite object and add leaves to it
    Composite composite;
    composite.add(&leaf1);
    composite.add(&leaf2);

    // Create another composite object and add a leaf to it
    Composite composite2;
    composite2.add(&leaf3);

    // Add the second composite to the first composite
    composite.add(&composite2);

    // Call operations on the composite, which will recursively call operations on its components
    composite.operation();

    return 0;
}


*/
