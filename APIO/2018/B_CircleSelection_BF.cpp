#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

struct circle {
	int x,y,r;
	int id;
};

bool operator< (const circle &a, const circle &b) {
	if (a.r!=b.r) return a.r>b.r;
	return a.id<b.id;
}

bool intersect (const circle &a, const circle &b) {
	long long tmp=(long long)(a.x-b.x)*(a.x-b.x)+(long long)(a.y-b.y)*(a.y-b.y);
	//printf("aa %d %d %lld\n",a.id,b.id,tmp);
	return tmp<=(long long)(a.r+b.r)*(a.r+b.r);
}

int par[100100];

int main () {
	int n;
	scanf("%d",&n);
	assert(n<10000);
	int a,b,c;
	vector<circle> tbl;
	for (int i=1;i<=n;i++) {
		scanf("%d%d%d",&a,&b,&c);
		tbl.push_back(circle{a,b,c,i});
	}	
	sort(tbl.begin(),tbl.end());


	for (int i=0;i<n;i++) {
		//printf("-- %d\n",tbl[i].id);
		if (par[tbl[i].id]) continue;
		par[tbl[i].id]=tbl[i].id;
		for (int j=i+1;j<n;j++) {
			if (intersect(tbl[i],tbl[j])) {
				//printf("xx %d\n",tbl[j].id);
				if (par[tbl[j].id]) continue;
				par[tbl[j].id]=tbl[i].id;
			}
		}
	}
	for (int i=1;i<=n;i++) {
		printf("%d ",par[i]);
	}
	printf("\n");
	return 0;
}
