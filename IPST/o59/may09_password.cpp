#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

string x;

bool cmp (int a,int b) {
	return x.compare(a,string::npos,x,b,string::npos)<0;
}

int mic[5010][5010];
vector<int> work[5010];

bool dp(int i,int j) {
	if (i>j) return true;
	if (mic[i][j]!=-1) return mic[i][j];
	if (x[i]==x[j]) return mic[i][j]=dp(i+2,j-2);
	return mic[i][j]=false;
}

bool cmp2(int a,int b) {
	return a>b;
}

int main () {
	cin >> x;
	int k;
	scanf("%d",&k);
	int n=x.length();

	memset(mic,-1,sizeof(mic));

	for (int i=0;i<n;i++) {
		for (int j=i;j<n;j++) {
			if (dp(i,j)) {
				work[i].push_back(j);
			}
		}
	}

	vector<int> suf(n);
	for (int i=0;i<n;i++) suf[i]=i;
	sort(suf.begin(),suf.end(),cmp);	
	
	//for (auto i:suf) {
		//printf("%s\n",x.c_str()+i);
	//}

	vector<int> lcp(n);
	vector<vector<int>> ll(n,vector<int>(n));
	lcp[0]=1e9;
	for (int i=1;i<n;i++) {
		int cur=0;
		while (x[suf[i-1]+cur]==x[suf[i]+cur]) cur++;
		lcp[i]=cur;
		//printf("%d\n",lcp[i]);
	}

	for (int i=0;i<n;i++) {
		ll[i][i]=n-suf[i];
		//ll[i].push_back(n);
		//printf("%d ",n);
		for (int j=i+1;j<n;j++) {
			ll[i][j]=min(ll[i][j-1],lcp[j]);	
			//ll[i].push_back(min(ll[i].back(),lcp[j]));
			//printf("%d ",ll[i].back());
		}
		//printf("\n");
	}
	
	vector<int> st(n,-1);
	for (int i=0;i<n;i++) {
		for (auto j:work[suf[i]]) {
			//int num=upper_bound(ll[i].begin(),ll[i].end(),j-suf[i]+1,cmp2)-ll[i].begin();
			if (j<=st[i]) continue;
			int num=0;
			while (i+num<n&&ll[i][i+num]>=j-suf[i]+1) {
				st[i+num]=suf[i+num]+j-suf[i];
				//printf("-- %d %d\n",i+num,st[i+num]);
				num++;
			}	
			//printf("%d %d %d\n",i,j,num);
			if (num>=k) {
				cout << x.substr(suf[i],j-suf[i]+1) << '\n';
				return 0;
			}
			k-=num;
		}
	}
	assert(false);
	return 0;
}
