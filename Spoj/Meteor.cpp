#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

struct rain{
	int l,r;
	long long a;
};

vector<int> chd[300100];
long long req[300100];
rain rr[300100];
long long bit[300100];
vector<int> chk[300100][2];
int lo[300100];
int hi[300100];

void update(int idx,long long val) {
	while (idx<300100) {
		bit[idx]+=val;
		idx+=(idx&-idx);
	}
}

long long get(int idx) {
	long long sum=0;
	while (idx) {
		sum+=bit[idx];
		idx-=(idx&-idx);
	}
	return sum;
}

void push(int l,int r,long long val) {
	if (l<=r) {
		update(l,val);
		update(r+1,-val);
	} else {
		update(1,val);
		update(r+1,-val);
		update(l,val);
	}
}

int main () {
	int n,m,x;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++) {
		scanf("%d",&x);
		chd[x].push_back(i);
	}
	for (int i=1;i<=n;i++) {
		scanf("%lld",&req[i]);
	}
	int k;
	scanf("%d",&k);
	for (int i=0;i<k;i++) {
		scanf("%d%d%lld",&rr[i].l,&rr[i].r,&rr[i].a);
	}
	for (int i=1;i<=n;i++) hi[i]=k;
	bool chg=true;
	for (int i=1;i<=n;i++) {
		chk[k/2][0].push_back(i);
	}

	long long sum;
	int now=0;
	while (chg) {
		//printf("yay\n");
		chg=false;
		memset(bit,0,sizeof(bit));
		for (int i=0;i<k;i++) {
			push(rr[i].l,rr[i].r,rr[i].a);
			while (chk[i][now].size()) {
				chg=true;
				sum=0;
				int idx=chk[i][now].back();
				chk[i][now].pop_back();
				//printf("checking %d at %d\n",idx,i);
				for (int j=0;j<chd[idx].size();j++) {
					sum+=get(chd[idx][j]);
					if (sum>=req[idx]) break;
				}
				//printf("sum %lld expect %lld\n",sum,req[idx]);
				if (sum>=req[idx]) {
					hi[idx]=i;
				} else {
					lo[idx]=i+1;
				}
				if (lo[idx]<hi[idx]) {
					//tmp.push_back(param{toChk[cur].id,(lo[toChk[cur].id]+hi[toChk[cur].id])>>1});
					chk[(lo[idx]+hi[idx])>>1][(now+1)%2].push_back(idx);
				}
			}
		}
		//sort(tmp.begin(),tmp.end(),cmp);
		now=(now+1)%2;
	}
	for (int i=1;i<=n;i++) {
		if (hi[i]==k) printf("NIE\n");
		else printf("%d\n",hi[i]+1);
	}
	return 0;
}
