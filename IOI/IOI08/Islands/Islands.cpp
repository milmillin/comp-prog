#include <cstdio>
#include <queue>
#include <cassert>
#include <vector>

using namespace std;

struct edge {
	int to,wgt;
};

vector<edge> pth[1000100];
bool visit[1000100];
long long ans;
vector<int> stk;
vector<int> cycle;
vector<long long> subCost;
vector<long long> cost;

void dfs(int idx,int par) {
	stk.push_back(idx);
	visit[idx]=true;
	int cnt=0;
	for (int i=0;i<(int)pth[idx].size();i++) {
		if (!cnt&&pth[idx][i].to==par) {
			cnt++;
			continue;
		}
		if (visit[pth[idx][i].to]) {
			//printf("ops %d %d\n",idx,pth[idx][i].to);
			//for (int j=0;j<stk.size();j++) {
				//printf("%d ",stk[j]);
			//}	
			//printf("\n");
			if (cycle.size()==0) {
				//printf("change\n");
				for (int j=stk.size()-1;j>=0;j--) {
					cycle.push_back(stk[j]);
					//printf("add %d %d\n",stk[j],pth[idx][i].to);
					if (stk[j]==pth[idx][i].to) break;
				}
			}
			continue;
		}
		dfs(pth[idx][i].to,idx);
	}

	stk.pop_back();
}

long long findCost(int idx,int a,int b) {
	long long ans=0;
	for (int i=0;i<(int)pth[idx].size();i++) {
		if (pth[idx][i].to==a||pth[idx][i].to==b) continue;
		ans=max(ans,findCost(pth[idx][i].to,idx,-1)+pth[idx][i].wgt);	
	}	
	return ans;
}

long long findd(int idx,int val) {
	for (int i=0;i<(int)pth[idx].size();i++) {
		if (pth[idx][i].to==val) return pth[idx][i].wgt;
	}
	assert(0);
}

int main () {
	int n;
	scanf("%d",&n);
	int a,b;
	for (int i=1;i<=n;i++) {
		scanf("%d%d",&a,&b);
		pth[i].push_back(edge{a,b});
		pth[a].push_back(edge{i,b});
	}
	long long ans=0;

	for (int i=1;i<=n;i++) {
		if (visit[i]) continue;
		stk.clear();
		cycle.clear();
		dfs(i,i);
		//printf("+++ %d\n",i);
		subCost.clear();
		cost.clear();
		int nn=cycle.size();

		//for (int j=0;j<nn;j++) {
			//printf("%d ",cycle[j]);
		//}
		//printf("\n");
		for (int j=0;j<nn;j++) {
			long long tmp=findCost(cycle[j],cycle[(j+1)%nn],cycle[(j-1+nn)%nn]);
			subCost.push_back(tmp);
			if (nn!=2) cost.push_back(findd(cycle[j],cycle[(j-1+nn)%nn]));
		}
		if (nn==2) {
			cost.push_back(pth[cycle[0]][0].wgt);
			cost.push_back(pth[cycle[0]][1].wgt);
		}
		//for (int j=0;j<nn;j++) {
			//printf("%lld ",cost[j]);
		//}
		//printf("\n");
		for (int j=0;j<nn;j++) {
			subCost.push_back(subCost[j]);
			cost.push_back(cost[j]);
		}
		//for (int j=0;j<nn*2;j++) {
			//printf("%lld ",cost[j]);
		//}
		//printf("\n");
		cost[0]=0;
		for (int j=1;j<nn*2;j++) {
			cost[j]+=cost[j-1];
		}
		//for (int j=0;j<2*nn;j++) {
			//printf("%d,%lld,%lld ",cycle[j%nn],subCost[j],cost[j]);
		//}
		//printf("\n");
		vector<long long> tbl(nn*2);
		for (int j=0;j<nn*2;j++) {
			tbl[j]=subCost[j];
			tbl[j]-=cost[j];
			//printf("%lld ",tbl[j]);
		}
		//printf("\n");
		deque<int> qq;
		qq.push_back(0);
		long long mx=0;
		for (int j=1;j<nn*2;j++) {
			while (!qq.empty()&&qq.front()<=j-nn) qq.pop_front();
			mx=max(mx,tbl[qq.front()]+cost[j]+subCost[j]);
			//printf ("%lld ",tbl[qq.front()]+cost[j]+subCost[j]);
			while (!qq.empty()&&tbl[qq.back()]<=tbl[j]) qq.pop_back();
			qq.push_back(j);
		}
		//printf("\n");
		ans+=mx;
		//printf("++%lld\n",mx);		
	}
	printf("%lld\n",ans);
	return 0;
}
