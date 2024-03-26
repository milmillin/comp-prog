#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

void solve() {
    int n, k;
    scanf("%d%d", &n, &k);
    vector<int> tbl(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &tbl[i]);
    }
    vector<int> bucket(k, 0);
    priority_queue<pair<int, int>> max_bucket;
    priority_queue<pair<int, int>> min_bucket;
    vector<int> ans;
    int f = 0;
    for (int i = 0; i < k; i++) {
        max_bucket.push({0, i});
        min_bucket.push({0, i});
    }
    for (int i = 0; i < n; i++) {
        if (tbl[i] == 1) {
            while (!min_bucket.empty() && bucket[min_bucket.top().second] != -min_bucket.top().first) min_bucket.pop();
            int sel = min_bucket.top().second;
            bucket[sel]++;
            f = max(f, bucket[sel]);
            ans.push_back(sel + 1);
            min_bucket.pop();
            min_bucket.push({-bucket[sel], sel});
            max_bucket.push({bucket[sel], sel});
        } else {
            while (!max_bucket.empty() && bucket[max_bucket.top().second] != max_bucket.top().first) max_bucket.pop();
            int sel = max_bucket.top().second;
            bucket[sel] = max(bucket[sel] - 1, 0);
            ans.push_back(sel + 1);
            max_bucket.pop();
            min_bucket.push({-bucket[sel], sel});
            max_bucket.push({bucket[sel], sel});
        }
    }
    for (int i : ans) {
        printf("%d ", i);
    }
    printf("\n");
}

int main() {
    int q;
    scanf("%d", &q);
    while (q--) solve();
    return 0;
}