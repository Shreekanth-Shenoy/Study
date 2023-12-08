#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

// Observer interface
class Observer {
public:
    virtual void update(float temperature) = 0;
};

// Subject (Observable)
class WeatherStation {
public:
    virtual void addObserver(std::unique_ptr<Observer> observer) = 0;
    virtual void removeObserver(std::unique_ptr<Observer> observer) = 0;
    virtual void notifyObservers() = 0;
};

// Concrete Subject (Concrete Observable)
class ConcreteWeatherStation : public WeatherStation {
public:
    void addObserver(std::unique_ptr<Observer> observer) override {
        observers.push_back(std::move(observer));
    }

    void removeObserver(std::unique_ptr<Observer> observer) override {
    observers.erase(std::remove_if(observers.begin(), observers.end(),
        [&observer](const std::unique_ptr<Observer>& val) {
            return val.get() == observer.get(); 
        }),
        observers.end());
    }

    void notifyObservers() override {
        for (const std::unique_ptr<Observer>& observer: observers) {
            observer->update(temperature);
        }
    }

    // Simulate changing weather conditions
    void setTemperature(float temperature) {
        this->temperature = temperature;
        notifyObservers();
    }

    float getTemperature() const {
        return temperature;
    }

private:
    std::vector<std::unique_ptr<Observer>> observers;
    float temperature = 0.0f; // Initialize temperature to 0.0
};

// Concrete Observer (Concrete Display Device)
class DisplayDevice : public Observer {
public:
    DisplayDevice(const std::string& name)
        : name(name) {
    }

    void update(float temperature) override {
        std::cout << name << " Display: Temperature updated to " << temperature << " degrees Celsius." << std::endl;
    }

private:
    std::string name;
};

int main() {
    // Create a weather station on the heap using std::make_unique
    std::unique_ptr<ConcreteWeatherStation> weatherStation = std::make_unique<ConcreteWeatherStation>();

    // Create display devices (observers) with unique_ptr ownership
    std::unique_ptr<DisplayDevice> display1 = std::make_unique<DisplayDevice>("Display 1");
    std::unique_ptr<DisplayDevice> display2 = std::make_unique<DisplayDevice>("Display 2");

    // Add display devices to the weather station
    weatherStation->addObserver(std::move(display1));
    weatherStation->addObserver(std::move(display2));

    // Simulate changing weather conditions
    weatherStation->setTemperature(25.5f);

    // The weatherStation is automatically deleted when the unique_ptr goes out of scope

    return 0;
}


/*

CHATGPT summary

Yes, the example I provided is a simplified demonstration of the Observer Pattern in C++. It illustrates the basic structure of the pattern:

Subject (Observable): The WeatherStation class is the subject. It maintains a list of observers and notifies them when the state (temperature) changes.

Observer: The Observer interface defines the update method, which concrete observers must implement to receive updates from the subject.

Concrete Subject (Concrete Observable): The ConcreteWeatherStation class is a specific implementation of the subject. It keeps track of observers and notifies them when the temperature changes.

Concrete Observer: The DisplayDevice class is a specific implementation of the observer. It implements the update method to display information when notified by the subject.

In a real-world scenario, the Observer Pattern is often used for implementing distributed event handling systems, user interfaces, and other situations where a change in one object needs to be communicated to other objects.


Basic code from chatgpt

#include <iostream>
#include <vector>

// Observer interface
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(float data) = 0;
};

// Subject (Observable)
class Subject {
public:
    virtual ~Subject() = default;
    virtual void addObserver(Observer* observer) = 0;
    virtual void removeObserver(Observer* observer) = 0;
    virtual void notifyObservers(float data) = 0;
};

// Concrete Observer
class ConcreteObserver : public Observer {
public:
    void update(float data) override {
        std::cout << "ConcreteObserver: Received update with data " << data << std::endl;
    }
};

// Concrete Subject
class ConcreteSubject : public Subject {
public:
    void addObserver(Observer* observer) override {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) override {
        // Implementation to remove observer
    }

    void notifyObservers(float data) override {
        for (Observer* observer : observers) {
            observer->update(data);
        }
    }

private:
    std::vector<Observer*> observers;
};

int main() {
    ConcreteSubject subject;
    ConcreteObserver observer1, observer2;

    subject.addObserver(&observer1);
    subject.addObserver(&observer2);

    subject.notifyObservers(42.0f);

    return 0;
}






*/