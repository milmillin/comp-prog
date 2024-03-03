#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int MAXN = 100100;

int n, q;
long long tsum[MAXN * 4];
long long tmax[MAXN * 4];

void update_set(int i, long long v, int t = 0, int tl = 0, int tr = n) {
    if (i < tl || i >= tr) return;
    if (tl + 1 == tr) { tsum[t] = tmax[t] = v; return; }
    int tm = (tl + tr) / 2;
    if (i < tm) update_set(i, v, t * 2 + 1, tl, tm);
    else update_set(i, v, t * 2 + 2, tm, tr);
    tsum[t] = tsum[t * 2 + 1] + tsum[t * 2 + 2];
    tmax[t] = max(tmax[t * 2 + 1], tmax[t * 2 + 2]);
}

void update_mod(int l, int r, int m, int t = 0, int tl = 0, int tr = n) {
    if (r <= tl || l >= tr || tmax[t] < m) return;
    if (tl + 1 == tr) { tsum[t] = tmax[t] = tsum[t] % m; return; }
    int tm = (tl + tr) / 2;
    update_mod(l, r, m, t * 2 + 1, tl, tm);
    update_mod(l, r, m, t * 2 + 2, tm, tr);
    tsum[t] = tsum[t * 2 + 1] + tsum[t * 2 + 2];
    tmax[t] = max(tmax[t * 2 + 1], tmax[t * 2 + 2]);
}

long long query(int l, int r, int t = 0, int tl = 0, int tr = n) {
    if (r <= tl || l >= tr) return 0;
    if (l <= tl && r >= tr) return tsum[t];
    int tm = (tl + tr) / 2;
    return query(l, r, t * 2 + 1, tl, tm) + query(l, r, t * 2 + 2, tm, tr);
}

int main() {
    scanf("%d%d", &n, &q);
    int x;
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        update_set(i, x);
    }
    int t, l, r, k;
    while (q--) {
        scanf("%d", &t);
        if (t == 1) {
            scanf("%d%d", &l, &r);
            printf("%lld\n", query(l - 1, r));
        } else if (t == 2) {
            scanf("%d%d%d", &l, &r, &x);
            update_mod(l - 1, r, x);
        } else {
            scanf("%d%d", &k, &x);
            update_set(k - 1, x);
        }
    }
    return 0;
}