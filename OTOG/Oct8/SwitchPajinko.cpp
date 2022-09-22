#include <cstdio>
#include <cassert>
#include <queue>

using namespace std;

int l[500500];
int r[500500];
bool isL[500500];
int cnt[500100];
long long nn[500100];
bool called[500100];


queue<int> q;

void swp(int idx) {
	//assert(called[idx]==false);
	if (called[idx]) return;
	called[idx]=true;
	if (idx==0) return;
	long long nl,nr;
	nl=nr=nn[idx]/2;
	if (nn[idx]%2) {
		if (isL[idx]) {
			isL[idx]=false;
			nl++;
		}
		else {
			isL[idx]=true;
			nr++;
		}
	}

	nn[l[idx]]+=nl;
	nn[r[idx]]+=nr;

	if (l[idx]!=0) cnt[l[idx]]--;
	if (r[idx]!=0) cnt[r[idx]]--;
	//assert(cnt[l[idx]]>=0&&cnt[r[idx]]>=0);
	if (l[idx]!=0) if (cnt[l[idx]]==0) q.push(l[idx]);
	if (r[idx]!=0) if (cnt[r[idx]]==0) q.push(r[idx]);
}

int main () {
	long long k;
	int n;
	scanf("%lld%d",&k,&n);
	char x;
	for (int i=1;i<=n;i++) {
		scanf(" %c%d%d",&x,&l[i],&r[i]);
		cnt[l[i]]++;
		cnt[r[i]]++;
		isL[i]=(x=='L');
	}
	nn[1]=k;
	q.push(1);
	for (int i=2;i<=n;i++) {
		if (cnt[i]==0) q.push(i);
	}
	int now;
	while (!q.empty()) {
		now=q.front();
		q.pop();
		swp(now);
	}
	for (int i=1;i<=n;i++) {
		printf("%c",(isL[i])?'L':'R');
	}
	printf("\n");
	return 0;
}
