#include <cstdio>
#include <vector>

using namespace std;

bool check(vector<vector<bool>> &tbl) {
	for (auto &aa:tbl) {
		for (auto i:aa) {
			if (!i) return false;		
		}
	}
	return true;
}

bool fill(int x,int y) {
	vector<vector<bool>> tbl(3,vector<bool>(3,false));
	int a,b;
	while (!check(tbl)) {
		printf("%d %d\n",x,y);
		fflush(stdout);
		scanf("%d%d",&a,&b);
		if (a==0&&b==0) return true;		
		tbl[a-x+1][b-y+1]=true;
	}									
	return false;
}

int main () {
	int q;
	scanf("%d",&q);
	while (q--) {
		int a;
		scanf("%d",&a);
		if (a==20) {
			for (int i=0;i<3;i++) {
				fill(2,2+i*3);
			}
		} else {
			for (int i=0;i<23;i++) {
				fill(2,2+i*3);
			}
		}
	}		
	return 0;
}
