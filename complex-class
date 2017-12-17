#include <cmath>
#include <iostream>

class Complex {
 private:
    double x_re, x_im;

 public:
    explicit Complex(double re = 0, double im = 0)
            : x_re(re)
            , x_im(im)
    {}

    double Re() const {
        return x_re;
    }

    double Im() const {
        return x_im;
    }

    Complex& operator += (const Complex& other) {
        x_im += other.x_im;
        x_re += other.x_re;
        return *this;
    }

    Complex& operator -= (const Complex& other) {
        x_im -= other.x_im;
        x_re -= other.x_re;
        return *this;
    }

    Complex& operator *= (const Complex& other) {
        double temp_re = x_re * other.x_re - x_im * other.x_im;
        double temp_im = x_re * other.x_im + x_im * other.x_re;
        x_re = temp_re;
        x_im = temp_im;
        return *this;
    }

    Complex& operator /= (const Complex& other) {
        double temp = other.x_im * other.x_im + other.x_re * other.x_re;
        double temp_re = (x_re * other.x_re + x_im * other.x_im) / temp;
        double temp_im = (x_im * other.x_re - x_re * other.x_im) / temp;
        x_re = temp_re;
        x_im = temp_im;
        return *this;
    }

    bool operator == (const Complex& other) {
        return (x_re == other.x_re && x_im == other.x_im);
    }

    bool operator != (const Complex& other) {
        return (!(*this == other));
    }

    Complex operator + () const {
        return Complex(+x_re, +x_im);
    }

    Complex operator - () const {
        return Complex(-x_re, -x_im);
    }
};

double abs(const Complex& x) {
    return std::hypot(x.Im(), x.Re());
}

template <typename Real>
Complex operator * (Complex x, const Real& other) {
    return x *= Complex(static_cast<double>(other));
}

template <typename Real>
Complex operator * (const Real& other, Complex x) {
    return x *= Complex(static_cast<double>(other));
}

Complex operator * (Complex x, const Complex& other) {
    return x *= other;
}

template <typename Real>
Complex operator / (Complex x, const Real& other) {
    return x /= Complex(static_cast<double>(other));
}

template <typename Real>
Complex operator / (const Real& other, Complex x) {
    return Complex(static_cast<double>(other)) /= x;
}

Complex operator / (Complex x, const Complex& other) {
    return x /= other;
}

template <typename Real>
Complex operator + (Complex x, const Real& other) {
    return x += Complex(static_cast<double>(other));
}

template <typename Real>
Complex operator + (const Real& other, Complex x) {
    return x += Complex(static_cast<double>(other));
}

Complex operator + (Complex x, const Complex& other) {
    return x += other;
}

template <typename Real>
Complex operator - (Complex x, const Real& other) {
    return x -= Complex(static_cast<double>(other));
}

template <typename Real>
Complex operator - (const Real& other, Complex x) {
    return Complex(static_cast<double>(other)) -= x;
}
Complex operator - (Complex x, const Complex& other) {
    return x -= other;
}
