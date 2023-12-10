#include <iostream>

using namespace std;

class Singleton {
public:
    // Only written to stick to the rule of 5s
    Singleton(const Singleton&) = delete;             // 1. Delete Copy constructor
    Singleton& operator=(const Singleton&) = delete;  // 2. Delete Copy assignment operator
    Singleton(Singleton&&) = delete;                  // 3. Delete Move constructor
    Singleton& operator=(Singleton&&) = delete;       // 4. Delete Move assignment operator

    static Singleton& Get() {
        static Singleton instance;
        return instance;
    }

    static void Print() {
        return Get().PrintImpl();
    }

    ~Singleton() {
        cout << "DTR";
    }

private:
    void PrintImpl() {
        std::cout << "HELLO" << std::endl;
    }

    Singleton() {}
};

int main() {
    Singleton& s = Singleton::Get();
    s.Print();          // Using the Singleton instance and calling Print

    Singleton::Print(); // Calling Print using the static function

    return 0;
}
