#include "../include/NumericInt.h"
#include "../include/NumericDouble.h"
#include "../include/NumericFloat.h"
#include "../include/NumericChar.h"
#include "../include/NumericComplex.h"
#include <stdexcept>

// Helper function to get numeric value as double for comparison
static double getNumericValue(const Numeric& num) {
    if (const NumericInt* p = dynamic_cast<const NumericInt*>(&num))
        return p->getValue();
    if (const NumericDouble* p = dynamic_cast<const NumericDouble*>(&num))
        return p->getValue();
    if (const NumericFloat* p = dynamic_cast<const NumericFloat*>(&num))
        return p->getValue();
    if (const NumericChar* p = dynamic_cast<const NumericChar*>(&num))
        return static_cast<double>(p->getValue());
    if (const NumericComplex* p = dynamic_cast<const NumericComplex*>(&num))
        return std::abs(p->getValue());
    throw std::runtime_error("Unknown numeric type");
}

// NumericInt implementations
std::unique_ptr<Numeric> NumericInt::add(const Numeric& other) const {
    double otherVal = getNumericValue(other);
    return std::make_unique<NumericInt>(value + static_cast<int>(otherVal));
}

std::unique_ptr<Numeric> NumericInt::subtract(const Numeric& other) const {
    double otherVal = getNumericValue(other);
    return std::make_unique<NumericInt>(value - static_cast<int>(otherVal));
}

std::unique_ptr<Numeric> NumericInt::multiply(const Numeric& other) const {
    double otherVal = getNumericValue(other);
    return std::make_unique<NumericInt>(value * static_cast<int>(otherVal));
}

std::unique_ptr<Numeric> NumericInt::divide(const Numeric& other) const {
    double otherVal = getNumericValue(other);
    if (otherVal == 0)
        throw std::runtime_error("Division by zero");
    return std::make_unique<NumericInt>(value / static_cast<int>(otherVal));
}

bool NumericInt::lessThan(const Numeric& other) const {
    return value < getNumericValue(other);
}

bool NumericInt::greaterThan(const Numeric& other) const {
    return value > getNumericValue(other);
}

bool NumericInt::equals(const Numeric& other) const {
    return value == getNumericValue(other);
}
