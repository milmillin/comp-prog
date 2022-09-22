#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <cassert>
#include <algorithm>
#include <utility>
#include <tuple>

using namespace std;
using ll = long long;

constexpr int MAXN = 2e5;
struct circle {
    int x, y, r, idx;
} circles[MAXN];

int ans[MAXN];
int parent[MAXN];
vector<int> tree[MAXN];

bool in_circle(int big_idx, int small_idx) {
    int dx = circles[big_idx].x - circles[small_idx].x;
    int dy = circles[big_idx].y - circles[small_idx].y;
    int r = circles[big_idx].r;
    return 1LL * dx * dx + 1LL * dy * dy <= 1LL * r * r;
}

struct arc {
    int idx;
    bool is_bot;

    double get_y(int x) const {
        ll dx = abs(circles[idx].x - x);
        ll r = circles[idx].r;
        assert(dx <= r);
        double dy = sqrt(r * r - dx * dx);

        return circles[idx].y + (is_bot ? -1.0 : 1.0) * dy;
    }

    bool operator<(const arc& o) const {
        // if two arcs are being compared, they must have some overlap
        int x = max(circles[idx].x - circles[idx].r, circles[o.idx].x - circles[o.idx].r);
        double ya = get_y(x);
        double yb = o.get_y(x);
        if (ya == yb) {
            if (is_bot == o.is_bot)
                return idx < o.idx;
            else
                return is_bot < o.is_bot;
        }

        return ya > yb;
    }
};

pair<int, bool> dfs(int u) {
    int dp = 0;
    bool used_child = false;
    for (int v : tree[u]) {
        auto res = dfs(v);
        dp += res.first;
        used_child |= res.second;
    }

    bool used;
    if (circles[u].idx >= 0) {
        used = used_child;
        ans[circles[u].idx] = dp + !used;
    } else {
        if (!used_child) {
            used = true;
            ++dp;
        }
    }

    return {dp, used};
}

int main() {
    int n, q;
    cin >> n >> q;

    vector<tuple<int, int, int>> events;
    for (int i = 0; i < n + q; ++i) {
        cin >> circles[i].x >> circles[i].y >> circles[i].r;
        circles[i].idx = i - n;

        int left = circles[i].x - circles[i].r;
        int right = circles[i].x + circles[i].r;
        events.emplace_back(left, -circles[i].y, i);
        events.emplace_back(right, -circles[i].y, ~i);
    }
    sort(begin(events), end(events));

    set<arc> arcs;
    for (auto& evt : events) {
        int idx = get<2>(evt);
        if (idx >= 0) {
            auto it = arcs.insert(arc{idx, false}).first;
            if (it == begin(arcs)) {
                parent[idx] = -1;
            } else {
                it = prev(it);
                if (in_circle(it->idx, idx)) {
                    parent[idx] = it->idx;
                } else {
                    parent[idx] = parent[it->idx];
                }
            }
            arcs.insert(arc{idx, true});
        } else {
            idx = ~idx;
            // close
            arcs.erase(arc{idx, false});
            arcs.erase(arc{idx, true});
        }
    }

    for (int u = 0; u < n + q; ++u) {
        if (parent[u] != -1) {
            tree[parent[u]].push_back(u);
        }
    }

    for (int u = 0; u < n + q; ++u) {
        if (parent[u] == -1) {
            dfs(u);
        }
    }

    for (int i = 0; i < q; ++i) {
        cout << ans[i] << '\n';
    }

    return 0;
}
