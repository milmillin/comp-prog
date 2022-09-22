#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

int eng[100100];
vector<string> nor(100100);
vector<string> rev(100100);
long long mem[100100][2];

long long minChg(int idx,bool chg) {
	if (idx==0) {
		if (chg) return eng[0];
		return 0;
	}
	if (mem[idx][chg]!=-1) return mem[idx][chg];
	if (chg) {
		long long minn=(1ll<<62);
		if (rev[idx]>=nor[idx-1]) minn=min(minn,minChg(idx-1,false));
		if (rev[idx]>=rev[idx-1]) minn=min(minn,minChg(idx-1,true));
		return mem[idx][chg]=minn+eng[idx];
	} else {
		long long minn=(1ll<<62);
		if (nor[idx]>=nor[idx-1]) minn=min(minn,minChg(idx-1,false));
		if (nor[idx]>=rev[idx-1]) minn=min(minn,minChg(idx-1,true));
		return mem[idx][chg]=minn;
	}
}

int main () {
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		scanf("%d",&eng[i]);
	}
	string x;
	for (int i=0;i<n;i++) {
		cin>>x;
		nor[i]=x;
		reverse(x.begin(),x.end());
		rev[i]=x;
	}
	/*
	for (int i=0;i<n;i++) {
		cout << nor[i] << " " << rev[i] << endl;
	}
	*/
	memset(mem,-1,sizeof(mem));
	long long ans = min(minChg(n-1,true),minChg(n-1,false));
	printf("%I64d\n",(ans==(1ll<<62))?-1:ans);
	return 0;
}
