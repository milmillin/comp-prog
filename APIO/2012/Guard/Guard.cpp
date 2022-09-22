#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

int block[100100];
int qs[100100];
int qq[100100];

bool ans[100100];

int main () {
	int n,k,m;	
	scanf("%d%d%d",&n,&k,&m);
	int a,b,c;
	vector<pair<int,int>> blk;
	vector<pair<int,int>> has;
	for (int i=0;i<m;i++) {
		scanf("%d%d%d",&a,&b,&c);
		if (c) has.push_back({a,b});
		else blk.push_back({a,b});
	}
	//assert(k>=(int)has.size());
	if (k<(int)has.size()) {
		printf("yay\n");
		return 0;
	}
	sort(blk.begin(),blk.end());
	int left=0;
	int rgt=0;
	int l=n;
	for (auto &i:blk) {
		if (i.first>rgt) {
			for (int j=i.first;j<=i.second;j++) {
				block[j]++;
				//printf("+%d\n",j);
				l--;
				qs[j]=j;
			}
			left=i.first;
			rgt=i.second;
		} else {
			for (int j=rgt+1;j<=i.second;j++) {
				block[j]++;
				//printf("+%d\n",j);
				l--;
				qs[j]=j;
			}
			rgt=max(rgt,i.second);
		}
		//printf("-- %d %d\n",left,rgt);
	}
	//printf("%d %d\n",l,k);
	//for (int i=1;i<=n;i++) {
		//if (block[i]>1) printf("ff\n");
	//}
	if (l==k) {
		for (int i=1;i<=n;i++) {
			if (!block[i]) printf("%d\n",i);
		}
		return 0;
	}
	//for (int i=1;i<=n;i++) {
		//printf("%d ",block[i]);
	//}
	//printf("\n");
	for (int i=1;i<=n;i++) {
		block[i]+=block[i-1];
		qs[i]+=qs[i-1];
		qq[i]=i;
		qq[i]+=qq[i-1];
	}

	bool printed=false;
	for (auto &i:has) {
		//printf("%d %d %d\n",i.first,i.second,block[i.second]-block[i.first-1]);
		if (i.second-i.first==block[i.second]-block[i.first-1]) {
			//printed=true;
			//printf("%d\n",qq[i.second]-qq[i.first-1]-qs[i.second]+qs[i.first-1]);									
			ans[qq[i.second]-qq[i.first-1]-qs[i.second]+qs[i.first-1]]=true;
		}
	}
	for (int i=1;i<=n;i++) {
		if (ans[i]) {
			printf("%d\n",i);
			printed=true;
		}
	}
	if (!printed) printf("-1\n");
	return 0;
}
