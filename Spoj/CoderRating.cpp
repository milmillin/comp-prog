#include <cstdio>
#include <algorithm>

using namespace std;

struct ei {
	int idx,rat1,rat2;
};

bool operator< (const ei &a, const ei &b) {
	if (a.rat1==b.rat1) return a.rat2<b.rat2;
	return a.rat1<b.rat1;
}

ei tbl[300100];
int ans[300100];
int bit[100100];

void update (int idx,int val) {
	while (idx<100100) {
		bit[idx]+=val;
		idx+=(idx&-idx);
	}
}

int get (int idx) {
	int sum=0;
	while (idx) {
		sum+=bit[idx];
		idx-=(idx&-idx);
	}
	return sum;
}


int main () {
	int n;
	scanf("%d",&n);
	//int a,b;
	for (int i=0;i<n;i++) {
		scanf("%d%d",&tbl[i].rat1,&tbl[i].rat2);
		tbl[i].idx=i;
	}
	sort(tbl,tbl+n);
	int cur=0;
	for (int i=0;i<n;i++) {
		while (cur<n&&tbl[cur].rat1<=tbl[i].rat1) {
			if (tbl[cur].rat1==tbl[i].rat1&&tbl[cur].rat2>=tbl[i].rat2) break;
			update(tbl[cur].rat2,1);
			cur++;
		}
		ans[tbl[i].idx]+=get(tbl[i].rat2);
		
	}
	for (int i=0;i<n;i++) {
		printf("%d\n",ans[i]);
	}
	return 0;
}
