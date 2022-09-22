#include <cstdio>
#include <vector>

using namespace std;

int pre[200];
int inn[200];
long long mic[200];

int cmpCnt;
const int mod=1000000007;

struct node {
	int idx;
	long long way;
	long long cnt;
};

vector<node> stk;

int main () {
	mic[0]=1;
	mic[1]=1;
	for (int i=2;i<=100;i++) {
		for (int j=0;j<i;j++) {
			mic[i]+=mic[j]*mic[i-j-1];
			mic[i]%=mod;
		}
	}
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		scanf("%d",&pre[i]);
	}
	for (int i=0;i<n;i++) {
		scanf("%d",&inn[i]);
	}
	int cur=0;
	bool newCmp;
	long long ans=1;
	int cntt=0;
	for (int i=0;i<n;i++) {
		//printf("%d\n",i);
		stk.push_back(node{pre[i],1,0});
		//newCmp=false;

		while (!stk.empty()&&stk.back().idx==inn[cur]) {
			//printf("--%d\n",stk.back().idx);
			int cnt=stk.back().cnt;
			long long way=mic[cnt];
			stk.pop_back();
			if (stk.empty()) {
				cntt++;
				ans*=way;
				ans%=mod;
			} else {
				stk.back().cnt++;
				stk.back().way*=way;
				stk.back().way%=mod;
			}
			cur++;
			//newCmp=true;
		}
		/*
		for (int i=0;i<stk.size();i++) {
			printf("%d ",stk[i]);
		}
		
		printf("\n");
		if (newCmp) {
			printf("yay ")
			cmpCnt++;
		*/
	}
	//printf("%d\n",cmpCnt);
	
	printf("%d\n",(mic[cntt]*ans)%mod);
	return 0;
}
