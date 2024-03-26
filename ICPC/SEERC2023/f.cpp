#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    vector<int> tbl(n);
    vector<int> tmp(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &tbl[i]);
    }
    int l = 0;
    while ((1 << l) < n) l++;
    long long ans0 = 0;
    long long ans1 = 0;
    for (int k = l; k > 0; k--) {
        int mask = (1 << k) - 1;
        int bitsel = (1 << (k - 1));
        long long shift0 = 0;
        long long shift1 = 0;
        int cnt0 = 0;
        int cnt1 = 0;
        for (int i = 0; i < n; i++) {
            int im = i & mask;
            if (im == 0) {
                cnt0 = cnt1 = 0;
            }
            if (tbl[i] & bitsel) {
                // printf("1 %d: %d\n", tbl[i], im - cnt1);
                shift1 += im - cnt1;
                cnt1++;
            } else {
                // printf("0 %d: %d\n", tbl[i], im - cnt0);
                shift0 += im - cnt0;
                cnt0++;
            }
        }
        ans1 = min(ans0, ans1) + min(shift0, shift1);
        ans0 += shift0;
        cnt0 = 0;
        cnt1 = bitsel;
        for (int i = 0; i < n; i++) {
            int im = i & mask;
            if (im == 0) {
                cnt0 = 0;
                cnt1 = bitsel;
            }
            if (tbl[i] & bitsel) {
                tmp[i - im + cnt1] = tbl[i];
                cnt1++;
            } else {
                tmp[i - im + cnt0] = tbl[i];
                cnt0++;
            }
        }
        swap(tbl, tmp);
    }
    printf("%lld\n", min(ans0, ans1 + 1));
    return 0;
}