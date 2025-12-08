#ifndef NUMERIC_FLOAT_H
#define NUMERIC_FLOAT_H

#include "Numeric.h"
#include <sstream>
#include <iomanip>

/**
 * Derived class for float numeric type
 */
class NumericFloat : public Numeric {
private:
    float value;

public:
    // Constructor
    explicit NumericFloat(float val = 0.0f) : value(val) {}

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
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << value;
        return oss.str() + "f";
    }

    // Clone method
    std::unique_ptr<Numeric> clone() const override {
        return std::make_unique<NumericFloat>(value);
    }

    // Getter
    float getValue() const { return value; }
};

#endif // NUMERIC_FLOAT_H
