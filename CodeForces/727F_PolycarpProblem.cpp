#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

long long qs[1000];
long long qsMin[1000];

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	vector<int> tbl(n+1);
	for (int i=1;i<=n;i++) {
		scanf("%d",&tbl[i]);
		//tbl[i]+=tbl[i-1];
	}
	vector<long long> ans;
	long long minn;
	int idx;
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=n;j++) {
			qs[j]=tbl[j]+qs[j-1];

			//printf("%d ",qs[j]);	
		}
		//printf("\n");
		minn=2e9;
		for (int j=n;j>=1;j--) {
			minn=min(minn,qs[j]);
			qsMin[j]=minn;
		}
		if (minn>=0) break;
		int tblMin=2e9;
		for (int j=1;j<=n;j++) {
			if (tbl[j]>=0) continue;
			if (qsMin[j]!=minn) break;
			if (tbl[j]<tblMin) {
				tblMin=tbl[j];
				idx=j;
			}
		}
		ans.push_back(minn);
		tbl[idx]=0;
		/*
		bool isset=false;
		for (int j=1;j<=n;j++) {
			if (tbl[j]>=0) continue;
			if (qsMin[j]>=0) continue;
			if (qsMin[j]-tbl[j]>=0) {
				printf("%d %d %d\n",qsMin[j],j,tbl[j]);
				tbl[j]=0;
				ans.push_back(qsMin[j]);
				isset=true;
				break;
			}
		}
		if (!isset) {
			for (int j=1;j<=n;j++) {
				if (tbl[j]>=0) continue;
				printf("**%d %d %d\n",qsMin[j],j,tbl[j]);
				tbl[j]=0;
				ans.push_back(qsMin[j]);
				break;
			}
		}
		*/
	}
	sort(ans.begin(),ans.end());
	/*
	for (int i=0;i<ans.size();i++) {
		printf("%d ",ans[i]);
	}
	printf("\n");
	*/
	long long x;
	for (int i=0;i<m;i++) {
		scanf("%I64d",&x);
		printf("%d\n",lower_bound(ans.begin(),ans.end(),-x)-ans.begin());
	}
	return 0;
}
