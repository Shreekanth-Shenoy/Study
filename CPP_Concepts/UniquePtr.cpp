#include <iostream>
#include <utility>

using namespace std;

template<typename T>
class UniquePtr {
public:
    // Default constructor and constructor with a pointer parameter
    UniquePtr(T* ptr = nullptr) : resource(ptr) {
        cout << "UniquePtr: Default and parameterized constructor" << endl;
    }

    // Rule of Three/Five/Zero: Copy constructor (deleted)
    UniquePtr(const UniquePtr& other) = delete;

    // Rule of Three/Five/Zero: Copy assignment operator (deleted)
    UniquePtr& operator=(const UniquePtr& other) = delete;

    // Move constructor with 'noexcept'
    UniquePtr(UniquePtr&& other) noexcept : resource(other.resource) {
        other.resource = nullptr;
        cout << "UniquePtr: Move constructor" << endl;
    }

    // Rule of Three/Five/Zero: Move assignment operator
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            // Release the current resource before taking the new one
            delete resource;
            resource = other.resource;
            other.resource = nullptr;
            cout << "UniquePtr: Move assignment operator" << endl;
        }
        return *this;
    }

    // Overloaded arrow operator for pointer-like behavior
    T* operator->() {
        return resource;
    }

    // Overloaded dereference operator for pointer-like behavior
    T& operator*() {
        return *resource;
    }

    // Getter function to obtain the raw pointer (marked as 'const')
    T* get() const {
        return resource;
    }

    // Destructor to release the owned resource
    ~UniquePtr() {
        delete resource;
        resource = nullptr;
        cout << "UniquePtr: Destructor" << endl;
    }

private:
    T* resource;  // Raw pointer to the owned resource
};

int main() {
    cout << "Creating ptr1..." << endl;
    UniquePtr<int> ptr1;             // Default constructor

    cout << "\nCreating ptr2..." << endl;
    UniquePtr<int> ptr2(new int(10));// Parameterized constructor with a new int

    cout << "\nUsing * on ptr2: " << *ptr2 << endl;  // Using dereference operator *

    //cout << "\nUsing -> on ptr2: " << ptr2->func() << endl;  // Using arrow operator ->

    cout << "\nUsing get() on ptr2: " << ptr2.get() << endl;  // Using get() to obtain raw pointer

    cout << "\nMoving ptr2 to ptr4..." << endl;
    UniquePtr<int> ptr4 = move(ptr2); // Move constructor

    cout << "\nMoving ptr4 to ptr1..." << endl;
    ptr1 = move(ptr4);                // Move assignment operator

    return 0;
}
