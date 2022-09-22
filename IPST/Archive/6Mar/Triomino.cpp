#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int f[810][4];

int meg(vector<int> &a) {
	sort(a.begin(),a.end());

	int cur=0;
	for (int i=0;i<(int)a.size();i++) {
		if (a[i]>cur) return cur;
		if (a[i]==cur) cur++;
	}
	return cur;
}

int main() {
	f[0][0]=0;
	f[1][0]=0;
	f[2][0]=1;
	f[1][1]=0;
	f[2][1]=1;
	f[2][2]=0;
	f[2][3]=0;
	vector<int> mrk0;
	vector<int> mrk1;
	vector<int> mrk2;
	vector<int> mrk3;
	for (int i=3;i<810;i++) {
		mrk0.clear();
		mrk1.clear();
		mrk2.clear();
		mrk3.clear();
		for (int j=0;j<=i-2;j++) {
			mrk0.push_back(f[j][0]^f[i-j-1][1]);
			mrk0.push_back(f[j+1][1]^f[i-j-2][0]);
			mrk1.push_back(f[j+1][3]^f[i-j-2][0]);
			if (j) mrk1.push_back(f[j][1]^f[i-j-1][1]);
			if (j) mrk1.push_back(f[j+1][2]^f[i-j-2][0]);
			if (j&&j<i-2) mrk2.push_back(f[j+1][2]^f[i-j-2][1]);
			if (j&&j<i-2) mrk2.push_back(f[j][1]^f[i-j-1][2]);
			if (j<i-2) mrk2.push_back(f[j+1][3]^f[i-j-2][1]);
			if (j) mrk2.push_back(f[j][1]^f[i-j-1][3]);
			if (j<i-2) mrk3.push_back(f[j+1][3]^f[i-j-2][1]);
			if (j) mrk3.push_back(f[j][1]^f[i-j-1][3]);
			if (j&&j<i-2) mrk3.push_back(f[j+1][2]^f[i-j-2][1]);
			if (j&&j<i-2) mrk3.push_back(f[j][1]^f[i-j-1][2]);
		}
		f[i][0]=meg(mrk0);
		f[i][1]=meg(mrk1);
		f[i][2]=meg(mrk2);
		f[i][3]=meg(mrk3);
	}
	/*
	for (int i=2;i<10;i++) {
		printf("%d %d %d %d\n",f[i][0],f[i+1][1],f[i+2][2],f[i+2][3]);
	}
	*/
	int	q;
	scanf("%d",&q);
	int n;
	for (int i=0;i<q;i++) {
		scanf("%d",&n);
		printf("%c\n",(f[n][0])?'X':'Y');
	}
	return 0;
}
