#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct eiei {
	int a,b,c;
	int idx;
};

bool operator< (const eiei &a, const eiei &b) {
	if (a.a==b.a) {
		if (a.b==b.b) {
			return a.c<b.c;
		}
		return a.b<b.b;
	}
	return a.a<b.a;
}

vector<eiei> tbl;
vector<eiei> neww;
bool visit[100100];

int main () {
	int n;
	scanf("%d",&n);
	int a,b,c;
	for (int i=1;i<=n;i++) {
		scanf("%d%d%d",&a,&b,&c);
		tbl.push_back(eiei{a,b,c,i});
		tbl.push_back(eiei{a,c,b,i});
		tbl.push_back(eiei{b,a,c,i});
		tbl.push_back(eiei{b,c,a,i});
		tbl.push_back(eiei{c,a,b,i});
		tbl.push_back(eiei{c,b,a,i});
	}
	sort(tbl.begin(),tbl.end());
	for (int i=0;i<tbl.size();i++) {
		//printf("%d %d %d %d\n",tbl[i].a,tbl[i].b,tbl[i].c,tbl[i].idx);
		if (i) {
			if (tbl[i].a==tbl[i-1].a&&tbl[i].b==tbl[i-1].b&&tbl[i].c==tbl[i-1].c&&tbl[i].idx==tbl[i-1].idx) {
				//printf("cont\n");
				continue;
			}
			
		}
		neww.push_back(tbl[i]);
	}
	//printf("---\n");
	int maxx=0;
	int id1=-1,id2=-1;
	int nowD;
	for (int i=0;i<neww.size();i++) {
		//printf("%d %d %d %d\n",neww[i].a,neww[i].b,neww[i].c,neww[i].idx);
		nowD=min(neww[i].a,min(neww[i].b,neww[i].c));
		if (nowD>maxx) {
			maxx=nowD;
			id1=neww[i].idx;
			id2=-1;
		}
		if (i!=neww.size()-1) {
			if (neww[i].a!=neww[i+1].a||neww[i].b!=neww[i+1].b) continue;
			nowD=min(neww[i].a,min(neww[i].b,neww[i].c+neww[i+1].c));
			if (nowD>maxx) {
				maxx=nowD;
				id1=neww[i].idx;
				id2=neww[i+1].idx;
			}
		}
	}
	if (id2==-1) {
		printf("1\n%d\n",id1);
	} else {
		printf("2\n%d %d\n",id1,id2);
	}
	return 0;
}
