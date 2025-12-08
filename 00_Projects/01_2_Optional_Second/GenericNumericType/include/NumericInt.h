#ifndef NUMERIC_INT_H
#define NUMERIC_INT_H

#include "Numeric.h"
#include <sstream>

/**
 * Derived class for integer numeric type
 */
class NumericInt : public Numeric {
private:
    int value;

public:
    // Constructor
    explicit NumericInt(int val = 0) : value(val) {}

    // Arithmetic operations
    std::unique_ptr<Numeric> add(const Numeric& other) const override;
    std::unique_ptr<Numeric> subtract(const Numeric& other) const override;
    std::unique_ptr<Numeric> multiply(const Numeric& other) const override;
    std::unique_ptr<Numeric> divide(const Numeric& other) const override;

    // Comparison operations
    bool lessThan(const Numeric& other) const override;
    bool greaterThan(const Numeric& other) const override;
    bool equals(const Numeric& other) const override;

    // String conversion
    std::string toString() const override {
        return std::to_string(value);
    }

    // Clone method
    std::unique_ptr<Numeric> clone() const override {
        return std::make_unique<NumericInt>(value);
    }

    // Getter
    int getValue() const { return value; }
};

#endif // NUMERIC_INT_H
