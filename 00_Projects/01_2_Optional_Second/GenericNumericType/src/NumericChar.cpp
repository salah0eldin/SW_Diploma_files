#include "../include/NumericChar.h"
#include "../include/NumericInt.h"
#include "../include/NumericDouble.h"
#include "../include/NumericFloat.h"
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

// NumericChar implementations
std::unique_ptr<Numeric> NumericChar::add(const Numeric& other) const {
    int result = static_cast<int>(value) + static_cast<int>(getNumericValue(other));
    return std::make_unique<NumericChar>(static_cast<char>(result));
}

std::unique_ptr<Numeric> NumericChar::subtract(const Numeric& other) const {
    int result = static_cast<int>(value) - static_cast<int>(getNumericValue(other));
    return std::make_unique<NumericChar>(static_cast<char>(result));
}

std::unique_ptr<Numeric> NumericChar::multiply(const Numeric& other) const {
    int result = static_cast<int>(value) * static_cast<int>(getNumericValue(other));
    return std::make_unique<NumericChar>(static_cast<char>(result));
}

std::unique_ptr<Numeric> NumericChar::divide(const Numeric& other) const {
    int otherVal = static_cast<int>(getNumericValue(other));
    if (otherVal == 0)
        throw std::runtime_error("Division by zero");
    int result = static_cast<int>(value) / otherVal;
    return std::make_unique<NumericChar>(static_cast<char>(result));
}

bool NumericChar::lessThan(const Numeric& other) const {
    return static_cast<int>(value) < getNumericValue(other);
}

bool NumericChar::greaterThan(const Numeric& other) const {
    return static_cast<int>(value) > getNumericValue(other);
}

bool NumericChar::equals(const Numeric& other) const {
    return static_cast<int>(value) == static_cast<int>(getNumericValue(other));
}
