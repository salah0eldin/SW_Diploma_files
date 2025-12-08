#ifndef NUMERIC_CHAR_H
#define NUMERIC_CHAR_H

#include "Numeric.h"
#include <sstream>

/**
 * Derived class for char numeric type
 */
class NumericChar : public Numeric {
private:
    char value;

public:
    // Constructor
    explicit NumericChar(char val = '\0') : value(val) {}

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
        oss << "'" << value << "' (" << static_cast<int>(value) << ")";
        return oss.str();
    }

    // Clone method
    std::unique_ptr<Numeric> clone() const override {
        return std::make_unique<NumericChar>(value);
    }

    // Getter
    char getValue() const { return value; }
};

#endif // NUMERIC_CHAR_H
