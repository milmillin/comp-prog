#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;


bool hs[1000100];
int wat[1000100];
int loc[1000100];

int mod=1000033;
int n,m;

int getHash(const string &x) {
	long long unit=1;
	long long ans=0;
	for (int i=x.size()-1;i>=0;i--) {
		ans+=unit*(x[i]-'a');
		ans%=mod;
		unit*=m;
		unit%=mod;
	}
	return ans;
}

bool increase(string &x) {
	for (int i=x.size()-1;i>=0;i--) {
		x[i]++;
		if (x[i]-'a'<m) return true;
		x[i]='a';
	}
	return false;
}

void insert(int val,int l) {
	int cur=val;
	while (hs[cur]) {
		cur++;
		cur%=mod;
	}
	hs[cur]=true;
	wat[cur]=val;
	loc[cur]=l;
}

string x;

bool compare(string &xx, int offset) {
	for (int i=0;i<(int)xx.size();i++) {
		if (xx[i]!=x[offset+i]) return false;
	}
	return true;
}

bool find(string &xx) {
	int h=getHash(xx);
	int c=h;
	while (hs[c]&&)
}


int main () {
	scanf("%d%d",&n,&m);
	cin >> x;
	string cur;
	long long val;
	long long rem=1;
	for (int i=1;i<=m;i++) {
		rem*=m;
		rem%=mod;
		memset(hs,0,sizeof(hs));
		val=0;
		for (int j=0;j<i;j++) {
			val*=m;
			val%=mod;
			val+=(x[j]-'a');
			val%=mod;
		}
		hs[val]=true;
		//printf("%lld ",val);
		for (int j=i;j<n;j++) {
			val*=m;
			val%=mod;
			val+=(x[j]-'a');
			val%=mod;
			val-=(x[j-i]-'a')*rem;
			val%=mod;
			val+=mod;
			val%=mod;
			hs[val]=true;	
			//printf("%lld ",val);
		}
		//printf("\n");

		cur.clear();
		for (int j=0;j<i;j++) cur.push_back('a');
		while (hs[getHash(cur)]) {
			//cout << cur << " " << getHash(cur) << '\n';
			if (!increase(cur)) break;
		}
		if (!hs[getHash(cur)]) {
			cout << cur << '\n';
			return 0;
		}
	}
	
	return 0;
}
