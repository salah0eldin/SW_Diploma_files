#include "../include/NumericFloat.h"
#include "../include/NumericInt.h"
#include "../include/NumericDouble.h"
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

// NumericFloat implementations
std::unique_ptr<Numeric> NumericFloat::add(const Numeric& other) const {
    return std::make_unique<NumericFloat>(value + static_cast<float>(getNumericValue(other)));
}

std::unique_ptr<Numeric> NumericFloat::subtract(const Numeric& other) const {
    return std::make_unique<NumericFloat>(value - static_cast<float>(getNumericValue(other)));
}

std::unique_ptr<Numeric> NumericFloat::multiply(const Numeric& other) const {
    return std::make_unique<NumericFloat>(value * static_cast<float>(getNumericValue(other)));
}

std::unique_ptr<Numeric> NumericFloat::divide(const Numeric& other) const {
    float otherVal = static_cast<float>(getNumericValue(other));
    if (otherVal == 0.0f)
        throw std::runtime_error("Division by zero");
    return std::make_unique<NumericFloat>(value / otherVal);
}

bool NumericFloat::lessThan(const Numeric& other) const {
    return value < getNumericValue(other);
}

bool NumericFloat::greaterThan(const Numeric& other) const {
    return value > getNumericValue(other);
}

bool NumericFloat::equals(const Numeric& other) const {
    return std::abs(value - static_cast<float>(getNumericValue(other))) < 1e-6f;
}
