#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>

using namespace std;

struct Event {
    int l;
    int sz;
    bool is_query;
    bool is_left;
    long long d;
    
    bool operator<(const Event& r) const {
        if (l != r.l) return l > r.l;
        if (sz != r.sz) return sz < r.sz;
        return is_query > r.is_query;
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
    int n;
    scanf("%d", &n);
    vector<int> c(n);
    vector<int> d(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &c[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &d[i]);
    }
    priority_queue<Event> evts;
    for (int i = 0; i < n; i++) {
        if (i - c[i] + 1 >= 0) evts.push(Event{i - c[i] + 1, c[i], true, false, d[i]});
        if (i + c[i] - 1 < n && c[i] != 1) evts.push(Event{i, c[i], true, true, d[i]});
        if (c[i] != 1) evts.push(Event{i, 1, true, false, 0});
    }
    MaxSuffixQuery qs;
    while (!evts.empty()) {
        Event e = evts.top();
        evts.pop();
        if (e.is_query) {
            long long d = qs.query(e.l + e.sz - 1);
            if (e.sz == 1) {
                printf("%lld ", d + e.d);
            } else {
                if (e.is_left) evts.push(Event{e.l + 1, e.sz - 1, false, true, d + e.d});
                else evts.push(Event{e.l, e.sz - 1, false, false, d + e.d});
            }
        } else {
            qs.add(e.l + e.sz - 1, e.d);
        }
    }
    printf("\n");
    return 0;
}