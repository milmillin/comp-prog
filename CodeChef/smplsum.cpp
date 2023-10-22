#include <cstdio>
#include <vector>
#include <algorithm>
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

constexpr int kMaxN = 10000000;
vector<int> prime;
bool is_composite[kMaxN + 1];
// int mu[kMaxN + 1];
// Frac func[kMaxN + 1];
// int func2[kMaxN + 1];
// long long func3[kMaxN + 1];
// long long answer[kMaxN + 1];
// vector<int> factors[kMaxN + 1];
// int cnt[kMaxN];
int lpf[kMaxN + 1];

void GenerateMobius() {
    // mu[1] = 1;
    // func[1] = 1;
    // func2[1] = 1;
    // func3[1] = 1;
    lpf[1] = 1;
    for (int i = 2; i <= kMaxN; i++) {
        if (!is_composite[i]) {
            prime.push_back(i);
            // cnt[i] = 1;
            // mu[i] = -1;
            // func[i] = Frac(1, i) - 1;
            // func2[i] = 1 - i;
            // func3[i] = 1 - i + (long long)i * i;
            lpf[i] = i;
        }
        for (int p : prime) {
            if (i * p > kMaxN) break;
            is_composite[i * p] = true;
            if (i % p == 0) {
                // cnt[i * p] = cnt[i] + 1;
                // mu[i * p] = 0;
                // func[i * p] = func[i] / p;
                // func2[i * p] = func2[i];
                // func3[i * p] = 1 - p + p * (long long)p * func3[i];
                lpf[i * p] = p;
                break;
            } else {
                // cnt[i * p] = 1;
                // mu[i * p] = -1 * mu[i];
                // func[i * p] = func[i] * func[p];
                // func2[i * p] = func2[i] * func2[p];
                // func3[i * p] = func3[i] * func3[p];
                lpf[i * p] = p;
            }
        }
    }
    // for (int i = 1; i <= kMaxN; i++) {
    //     for (int j = i; j <= kMaxN; j += i) {
    //         factors[j].push_back(i);
    //     }
    // }
}

// void GenerateAnswer() {
//     // fill(answer, answer + kMaxN - 1, 0);
//     long long n;
//     for (int d = 1; d <= kMaxN; d++) {
//         for (int i = max(1, 1000000 / d); (n = i * d) <= kMaxN; i++) {
//             answer[n] += (func2[d] * (long long)i * i);
//         }
//     }
// }

// long long Fast2(long long n) {
//     long long ans = 0;
//     long long j;
//     for (int i = 1; i * i <= n; i++) {
//         if (n % i != 0) continue;
//         j = n / i;
//         ans += (func2[i] * j * j);
//         if (j != i) ans += func2[j] * i * i;
//     }
//     return ans;
// }

// long long Fast(int n) {
//     long long ans = 0;
//     for (int k = 1; k <= n; k++) {
//         if (n % k != 0) continue;
//         long long sum = 0;
//         for (int d = 1; d * k <= n; d++) {
//             if ((n / k) % d != 0) continue;
//             sum += n / ((long long)k * d) * mu[d];
//         }
//         ans += sum * n / k;
//     }
//     return ans;
// }

long long Fast3(int n) {
    long long ans = 1;
    int last = 1;
    long long cur = 1;
    while (n != 1) {
        long long p = lpf[n];
        // printf("-- %lld\n", p);
        if (p != last) {
            ans *= cur;
            cur = 1 - p + p * p;
            last = p;
        } else {
            cur *= p * p;
            cur += 1 - p;
        }
        n /= p;
    }
    ans *= cur;
    return ans;
}

long long Slow(int n) {
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += n / __gcd(i, n);
    }
    return ans;
}


void f() {
    int n;
    scanf("%d", &n);
    printf("%lld\n", Fast3(n));
}

int main() {
    GenerateMobius();
    // GenerateAnswer();
    // printf("asdf\n");
    int q;
    scanf("%d", &q);
    while (q--) f();
    // int i = 1;
    // long long slow;
    // long long fast;
    // while ((slow = Slow(i)) == (fast = Fast2(i))) {
    //     printf("%d: %lld %lld\n", i, slow, fast);
    //     i++;
    // }
    // printf("%d: %lld %lld\n", i, slow, fast);
    // for (int i = 1; i <= 20; i++) {
    //     printf("%d: %lld %lld\n", i, Slow(i), Fast3(i));
    // }
    return 0;
}