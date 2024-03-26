#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

bool work[40];
bool imp[40][40];

bool imp2[40][40];

long long cnt[1 << 20];

int main() {
    int n;
    scanf("%d", &n);
    vector<long long> tbl(n);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &tbl[i]);
        // for (int j = 40; j >= 0; j--) {
        //     printf("%d", (tbl[i] & (1ll << j)) != 0);
        // }
        // printf("\n");
    }

    for (int i = 0; i < 40; i++) {
        work[i] = true;
    }

    long long full = (1ll << 40) - 1;
    for (int k = 0; k < 40; k++) {
        long long and1 = full;
        bool has0 = false;
        bool has1 = false;
        for (int i = 0; i < n; i++) {
            if (tbl[i] & (1ll << k)) {
                // printf("- %lld\n", tbl[i]);
                and1 &= tbl[i];
                // printf("-> %lld\n", and1);
                has1 = true;
            } else {
                has0 = true;
            }
        }
        // printf("%lld\n", and1);
        for (int j = 0; j < 40; j++) {
            if (j == k) continue;
            if (and1 & (1ll << j)) {
                imp[k][j] = true;
            }
        }
        if (!has0 || !has1) {
            work[k] = false;
        }
    }

    // for (int k = 0; k < 40; k++) {
    //     for (int j = 0; j < 40; j++) {
    //         printf("%d ", imp[k][j]);
    //     }
    //     printf("\n");
    // }

    for (int k = 0; k < 40; k++) {
        for (int j = k + 1; j < 40; j++) {
            if (imp[k][j] && imp[j][k]) work[j] = false;
        }
    }
    vector<int> active;
    for (int i = 0; i < 40; i++) {
        if (work[i]) active.push_back(i);
    }
    int m = active.size();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            imp2[i][j] = imp[active[i]][active[j]];
            // printf("%d ", (int)imp2[i][j]);
        }
        // printf("\n");
    }

    // for (int i = 0; i < n; i++) {
    //     for (int j = m - 1; j >= 0; j--) {
    //         printf("%d", (tbl[i] & (1ll << active[j])) != 0);
    //     }
    //     printf("\n");
    // }

    int m2 = m / 2;
    int sz = 1 << m2;
    // int xxx = 0;
    for (int ma = 0; ma < sz; ma++) {
        bool _work = true;
        for (int i = 0; i < m2; i++) {
            if (!(ma & (1 << i))) continue;
            for (int j = i + 1; j < m2; j++) {
                if (!(ma & (1 << j))) continue;
                if (imp2[i][j] || imp2[j][i]) {
                    _work = false;
                    break;
                }
            }
            if (!_work) break;
        }
        if (_work) {
            cnt[ma]++;
            // xxx++;
            // long long cur = 0;
            // for (int j = 0; j < m2; j++) {
            //     if (ma & (1 << j)) {
            //         cur += (1 << active[j]);
            //     }
            // }
            // printf("%lld\n", cur);
        }
    }
    // printf("-- %d\n", xxx);
    for (int i = 0; i < m2; i++) {
        for (int ma = 0; ma < sz; ma++) {
            if (ma & (1 << i)) {
                cnt[ma] += cnt[ma ^ (1 << i)];
            }
        }
    }
    int m3 = m - m2;
    int sz3 = 1 << m3;
    long long ans = 0;
    for (int ma = 0; ma < sz3; ma++) {
        bool _work = true;
        int ma_l = (1 << m2) - 1;
        for (int i = 0; i < m3; i++) {
            if (!(ma & (1 << i))) continue;
            for (int j = i + 1; j < m3; j++) {
                if (!(ma & (1 << j))) continue;
                if (imp2[m2 + i][m2 + j] || imp2[m2 + j][m2 + i]) {
                    _work = false;
                    break;
                }
            }
            if (!_work) break;
            for (int j = 0; j < m2; j++) {
                if (imp2[m2 + i][j] || imp2[j][m2 + i]) ma_l &= ~(1 << j);
            }
        }
        if (_work) {
            ans += cnt[ma_l];
        }
    }
    printf("%lld\n", ans);
    return 0;
}