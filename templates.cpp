//Some template examples



#include <iostream>
#include <vector>
#include <string>

// Generic template for data storage
template <typename T>
class DataStorage {
public:
    void store(const T& data) {
        std::cout << "Storing generic data: " << data << std::endl;
    }
};

// Template specialization for strings
template <>
class DataStorage<std::string> {
public:
    void store(const std::string& data) {
        std::cout << "Storing string data with length: " << data.length() << std::endl;
    }
};

// Example custom type
class StringWrapper {
public:
    StringWrapper(const std::string& str) : data(str) {}

    const std::string& getString() const {
        return data;
    }

private:
    std::string data;
};

// Template specialization for StringWrapper
template <>
class DataStorage<StringWrapper> {
public:
    void store(const StringWrapper& data) {
        std::cout << "Storing StringWrapper data: " << data.getString() << std::endl;
    }
};

int main() {
    // Using generic template for int
    DataStorage<int> intStorage;
    intStorage.store(42);

    // Using specialized template for strings
    DataStorage<std::string> stringStorage;
    stringStorage.store("Hello, specialization!");

    // Using specialized template for custom type StringWrapper
    DataStorage<StringWrapper> wrapperStorage;
    StringWrapper myWrapper("Custom StringWrapper");
    wrapperStorage.store(myWrapper);

    return 0;
}















/*#include <iostream>
#include <functional>

// Template wrapper function for a specific function signature (int(int, int))
template <typename Function>
int wrapper(const Function& func, int a, int b) {
    // Pre-processing before calling the function
    std::cout << "Performing pre-processing..." << std::endl;

    // Call the provided function with the arguments
    int result = func(a, b);

    // Post-processing after calling the function
    std::cout << "Performing post-processing..." << std::endl;

    return result;
}

// Example function to be wrapped
int add(int a, int b) {
    return a + b;
}

// Example function to be wrapped
int minus(int a, int b) {
    return a - b;
}

int main() {
    // Using the template wrapper function with the 'add' function
    int result = wrapper(add, 5, 3);

    // Displaying the result
    std::cout << "Result: " << result << std::endl;
    
    
    // Using the template wrapper function with the 'add' function
    int result1 = wrapper(minus, 5, 3);

    // Displaying the result
    std::cout << "Result: " << result1 << std::endl;
    return 0;
}
*/
