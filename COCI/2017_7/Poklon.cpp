#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int l[1000100];
int r[1000100];

struct bigInt {
	unsigned int a;
	int p;

	bigInt ex() const {
		return bigInt{a,p+1};
	}
};

bool operator< (const bigInt &a, const bigInt &b) {
	if (a.p<b.p) return !(b<a);
	if (a.p==b.p) return a.a<b.a;
	for (int i=31;i>max(31-(a.p-b.p),0);i--) {
		if ((1<<i)&a.a) return false;
	}
	unsigned int tmp = a.a << (a.p-b.p);
	return tmp < b.a;
}

bigInt getWgt(int idx) {
	if (idx<0) return bigInt{(unsigned int)(-idx),0};
	return max(getWgt(l[idx]),getWgt(r[idx])).ex();
}

int main () {
	int n;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		scanf("%d%d",&l[i],&r[i]);
	}
	auto tt=getWgt(1);
	//printf("%lld\n",ans);
	int ans=tt.a;
	string x;
	while (ans) {
		if (ans%2) x.push_back('1');
		else x.push_back('0');
		ans/=2;
	}
	reverse(x.begin(),x.end());
	cout << x;
	for (int i=0;i<tt.p;i++) {
		printf("0");
	}
	printf("\n");
	return 0;
}
