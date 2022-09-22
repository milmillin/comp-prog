#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

template<const int mod>
class IntMod {
	int _x;

	static int powmod(int a, int b) {
		int res = 1;
		while (b) {
			if (b & 1) {
				res = ((long long)res * a) % mod;
				b--;
			} else {
				a = ((long long)a * a) % mod;
				b >>= 1;
			}
		}
		return res;
	}

	static int invert(int x) {
		return powmod(x, mod - 2);
	}

	public:
	IntMod(long long x) {
		if (x < 0) {
			x = x % mod + mod;
		}
		if (x >= mod) {
			x %= mod;
		}
		_x = x;
	}

	operator int() const { return _x; }

	IntMod operator+(const IntMod &r) const {
		return IntMod(_x + r._x);
	}

	IntMod operator- (const IntMod &r) const {
		return IntMod(_x - r._x);
	}

	IntMod operator* (const IntMod &r) const {
		return IntMod((long long)_x * r._x);
	}

	IntMod operator/ (const IntMod &r) const {
		return IntMod((long long)_x * invert(r._x));
	}

	bool operator== (const IntMod &r) const {
		return _x == r._x;
	}

	bool operator!= (const IntMod &r) const {
		return _x != r._x;
	}
};

long long gcd(long long a, long long b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}

class frac {
	public:
	long long a;
	long long b;

	frac(int x): a(x), b(1) {}
	frac(long long x): a(x), b(1) {}
	frac(long long x, long long y): a(x), b(y) {
		long long g = gcd(a, b);
		a /= g;
		b /= g;
	}

	frac operator+ (const frac &r) {
		return frac(a * r.b + r.a * b, b * r.b);
	}

	frac operator- (const frac &r) {
		return frac(a * r.b - r.a * b, b * r.b);
	}

	frac operator* (const frac &r) {
		return frac(a * r.a, b * r.b);
	}

	frac operator/ (const frac &r) {
		return frac(a * r.b, b * r.a);
	}

	bool operator== (const frac &r) {
		return a * r.b == r.a * b;
	}

	bool operator!= (const frac &r) {
		return !(*this == r);
	}
};

template<typename number>
class MatrixSolver {
	typedef vector<vector<number>> matrix;

	public:
	// multiply a row by a constant c;
	static void rowOp1(matrix &mat, int r, number c) {
		int m = mat[0].size();
		for (int i = 0; i < m; i++) {
			mat[r][i] = mat[r][i] * c;
		}
	}

	// r2 += c * r1
	static void rowOp2(matrix &mat, int r1, int r2, number c) {
		int m = mat[0].size();
		for (int i = 0; i < m; i++) {
			mat[r2][i] = mat[r2][i] + c * mat[r1][i];
		}
	}

	// swap(r1, r2)
	static void rowOp3(matrix &mat, int r1, int r2) {
		int m = mat[0].size();
		for (int i = 0; i < m; i++) {
			swap(mat[r2][i], mat[r1][i]);
		}
	}

	static number determinant(const matrix &mat) {
		int n = mat.size();
		int m = mat[0].size();
		if (n != m) return 0;

		matrix tmp = mat;

		number det = 1;

		for (int i = 0; i < n; i++) {
			// find row with non-zero i-th element
			bool found = false;
			for (int j = i; j < n; j++) {
				if (tmp[j][i] != (number)0) {
					if (j != i) {
						rowOp3(tmp, i, j);
						det = det * number(-1);
					}
					found = true;
					break;
				}
			}

			if (!found) return 0;

			for (int j = i + 1; j < n; j++) {
				rowOp2(tmp, i, j, (number)-1 * tmp[j][i] / tmp[i][i]);
			}

			det = det * tmp[i][i];
		}
		return det;
	}
};

const int mod = 1000000007;

int main () {
	int q;
	scanf("%d", &q);

	while (q--) {
		int n;
		scanf("%d", &n);
		vector<vector<IntMod<mod>>> mat(n, vector<IntMod<mod>>(n, 0));
		int x;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf("%d", &x);
				mat[i][j] = x;
			}
		}

		IntMod<mod> det = MatrixSolver<IntMod<mod>>::determinant(mat);

		printf("%d\n", det);
	}
}
