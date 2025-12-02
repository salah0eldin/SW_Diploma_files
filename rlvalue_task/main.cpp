#include <iostream>
#include <cstring>

class MyClass {
    private:
        int value;
        char* name;
    public:
        MyClass() : value(0), name(nullptr) {
            std::cout << "Default constructor called" << std::endl;
        }

        MyClass(int v, const char* n) : value(v) {
            std::cout << "Parameterized constructor called (value: " << v << ", name: " << n << ")" << std::endl;
            name = new char[strlen(n) + 1];
            strcpy(name, n);
        }
        
        MyClass(const MyClass& other) : value(other.value) {
            std::cout << "Copy constructor called (copying value: " << other.value << ")" << std::endl;
            name = new char[strlen(other.name) + 1];
            strcpy(name, other.name);
        }

        MyClass(MyClass&& other) noexcept : value(other.value), name(other.name) {
            std::cout << "Move constructor called (moving value: " << other.value << ")" << std::endl;
            other.name = nullptr;
        }
        
        MyClass& operator=(const MyClass& other) {
            std::cout << "Copy assignment operator called" << std::endl;
            if (this != &other) {
                value = other.value;
                if(name != nullptr) delete[] name;
                name = new char[strlen(other.name) + 1];
                strcpy(name, other.name);
            }
            return *this;
        }
        
        MyClass& operator=(MyClass&& other) noexcept {
            std::cout << "Move assignment operator called" << std::endl;
            if (this != &other) {
                value = other.value;
                if(name != nullptr) delete[] name;
                name = other.name;
                other.name = nullptr;
            }
            return *this;
        }

        ~MyClass() {
            std::cout << "Destructor called (value: " << value << ")" << std::endl;
            delete[] name;
        }
};

int main() {
    std::cout << "=== Example 1: Default Constructor ===" << std::endl;
    {
        MyClass obj1;
    }
    std::cout << std::endl;

    std::cout << "=== Example 2: Parameterized Constructor ===" << std::endl;
    {
        MyClass obj2(42, "Hello");
    }
    std::cout << std::endl;

    std::cout << "=== Example 3: Copy Constructor ===" << std::endl;
    {
        MyClass obj3(100, "Original");
        MyClass obj4(obj3);  // Copy constructor
    }
    std::cout << std::endl;

    std::cout << "=== Example 4: Move Constructor ===" << std::endl;
    {
        MyClass obj6(std::move(MyClass(200, "ToMove")));  // Move constructor
    }
    std::cout << std::endl;

    std::cout << "=== Example 5: Copy Assignment Operator ===" << std::endl;
    {
        MyClass obj7(300, "First");
        MyClass obj8(400, "Second");
        obj8 = obj7;  // Copy assignment
    }
    std::cout << std::endl;

    std::cout << "=== Example 6: Move Assignment Operator ===" << std::endl;
    {
        MyClass obj10(600, "Target");
        obj10 = MyClass(500, "Source");  // Move assignment
    }
    std::cout << std::endl;

    std::cout << "=== All examples completed ===" << std::endl;

    return 0;
}