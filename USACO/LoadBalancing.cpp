#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

struct pnt{
	int x,y;
};

bool cmp(const pnt &a, const pnt &b) {
	return a.x<b.x;
}

pnt tbl[100100];
map<int,int> mp;

int bit1[100100];
int bit2[100100];

int cnt1,cnt2;

void update(int *bit,int idx, int val) {
	while (idx<100100) {
		bit[idx]+=val;
		idx+=(idx&-idx);
	}
}

int get(int *bit, int idx) {
	int sum=0;
	while (idx) {
		sum+=bit[idx];
		idx-=(idx&-idx);
	}
	return sum;
}

pair<int,bool> solve(int idx) {
	int tmp1=get(bit1,idx);
	int tmp2=get(bit2,idx);
	int ans=max(max(tmp1,cnt1-tmp1),max(tmp2,cnt2-tmp2));
	return make_pair(ans,(tmp1==ans)||(tmp2==ans));
}

int main () {
	freopen("balancing.in","r",stdin);
	freopen("balancing.out","w",stdout);
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		scanf("%d%d",&tbl[i].x,&tbl[i].y);
		mp[tbl[i].y];
	}
	int cur=1;
	for (map<int,int>::iterator it=mp.begin();it!=mp.end();it++) {
		it->second=cur;
		cur++;
	}
	sort(tbl,tbl+n,cmp);
	int last=-1;
	for (int i=0;i<n;i++) {
	//	printf("%d %d\n",tbl[i].x,tbl[i].y);
		update(bit2,mp[tbl[i].y],1);
		cnt2++;
	}
	int ans=2e9;
	for (int i=1;i<cur;i++) {
		ans=min(ans,max(get(bit2,i),n-get(bit2,i)));
	}
	int f,l,m;
	pair<int,bool> tmp;
	for (int i=0;i<n;) {
		last=tbl[i].x;
		for (;i<n&&tbl[i].x==last;i++) {
			update(bit2,mp[tbl[i].y],-1);
			update(bit1,mp[tbl[i].y],1);
			cnt2--;
			cnt1++;
		}
		//printf("%d\n",last);
		f=1;
		l=cur-1;
		while (f<l) {
			m=(f+l)>>1;
			tmp=solve(m);
			ans=min(ans,tmp.first);
			if (tmp.second) {
				l=m;
			} else {
				f=m+1;
			}
			//printf("%d %d\n",m,tmp.first);
		}
		//printf("--%d %d %d\n",cnt1,cnt2,ans);
	}
	printf("%d\n",ans);
	return 0;
}
