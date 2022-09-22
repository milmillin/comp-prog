#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int mem[1010][3];
vector<int> pth[1010];

int recur(int idx,int st,int org) {
	if (mem[idx][st]!=-1) return mem[idx][st];
	if (st==0) {
		//blank
		int sum=0;
		for (int i=0;i<pth[idx].size();i++) {
			if (pth[idx][i]==org) continue;
			sum+=max(recur(pth[idx][i],0,idx),max(recur(pth[idx][i],1,idx),recur(pth[idx][i],2,idx)));
		}
		return mem[idx][st]=sum;
	} else if (st==1) {
		//set1
		int sum=0;
		for (int i=0;i<pth[idx].size();i++) {
			if (pth[idx][i]==org) continue;
			sum+=recur(pth[idx][i],0,idx);
		}
		return mem[idx][st]=sum+1;
	} else if (st==2) {
		//set2
		int sum=0;
		int maxDif=0;
		int blk,wht;
		for (int i=0;i<pth[idx].size();i++) {
			if (pth[idx][i]==org) continue;
			blk=recur(pth[idx][i],0,idx);
			wht=recur(pth[idx][i],1,idx);
			maxDif=max(maxDif,wht-blk);
			sum+=recur(pth[idx][i],0,idx);
		}
		return mem[idx][st]=maxDif+sum+1; 
	}
}

void f() {
	for (int i=0;i<1010;i++) {
		pth[i].clear();
	}
	int n;
	scanf("%d",&n);
	int a,b;
	for (int i=1;i<n;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		pth[b].push_back(a);
	}
	memset(mem,-1,sizeof(mem));

	
	printf("%d\n",max(recur(1,0,-1),max(recur(1,1,-1),recur(1,2,-1))));
	/*
	for (int i=1;i<=n;i++) {
		for (int j=0;j<3;j++) {
			printf("%d ",mem[i][j]);
		}
		printf("\n");
	}
	*/
}

int main () {
	int q;
	scanf("%d",&q);
	while (q--) f();
	return 0;
}
