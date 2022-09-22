#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int col[200100];
int cnt[200100];
int maxCol;
vector<int> pth[200100];
bool visit[200100];

int key;
int fst[200100];

int recur(int idx) {
	visit[idx]=true;
	if (fst[col[idx]]!=key) {
		fst[col[idx]]=key;
		cnt[col[idx]]=0;
	}
	cnt[col[idx]]++;
	if (cnt[col[idx]]>maxCol) {
		maxCol=cnt[col[idx]];
		//maxColIdx=idx;
	}
	int size=1;
	for (int i=0;i<pth[idx].size();i++) {
		if (visit[pth[idx][i]]) continue;
		size+=recur(pth[idx][i]);
	}
	return size;
}

int main () {
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	for (int i=1;i<=n;i++) {
		scanf("%d",&col[i]);
	}
	int l,r;
	for (int i=0;i<m;i++) {
		scanf("%d%d",&l,&r);
		pth[l].push_back(r);
		pth[r].push_back(l);
	}
	int anss=0;
	int  ans;
	key=0;
	for (int i=1;i<=n;i++) {
		if (visit[i]) continue;
		//memset(cnt,0,sizeof(cnt));
		maxCol=0;
		key++;
		ans=recur(i);
		anss+=ans-maxCol;
	}
	printf("%d\n",anss);
	return 0;
}
