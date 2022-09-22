#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int tbl[100100];
vector<int> dat[100100];
int amt[100100];

bool cmp (const int a, const int b) {
	return dat[a].end()<dat[b].end();
}

int bit[100100];

int get(int idx) {
	int sum=0;
	while (idx) {
		sum+=bit[idx];
		idx-=(idx&-idx);
	}
	return sum;
}

void update(int idx,int val) {
	while (idx<100100) {
		bit[idx]+=val;
		idx+=(idx&-idx);
	}
}

int cnt[100100];
bool visit[100100];

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) {
		scanf("%d",&tbl[i]);
		if (tbl[i]) {
			dat[tbl[i]].push_back(i);
			cnt[i]++;
		}
		cnt[i]+=cnt[i-1];
		//else update(i,1);
	}
	
	for (int i=1;i<=m;i++) {
		scanf("%d",&amt[i]);
	}	

	int lo=1,hi=n;
	int mid;
	while (lo<hi) {
		mid=(lo+hi)/2;
		int zero=0;
		int i=mid;
		int subCnt=0;
		
		memset(visit,0,sizeof(visit));
		while (i&&!tbl[i]) i--;
		if (!tbl[i]) {
			//printf("-1\n");
			//return 0;
			lo=mid+1;
			continue;
		}
		//printf("%d %d\n",mid,i);
		for (;i>=1;i--) {
			if (tbl[i]) {
				if (visit[tbl[i]]){
					if (zero) zero--;
				} else {
					visit[tbl[i]]=true;
					zero+=amt[tbl[i]];
					subCnt++;
				}
			} else {
				if (zero) zero--;
			}
			
		}
		if (zero||subCnt!=m) {
			//printf("n\n");
			lo=mid+1;
		} else {
			//printf("y\n");
			hi=mid;
		}
	}
	mid=hi;
	int zero=0;
		int i=mid;
		int subCnt=0;
		memset(visit,0,sizeof(visit));
		while (i&&!tbl[i]) i--;
		if (!tbl[i]) {
			printf("-1\n");
			return 0;
		}
		for (;i>=1;i--) {
			if (tbl[i]) {
				if (visit[tbl[i]]){
					if (zero) zero--;
				} else {
					visit[tbl[i]]=true;
					zero+=amt[tbl[i]];
					subCnt++;
				}
			} else {
				if (zero) zero--;
			}
			
		}
		if (zero||subCnt!=m) {
			printf("-1\n");
		} else {
			printf("%d\n",hi);
		}

	/*
	for (int i=0;i<m;i++) {
		scanf("%d",&amt[i]);
	}
	vector<int> ord(m);
	for (int i=1;i<=m;i++) {
		ord[i]=i;
		if (dat[i].size()==0) {
			printf("-1\n");
			return 0;
		}
	}
	sort(ord.begin(),ord.end(),cmp);
	int now;
	for (int i=0;i<m;i++) {
		now=ord[i];
		for (int j=0;j<dat[now].size();j++) {
			if (j==dat[now].size()-1) {
				if jjj
			}
		}
	}
	*/
	return 0;
}
