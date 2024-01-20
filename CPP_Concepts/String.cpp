#include <iostream>
#include <cstring>

class String {
public:
    // Default constructor
    String() : dataStore(nullptr), len(0) {
        std::cout << "Default CTR" << std::endl;
    }

    // Parameterized constructor
    String(const char* data) {
        std::cout << "Parameterized CTR" << std::endl;
        len = std::strlen(data);
        dataStore = new char[len + 1];
        std::strcpy(dataStore, data);
    }

    // Copy constructor
    String(const String& other) {
        std::cout << "Copy CTR" << std::endl;
        len = other.len;
        dataStore = new char[len + 1];
        std::strcpy(dataStore, other.dataStore);
    }

    // Copy assignment operator
    String& operator=(const String& other) {
        std::cout << "Copy Assignment Operator" << std::endl;
        if (this != &other) {
            char* temp = dataStore;
            len = other.len;
            dataStore = new char[len + 1];
            std::strcpy(dataStore, other.dataStore);
            delete[] temp;
        }
        return *this;
    }

    // Move constructor
    String(String&& other) noexcept {
        std::cout << "Move CTR" << std::endl;
        len = other.len;
        dataStore = other.dataStore;
        other.len = 0;
        other.dataStore = nullptr;
    }

    // Move assignment operator
    String& operator=(String&& other) noexcept {
        std::cout << "Move Assignment Operator" << std::endl;
        if (this != &other) {
            char* temp = dataStore;
            dataStore = other.dataStore;
            len = other.len;
            other.dataStore = nullptr;
            other.len = 0;
            delete[] temp;
        }
        return *this;
    }

    // Destructor
    ~String() {
        delete[] dataStore;
        std::cout << "Destructor" << std::endl;
    }

    // Subscript operator
    char& operator[](int index) {
        return dataStore[index];
    }

    friend std::ostream& operator<<(std::ostream& stream, const String& string);

private:
    char* dataStore;
    size_t len;
};

// Output stream operator
std::ostream& operator<<(std::ostream& stream, const String& data) {
    stream << data.dataStore;
    return stream;
}

int main() {
    String str1;             // Default CTR
    String str2 = "Hello";   // Parameterized CTR
    String str3 = str2;      // Copy CTR
    str1 = str2;             // Copy Assignment Operator

    std::cout << "str1: " << str1 << std::endl;
    std::cout << "str2: " << str2 << std::endl;
    std::cout << "str3: " << str3 << std::endl;
    std::cout << "str2[2]: " << str2[2] << std::endl;

    String str4 = std::move(str2);  // Move CTR
    std::cout << "str4: " << str4 << std::endl;

    str4 = std::move(str3);  // Move Assignment Operator
    std::cout << "str4: " << str4 << std::endl;

    return 0;
}
