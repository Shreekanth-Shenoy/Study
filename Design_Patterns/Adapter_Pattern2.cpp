#include <iostream>
#include <memory>
#include <string>

// Adaptee interface
class Adaptee {
public:
    virtual ~Adaptee() = default;
    virtual void charge() const = 0;
};

// Concrete Adaptees
class iPhone : public Adaptee {
public:
    void charge() const override {
        std::cout << "Charging iPhone with Lightning connector\n";
    }
};

class Android : public Adaptee {
public:
    void charge() const override {
        std::cout << "Charging Android device with USB-C connector\n";
    }
};

class Laptop : public Adaptee {
public:
    void charge() const override {
        std::cout << "Charging laptop with USB connector\n";
    }
};

// Target interface
class UniversalAdapter {
private:
    std::unique_ptr<Adaptee> adaptee;

public:
    UniversalAdapter(std::unique_ptr<Adaptee>&& adaptee) : adaptee(std::move(adaptee)) {}

    void process(const std::string& data) const {
        std::cout << "UniversalAdapter processing data: " << data << "\n";
        adaptee->charge();
    }
};

// Client code
int main() {
    std::cout << "Using UniversalAdapter with unique pointers for a single device:\n";

    // Create an adapter for a single device and process it
    std::unique_ptr<Adaptee> device = std::make_unique<iPhone>();
    auto adapter = std::make_unique<UniversalAdapter>(std::move(device));
    adapter->process("Data for device");

    return 0;
}
