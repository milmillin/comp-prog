#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

int mod=1000003;

struct mat {
	vector<vector<int>> tbl;
	int size;
	mat(int _size): tbl(_size,vector<int>(_size,0)),size(_size) {
	}
	const vector<int>& operator[](int idx) const {
		return tbl[idx];
	}
	vector<int>& operator[](int idx) {
		return tbl[idx];
	}

};


mat operator* (const mat &a, const mat &b) {
	mat tmp(a.size);
	for (int i=0;i<tmp.size;i++) {
		for (int j=0;j<tmp.size;j++) {
			for (int k=0;k<tmp.size;k++) {
				tmp[i][j]+=((long long)a[i][k]*b[k][j])%mod;
				tmp[i][j]%=mod;
			}
		}	
	}
	return tmp;
}

mat poww(const mat &a,int exp) {
	if (exp==1) return a;
	mat tmp=poww(a,exp/2);
	tmp=tmp*tmp;
	if (exp%2) return tmp*a;
	return tmp;
}

int mic[200][200];
int tbl[200][200];

int main () {
	int r,c,k;
	scanf("%d%d%d",&r,&c,&k);
	for (int i=1;i<=r;i++) {
		for (int j=1;j<=c;j++) {
			scanf("%d",&tbl[i][j]);
		}
	}

	mat base(r);

	for (int k=1;k<=r;k++) {
		memset(mic,0,sizeof(mic));
		if (tbl[k][1])mic[k][1]=1;
		for (int j=1;j<c;j++) {
			for (int i=1;i<=r;i++) {
				if (tbl[i-1][j+1]) mic[i-1][j+1]+=mic[i][j];
				if (tbl[i][j+1]) mic[i][j+1]+=mic[i][j];
				if (tbl[i+1][j+1]) mic[i+1][j+1]+=mic[i][j];

				mic[i-1][j+1]%=mod;
				mic[i][j+1]%=mod;
				mic[i+1][j+1]%=mod;
			}
		}
		for (int i=1;i<=r;i++) {
			base[i-1][k-1]=mic[i][c];
		}
	}

	mat res=poww(base,k);
	for (int i=0;i<r;i++) {
		int ans=0;
		for (int j=0;j<r;j++) {
			ans+=res[j][i];
			ans%=mod;
		}
		printf("%d\n",ans);
	}	
	return 0;
}
