#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct bridge {
  int from, to;
};

struct edge {
	int idx,wgt;
};

bool operator< (const edge &a, const edge &b) {
	return a.wgt>b.wgt;
}

vector<bridge> tbl;
priority_queue<edge> q;
int mp[400100];
int logg[400100];
int pre[200100];
int inn[200100];

int hgt[19][400100];
int poww[19];

int timee=1;

void recur(int idx) {
	if (idx>200000) return;
	pre[idx]=timee;
	hgt[0][timee]=logg[idx];
	//printf("%d\n",logg[idx]);
	timee++;
	recur(idx*2);
	inn[idx]=timee;
	hgt[0][timee]=logg[idx];
	timee++;
	recur(idx*2+1);
}

void init() {
	int cur=1;
	int now=0;
	for (int i=1;i<400100;i++) {
		if (i==cur) {
			logg[i]=now;
			cur*=2;
			now++;
		} else {
			logg[i]=logg[i-1];
		}
	}
	poww[0]=1;
	for (int i=1;i<19;i++) {
		poww[i]=poww[i-1]*2;
	}
	recur(1);
	cur=1;
	for (int i=1;i<19;i++) {
		for (int j=1;j<=400000-cur*2+1;j++) {
			hgt[i][j]=min(hgt[i-1][j],hgt[i-1][j+cur]);
			//printf("%d ",hgt[i][j]);
		}
		//printf("\n");
		cur*=2;
	}
}

int sz;

int getMin(int a,int b) {
	//printf("getMin %d %d\n",a,b);	
	int lev = logg[b-a+1];
	int len = poww[lev];
	//printf("%d %d\n",lev,len);
	return min(hgt[lev][a],hgt[lev][b-len+1]);
}

int getDis(int a,int b) {
	if (a>sz) {
		a-=sz+1;
		b-=sz+1;
	}
	if (pre[a]>pre[b]) swap(a,b);
	//printf("getDis %d %d\n ",a,b);
	
	return logg[a]+logg[b]-2*getMin(pre[a],inn[b]);
}

vector<int> clr;

int main () {
	init();
	int k,l,qq;
	scanf("%d%d%d",&k,&l,&qq);
	sz=pow(2,k)-1;
	int a,b;
	for (int i=0;i<l;i++) {
		scanf("%d%d",&a,&b);
		tbl.push_back(bridge{a,b});
	}
	for (int i=0;i<400100;i++) {
		mp[i]=2e9;
	}
	for (int i=0;i<qq;i++) {
		scanf("%d%d",&a,&b);
		q.push(edge{a,0});
		int now,nowDis;
		//mp.clear();
		for (int j=0;j<clr.size();j++) {
			mp[clr[j]]=2e9;
		}
		clr.clear();
		int ans=2e9;
		while (!q.empty()) {
			now = q.top().idx;
			nowDis= q.top().wgt;
			q.pop();
			//printf("pop %d %d\n",now,nowDis);
			if (now==b) ans=min(ans,nowDis);
			if (nowDis>mp[now]) continue;
			for (int i=0;i<l;i++) {
				if (now<=sz) {
					int dis=getDis(now,tbl[i].from);
					int inMap = mp[tbl[i].to]; 
					if (inMap<=nowDis+dis+1) continue;
					if (inMap==2e9) clr.push_back(tbl[i].to);
					mp[tbl[i].to]=min(inMap,nowDis+dis+1);
					//printf("push %d %d\n",tbl[i].to,nowDis+dis+1);
					q.push(edge{tbl[i].to,nowDis+dis+1});
				} else {
					int dis=getDis(now,tbl[i].to);
					int inMap = mp[tbl[i].from];
					if (inMap<=nowDis+dis+1) continue;
					if (inMap==2e9) clr.push_back(tbl[i].from);
					mp[tbl[i].from]=min(inMap,nowDis+dis+1);
					
				//	printf("push %d %d\n",tbl[i].to,nowDis+dis+1);
					q.push(edge{tbl[i].from,nowDis+dis+1});
				}
			}
			if ((now<=sz)==(b<=sz)) {
				int dis=getDis(now,b);
				int inMap = mp[b];
				if (inMap<=nowDis+dis) continue;
				if (inMap==2e9) clr.push_back(b);
				mp[b]=min(inMap,nowDis+dis);
				
				//printf("push %d %d\n",b,nowDis+dis+1);
				q.push(edge{b,nowDis+dis});
			}
		}
		printf("%d\n",ans);
	}
}
