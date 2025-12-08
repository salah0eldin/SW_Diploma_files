#ifndef NUMERIC_H
#define NUMERIC_H

#include <string>
#include <iostream>
#include <memory>

/**
 * Abstract base class for all numeric types
 * Provides interface for arithmetic operations, comparisons, and I/O
 */
class Numeric {
public:
    // Virtual destructor for proper cleanup
    virtual ~Numeric() = default;

    // Pure virtual arithmetic operations
    virtual std::unique_ptr<Numeric> add(const Numeric& other) const = 0;
    virtual std::unique_ptr<Numeric> subtract(const Numeric& other) const = 0;
    virtual std::unique_ptr<Numeric> multiply(const Numeric& other) const = 0;
    virtual std::unique_ptr<Numeric> divide(const Numeric& other) const = 0;

    // Pure virtual comparison operations
    virtual bool lessThan(const Numeric& other) const = 0;
    virtual bool greaterThan(const Numeric& other) const = 0;
    virtual bool equals(const Numeric& other) const = 0;

    // Pure virtual string conversion
    virtual std::string toString() const = 0;

    // Pure virtual clone method for copying
    virtual std::unique_ptr<Numeric> clone() const = 0;

    // Stream output operator
    friend std::ostream& operator<<(std::ostream& os, const Numeric& num);
};

// Stream output implementation
inline std::ostream& operator<<(std::ostream& os, const Numeric& num) {
    os << num.toString();
    return os;
}

#endif // NUMERIC_H
