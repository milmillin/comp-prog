#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct folder{
	int length;
	int numfile;
	vector<int> sub;
};

folder flds[100100];
long long initLen;
long long curLen;
long long ans;

void init(folder &f) {
	if (f.sub.size()==0) {
		initLen+=curLen-1;
		f.numfile=1;
		return;
	}
	for (auto i:f.sub) {
		curLen+=flds[i].length+1;
		init(flds[i]);
		f.numfile+=flds[i].numfile;	
		curLen-=flds[i].length+1;
	}
}

int numFile;
void solve(folder &f) {
	ans=min(ans,initLen);
	for (auto i:f.sub) {
		if (flds[i].sub.size()==0) continue;
		initLen-=(flds[i].length+1)*flds[i].numfile;
		initLen+=3*(numFile-flds[i].numfile);
		solve(flds[i]);
		initLen+=(flds[i].length+1)*flds[i].numfile;
		initLen-=3*(numFile-flds[i].numfile);	
	}
}


int main () {
	freopen("dirtraverse.in","r",stdin);
	freopen("dirtraverse.out","w",stdout);
	int n;
	scanf("%d",&n);
	string x;
	int a,b;
	for (int i=1;i<=n;i++) {
		cin>>x;
		flds[i].length=x.length();
		scanf("%d",&a);
		for (int j=0;j<a;j++) {
			scanf("%d",&b);
			flds[i].sub.push_back(b);
		}
	}
	init(flds[1]);
	numFile = flds[1].numfile;
	ans=initLen;
	solve(flds[1]);
	printf("%lld\n",ans);
	return 0;
}
