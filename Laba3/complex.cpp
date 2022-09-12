#include "complex.h"
#include <limits>

bool is_equal(Real a, Real b) {
    return fabs(a - b) < std::numeric_limits<Real>::epsilon();
}

Complex::Complex() :
    _real(0),
    _imagine(0)
{ }

Complex::Complex(Real x) :
    _real(x),
    _imagine(0)
{ }

Complex::Complex(int x) :
    Complex(static_cast<Real>(x))
{ }

Complex::Complex(Real real, Real imagine) :
    _real(real),
    _imagine(imagine)
{ }

Complex::Complex(const Complex &obj) :
    _real(obj._real),
    _imagine(obj._imagine)
{ }

Complex &Complex::operator=(const Complex &obj) {
    if(this != &obj)
    {
        _real = obj._real;
        _imagine = obj._imagine;
    }

    return *this;
}

Complex Complex::operator+(const Complex &rhs) {
    return Complex(this->_real + rhs._real, this->_imagine + rhs._imagine);
}

Complex Complex::operator-(const Complex &rhs) {
    return Complex(this->_real - rhs._real, this->_imagine - rhs._imagine);
}

Complex operator*(const Complex &lhs, const Complex &rhs) {
    Real real = lhs._real * rhs._real - lhs._imagine * rhs._imagine;
    Real imagine = lhs._imagine * rhs._real + lhs._real * rhs._imagine;
    return Complex(real, imagine);
}

Complex operator/(const Complex &lhs, const Complex &rhs) {
    Real denom = rhs._real * rhs._real + rhs._imagine * rhs._imagine;
    Real real = (lhs._real * rhs._real + lhs._imagine * rhs._imagine) / denom;
    Real imagine = (lhs._imagine * rhs._real + lhs._real * rhs._imagine) / denom;
    return Complex(real, imagine);
}

bool Complex::operator==(const Complex &rhs) {
    return is_equal(_real, rhs._real) && is_equal(_imagine, rhs._imagine);
}

bool Complex::operator!=(const Complex &rhs) {
    return !(*this == rhs);
}

std::ostream &operator <<(std::ostream &os, const Complex &val) {
    auto sign = val.imagine() > 0 ? '+' : '-';
    os << val.real() << ' ' << sign << " j" << fabs(val.imagine());

    return os;
}
