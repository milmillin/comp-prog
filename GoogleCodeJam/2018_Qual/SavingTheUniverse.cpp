#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solve(int p, const string &x) {
	long long sum=0;
	vector<int> tbl;
	int cur=1;
	for (char i:x) {
		if (i=='C') {
			cur<<=1;
			tbl.push_back(0);
		} else {
			tbl.push_back(cur);
			sum+=cur;
		}
	}
	if (sum<=p) return 0;
	int cnt=0;
	int curpos=tbl.size()-1;
	while (curpos>=0&&tbl[curpos]!=0) curpos--;
	if (curpos<0) return -1;
	while (sum>p) {
		if (tbl[curpos+1]==0||curpos==tbl.size()-1) {
			curpos--;
			while (curpos>=0&&tbl[curpos]!=0) curpos--;
			if (curpos<0) return -1;
		} else {
			sum-=tbl[curpos+1];
			tbl[curpos]=tbl[curpos+1]>>1;
			sum+=tbl[curpos];
			tbl[curpos+1]=0;
			curpos++;
			cnt++;
		}
	}				
	return cnt;
}

int main () {
	int q;
	scanf("%d",&q);
	string x;
	int p;
	for (int i=1;i<=q;i++) {
		scanf("%d",&p);
		cin >> x;	
		int tmp = solve(p,x);
		printf("Case #%d: ",i);
		if (tmp==-1) printf("IMPOSSIBLE\n");
		else printf("%d\n",tmp);
	}
	return 0;
}
