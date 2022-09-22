#include <cstdio>
#include <cassert>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int n;
string x;

struct number {
	long long val;
	bool overflow;

	number() {
		val=-1;
		overflow=false;
	}

	number(long long _val) {
		val=_val;
		overflow=false;
	}
	number(long long _val,bool ov) {
		val=_val;
		overflow=ov;
	}

	number operator+(const number &r) const {
		number tmp;
		tmp.val=val+r.val;
		tmp.overflow=overflow||r.overflow;
		if (!tmp.overflow&&tmp.val>1e18) tmp.overflow=true;
		return tmp;
	}

	number& operator=(const number &r) {
		val=r.val;
		overflow=r.overflow;
		return *this;
	}

	bool operator<(const number &r) const {
		if (!r.overflow&&!overflow) return val<r.val;
		if (r.overflow&&overflow) return false;
		return r.overflow;
	}
};

number mic[5010][5010];

number dp(int i,int j) {
	if (i<0||i>n-j) return 0;
	if (i==0&&j==n) return 1;
	if (j==n) return 0;
	if (mic[i][j].val!=-1) return mic[i][j];
	if (x[j]=='.') mic[i][j]=dp(i+1,j+1)+dp(i-1,j+1);
	else if (x[j]=='(') mic[i][j]=dp(i+1,j+1);
	else if (x[j]==')') mic[i][j]=dp(i-1,j+1);
	return mic[i][j];
}

void print(int i,int j,long long k) {
	if (j==n) return;
	if (x[j]=='.') {
		if (number(k-1)<dp(i+1,j+1)) {
			printf("(");
			print(i+1,j+1,k);	
		} else {
			printf(")");
			print(i-1,j+1,k-dp(i+1,j+1).val);
		}
	} else {
		printf("%c",x[j]);
		print((x[j]=='(')?i+1:i-1,j+1,k);
	}	
}

int main () {
	cin >> x;
	long long k;
	scanf("%lld",&k);
	n=x.length();		
	//memset(mic,-1,sizeof(mic));
	//printf("%lld\n",dp(0,0));
	//if (k>dp(0,0)) return 0;
	print(0,0,k);
	printf("\n");
	//assert(k<=dp(0,0));
	//for (long long i=1;i<=k;i++) {
		//print(0,0,i);
		//printf("\n");
	//}
	return 0;
}
