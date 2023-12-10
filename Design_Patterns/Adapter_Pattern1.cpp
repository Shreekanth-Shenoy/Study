#include <iostream>

// Target interface
class AndroidCharger {
public:
    virtual ~AndroidCharger() = default;
    virtual void chargeWithUSB_C() const = 0;
};

// Adaptee (the class to be adapted)
class IPhone {
public:
    void chargeWithLightning() const {
        std::cout << "Charging with Lightning connector\n";
    }
};

// Adapter
class USBToLightningAdapter : public AndroidCharger {
private:
    IPhone iPhone;

public:
    void chargeWithUSB_C() const override {
        std::cout << "Adapter converting USB-C to Lightning for iPhone charging\n";
        iPhone.chargeWithLightning();
        // Additional logic to adapt the charging if needed
    }
};

// Client code
void useAndroidCharger(const AndroidCharger& charger) {
    charger.chargeWithUSB_C();
}

int main() {
    std::cout << "Using Android charger:\n";

    AndroidCharger* adapter = new USBToLightningAdapter();
    useAndroidCharger(*adapter);

    delete adapter;

    return 0;
}
