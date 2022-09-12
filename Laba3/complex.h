#ifndef COMPLEX_H
#define COMPLEX_H

#include <cmath>
#include <ostream>

using Real = double;

class Complex {
public:
    Complex();

    Complex(Real x);

    Complex(int x);

    Complex(Real real, Real imagine);

    Complex(Complex const& obj);

    Complex(Complex && obj) = default;

    Complex& operator=(Complex const& obj);

    Complex &operator=(Complex && obj) = default;

    Complex operator+(Complex const& rhs);

    Complex operator-(Complex const& rhs);

    friend Complex operator*(Complex const& lhs, Complex const& rhs);

    friend Complex operator/(Complex const& lhs, Complex const& rhs);

    bool operator==(Complex const& rhs);

    bool operator!=(Complex const& rhs);

    inline Real real() const {
        return _real;
    }

    inline Real imagine() const {
        return _imagine;
    }

    friend std::ostream& operator <<(std::ostream& os, Complex const& val);

private:
    Real _real;
    Real _imagine;
};

#endif // COMPLEX_H
