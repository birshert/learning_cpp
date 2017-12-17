#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <utility>

template <typename T>
class Polynomial {
private:
    std::map<size_t, T> data;

    void normalize(std::map<size_t, T> &coef) {
        for (auto iter = coef.begin(); iter  != coef.end();) {
            if (iter->second == T(0)) {
                iter = coef.erase(iter);
            } else {
                iter++;
            }
        }
    }

public:
    Polynomial<T>(const std::vector<T> &coef) {
        for (size_t i = 0; i != coef.size(); ++i) {
            data[i];
            data[i] = coef[i];
        }
        normalize(data);
    }

    template <typename Iter>
    Polynomial<T>(Iter first, Iter last) {
        data.clear();
        size_t degree = 0;
        for (; first != last; ++degree) {
            data[degree];
            data[degree] = *first++;
        }
        normalize(data);
    }

    Polynomial<T>(const T &num = T()) {
        data.clear();
        data[0];
        data[0] = num;
        normalize(data);
    }

    bool operator == (const Polynomial<T> &other) {
        return data == other.data;
    }

    bool operator != (const Polynomial<T> &other) {
        return data != other.data;
    }

    bool operator == (const T &num) {
        return data == Polynomial<T>(num).data;
    }

    bool operator != (const T &num) {
        return data != Polynomial<T>(num).data;
    }

    T operator [] (size_t i) const {
        if (data.find(i) != data.end()) {
            return data.at(i);
        } else {
            return T(0);
        }
    }

    T operator () (const T& point) const {
        if (data.empty()) {
            return T(0);
        } else {
            T ans = T(0);
            T x = T(1);
            for (size_t i = 0; i != Degree() + 1; ++i) {
                if (data.count(i)) {
                    ans += data.at(i) * x;
                }
                x *= point;
            }
            return ans;
        }
    }

    Polynomial& operator *= (const Polynomial& other) {
        if (data.empty() || other.data.empty()) {
            Polynomial<T> temp(T(0));
            data = temp.data;
            return *this;
        }
        size_t deg = Degree() + other.Degree() + 2;
        std::vector <T> temp(deg + 1);
        for (size_t i = 0; i != temp.size(); ++i) {
            temp[i] = T(0);
        }
        for (auto it1 = other.data.begin(); it1 != other.data.end(); ++it1) {
            for (auto it2 = data.begin(); it2 != data.end(); ++it2) {
                temp[it1->first + it2->first] += it1->second * it2->second;
            }
        }
        Polynomial<T> copy(temp);
        data = copy.data;
        normalize(data);
        return *this;
    }

    Polynomial& operator *= (const T& other) {
        for (auto it = data.begin(); it != data.end(); ++it) {
            it->second *= other;
        }
        normalize(data);
        return *this;
    }

    long long Degree() const {
        if (data.empty()) {
            return -1;
        } else {
            return static_cast<long long>(data.rbegin()->first);
        }
    }

    Polynomial<T>& operator += (const Polynomial<T> &other) {
        for (auto kv : other.data) {
            data[kv.first];
            data[kv.first] += kv.second;
        }
        normalize(data);
        return *this;
    }

    Polynomial<T>& operator -= (const Polynomial<T> &other) {
        for (auto kv : other.data) {
            data[kv.first];
            data[kv.first] -= kv.second;
        }
        normalize(data);
        return *this;
    }

    friend std::ostream& operator << (std::ostream& out, const Polynomial<T> &pol) {
        bool flag = false;
        for (auto iter = pol.data.rbegin(); iter != pol.data.rend(); ++iter) {
            T coef = iter->second;
            size_t degree = iter->first;
            if (coef > T(0) && flag) {
                out << '+';
            }
            flag = true;
            if (degree == 0) {
                out << coef;
            } else if (coef == T(1)) {
                out << 'x';
            } else if (coef == T(-1)) {
                out << "-x";
            } else {
                out << coef << "*x";
            }
            if (degree > 1) {
                out << '^' << degree;
            }
        }
        if (pol.data.size() == 0) {
            out << 0;
        }
        return out;
    }

    friend Polynomial<T> operator & (const Polynomial<T>& first, const Polynomial<T>& second) {
        Polynomial<T> ans;
        if (first.data.find(0) != first.data.end()) {
            ans += first.data.find(0)->second;
        }
        Polynomial<T> copy = second;
        size_t degree = 1;
        for (auto iter = first.data.begin(); iter != first.data.end(); ++iter) {
            if (iter->first != 0) {
                while (degree != iter->first) {
                    copy *= second;
                    ++degree;
                }
                ans += copy * iter->second;
            }
        }
        return ans;
    }

    Polynomial<T> operator /= (const Polynomial<T> &other) {
        Polynomial<T> ans(T(0));
        while (this->Degree() >= other.Degree()) {
            int deg = this->Degree() - other.Degree();
            T k = data.rbegin()->second / other.data.rbegin()->second;
            std::map<size_t, T> temp;
            temp[deg] = k;
            Polynomial<T> pol;
            pol.data = temp;
            ans += pol;
            *this -= other * pol;
        }
        *this = ans;
        return *this;
    }

    Polynomial<T> &operator%=(const Polynomial<T> &other) {
        Polynomial<T> k = *this / other;
        *this -= other * k;
        normalize(data);
        return *this;
    }

    friend Polynomial<T> operator , (const Polynomial<T>& first, const Polynomial<T>& second) {
        Polynomial<T> gcd = first, copy = second;
        while (copy.data.size() != 0) {
            gcd %= copy;
            std::swap(gcd, copy);
        }
        if (gcd.data.size() != 0) {
            Polynomial<T> div(gcd.data.rbegin()->second);
            gcd /= div;
        }
        return gcd;
    }

    auto begin() const {
        return data.begin();
    }

    auto end() const {
        return data.end();
    }
};

template <typename T>
Polynomial<T> operator +(Polynomial<T> first, const Polynomial<T> &second) {
    return first += second;
}

template <typename T>
Polynomial<T> operator -(Polynomial<T> first, const Polynomial<T> &second) {
    return first -= second;
}

template <typename T>
Polynomial<T> operator *(Polynomial<T> first, const Polynomial<T> &second) {
    return first *= second;
}

template<typename T>
Polynomial<T> operator /(const Polynomial<T> &first, const Polynomial<T> &second) {
    auto copy = first;
    copy /= second;
    return copy;
}

template<typename T>
Polynomial<T> operator %(const Polynomial<T> &first, const Polynomial<T> &second) {
    auto copy = first;
    copy %= second;
    return copy;
}

template <typename T>
Polynomial<T> operator +(Polynomial<T> poly, const T &num) {
    return poly += Polynomial<T>(num);
}

template <typename T>
Polynomial<T> operator +(const T &num, Polynomial<T> poly) {
    return poly += Polynomial<T>(num);
}

template <typename T>
Polynomial<T> operator -(Polynomial<T> poly, const T &num) {
    return poly -= Polynomial<T>(num);
}

template <typename T>
Polynomial<T> operator -(const T &num, Polynomial<T> poly) {
    return Polynomial<T>(num) -= poly;
}

template <typename T>
Polynomial<T> operator *(Polynomial<T> poly, const T &num) {
    return poly *= Polynomial<T>(num);
}

template <typename T>
Polynomial<T> operator *(const T &num, Polynomial<T> poly) {
    return poly *= Polynomial<T>(num);
}
