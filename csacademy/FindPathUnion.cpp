#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct ei {
	long long val;
	int len;
	int length() {
		return len;
	}
	int operator[] (int at) {
		return (val&(1ll<<(59-at)))!=0;
	}
};

bool operator< (const ei &a, const ei &b) {
	if (a.val!=b.val) return a.val<b.val;
	return a.len<b.len;
}

vector<ei> tbl;

int ans=-1;

void solve(int l,int r,int at) {
	if (l>=r) return;
	//if (l+1==r) return;
	ans++;
	//printf("%d %d %d\n",l,r,at);
	int curn=l-1;
	int cur0=l-1;
	int cur1=l-1;
	for (int i=l;i<r;i++) {
		//printf("** %d %d\n",tbl[i].len,tbl[i][at]);
		if (tbl[i].length()<=at) {
			curn=i;
			continue;
		}
		if (tbl[i][at]==0) {
			cur0=i;
			continue;
		}
		if (tbl[i][at]==1) {
			cur1=i;
			continue;
		}
	}
	//printf("-- %d %d %d\n",curn,cur0,cur1);
	if (curn==r) return;
	solve(curn+1,cur0+1,at+1);
	solve(cur0+1,cur1+1,at+1);
}

void printBin(long long x) {
	string y;
	long long tmp=x;
	//printf("%lld\n",tmp);
	while (tmp) {
		y.push_back((tmp%2)+'0');
		tmp>>=1;
	}
	//cout << y << endl;
	reverse(y.begin(),y.end());
	cout << y << endl;
	//printf("%d\n",y.length());
}

int main () {
	int n;
	scanf("%d",&n);
	long long x;
	long long xx;
	int cnt;
	for (int i=0;i<n;i++) {
		scanf("%lld",&x);
		xx=x;
		cnt=0;
		while (x) {
			x>>=1;
			cnt++;
		}
		xx<<=(60-cnt);
		//printf("%d\n",cnt);
		//printBin(xx);
		tbl.push_back(ei{xx,cnt});
	}
	sort(tbl.begin(),tbl.end());
	//for (auto &a:tbl) {
		//printf("%d ",a.len);
		//printBin(a.val);
	//}
	solve(0,n,1);
	printf("%d\n",ans);
	return 0;
}
