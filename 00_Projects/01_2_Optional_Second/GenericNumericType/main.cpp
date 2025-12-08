#include "include/Numeric.h"
#include "include/NumericInt.h"
#include "include/NumericDouble.h"
#include "include/NumericFloat.h"
#include "include/NumericChar.h"
#include "include/NumericComplex.h"
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

// Helper function to print a separator
void printSeparator(const std::string& title = "") {
    std::cout << "\n" << std::string(60, '=') << "\n";
    if (!title.empty()) {
        std::cout << "  " << title << "\n";
        std::cout << std::string(60, '=') << "\n";
    }
}

// Function to display all elements in the vector
void displayVector(const std::vector<std::unique_ptr<Numeric>>& vec) {
    std::cout << "Vector contents:\n";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << "  [" << i << "] = " << *vec[i] << "\n";
    }
}

// Demonstration of arithmetic operations
void demonstrateArithmetic() {
    printSeparator("Arithmetic Operations Demo");
    
    NumericInt a(10);
    NumericDouble b(3.5);
    NumericFloat c(2.5f);
    
    std::cout << "a = " << a << " (int)\n";
    std::cout << "b = " << b << " (double)\n";
    std::cout << "c = " << c << " (float)\n\n";
    
    // Addition
    auto sum = a.add(b);
    std::cout << "a + b = " << *sum << "\n";
    
    // Subtraction
    auto diff = a.subtract(c);
    std::cout << "a - c = " << *diff << "\n";
    
    // Multiplication
    auto prod = b.multiply(c);
    std::cout << "b * c = " << *prod << "\n";
    
    // Division
    auto quot = a.divide(b);
    std::cout << "a / b = " << *quot << "\n";
}

// Demonstration of comparison operations
void demonstrateComparison() {
    printSeparator("Comparison Operations Demo");
    
    NumericInt a(5);
    NumericDouble b(5.0);
    NumericFloat c(10.5f);
    
    std::cout << "a = " << a << " (int)\n";
    std::cout << "b = " << b << " (double)\n";
    std::cout << "c = " << c << " (float)\n\n";
    
    std::cout << "a < c: " << (a.lessThan(c) ? "true" : "false") << "\n";
    std::cout << "c > a: " << (c.greaterThan(a) ? "true" : "false") << "\n";
    std::cout << "a == b: " << (a.equals(b) ? "true" : "false") << "\n";
    std::cout << "a == c: " << (a.equals(c) ? "true" : "false") << "\n";
}

// Demonstration of complex numbers
void demonstrateComplex() {
    printSeparator("Complex Number Operations Demo");
    
    NumericComplex c1(3.0, 4.0);
    NumericComplex c2(1.0, 2.0);
    NumericInt real(5);
    
    std::cout << "c1 = " << c1 << "\n";
    std::cout << "c2 = " << c2 << "\n";
    std::cout << "real = " << real << "\n\n";
    
    auto sum = c1.add(c2);
    std::cout << "c1 + c2 = " << *sum << "\n";
    
    auto diff = c1.subtract(c2);
    std::cout << "c1 - c2 = " << *diff << "\n";
    
    auto prod = c1.multiply(c2);
    std::cout << "c1 * c2 = " << *prod << "\n";
    
    auto quot = c1.divide(c2);
    std::cout << "c1 / c2 = " << *quot << "\n";
    
    auto complexPlusReal = c1.add(real);
    std::cout << "c1 + real = " << *complexPlusReal << "\n";
}

// Demonstration of char operations
void demonstrateChar() {
    printSeparator("Char Operations Demo");
    
    NumericChar ch1('A');
    NumericChar ch2('B');
    NumericInt offset(3);
    
    std::cout << "ch1 = " << ch1 << "\n";
    std::cout << "ch2 = " << ch2 << "\n";
    std::cout << "offset = " << offset << "\n\n";
    
    auto sum = ch1.add(offset);
    std::cout << "ch1 + offset = " << *sum << "\n";
    
    auto diff = ch2.subtract(ch1);
    std::cout << "ch2 - ch1 = " << *diff << "\n";
    
    std::cout << "ch1 < ch2: " << (ch1.lessThan(ch2) ? "true" : "false") << "\n";
}

// Main demonstration with vector
void demonstrateVector() {
    printSeparator("Vector of Mixed Numeric Types");
    
    // Create vector of Numeric pointers
    std::vector<std::unique_ptr<Numeric>> numbers;
    
    // Push different numeric types
    numbers.push_back(std::make_unique<NumericInt>(42));
    numbers.push_back(std::make_unique<NumericDouble>(3.14159));
    numbers.push_back(std::make_unique<NumericFloat>(2.718f));
    numbers.push_back(std::make_unique<NumericChar>('X'));
    numbers.push_back(std::make_unique<NumericComplex>(3.0, 4.0));
    numbers.push_back(std::make_unique<NumericInt>(-15));
    numbers.push_back(std::make_unique<NumericDouble>(99.99));
    
    displayVector(numbers);
    
    // Sort the vector based on comparison
    printSeparator("Sorting Vector");
    std::sort(numbers.begin(), numbers.end(),
        [](const std::unique_ptr<Numeric>& a, const std::unique_ptr<Numeric>& b) {
            return a->lessThan(*b);
        });
    
    displayVector(numbers);
    
    // Perform operations on vector elements
    printSeparator("Operations on Vector Elements");
    
    if (numbers.size() >= 2) {
        std::cout << "Adding first two elements:\n";
        auto sum = numbers[0]->add(*numbers[1]);
        std::cout << *numbers[0] << " + " << *numbers[1] << " = " << *sum << "\n\n";
        
        std::cout << "Multiplying elements at index 2 and 3:\n";
        if (numbers.size() >= 4) {
            auto prod = numbers[2]->multiply(*numbers[3]);
            std::cout << *numbers[2] << " * " << *numbers[3] << " = " << *prod << "\n";
        }
    }
}

// Demonstrate cloning
void demonstrateCloning() {
    printSeparator("Cloning Objects");
    
    NumericInt original(100);
    std::cout << "Original: " << original << "\n";
    
    auto cloned = original.clone();
    std::cout << "Cloned: " << *cloned << "\n";
    
    auto modified = cloned->add(NumericInt(50));
    std::cout << "Cloned + 50: " << *modified << "\n";
    std::cout << "Original (unchanged): " << original << "\n";
}

// Error handling demonstration
void demonstrateErrorHandling() {
    printSeparator("Error Handling Demo");
    
    NumericInt a(10);
    NumericInt zero(0);
    
    std::cout << "Attempting division by zero...\n";
    try {
        auto result = a.divide(zero);
        std::cout << "Result: " << *result << "\n";
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << "\n";
    }
}

int main() {
    std::cout << "\n";
    std::cout << "========================================================\n";
    std::cout << "  Generic Numeric Data Type - Comprehensive Demo\n";
    std::cout << "========================================================\n";
    
    try {
        // Run all demonstrations
        demonstrateArithmetic();
        demonstrateComparison();
        demonstrateComplex();
        demonstrateChar();
        demonstrateVector();
        demonstrateCloning();
        demonstrateErrorHandling();
        
        printSeparator("Demo Complete");
        std::cout << "\nAll demonstrations completed successfully!\n\n";
        
    } catch (const std::exception& e) {
        std::cerr << "\nUnexpected error: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}
