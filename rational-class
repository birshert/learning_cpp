#include <iostream>

class Rational {
 private:
    int x_u, x_l;

    int gcd(int a, int b) {
        if (b == 0) {
            return a;
        } else {
            return gcd(b, a % b);
        }
    }

    Rational& normal() {
        int u = x_u;
        int l = x_l;

        int gcd_temp = gcd(abs(l), abs(u));

        if (gcd_temp != 0) {
            u /= gcd_temp;
            l /= gcd_temp;
        }

        if (l < 0) {
            l *= -1;
            u *= -1;
        }

        x_u = u;
        x_l = l;

        return *this;
    }

 public:
    explicit Rational(int u = 0, int l = 1)
            : x_u(u)
            , x_l(l) {
        normal();
    }

    int numerator() const {
        return x_u;
    }

    int denominator() const {
        return x_l;
    }

    int u() {
        return x_u;
    }

    int l() {
        return x_l;
    }

    Rational operator -() {
        return (Rational(-x_u, x_l));
    }

    Rational operator +() {
        return (Rational(+x_u, +x_l));
    }

    Rational& operator += (const Rational& other) {
        int temp_l = x_l * other.x_l;
        int temp_u = x_u *  other.x_l + other.x_u * x_l;
        x_u = temp_u;
        x_l = temp_l;
        return normal();
    }

    Rational& operator -= (const Rational& other) {
        int temp_l = x_l * other.x_l;
        int temp_u = x_u *  other.x_l - other.x_u * x_l;
        x_u = temp_u;
        x_l = temp_l;
        return normal();
    }

    Rational& operator *= (const Rational& other) {
        int temp_u = x_u, temp_l = x_l;
        temp_u = x_u * other.x_u;
        temp_l = x_l * other.x_l;
        x_u = temp_u;
        x_l = temp_l;
        return normal();
    }

    Rational& operator /= (const Rational& other) {
        int temp_u = x_u, temp_l = x_l;
        temp_u = x_u * other.x_l;
        temp_l = x_l * other.x_u;
        x_u = temp_u;
        x_l = temp_l;
        return normal();
    }

    bool operator == (const Rational& other) {
        return (x_u == other.x_u && x_l == other.x_l);
    }

    bool operator != (const Rational& other) {
        return !(*this == other);
    }

    Rational& operator ++() {
        x_u += x_l;
        return normal();
    }

    Rational operator ++(int) {
        auto copy = *this;
        x_u += x_l;
        return copy;
    }

    Rational& operator --() {
        x_u -= x_l;
        return normal();
    }

    Rational operator --(int) {
        auto copy = *this;
        x_u -= x_l;
        return copy;
    }
};

Rational operator + (Rational x, const Rational& other) {
    return x += other;
}

Rational operator + (Rational x, int num) {
    return x += Rational(num * x.l(), x.l());
}

Rational operator + (int num, Rational x) {
    return Rational(num * x.l(), x.l()) += x;
}

Rational operator - (Rational x, const Rational& other) {
    return x -= other;
}

Rational operator - (Rational x, int num) {
    return x -= Rational(num * x.l(), x.l());
}

Rational operator - (int num, Rational x) {
    return Rational(num * x.l(), x.l()) -= x;
}

Rational operator * (Rational x, const Rational& other) {
    return x *= other;
}

Rational operator * (Rational x, int num) {
    return Rational(x.u() * num, x.l());
}

Rational operator * (int num, Rational x) {
    return Rational(x.u() * num, x.l());
}

Rational operator / (Rational x, const Rational& other) {
    return x /= other;
}

Rational operator / (Rational x, int num) {
    return Rational(x.u(), x.l() * num);
}

Rational operator / (int num, Rational x) {
    return Rational(x.u(), x.l() * num);
}
