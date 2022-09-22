#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

void f() {
	int n;
	scanf("%d",&n);
	vector<vector<char>> tbl(n,vector<char>(n));		
	vector<int> total(n,0);
	vector<int> win(n,0);
	for (int i=0;i<n;i++) {
		for (int j=0;j<n;j++) {
			scanf(" %c",&tbl[i][j]);
			if (tbl[i][j]!='.') {
				total[i]++;
				if (tbl[i][j]=='1') win[i]++;
			}
		}
	}
	vector<double> wp(n,0);
	for (int i=0;i<n;i++) {
		wp[i]=(double)win[i]/total[i];
	}

	vector<double> owp(n,0);
	for (int i=0;i<n;i++) {
		double sumwp=0;
		int nop=0;
		for (int j=0;j<n;j++) {
			if (tbl[i][j]=='.') continue;
			if (tbl[i][j]=='1') {
				sumwp+=(double)(win[j])/(total[j]-1);
			} else {
				sumwp+=(double)(win[j]-1)/(total[j]-1);
			}
			nop++;
		}
		owp[i]=sumwp/nop;
	}

	vector<double> oowp(n,0);
	for (int i=0;i<n;i++) {
		double sumowp=0;
		int nop=0;
		for (int j=0;j<n;j++) {
			if (tbl[i][j]=='.') continue;
			sumowp+=owp[j];
			nop++;
		}
		oowp[i]=sumowp/nop;
	}

	for (int i=0;i<n;i++) {
		printf("%f\n",0.25*wp[i]+0.5*owp[i]+0.25*oowp[i]);
		//printf("%f %f %f\n",wp[i],owp[i],oowp[i]);
	}
}

int main () {
	int q;
	scanf("%d",&q);
	for (int i=1;i<=q;i++) {
		printf("Case #%d:\n",i);
		f();
	}
	return 0;
}
