#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct phone {
	int x,y,z,mp;
	bool dis;
};

bool cmp (const phone &a, const phone &b) {
	return a.z>b.z;
}

bool cmp2 (const phone &a, const phone &b) {
	if (a.x==b.x) {
		if (a.y==b.y) {
			return a.z<b.z;
		}
		return a.y<b.y;
	}
	return a.x<b.x;
}

int bit[100100];

int get(int idx) {
	int sum=0;
	while (idx) {
		sum=max(sum,bit[idx]);
		idx-=(idx&-idx);
	}
	return sum;
}

void update(int idx,int val) {
	while (idx<100100) {
		bit[idx]=max(bit[idx],val);
		idx+=(idx&-idx);
	}
}

int main () {
	int n;
	scanf("%d",&n);
	vector<phone> tbl(n);
	for (int i=0;i<n;i++) {
		scanf("%d%d%d",&tbl[i].x,&tbl[i].y,&tbl[i].z);
		tbl[i].dis=false;
	}
	sort(tbl.begin(),tbl.end(),cmp);
	int cur=0;
	int now=2e9;
	for (int i=0;i<n;i++) {
		if (tbl[i].z<now) {
			cur++;
			now=tbl[i].z;
			tbl[i].mp=cur;
		} else if (tbl[i].z==now) {
			tbl[i].mp=cur;
		}
		//printf("%d\n",tbl[i].mp);
	}
	sort(tbl.begin(),tbl.end(),cmp2);

	//printf("yay\n");
	int cnt=0;
	for (int i=n-1;i>=0;i--) {
		if (get(tbl[i].mp)>=tbl[i].y) {
			cnt++;
		}
		update(tbl[i].mp,tbl[i].y);
	}
	printf("%d\n",cnt);
	return 0;
}
