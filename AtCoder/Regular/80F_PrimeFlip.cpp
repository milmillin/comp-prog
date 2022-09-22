#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

bool isPrime[10001000];
vector<int> prime;

void init() {
	for (int i=3;i<10001000;i+=2) {
		isPrime[i]=true;
	}
	for (int i=3;i<10001000;i+=2) {
		if (!isPrime[i]) continue;
		for (int j=i+i;j<10001000;j+=i) {
			isPrime[j]=false;
		}
	}
	for (int i=3;i<10001000;i+=2) {
		if (!isPrime[i]) continue;
		prime.push_back(i);
	}
}

bool up[10001000];

void sett(int idx) {
	while (idx<10001000) {
		up[idx]=!up[idx];
		idx+=(idx&-idx);
	}
}

bool gett(int idx) {
	bool ans=false;
	while (idx) {
		ans^=up[idx];
		idx-=(idx&-idx);
	}
	return ans;
}

int main () {
	int n;
	scanf("%d",&n);
	vector<int> tbl(n);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
		sett(tbl[i]);
		sett(tbl[i]+1);
	}
	init();
	int l=tbl[0];
	int r=tbl[n-1];
	int cnt=0;
	while (l<r) {
		int pr=*lower_bound(prime.begin(),prime.end(),r-l+1);
		sett(l);
		sett(l+pr);
		cnt++;
		l++;
		r=l+pr-1;
		while (l<r&&!gett(r)) r--;
	}
	printf("%d\n",cnt);	
	return 0;
}
