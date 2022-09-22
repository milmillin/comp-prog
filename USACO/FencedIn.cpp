#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct line {
	int val,type;
};

bool cmp (const line &a, const line &b) {
	return a.val<b.val;
}

int cnt[2];

int main () {
	freopen("fencedin.in","r",stdin);
	freopen("fencedin.out","w",stdout);
	int a,b,n,m;
	scanf("%d%d%d%d",&a,&b,&n,&m);
	vector<line>tbl;
	vector<int>ver(n+1);
	vector<int>hor(m+1);
	for (int i=0;i<n;i++) {
		scanf("%d",&ver[i]);
	}
	ver[n]=a;
	sort(ver.begin(),ver.end());
	for (int i=0;i<m;i++) {
		scanf("%d",&hor[i]);
	}
	hor[m]=b;
	sort(hor.begin(),hor.end());
	int last=0;
	for (int i=0;i<=n;i++) {
		tbl.push_back(line{ver[i]-last,0});
		last=ver[i];
	}
	last=0;
	for (int i=0;i<=m;i++) {
		tbl.push_back(line{hor[i]-last,1});
		last=hor[i];
	}
	sort(tbl.begin(),tbl.end(),cmp);
	long long ans=0;
	bool isVer,isHor;
	isVer=isHor=false;
	int brk;
	for (int i=0;i<(int)tbl.size();i++) {
		//printf("%d %d %d\n",tbl[i].val,tbl[i].type,cnt[0]);
		//if (!i) scanf("%d",&brk);
		//if (tbl[i].type) scanf("%d",&brk);
		//scanf("%d",&brk);
		if (tbl[i].type) {
			//hor
			if (!isHor) {
				ans+=(long long)tbl[i].val*n;
			} else {
				long long tmp=(long long)tbl[i].val*(n-cnt[0]+((cnt[0])?1:0));
				//printf("%I64d\n",tmp);
				
				ans+=tmp;
			}
			isHor=true;
			cnt[1]++;
		} else {
			//ver
			if (!isVer) {
				ans+=(long long)tbl[i].val*m;
			} else {
				long long tmp=(long long)tbl[i].val*(m-cnt[1]+((cnt[1])?1:0));
				//printf("%I64d\n",tmp);
				ans+=tmp;
			}
			isVer=true;
			cnt[0]++;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
