#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

constexpr int MAXN = 200010;
constexpr long long INF = 2e18;


struct Node {
    long long sum;
    long long max1;
    long long max2;
    long long maxc;
    long long min1;
    long long min2;
    long long minc;
    long long lazy;
};

int n;
long long A[MAXN];
Node T[MAXN * 4];

void merge(int t) {
    int tl = t * 2 + 1;
    int tr = t * 2 + 2;

    // sum
    T[t].sum = T[tl].sum + T[tr].sum;

    // max
    if (T[tl].max1 == T[tr].max1) {
        T[t].max1 = T[tl].max1;
        T[t].maxc = T[tl].maxc + T[tr].maxc;
        T[t].max2 = max(T[tl].max2, T[tr].max2);
    } else if (T[tl].max1 > T[tr].max1) {
        T[t].max1 = T[tl].max1;
        T[t].maxc = T[tl].maxc;
        T[t].max2 = max(T[tl].max2, T[tr].max1);
    } else {
        T[t].max1 = T[tr].max1;
        T[t].maxc = T[tr].maxc;
        T[t].max2 = max(T[tr].max2, T[tl].max1);
    }

    // min
    if (T[tl].min1 == T[tr].min1) {
        T[t].min1 = T[tl].min1;
        T[t].minc = T[tl].minc + T[tr].minc;
        T[t].min2 = min(T[tl].min2, T[tr].min2);
    } else if (T[tl].min1 < T[tr].min1) {
        T[t].min1 = T[tl].min1;
        T[t].minc = T[tl].minc;
        T[t].min2 = min(T[tl].min2, T[tr].min1);
    } else {
        T[t].min1 = T[tr].min1;
        T[t].minc = T[tr].minc;
        T[t].min2 = min(T[tr].min2, T[tl].min1);
    }
}

void push_add(int t, int tl, int tr, long long v) {
    if (v == 0) return;
    T[t].sum += (tr - tl) * v;
    T[t].max1 += v;
    if (T[t].max2 != -INF) T[t].max2 += v;
    T[t].min1 += v;
    if (T[t].min2 != INF) T[t].min2 += v;
    T[t].lazy += v;
}

// chmin
void push_max(int t, int tl, int tr, long long v) {
    if (T[t].max1 <= v) return;
    T[t].sum += (v - T[t].max1) * T[t].maxc;
    T[t].max1 = v;
    if (tl + 1 == tr) {
        T[t].min1 = T[t].max1;
    } else {
         if (v <= T[t].min1) {
            T[t].min1 = v;
            // assert(T[t].min2 == INF);
        } else if (v < T[t].min2) {
            T[t].min2 = v;
        }
    }
}

// chmax
void push_min(int t, int tl, int tr, long long v) {
    if (T[t].min1 >= v) return;
    T[t].sum += (v - T[t].min1) * T[t].minc;
    T[t].min1 = v;
    if (tl + 1 == tr) {
        T[t].max1 = T[t].min1;
    } else {
        if (v >= T[t].max1) {
            T[t].max1 = v;
            // assert(T[t].max2 == -INF);
        } else if (v > T[t].max2) {
            T[t].max2 = v;
        }
    }
}

void pushdown(int t, int tl, int tr) {
    if (tl + 1 == tr) return;
    int tm = (tl + tr) / 2;
    int t1 = t * 2 + 1;
    int t2 = t * 2 + 2;
    // sum
    push_add(t1, tl, tm, T[t].lazy);
    push_add(t2, tm, tr, T[t].lazy);
    T[t].lazy = 0;
    // max
    push_max(t1, tl, tm, T[t].max1);
    push_max(t2, tm, tr, T[t].max1);
    // min
    push_min(t1, tl, tm, T[t].min1);
    push_min(t2, tm, tr, T[t].min1);
}

void build(int t = 0, int tl = 0, int tr = n) {
    T[t].lazy = 0;
    if (tl + 1 == tr) {
        T[t].sum = T[t].max1 = T[t].min1 = A[tl];
        T[t].maxc = T[t].minc = 1;
        T[t].min2 = INF;
        T[t].max2 = -INF;
        return;
    }
    int tm = (tl + tr) / 2;
    build(t * 2 + 1, tl, tm);
    build(t * 2 + 2, tm, tr);
    merge(t);
}

void update_add(int l, int r, long long v, int t = 0, int tl = 0, int tr = n) {
    if (r <= tl || l >= tr) return;
    if (l <= tl && r >= tr) { push_add(t, tl, tr, v); return; }
    pushdown(t, tl, tr);
    int tm = (tl + tr) / 2;
    update_add(l, r, v, t * 2 + 1, tl, tm);
    update_add(l, r, v, t * 2 + 2, tm, tr);
    merge(t);
}

void update_chmin(int l, int r, long long v, int t = 0, int tl = 0, int tr = n) {
    if (r <= tl || l >= tr || v >= T[t].max1) return;
    if (l <= tl && r >= tr && v > T[t].max2) { push_max(t, tl, tr, v); return; }
    pushdown(t, tl, tr);
    int tm = (tl + tr) / 2;
    update_chmin(l, r, v, t * 2 + 1, tl, tm);
    update_chmin(l, r, v, t * 2 + 2, tm, tr);
    merge(t);
}

void update_chmax(int l, int r, long long v, int t = 0, int tl = 0, int tr = n) {
    if (r <= tl || l >= tr || v <= T[t].min1) return;
    if (l <= tl && r >= tr && v < T[t].min2) { push_min(t, tl, tr, v); return; }
    pushdown(t, tl, tr);
    int tm = (tl + tr) / 2;
    update_chmax(l, r, v, t * 2 + 1, tl, tm);
    update_chmax(l, r, v, t * 2 + 2, tm, tr);
    merge(t);
}

long long query_sum(int l, int r, int t = 0, int tl = 0, int tr = n) {
    if (r <= tl || l >= tr) return 0;
    if (l <= tl && r >= tr) return T[t].sum;
    pushdown(t, tl, tr);
    int tm = (tl + tr) / 2;
    return query_sum(l, r, t * 2 + 1, tl, tm) + query_sum(l, r, t * 2 + 2, tm, tr);
}

void print(int t = 0, int tl = 0, int tr = n) {
    printf("%d, [%d, %d), sum: %lld, max1: %lld, max2: %lld, maxc: %lld, min1: %lld, min2: %lld, minc: %lld, lazy: %lld\n", t, tl, tr, T[t].sum, T[t].max1, T[t].max2, T[t].maxc, T[t].min1, T[t].min2, T[t].minc, T[t].lazy);
    if (tl + 1 == tr) return;
    int tm = (tl + tr) / 2;
    print(t * 2 + 1, tl, tm);
    print(t * 2 + 2, tm, tr);
}

int main() {
    int q;
    scanf("%d%d", &n, &q);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &A[i]);
    }
    build();
    // print();
    // printf("-------\n");
    int t, l, r;
    long long b;
    while (q--) {
        scanf("%d", &t);
        if (t == 0) {
            scanf("%d%d%lld", &l, &r, &b);
            update_chmin(l, r, b);
        } else if (t == 1) {
            scanf("%d%d%lld", &l, &r, &b);
            update_chmax(l, r, b);
        } else if (t == 2) {
            scanf("%d%d%lld", &l, &r, &b);
            update_add(l, r, b);
        } else if (t == 3) {
            scanf("%d%d", &l, &r);
            printf("%lld\n", query_sum(l, r));
        }
        // print();
        // printf("-------\n");
    }
    return 0;
}