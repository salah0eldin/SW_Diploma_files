#include <iostream>

template <typename T>
class Base {
public:
    T value;

    virtual void getValue() {
        std::cout << "Value of T: " << value << std::endl;
    }
    
};

template <>
class Base<int> : public Base<> {
public:
    void getValue() override {
        std::cout << "Value of int: " << value << std::endl;
    }
};

int main() {

    return 0;
}
