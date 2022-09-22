#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int rnk[20][100100];

struct pp {
	int id;
	int a,b;
};

bool operator< (const pp &a, const pp &b) {
	if (a.a!=b.a) return a.a<b.a;
	return a.b<b.b;
}

void f() {
	int n;
	scanf("%d",&n);
	string x;
	cin>>x;
	for (int i=0;i<n;i++) {
		rnk[0][i]=x[i]-'a';
	}
	for (int i=1;i<20;i++) {
		vector<pp> tmp(n);
		for (int j=0;j<n;j++) {
			//printf("%d yay %d %d\n",i,j,(j+(1<<(i-1)))%n);
			int a = (j+(1<<(i-1)))%n;
			tmp[j]=pp{j,rnk[i-1][j],rnk[i-1][a]};
		}
		sort(tmp.begin(),tmp.end());
		rnk[i][tmp[0].id]=0;
		for (int j=1;j<n;j++) {
			//printf("%d %d\n",i,tmp[j].id);
			rnk[i][tmp[j].id]=((tmp[j].a==tmp[j-1].a&&tmp[j].b==tmp[j-1].b)?rnk[i][tmp[j-1].id]:j);
		}
		//printf("--%d\n",i);
	}
	//printf("ei\n");
	int ans=2e9;
	int id=-1;
	for (int i=0;i<n;i++) {
		if (rnk[19][i]<ans) {
			ans=rnk[19][i];
			id=i;
		}
	}
	printf("%d\n",id);
}

int main () {
	int q;
	scanf("%d",&q);
	while (q--) f();
	return 0;
}
