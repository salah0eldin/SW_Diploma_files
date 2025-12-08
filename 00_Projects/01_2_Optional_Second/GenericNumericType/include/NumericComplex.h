#ifndef NUMERIC_COMPLEX_H
#define NUMERIC_COMPLEX_H

#include "Numeric.h"
#include <complex>
#include <sstream>
#include <iomanip>

/**
 * Derived class for complex<double> numeric type
 */
class NumericComplex : public Numeric {
private:
    std::complex<double> value;

public:
    // Constructor
    explicit NumericComplex(double real = 0.0, double imag = 0.0) 
        : value(real, imag) {}
    
    explicit NumericComplex(const std::complex<double>& val) 
        : value(val) {}

    // Arithmetic operations
    std::unique_ptr<Numeric> add(const Numeric& other) const override;
    std::unique_ptr<Numeric> subtract(const Numeric& other) const override;
    std::unique_ptr<Numeric> multiply(const Numeric& other) const override;
    std::unique_ptr<Numeric> divide(const Numeric& other) const override;

    // Comparison operations (based on magnitude)
    bool lessThan(const Numeric& other) const override;
    bool greaterThan(const Numeric& other) const override;
    bool equals(const Numeric& other) const override;

    // String conversion
    std::string toString() const override {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2);
        oss << value.real();
        if (value.imag() >= 0)
            oss << "+";
        oss << value.imag() << "i";
        return oss.str();
    }

    // Clone method
    std::unique_ptr<Numeric> clone() const override {
        return std::make_unique<NumericComplex>(value);
    }

    // Getter
    std::complex<double> getValue() const { return value; }
};

#endif // NUMERIC_COMPLEX_H
