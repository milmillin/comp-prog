#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
 
using namespace std;
 
//long long tbl[100100];
 
struct loc {
	long long val;
	int ls,idx;
};
 
bool operator< (const loc &a, const loc &b) {
	return a.val<b.val;
}
 
vector<long long> cube;
vector<long long> sq;
vector<loc> work;
vector<long long> ls[100100];
vector<int> cntt[100100];
 
bool find(vector<long long> &tbl,long long x) {
	return (*lower_bound(tbl.begin(),tbl.end(),x))==x;
}
 
bool find2(vector<loc> &tbl,long long x,loc &out) {
	auto tmp = lower_bound(tbl.begin(),tbl.end(),loc{x,0,0});
	if (tmp->val==x) {
		out=*tmp;
		return true;
	}
	return false;
}
 
int mic[1010][2];
 
int solve(int ls,int x,int sel) {
	if (x==0) return (sel)?cntt[ls][0]:0;
	if (mic[x][sel]!=-1) return mic[x][sel];
	if (sel) {
		return mic[x][sel]=cntt[ls][x]+solve(ls,x-1,0);
	} else {
		return mic[x][sel]=max(solve(ls,x-1,0),solve(ls,x-1,1));
	}
}
 
int main () {
	int n;
	scanf("%d",&n);
	for (long long i=1;i*i*i<=1e10;i++) {
		cube.push_back(i*i*i);
	}
	for (long long i=1;i*i<=1e10;i++) {
		sq.push_back(i*i);
	}
	for (long long i=2;i<1e5;i++) {
		if (find(cube,i)) continue;
		if (find(sq,i)) continue;
		//printf("%lld\n",i);
		for (long long j=i;j<=1e10;j*=j) {
			if (j<=0) break;
			//printf("%lld\n",j);
			//scanf("%d",&n);
			work.push_back(loc{j,(int)i,(int)ls[i].size()});
			ls[i].push_back(j);
			cntt[i].push_back(0);
		}
	}
	sort(work.begin(),work.end());
	long long x;
	int ans=0;
	bool cb=false;
	for (int i=0;i<n;i++) {
		scanf("%lld",&x);
		loc now;
		if (find(cube,x)) {
			cb=true;
		} else if (find2(work,x,now)) {
			cntt[now.ls][now.idx]++;
		} else if (x>1e5) {
			ans++;
		}
	}
	for (int i=2;i<=1e5;i++) {
		memset(mic,-1,sizeof(mic));
		if (cntt[i].size()==0) continue;
		int tmp = max(solve(i,cntt[i].size()-1,0),solve(i,cntt[i].size()-1,1));
		ans+=tmp;
		if (tmp) {
			for (int j=0;j<(int)cntt[i].size();j++) {
				printf("%lld, %d, %d, %d\n",ls[i][j],cntt[i][j],mic[j][0],mic[j][1]);
			}
			printf("%d %d\n",i,tmp);		
		}
	}
	printf("%d\n",ans+cb);
	return 0;
}
