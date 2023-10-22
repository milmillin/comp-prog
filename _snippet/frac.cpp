#include <numeric>

using namespace std;

class Frac {
    public:
    // a / b
    long long a;
    long long b;

    Frac() : a(0), b(1) {}
    Frac(long long a_): a(a_), b(1) {}
    Frac(int a_): a(a_), b(1) {}
    Frac(long long a_, long long b_): a(a_), b(b_) { Fixme(); }

    Frac& operator+=(const Frac& rhs) {
        a = a * rhs.b + b * rhs.a;
        b = b * rhs.b;
        Fixme();
        return *this;
    }
    Frac& operator-=(const Frac& rhs) {
        a = a * rhs.b - b * rhs.a;
        b = b * rhs.b;
        Fixme();
        return *this;
    }
    Frac& operator*=(const Frac& rhs) {
        a *= rhs.a;
        b *= rhs.b;
        Fixme();
        return *this;
    }
    Frac& operator/=(const Frac& rhs) {
        a *= rhs.b;
        b *= rhs.a;
        Fixme();
        return *this;
    }
    Frac operator+() const { return *this; }
    Frac operator-() const { return Frac() - *this; }

    friend Frac operator+(const Frac& lhs, const Frac& rhs) {
        return Frac(lhs) += rhs;
    }
    friend Frac operator-(const Frac& lhs, const Frac& rhs) {
        return Frac(lhs) -= rhs;
    }
    friend Frac operator*(const Frac& lhs, const Frac& rhs) {
        return Frac(lhs) *= rhs;
    }
    friend Frac operator/(const Frac& lhs, const Frac& rhs) {
        return Frac(lhs) /= rhs;
    }
    friend bool operator==(const Frac& lhs, const Frac& rhs) {
        return lhs.a == rhs.a && lhs.b == rhs.b;
    }
    friend bool operator!=(const Frac& lhs, const Frac& rhs) {
        return lhs.a != rhs.a || lhs.b != rhs.b;
    }

    private:
    void Fixme() {
        long long g = gcd(a, b);
        if (b < 0) g = -g;
        a /= g;
        b /= g;
    }
};