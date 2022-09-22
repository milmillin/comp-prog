#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct edge {
	int to,wgt;
	bool enb;
};

struct node {
	int id,mxChd;
};

struct route {
	int dis,dep;
};

struct param {
	int a,b;
};

vector<edge> pth[200100];

int mnChd;
int mnId;
int size;
bool cnt;
bool visit[200100][2];
int chd[200100];
int mrk[1000100];
vector<route> rte;
int k;
int ans=2e9;
vector<param> stk;

int dfs(int n,int hgt,int dd) {
	visit[n][!cnt]=false;
	visit[n][cnt]=true;
	int sum=1;
	for (int i=0;i<(int)pth[n].size();i++) {
		if (visit[pth[n][i].to][cnt]) continue;
		if (!pth[n][i].enb) continue;
		//c++;
		sum+=dfs(pth[n][i].to,hgt+1,dd+pth[n][i].wgt);
	}
	//if (c==0) {
	rte.push_back(route{dd,hgt});
	//}
	return chd[n]=sum;
}

int chdCnt(int n) {
	visit[n][!cnt]=false;
	visit[n][cnt]=true;
	int mxChd=-1;
	int sum=1;
	int tmp;
	for (int i=0;i<(int)pth[n].size();i++) {
		if (visit[pth[n][i].to][cnt]) continue;
		if (!pth[n][i].enb) continue;
		tmp=chdCnt(pth[n][i].to);
		mxChd=max(mxChd,tmp);
		sum+=tmp;
	}
	mxChd=max(mxChd,size-sum);
	if (mxChd<mnChd) {
		mnChd=mxChd;
		mnId=n;
	}
	return sum;
}

void divide(int n, int sz) {
	mnChd=2e9;
	mnId=-1;

	size=sz;

	//findRoot;
	chdCnt(n);
	
	cnt=!cnt;

//	printf("The root: %d\n",mnId);
	//Consider Different Sides
	visit[mnId][0]=true;
	visit[mnId][1]=true;
	
	vector<int> clr;
	vector<int> chSz;

	for (int i=0;i<(int)pth[mnId].size();i++) {
		if (visit[pth[mnId][i].to][cnt]) continue;
		if (!pth[mnId][i].enb) continue;
		//printf("%d\n",pth[mnId][i].to);
		
		rte.clear();
		dfs(pth[mnId][i].to,1,pth[mnId][i].wgt);
		chSz.push_back(chd[pth[mnId][i].to]);
		for (int j=0;j<(int)rte.size();j++) {
			//printf("%d %d\n",rte[j].dis,rte[j].dep);
			if (rte[j].dis>k) continue;
			if (rte[j].dis==k) {
				ans=min(ans,rte[j].dep);
				continue;
			}
			if (mrk[k-rte[j].dis]) {
				ans=min(ans,mrk[k-rte[j].dis]+rte[j].dep);
			}
		}
		for (int j=0;j<(int)rte.size();j++) {
			if (rte[j].dis>k) continue;
			if (!mrk[rte[j].dis]) mrk[rte[j].dis]=rte[j].dep;
			else mrk[rte[j].dis]=min(mrk[rte[j].dis],rte[j].dep);
			clr.push_back(rte[j].dis);
		}
	//	printf("----\n");
	}
	for (int i=0;i<(int)clr.size();i++) {
		//printf("%d\n",clr[i]);
		mrk[clr[i]]=0;
	}
	cnt=!cnt;
	
	//Divide!!!
	int root=mnId;
	for (int i=0;i<(int)pth[root].size();i++) {
		//printf("**%d %d %d\n",i,cnt,pth[root][i].to);
		if (visit[pth[root][i].to][cnt]) continue;
		if (!pth[root][i].enb) continue;
		//divide(pth[root][i].to,chSz[i]);
		stk.push_back(param{pth[root][i].to,chSz[i]});
		//printf("%d\n",i);
	}
	//printf("endd\n");	
}



int main () {
	int n;
	scanf("%d%d",&n,&k);
	int a,b,c;
	for (int i=1;i<n;i++) {
		scanf("%d%d%d",&a,&b,&c);
		pth[a].push_back(edge{b,c,1});
		pth[b].push_back(edge{a,c,1});
	}
	cnt=0;
//	divide(0,n);
	stk.push_back(param{0,n});
	while (!stk.empty()) {
		a=stk.back().a;
		b=stk.back().b;
		stk.pop_back();
		divide(a,b);

	}
	printf("%d\n",(ans==2e9)?-1:ans);
	return 0;
}

