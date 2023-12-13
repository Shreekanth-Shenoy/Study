#include <iostream>
#include <vector>
#include <string>

// Iterator interface
class Iterator {
public:
    virtual bool hasNext() const = 0;
    virtual const std::string& next() = 0;
};

// Concrete Iterator implementation for a vector of strings
class VectorIterator : public Iterator {
    const std::vector<std::string>& collection;
    size_t index;

public:
    VectorIterator(const std::vector<std::string>& coll) : collection(coll), index(0) {}

    bool hasNext() const override {
        return index < collection.size();
    }

    const std::string& next() override {
        if (!hasNext()) {
            throw std::out_of_range("Iterator reached the end");
        }
        return collection[index++];
    }
};

// Bakery class representing a collection of bakery items
class Bakery {
    std::vector<std::string> items;

public:
    void addItem(const std::string& item) {
        items.push_back(item);
    }

    Iterator* createIterator() {
        return new VectorIterator(items);
    }
};

int main() {
    Bakery bakery;
    bakery.addItem("Croissant");
    bakery.addItem("Baguette");
    bakery.addItem("Donut");

    Iterator* iterator = bakery.createIterator();

    std::cout << "Bakery Items:" << std::endl;
    while (iterator->hasNext()) {
        const std::string& item = iterator->next();
        std::cout << item << std::endl;
    }

    delete iterator;

    return 0;
}
