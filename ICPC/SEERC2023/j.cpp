#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

void f() {
    int n;
    scanf("%d", &n);
    n *= 2;
    vector<int> tbl(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &tbl[i]);
    }
    sort(tbl.begin(), tbl.end());
    long long ans = 0;
    int c = n / 2;
    for (int i = 0; i < c; i++) {
        ans -= tbl[i];
    }
    for (int i = c; i < n; i++) {
        ans += tbl[i];
    }
    printf("%lld\n", ans);
}

int main() {
    int q;
    scanf("%d", &q);
    while (q--) f();
    return 0;
}