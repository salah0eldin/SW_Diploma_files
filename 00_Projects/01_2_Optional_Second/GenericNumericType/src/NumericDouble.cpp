#include "../include/NumericDouble.h"
#include "../include/NumericInt.h"
#include "../include/NumericFloat.h"
#include "../include/NumericChar.h"
#include "../include/NumericComplex.h"
#include <stdexcept>
#include <cmath>

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

// NumericDouble implementations
std::unique_ptr<Numeric> NumericDouble::add(const Numeric& other) const {
    return std::make_unique<NumericDouble>(value + getNumericValue(other));
}

std::unique_ptr<Numeric> NumericDouble::subtract(const Numeric& other) const {
    return std::make_unique<NumericDouble>(value - getNumericValue(other));
}

std::unique_ptr<Numeric> NumericDouble::multiply(const Numeric& other) const {
    return std::make_unique<NumericDouble>(value * getNumericValue(other));
}

std::unique_ptr<Numeric> NumericDouble::divide(const Numeric& other) const {
    double otherVal = getNumericValue(other);
    if (otherVal == 0.0)
        throw std::runtime_error("Division by zero");
    return std::make_unique<NumericDouble>(value / otherVal);
}

bool NumericDouble::lessThan(const Numeric& other) const {
    return value < getNumericValue(other);
}

bool NumericDouble::greaterThan(const Numeric& other) const {
    return value > getNumericValue(other);
}

bool NumericDouble::equals(const Numeric& other) const {
    return std::abs(value - getNumericValue(other)) < 1e-9;
}
