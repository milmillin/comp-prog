#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

string x;

unsigned long long prm = 22801763489;
unsigned long long poww[1000100];

void init() {
	poww[0]=1;
	poww[1]=26;
	for (int i=2;i<=1000000;i++) {
		poww[i]=poww[i-1]*26;
		poww[i]%=prm;
	}
}

bool check(int a,int b,int len) {
	for (int i=0;i<len;i++) {
		if (x[a+i]!=x[b+i]) return false;
	}
	return true;
}

int solve(int a,int b) {
	if (a>b) return 0;
	if (a==b) return 1;
	int l=a;
	int r=b;
	unsigned long long ha1=0,ha2=0;
	while(l<r) {
		ha1*=26;
		ha1%=prm;
		ha1+=x[l]-'a';
		ha1%=prm;
		ha2+=(poww[b-r]*(x[r]-'a'))%prm;
		ha2%=prm;
		//printf("%llu %llu\n",ha1,ha2);
		if (ha2==ha1) {
			if (check(a,r,b-r+1)) {
				return 2+solve(l+1,r-1);
			}
		}
		l++;
		r--;
	}
	return 1;
}

void f() {
	cin >> x;
	int n = x.length();
	printf("%d\n",solve(0,n-1));
}

int main () {
	init();
	int q;
	scanf("%d",&q);	
	while (q--) f();
	return 0;
}
