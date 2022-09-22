#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

int tbl[5050];
int rmd[50500];
int id[50500];

struct param {
	int id,wgt;
	param(int a,int b) {
		id=a;
		wgt=b;
	}
};

bool operator< (const param &a, const param &b) {
	return a.wgt>b.wgt;
}

priority_queue<param> q;

int main () {
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
	}
	//memset(rmd,63,sizeof(rmd));
	for (int i=0;i<tbl[0];i++) {
		rmd[i]=1000000100;
	}
	q.push(param(0,0));
	int nowi,nowWgt;
	int nxt;
	while (!q.empty()) {
		nowi=q.top().id;
		nowWgt=q.top().wgt;
		q.pop();
		if (nowWgt>rmd[nowi]) continue;
		rmd[nowi]=nowWgt;
		for (int i=1;i<n;i++) {
			nxt=(nowi+tbl[i])%tbl[0];
			int w = (nowi+tbl[i])/tbl[0];
			if (nowWgt+w>=rmd[nxt]) continue;
			rmd[nxt]=nowWgt+w;
			q.push(param(nxt,nowWgt+w));
		}
	}

	int q;
	int x;
	scanf("%d",&q);
	while (q--) {
		scanf("%d",&x);
		if (rmd[x%tbl[0]]<=x/tbl[0]) printf("TAK\n");
		else printf("NIE\n");
	}
	return 0;
}
