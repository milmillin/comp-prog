#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct ei {
	int r,c,val;
};

bool operator< (const ei &a,const ei &b) {
	return a.val>b.val;
}

vector<ei> tbl;

long long bit[1010][1010];

void update(int r,int c,int val) {
	for (int i=r;i<1010;i+=(i&-i)) {
		for (int j=c;j<1010;j+=(j&-j)) {
			bit[i][j]+=val;
		}
	}
}

long long get(int r,int c) {
	long long sum=0;
	for (int i=r;i>0;i-=(i&-i)) {
		for (int j=c;j>0;j-=(j&-j)) {
			sum+=bit[i][j];
		}
	}
	return sum;
}

int main () {
	int n;
	scanf("%d",&n);
	int x;
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=n;j++) {
			scanf("%d",&x);
			tbl.push_back(ei{i,j,x});	
		}
	}
	sort(tbl.begin(),tbl.end());
	long long ans=0;
	n*=n;
	int cur=0;
	for (int i=0;i<n;i++) {
		//printf("%d\n",i);
		while (cur<n&&tbl[cur].val>tbl[i].val) {
			update(tbl[cur].r,tbl[cur].c,1);
			cur++;
		}
		ans+=get(tbl[i].r,tbl[i].c);
		//printf("yay\n");
		//update(tbl[i].r,tbl[i].c,1);
	}
	printf("%lld\n",ans);
	return 0;
}
