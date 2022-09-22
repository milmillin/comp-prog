#include <bits/stdc++.h>

using namespace std;

struct ei {
	long long w, h;
};

struct line {
	long long m, b;
};

vector<ei> tbl;

vector<line> stk;

bool bad(int l) {
	int l1 = l-3;
	int l2 = l-2;
	int l3 = l-1;
	return (stk[l3].b-stk[l1].b)*(stk[l1].m-stk[l2].m)< (stk[l2].b-stk[l1].b)*(stk[l1].m-stk[l3].m);
}

void add(long long m,long long b) {
	stk.push_back(line{m, b});
	while (stk.size() >= 3 && bad(stk.size())){
		stk.erase(stk.end()-2);
	}
}

int idx;

long long query(long long x) {
	if (idx >= stk.size()) idx = stk.size()-1;
	
	while (idx<(int)stk.size()-1 && stk[idx+1].m*x+stk[idx+1].b<stk[idx].m*x+stk[idx].b) {
		idx++;
	}
	return stk[idx].m*x+stk[idx].b;
}

bool operator<(const ei &a, const ei &b) {
	if (a.w != b.w) return a.w<b.w;
	return a.h<b.h;
}

int main () {
	int n;
	scanf("%d", &n);
	int a, b, c;
	for (int i = 0; i<n; i++) {
		scanf("%d%d%d", &a, &b, &c);
		tbl.push_back(ei{(long long)a*b, c});		
	}
	sort(tbl.begin(), tbl.end());
	vector<ei> nec;
	for (int i = 0; i<(int)tbl.size(); i++) {
		while (!nec.empty() && nec.back().h<=tbl[i].h) nec.pop_back();
		nec.push_back(tbl[i]);	
	}

	long long cost = 0;
	idx = 0;
	add(nec[0].h, 0);
	for (int i = 0; i<(int)nec.size(); i++) {
		cost = query(nec[i].w);
		add(nec[i+1].h, cost);
	}
	printf("%lld\n", cost);
	return 0;
}
