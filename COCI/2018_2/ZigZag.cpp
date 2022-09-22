#include <cstdio>
#include <vector>
#include <queue>
#include <string>
#include <iostream>

using namespace std;

struct word {
	string x;
	int cnt;
};

bool operator< (const word &a, const word&b) {
	if (a.cnt!=b.cnt) return a.cnt>b.cnt;
	return a.x>b.x;
}

priority_queue<word> qq[30];

int main () {
	int k,n;
	scanf("%d%d",&k,&n);
	string x;
	for (int i=0;i<k;i++) {
		cin>>x;
		qq[x[0]-'a'].push(word{x,0});
	}
	char xx;
	word now;
	for (int i=0;i<n;i++) {
		scanf(" %c",&xx);
		now = qq[xx-'a'].top();
		qq[xx-'a'].pop();
		cout << now.x << '\n';
		now.cnt++;
		qq[xx-'a'].push(now);
	}
	return 0;
}
