#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct ei {
	int a,b;
};

bool operator< (const ei &a, const ei &b) {
	if (a.a!=b.a) return a.a<b.a;
	return a.b<b.b;
}

vector<ei> tbl;

int bit[100100];
int mod=1e9+7;

int get(int idx) {
	int sum=0;
	while (idx) {
		sum+=bit[idx];
		sum%=mod;
		idx-=(idx&-idx);
	}
	return sum;
}

void set(int idx,int val) {
	while (idx<100100) {
		bit[idx]+=val;
		bit[idx]%=mod;
		idx+=(idx&-idx);
	}
}


long long poww(int x,int b) {
	if (b==0) return 1;
	if (b==1) return x;
	long long tmp = poww(x,b/2);
	tmp=(tmp*tmp)%mod;
	if (b%2) {
		return (tmp*x)%mod;
	}
	return tmp;
}

int main () {
	int n;
	scanf("%d",&n);
	int a,b;
	for (int i=0;i<n;i++) {
		scanf("%d%d",&a,&b);
		tbl.push_back(ei{a,b});
	}
	sort(tbl.begin(),tbl.end());
	long long ans=0;
	long long cur;
	for (auto &tt:tbl) {
		cur = get(100000)-get(tt.b)+1;
		cur%=mod;
		ans+=cur;
		ans%=mod;
		set(tt.b,cur);
	}
	printf("%lld\n",(ans+mod)%mod);
	return 0;
}
