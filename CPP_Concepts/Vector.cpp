#include <iostream>
#include <algorithm>

template <typename T>
class Vector {
public:
    // Default constructor
    Vector() : dataStore(nullptr), size(0), capacity(0) {
        std::cout << "Default CTR" << std::endl;
    }

    // Parameterized constructor with size and initial value
    Vector(size_t initialSize, const T& initialValue) : size(initialSize), capacity(initialSize * 2) {
        std::cout << "Parameterized CTR" << std::endl;
        dataStore = new T[capacity];
        std::fill_n(dataStore, size, initialValue);
    }

    // Copy constructor
    Vector(const Vector& other) : size(other.size), capacity(other.capacity) {
        std::cout << "Copy CTR" << std::endl;
        dataStore = new T[capacity];
        std::copy(other.dataStore, other.dataStore + size, dataStore);
    }

    // Copy assignment operator
    Vector& operator=(const Vector& other) {
        std::cout << "Copy Assignment Operator" << std::endl;
        if (this != &other) {
            delete[] dataStore;
            size = other.size;
            capacity = other.capacity;
            dataStore = new T[capacity];
            std::copy(other.dataStore, other.dataStore + size, dataStore);
        }
        return *this;
    }

    // Move constructor
    Vector(Vector&& other) noexcept : size(other.size), capacity(other.capacity), dataStore(other.dataStore) {
        std::cout << "Move CTR" << std::endl;
        other.size = 0;
        other.capacity = 0;
        other.dataStore = nullptr;
    }

    // Move assignment operator
    Vector& operator=(Vector&& other) noexcept {
        std::cout << "Move Assignment Operator" << std::endl;
        if (this != &other) {
            delete[] dataStore;
            size = other.size;
            capacity = other.capacity;
            dataStore = other.dataStore;
            other.size = 0;
            other.capacity = 0;
            other.dataStore = nullptr;
        }
        return *this;
    }

    // Destructor
    ~Vector() {
        delete[] dataStore;
        std::cout << "Destructor" << std::endl;
    }

    // Subscript operator
    T& operator[](size_t index) {
        return dataStore[index];
    }

    // Add an element to the end of the vector
    void push_back(const T& value) {
        if (size == capacity) {
            resize();
        }
        dataStore[size++] = value;
    }

    void emplace_back(T&& value){
        if (size == capacity) {
            resize();
        }
        dataStore[size++] = std::move(value);

    }

    // Get the size of the vector
    size_t getSize() const {
        return size;
    }

    // Get the capacity of the vector
    size_t getCapacity() const {
        return capacity;
    }

private:
    T* dataStore;
    size_t size;
    size_t capacity;

    // Helper function to resize the vector
    void resize() {
        capacity = (capacity == 0) ? 1 : capacity * 2;
        T* newData = new T[capacity];
        std::copy(dataStore, dataStore + size, newData);
        delete[] dataStore;
        dataStore = newData;
    }
};

int main() {
    Vector<int> vec1;                 // Default CTR
    Vector<int> vec2(5, 10);          // Parameterized CTR
    Vector<int> vec3 = vec2;          // Copy CTR
    vec1 = vec2;                      // Copy Assignment Operator

    std::cout << "vec1 size: " << vec1.getSize() << ", capacity: " << vec1.getCapacity() << std::endl;
    std::cout << "vec2 size: " << vec2.getSize() << ", capacity: " << vec2.getCapacity() << std::endl;
    std::cout << "vec3 size: " << vec3.getSize() << ", capacity: " << vec3.getCapacity() << std::endl;

    vec1.push_back(15);
    std::cout << "vec1 size: " << vec1.getSize() << ", capacity: " << vec1.getCapacity() << std::endl;
    std::cout << "vec2 size: " << vec2.getSize() << ", capacity: " << vec2.getCapacity() << std::endl;
    std::cout << "vec3 size: " << vec3.getSize() << ", capacity: " << vec3.getCapacity() << std::endl;

    // Example of using emplace_back
    vec3.emplace_back(std::move(42));  // Emplace an element with value 42 at the end

    std::cout << "vec1 size: " << vec1.getSize() << ", capacity: " << vec1.getCapacity() << std::endl;
    for (size_t i = 0; i < vec1.getSize(); ++i) {
        std::cout << vec1[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}