#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

vector<pair<int,int>> tbl;

long long cube(int x) {
	return (long long)x*x*x;
}

long long mic1[300][300];
long long mic2[300][300];

long long dp2(int i,int j);

long long dp1(int i,int j) {
	if (i==j) return cube(tbl[i].second);	
	if (mic1[i][j]!=-1) return mic1[i][j];
	long long ans=max(cube(tbl[i].second)+dp1(i+1,j),cube(tbl[j].second)+dp1(i,j-1));
	for (int k=i+1;k<j;k++) {
		ans=max(ans,cube(tbl[k].second)+dp2(k-1,k+1));
	}	
	return mic1[i][j]=ans;
}

int n;
long long dp2(int i,int j) {
	if (mic2[i][j]!=-1) return mic2[i][j];
	long long ans=dp1(1,i)+dp1(j,n-1);
	if (tbl[i].first==tbl[j].second) {
		ans=max(ans,)
	}
}


int main () {
	scanf("%d",&n);
	int last=0;
	int x;
	for (int i=0;i<n;i++) {
		scanf("%d",&x);
		if (x!=last) {
			tbl.push_back({x,1});
		} else {
			tbl.back().second++;
		}
	}
	n=tbl.size();
	return 0;
}
