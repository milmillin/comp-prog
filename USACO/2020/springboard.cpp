#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

void setIO(const string& name) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen((name + ".in").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
}

struct Event {
    long long x;
    long long y;
    int id;
    bool add;

    bool operator<(const Event& r) const {
        if (x != r.x) return x < r.x;
        if (y != r.y) return y < r.y;
        if (add != r.add) return add < r.add;
        return id < r.id;
    }
};

class MaxSuffixQuery {
    public:
        // Returns maximum vi s.t. yi >= y.
        long long query(int y) const {
            auto it = data_.lower_bound(y);
            return it == data_.end() ? 0 : it->second;
        }

        // Add (yi, vi)
        void add(int y, long long v) {
            auto it = data_.lower_bound(y);
            if (it != data_.end() && it->second >= v) return;
            it = data_.insert(it, {y, v});
            it->second = v;
            while (it != data_.begin() && prev(it)->second <= v) data_.erase(prev(it));
        }
    private:
        map<int, long long> data_;
};

int main() {
    setIO("boards");
    int n, p;
    scanf("%d%d", &n, &p);
    vector<long long> ans(p);
    vector<Event> evts;
    int x1, y1, x2, y2;
    for (int i = 0; i < p; i++) {
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        evts.push_back(Event{x1, y1, i, true});
        evts.push_back(Event{x2, y2, i, false});
    }
    sort(evts.begin(), evts.end());
    MaxSuffixQuery qs;
    for (const Event& evt : evts) {
        if (evt.add) {
            ans[evt.id] = -qs.query(-evt.y) + evt.x + evt.y;
        } else {
            qs.add(-evt.y, -ans[evt.id] + evt.x + evt.y);
        }
    }
    printf("%lld\n", -qs.query(-n) + 2 * n);
    return 0;
}