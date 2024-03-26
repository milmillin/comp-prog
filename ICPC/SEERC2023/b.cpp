#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    vector<int> tbl(n);
    map<int, vector<int>> loc;
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &tbl[i]);
        loc[tbl[i]].push_back(i);
        sum += tbl[i];
    }
    if ((sum * 2) % n != 0) {
        printf("-1\n");
        return 0;
    }
    long long each = (sum * 2) / n;
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        auto it = loc.find(each - tbl[i]);
        if (it == loc.end() || it->second.empty()) {
            printf("-1\n");
            return 0;
        }
        ans.push_back(it->second.back());
        it->second.pop_back();
    }
    for (int i : ans) {
        printf("%d ", i + 1);
    }
    printf("\n");
    return 0;
}