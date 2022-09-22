#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

long long binToDec(char* x) {
	int len = strlen(x);
	long long ans=0;
	for (int i=0;i<len;i++) {
		ans*=2;
		ans+=x[i]-'0';
	}
	return ans;
}

int bitCnt(long long x) {
	int cnt=0;
	long long cur=1;
	for (int i=0;i<40;i++) {
		if (x&cur) cnt++;
		cur=cur<<1;
	}
	//printf("%d\n",cnt);
	return cnt;
}

void f(int ii) {
	int n,l;
	scanf("%d%d",&n,&l);
	char x[50];
	vector<long long> tbl(n);
	vector<long long> b(n);
	map<long long,int> mm;
	for (int i=0;i<n;i++) {
		scanf("%s",x);
		tbl[i]=binToDec(x);
	}
	int tmp;
	vector<long long> ans;
	for (int i=0;i<n;i++) {
		scanf("%s",x);
		b[i]=binToDec(x);
		for (int j=0;j<n;j++) {
			//printf("%lld %lld %lld\n",b[i],tbl[j],b[i]^tbl[j]);
			tmp = ++mm[b[i]^tbl[j]];
			//printf("%d\n",tmp);
			if (tmp==n) ans.push_back(b[i]^tbl[j]);
		}
	}
	int minn=2e9;
	for (int i=0;i<ans.size();i++) {
		//printf("%lld\n",ans[i]);
		minn=min(minn,bitCnt(ans[i]));
	}
	if (minn==2e9) printf("Case #%d: NOT POSSIBLE\n",ii);
	else printf("Case #%d: %d\n",ii,minn);
	return;
}

int main () {
	int q;
	scanf("%d",&q);
	for (int i=0;i<q;i++) {
		f(i+1);
	}
	return 0;
}
