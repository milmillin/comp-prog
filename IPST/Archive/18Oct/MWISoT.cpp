#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int wgt[100100];
vector<int> pth[100100];
int mem[100100][2];

int recur(int idx,int st,int org) {
	if (mem[idx][st]!=-1) return mem[idx][st];
	if (st==0) {
		//not select
		int sum=0;
		for (int i=0;i<pth[idx].size();i++) {
			if (pth[idx][i]==org) continue;
			sum+=max(recur(pth[idx][i],0,idx),recur(pth[idx][i],1,idx));
		}
		return mem[idx][st]=sum;
	} else {
		//select
		int sum=0;
		for (int i=0;i<pth[idx].size();i++) {
			if (pth[idx][i]==org) continue;
			sum+=recur(pth[idx][i],0,idx);
		}
		return mem[idx][st]=sum+wgt[idx];
	}
}

int main () {
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		scanf("%d",&wgt[i]);
	}
	int a,b;
	for (int i=1;i<n;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		pth[b].push_back(a);
	}
	memset(mem,-1,sizeof(mem));
	printf("%d\n",max(recur(0,0,-1),recur(0,1,-1)));
	return 0;
}
