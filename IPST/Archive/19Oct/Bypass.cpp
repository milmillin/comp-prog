#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct {
	int to,cntAtTo;
} edge;

typedef struct {
	int from,to;
} edgee;

vector<int> pth[100100];
vector<edge> rePth[100100];
vector<edgee> ee;
bool visit[100100];
int cntt[100100];
edge maxCntAtTo[100100][2];
int n;

int cnt(int idx) {
	visit[idx]=true;
	//printf("%d\n",idx);
	int sum=1;
	int tmp;
	for (int i=0;i<pth[idx].size();i++) {
		if (visit[pth[idx][i]]) continue;
		tmp=cnt(pth[idx][i]);
		
	//	printf("--%d %d %d\n",idx,pth[idx][i],tmp);	
		if (tmp>=maxCntAtTo[idx][0].cntAtTo) {
			//printf("A\n");
			maxCntAtTo[idx][1].to=maxCntAtTo[idx][0].to;
			maxCntAtTo[idx][1].cntAtTo=maxCntAtTo[idx][0].cntAtTo;
			maxCntAtTo[idx][0]=edge{pth[idx][i],tmp};
		} else if (tmp>maxCntAtTo[idx][1].cntAtTo) {
			//printf("B\n");
			maxCntAtTo[idx][1]=edge{pth[idx][i],tmp};
		}
		
		if (n-tmp>=maxCntAtTo[pth[idx][i]][0].cntAtTo) {
			//printf("C\n");
			maxCntAtTo[pth[idx][i]][1].to=maxCntAtTo[pth[idx][i]][0].to;
			maxCntAtTo[pth[idx][i]][1].cntAtTo=maxCntAtTo[pth[idx][i]][0].cntAtTo;
			maxCntAtTo[pth[idx][i]][0]=edge{idx,n-tmp};
		} else if (n-tmp>maxCntAtTo[pth[idx][i]][1].cntAtTo) {
			//printf("D\n");
			maxCntAtTo[pth[idx][i]][1]=edge{idx,n-tmp};
		}


		//rePth[idx].push_back(edge{pth[idx][i],tmp});
		//rePth[pth[idx][i]].push_back(edge{idx,n-tmp});

		sum+=tmp;
	}
	return sum;
}

typedef struct {
	int idx;
	bool visited;
} dfs;

void recur() {
	vector<dfs> stk;
	stk.push_back(dfs{1,false});
	int now;
	while (!stk.empty()) {
		now = stk.back().idx;
		//printf("%d %d\n",now,stk.back().visited);
		if (stk.back().visited) {
			int sum=1;
			int tmp;
			for (int i=0;i<pth[now].size();i++) {
				//if (visit[pth[now][i]]) continue;
				tmp=cntt[pth[now][i]];
				if (!tmp) continue;
				//printf("--%d %d\n",pth[now][i],tmp);
				rePth[now].push_back(edge{pth[now][i],tmp});
				rePth[pth[now][i]].push_back(edge{now,n-tmp});

				sum+=tmp;
			}
			cntt[now]=sum;
			//printf("--%d\n",cntt[now]);
			stk.pop_back();
		} else {
			stk.back().visited=true;
			visit[now]=true;
			for (int i=0;i<pth[now].size();i++) {
				if (visit[pth[now][i]]) continue;
				stk.push_back(dfs{pth[now][i],false});	
			}
		}
	}
}

int main () {
	//int n;
	scanf("%d",&n);
	int a,b;
	for (int i=1;i<n;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		pth[b].push_back(a);
		ee.push_back(edgee{a,b});
	}
	cnt(1);
	//recur();
	int from,to;
	long long anss=0;
	/*
	for (int i=1;i<=n;i++) {
		printf("%d %d\n",maxCntAtTo[i][0].cntAtTo,maxCntAtTo[i][1].cntAtTo);
	}
	*/
	for (int i=0;i<ee.size();i++) {
		from = ee[i].from;
		to = ee[i].to;
		int maxFrom=0,maxTo=0;
		if (maxCntAtTo[to][0].to==from) maxTo=maxCntAtTo[to][1].cntAtTo;
		else maxTo=maxCntAtTo[to][0].cntAtTo;

		if (maxCntAtTo[from][0].to==to) maxFrom=maxCntAtTo[from][1].cntAtTo;
		else maxFrom=maxCntAtTo[from][0].cntAtTo;
		/*
		for (int j=0;j<rePth[from].size();j++) {
			if (rePth[from][j].to==to) continue;
			maxFrom=max(maxFrom,rePth[from][j].cntAtTo);
		}
		for (int j=0;j<rePth[to].size();j++) {
			if (rePth[to][j].to==from) continue;
			maxTo=max(maxTo,rePth[to][j].cntAtTo);
		}
		*/
		anss=max(anss,(long long)maxFrom*maxTo);
	}
	printf("%lld\n",anss);
	return 0;
}
