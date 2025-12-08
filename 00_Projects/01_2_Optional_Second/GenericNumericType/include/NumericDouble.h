#ifndef NUMERIC_DOUBLE_H
#define NUMERIC_DOUBLE_H

#include "Numeric.h"
#include <sstream>
#include <iomanip>

/**
 * Derived class for double numeric type
 */
class NumericDouble : public Numeric {
private:
    double value;

public:
    // Constructor
    explicit NumericDouble(double val = 0.0) : value(val) {}

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
        return oss.str();
    }

    // Clone method
    std::unique_ptr<Numeric> clone() const override {
        return std::make_unique<NumericDouble>(value);
    }

    // Getter
    double getValue() const { return value; }
};

#endif // NUMERIC_DOUBLE_H
