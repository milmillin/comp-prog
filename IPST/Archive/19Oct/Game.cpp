#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

vector<int> pth[5050];
vector<int> stk;
bool onStk[5050];

int indexx[5050];
int lowlink[5050];
int timee;

int num;
int compNum[5050];
int compSz[5050];

void recur(int idx) {
	timee++;
	indexx[idx]=timee;
	lowlink[idx]=timee;
	stk.push_back(idx);
	onStk[idx]=true;
	//printf("%d\n",idx);
	for (int i=0;i<pth[idx].size();i++) {
	//	printf("yay\n");
		if (indexx[pth[idx][i]]==0) {
			//printf("**%d\n",pth[idx][i]);
			recur(pth[idx][i]);
			lowlink[idx]=min(lowlink[idx],lowlink[pth[idx][i]]);
		} else if (onStk[pth[idx][i]]) {
			//printf("Kuy\n");
			lowlink[idx]=min(lowlink[idx],indexx[pth[idx][i]]);
		}
	}
	//printf("-%d %d\n",lowlink[idx],indexx[idx]);	
	if (lowlink[idx]==indexx[idx]) {
		//printf("yay\n");
		num++;
		int now;
		do {
			now=stk.back();
			stk.pop_back();
			onStk[now]=false;
			compNum[now]=num;
			compSz[num]++;
			//comp[num].push_back(now);
		} while (now!=idx);
		//if (stk.empty()) printf("eiei\n");	
	}
}

vector<int> from;
vector<int> to;

vector<int> compPth[5050];
int indeg[5050];
int cnt[5050];

bool visit[5050];

int rnkk[5050];

void recur2(int idx,int rnk) {
	//visit[idx]=true;
	rnkk[idx]=max(rnkk[idx],rnk);
	//cnt[rnk]+=compSz[idx];
	for (int i=0;i<compPth[idx].size();i++) {
		//if (visit[compPth[idx][i]]) continue;
		recur2(compPth[idx][i],rnk+1);
	}
}

int main () {
	int n,k;
	scanf("%d%d",&n,&k);
	int a,b;
	for (int i=0;i<k;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		from.push_back(a);
		to.push_back(b);
	}
	for (int i=0;i<n;i++) {	
		if (indexx[i]) continue;
		recur(i);
	}
	/*
	for (int i=0;i<n;i++) {
		printf("%d ",compNum[i]);
	}
	printf("\n");
	*/
	for (int i=0;i<k;i++) {
		if (compNum[from[i]]==compNum[to[i]]) continue;
		compPth[compNum[from[i]]].push_back(compNum[to[i]]);
		indeg[compNum[to[i]]]++;
	}
	for (int i=1;i<=num;i++) {
		if (!indeg[i]) recur2(i,0);
	}
	for (int i=1;i<=num;i++) {
	  cnt[rnkk[i]]+=compSz[i];
	}
	
	for (int i=0;cnt[i]!=0;i++) {
		printf("%d ",cnt[i]);
	}
	printf("\n");
	
	return 0;
}
