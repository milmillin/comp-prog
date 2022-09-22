#include <cstdio>
#include <string>

using namespace std;

string f() {
	int n, xb, xa;
	scanf("%d%d%d", &n, &xb, &xa);
	int x;
	int ca, cb, caub, cab;
	ca = cb = caub = cab = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", &x);
		if ((x % xa) != 0 && (x % xb) != 0) continue;
		caub++;
		if ((x % xa) == 0) {
			ca++;
		}
		if ((x % xb) == 0) {
			cb++;
		}
	}
	cab = ca + cb - caub;
	ca -= cab;
	cb -= cab;
	if (cb < ca) return "ALICE";
	if (cb > ca) return "BOB";
	if (cab) return "BOB";
	return "ALICE";
}

int main () {
	int q;
	scanf("%d", &q);
	while (q--) {
		printf("%s\n", f().c_str());
	}
	return 0;
}
