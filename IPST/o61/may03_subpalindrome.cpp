#include <cstdio>
#include <cmath>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

char buf[100100];
vector<int> pos[100100];
vector<int> pose[100100];

int curl;
int curr;

long long ans=0;

void incl() {
	int tmp = upper_bound(pos[curl].begin(),pos[curl].end(),curr)-pos[curl].begin();
	ans-=tmp;	
	//printf("incl %d %d\n",curl,tmp);
	curl++;
}

void decl() {
	curl--;
	int tmp = upper_bound(pos[curl].begin(),pos[curl].end(),curr)-pos[curl].begin();
	//printf("decl %d %d\n",curl+1,tmp);
	ans+=tmp;
}

void incr() {
	curr++;
	int tmp = pose[curr].end()-lower_bound(pose[curr].begin(),pose[curr].end(),curl);
	//printf("incr %d %d\n",curr-1,tmp);
	ans+=tmp;
}

void decr() {
	int tmp = pose[curr].end()-lower_bound(pose[curr].begin(),pose[curr].end(),curl);
	ans-=tmp;
	//printf("decr %d %d\n",curr,tmp);
	curr--;
}


struct query {
	int l,r;
	long long ans;
	int id;
};

int blkSz;

bool byMO (const query &a, const query &b) {
	if (a.l/blkSz!=b.l/blkSz) return a.l/blkSz<b.l/blkSz;
	return a.r<b.r;
}

bool byID (const query &a, const query &b) {
	return a.id<b.id;
}

int main () {
	int n;
	scanf("%d",&n);

	blkSz = (int)floor(sqrt(n));

	scanf("%s",buf+1);
	buf[0]='$';

	for (int i=1;i<=n;i++) {
		int r=0;
		pos[i].push_back(i);
		pose[i].push_back(i);
		while (buf[i-r-1]==buf[i+r+1]) {
			r++;
			pos[i-r].push_back(i+r);
			pose[i+r].push_back(i-r);
		}
	}
	for (int i=2;i<=n;i++) {
		int r=0;
		if (buf[i-1]!=buf[i]) continue;
		pos[i-1].push_back(i);
		pose[i].push_back(i-1);
		while (buf[i-r-2]==buf[i+r+1]) {
			pos[i-r-2].push_back(i+r+1);
			pose[i+r+1].push_back(i-r-2);
			r++;
		}
	}

	for (int i=1;i<=n;i++) {
		sort(pos[i].begin(),pos[i].end());
		sort(pose[i].begin(),pose[i].end());	
		//for (auto j:pos[i]) {
			//printf("%d ",j);
		//}
		//printf("\n");
		//for (auto j:pose[i]) {
			//printf("%d ",j);
		//}
		//printf("\n\n");
	}

	int q;
	scanf("%d",&q);
	int a,b;
	vector<query> qs;
	for (int i=0;i<q;i++) {
		scanf("%d%d",&a,&b);
		qs.push_back(query{a,b,0,i});
	}
	sort(qs.begin(),qs.end(),byMO);
	curl=curr=0;
	for (auto &qq:qs) {
		while (curl<qq.l) incl();
		while (curl>qq.l) decl();
		while (curr<qq.r) incr();
		while (curr>qq.r) decr();
		qq.ans=ans;
	}
	sort(qs.begin(),qs.end(),byID);
	for (auto &qq:qs) {
		printf("%lld\n",qq.ans);
	}
	return 0;
}
