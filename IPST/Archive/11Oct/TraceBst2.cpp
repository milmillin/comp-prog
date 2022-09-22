#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

typedef struct {
	int idx;
	int ans;
	string x;
} pth;

vector<pth> eiei;
int chMap[256];

bool operator< (const pth &a, const pth &b) {
	int len = min (a.x.length(),b.x.length());
	for (int i=0;i<len;i++) {
		if (a.x[i]==b.x[i]) continue;
		return chMap[a.x[i]]<chMap[b.x[i]];
	}
	return a.x.length()<b.x.length();
}

bool cmp (const pth &a, const pth &b) {
	return a.idx<b.idx;	
}

int main () {
	chMap['L']=1;
	chMap['*']=2;
	chMap['R']=3;
	int n;
	scanf("%d",&n);
	string x;
	for (int i=0;i<n;i++) {
		cin>>x;
		eiei.push_back(pth{i,0,x});
	}
	sort(eiei.begin(),eiei.end());
	for (int i=0;i<n;i++) {
		if (!i) eiei[i].ans=1;
		else {
			if (eiei[i].x==eiei[i-1].x) eiei[i].ans=eiei[i-1].ans;
			else eiei[i].ans=eiei[i-1].ans+1;
		}
	}
	sort(eiei.begin(),eiei.end(),cmp);
	for (int i=0;i<n;i++) {
		printf("%d\n",eiei[i].ans);
	}
	return 0;
}
