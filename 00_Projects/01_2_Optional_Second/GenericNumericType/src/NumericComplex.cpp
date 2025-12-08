#include "../include/NumericComplex.h"
#include "../include/NumericInt.h"
#include "../include/NumericDouble.h"
#include "../include/NumericFloat.h"
#include "../include/NumericChar.h"
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

// NumericComplex implementations
std::unique_ptr<Numeric> NumericComplex::add(const Numeric& other) const {
    if (const NumericComplex* p = dynamic_cast<const NumericComplex*>(&other)) {
        return std::make_unique<NumericComplex>(value + p->getValue());
    }
    // Add real number to complex
    double otherVal = getNumericValue(other);
    return std::make_unique<NumericComplex>(value.real() + otherVal, value.imag());
}

std::unique_ptr<Numeric> NumericComplex::subtract(const Numeric& other) const {
    if (const NumericComplex* p = dynamic_cast<const NumericComplex*>(&other)) {
        return std::make_unique<NumericComplex>(value - p->getValue());
    }
    // Subtract real number from complex
    double otherVal = getNumericValue(other);
    return std::make_unique<NumericComplex>(value.real() - otherVal, value.imag());
}

std::unique_ptr<Numeric> NumericComplex::multiply(const Numeric& other) const {
    if (const NumericComplex* p = dynamic_cast<const NumericComplex*>(&other)) {
        return std::make_unique<NumericComplex>(value * p->getValue());
    }
    // Multiply complex by real number
    double otherVal = getNumericValue(other);
    return std::make_unique<NumericComplex>(value * otherVal);
}

std::unique_ptr<Numeric> NumericComplex::divide(const Numeric& other) const {
    if (const NumericComplex* p = dynamic_cast<const NumericComplex*>(&other)) {
        std::complex<double> otherVal = p->getValue();
        if (std::abs(otherVal) == 0.0)
            throw std::runtime_error("Division by zero");
        return std::make_unique<NumericComplex>(value / otherVal);
    }
    // Divide complex by real number
    double otherVal = getNumericValue(other);
    if (otherVal == 0.0)
        throw std::runtime_error("Division by zero");
    return std::make_unique<NumericComplex>(value / otherVal);
}

bool NumericComplex::lessThan(const Numeric& other) const {
    // Compare magnitudes
    return std::abs(value) < getNumericValue(other);
}

bool NumericComplex::greaterThan(const Numeric& other) const {
    // Compare magnitudes
    return std::abs(value) > getNumericValue(other);
}

bool NumericComplex::equals(const Numeric& other) const {
    if (const NumericComplex* p = dynamic_cast<const NumericComplex*>(&other)) {
        std::complex<double> otherVal = p->getValue();
        return std::abs(value.real() - otherVal.real()) < 1e-9 &&
               std::abs(value.imag() - otherVal.imag()) < 1e-9;
    }
    // Compare magnitude with real number
    return std::abs(std::abs(value) - getNumericValue(other)) < 1e-9;
}
