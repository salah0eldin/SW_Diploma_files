# Generic Numeric Data Type in C++

## Project Overview
A polymorphic numeric type system that unifies different numeric types (int, double, float, char, complex) under a common interface using object-oriented programming principles.

## Features
- **Abstract Base Class**: `Numeric` serves as the base for all numeric types
- **Polymorphic Operations**: Runtime polymorphism through virtual functions
- **Multiple Numeric Types**: Support for int, double, float, char, and complex<double>
- **Arithmetic Operations**: Addition, subtraction, multiplication, and division
- **Comparison Operations**: Less than, greater than, and equality checks
- **Type-Safe**: Uses smart pointers (std::unique_ptr) for memory management
- **String Conversion**: toString() method for all types
- **Stream I/O**: Overloaded stream operators for easy output

## Project Structure
```
GenericNumericType/
├── include/
│   ├── Numeric.h           # Abstract base class
│   ├── NumericInt.h        # Integer implementation
│   ├── NumericDouble.h     # Double implementation
│   ├── NumericFloat.h      # Float implementation
│   ├── NumericChar.h       # Character implementation
│   └── NumericComplex.h    # Complex number implementation
├── src/
│   ├── NumericInt.cpp      # Integer implementation
│   ├── NumericDouble.cpp   # Double implementation
│   ├── NumericFloat.cpp    # Float implementation
│   ├── NumericChar.cpp     # Character implementation
│   └── NumericComplex.cpp  # Complex implementation
├── main.cpp                # Demonstration program
├── Makefile                # Build configuration
└── README.md               # This file
```

## Requirements
- C++14 or later
- g++ compiler (or any C++14 compatible compiler)
- Make (for building with Makefile)

## Building the Project

### Using Make (Recommended)
```bash
# Build the project
make

# Build and run
make run

# Clean build artifacts
make clean

# Rebuild from scratch
make rebuild

# Show help
make help
```

### Manual Compilation
```bash
# Create build directory
mkdir -p build/obj

# Compile source files
g++ -std=c++14 -Wall -Wextra -Iinclude -c src/NumericInt.cpp -o build/obj/NumericInt.o
g++ -std=c++14 -Wall -Wextra -Iinclude -c src/NumericDouble.cpp -o build/obj/NumericDouble.o
g++ -std=c++14 -Wall -Wextra -Iinclude -c src/NumericFloat.cpp -o build/obj/NumericFloat.o
g++ -std=c++14 -Wall -Wextra -Iinclude -c src/NumericChar.cpp -o build/obj/NumericChar.o
g++ -std=c++14 -Wall -Wextra -Iinclude -c src/NumericComplex.cpp -o build/obj/NumericComplex.o
g++ -std=c++14 -Wall -Wextra -Iinclude -c main.cpp -o build/obj/main.o

# Link
g++ build/obj/*.o -o build/numeric_demo

# Run
./build/numeric_demo
```

## Usage Example

```cpp
#include "include/Numeric.h"
#include "include/NumericInt.h"
#include "include/NumericDouble.h"
#include <vector>
#include <memory>

int main() {
    // Create a vector of mixed numeric types
    std::vector<std::unique_ptr<Numeric>> numbers;
    
    // Add different types
    numbers.push_back(std::make_unique<NumericInt>(42));
    numbers.push_back(std::make_unique<NumericDouble>(3.14));
    
    // Perform operations
    auto sum = numbers[0]->add(*numbers[1]);
    std::cout << *sum << std::endl;
    
    // Compare values
    if (numbers[0]->lessThan(*numbers[1])) {
        std::cout << "First is smaller" << std::endl;
    }
    
    return 0;
}
```

## Key Design Decisions

### 1. Abstract Base Class
- Pure virtual functions enforce implementation in derived classes
- Virtual destructor ensures proper cleanup
- No templates in base class (as per requirements)

### 2. Smart Pointers
- `std::unique_ptr` for automatic memory management
- Prevents memory leaks
- Clear ownership semantics

### 3. Dynamic Type Checking
- `dynamic_cast` for type-specific operations
- Allows complex numbers to interact with other types
- Falls back to numeric value conversion when needed

### 4. Comparison Strategy
- Complex numbers compared by magnitude
- Other types compared by numeric value
- Floating point comparison uses epsilon for equality

### 5. Clone Pattern
- Deep copying through virtual clone() method
- Enables proper copying in polymorphic contexts

## Demonstration Features

The main program demonstrates:
1. **Arithmetic Operations**: All basic math operations
2. **Comparison Operations**: All comparison operators
3. **Complex Numbers**: Full complex number support
4. **Character Operations**: Arithmetic with characters
5. **Vector Storage**: Storing mixed types in std::vector
6. **Sorting**: Sorting mixed numeric types
7. **Cloning**: Deep copying objects
8. **Error Handling**: Division by zero protection

## Implementation Highlights

### Polymorphic Operations
All operations return `std::unique_ptr<Numeric>`, allowing runtime polymorphism:
```cpp
std::unique_ptr<Numeric> result = num1->add(*num2);
```

### Type Conversions
Automatic conversion between compatible types for operations:
```cpp
NumericInt a(5);
NumericDouble b(3.5);
auto sum = a.add(b);  // Works seamlessly
```

### Stream Output
Clean output through overloaded operators:
```cpp
NumericComplex c(3.0, 4.0);
std::cout << c;  // Outputs: 3.00+4.00i
```

## Limitations & Future Enhancements

### Current Limitations
- Type conversions may lose precision
- Limited operator overloading (uses methods instead)
- No input stream support yet

### Potential Enhancements
- Add more numeric types (long, unsigned variants)
- Implement operator overloading (+, -, *, /, <, >, ==)
- Add std::istream support for reading values
- Implement more complex operations (pow, sqrt, etc.)
- Add unit tests
- Improve complex number operations with other types

## License
Educational project for SW Diploma program.

## Author
Created as part of the Generic Numeric Data Type Mini Project.
