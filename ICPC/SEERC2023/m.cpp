#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int INF = 1e9 + 10;

void f() {
    int n;
    scanf("%d", &n);
    vector<int> tbl(n);
    int mx = -1;
    int mn = INF;
    int mx_id1 = -1;
    int mx_id2 = -1;
    int mn_id1 = -1;
    int mn_id2 = -1;
    vector<int> pref_mn(n);
    vector<int> pref_mx(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &tbl[i]);
        if (tbl[i] > mx) {
            mx = tbl[i];
            mx_id1 = mx_id2 = i;
        } else if (tbl[i] == mx) {
            mx_id2 = i;
        }
        if (tbl[i] < mn) {
            mn = tbl[i];
            mn_id1 = mn_id2 = i;
        } else if (tbl[i] == mn) {
            mn_id2 = i;
        }
        pref_mn[i] = mn;
        pref_mx[i] = mx;
    }
    vector<int> suff_mn(n);
    vector<int> suff_mx(n);
    int _mn = INF;
    int _mx = -1;
    for (int i = n - 1; i >= 0; i--) {
        _mn = min(_mn, tbl[i]);
        _mx = max(_mx, tbl[i]);
        suff_mn[i] = _mn;
        suff_mx[i] = _mx;
    }

    int mn_mx = mx;
    int mx_mn = mn;
    for (int i = mx_id1; i <= mx_id2; i++) mn_mx = min(mn_mx, tbl[i]);
    for (int i = mn_id1; i <= mn_id2; i++) mx_mn = max(mx_mn, tbl[i]);

    int lo = 0;
    int hi = mx - mn;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        bool work = false;

        // mx
        int cl = mx_id1;
        int cr = mx_id2;
        int c_min = mn_mx;
        while (cl - 1 >= 0 && mx - min(c_min, tbl[cl - 1]) <= mid) {
            c_min = min(c_min, tbl[cl - 1]);
            cl--;
        }
        while (cr + 1 < n && mx - min(c_min, tbl[cr + 1]) <= mid) {
            c_min = min(c_min, tbl[cr + 1]);
            cr++;
        }
        work |= (mx - c_min <= mid) && (max((cl - 1 >= 0) ? pref_mx[cl - 1] : -1, (cr + 1 < n) ? suff_mx[cr + 1] : -1) - min((cl - 1 >= 0) ? pref_mn[cl - 1] : INF, (cr + 1 < n) ? suff_mn[cr + 1] : INF)) <= mid;

        if (!work) {
            cl = mn_id1;
            cr = mn_id2;
            int c_max = mx_mn;
            while (cl - 1 >= 0 && max(c_max, tbl[cl - 1]) - mn <= mid) {
                c_max = max(c_max, tbl[cl - 1]);
                cl--;
            }
            while (cr + 1 < n && max(c_max, tbl[cr + 1]) - mn <= mid) {
                c_max = max(c_max, tbl[cr + 1]);
                cr++;
            }
            work |= (c_max - mn <= mid) && (max((cl - 1 >= 0) ? pref_mx[cl - 1] : -1, (cr + 1 < n) ? suff_mx[cr + 1] : -1) - min((cl - 1 >= 0) ? pref_mn[cl - 1] : INF, (cr + 1 < n) ? suff_mn[cr + 1] : INF)) <= mid;
        }

        if (!work) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    printf("%d\n", lo);
}

int main() {
    int q;
    scanf("%d", &q);
    while (q--) f();
    return 0;
}