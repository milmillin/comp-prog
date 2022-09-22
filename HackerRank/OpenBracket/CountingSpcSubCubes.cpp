#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

void f() {
	int n;
	scanf("%d",&n);
	vector<vector<vector<int> > > tbl(n+1,vector<vector<int> >(n+1,vector<int>(n+1)));
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=n;j++) {
			for (int k=1;k<=n;k++) {
				scanf("%d",&tbl[i][j][k]);
			}
		}
	}
	for (int sz=1;sz<=n;sz++) {
		//printf("%d\n",sz);
		vector<vector<vector<int> > > maxZ(n+1,vector<vector<int> >(n+1,vector<int>(n+1)));
		for (int i=1;i<=n;i++) {
			for (int j=1;j<=n;j++) {
				deque<int> q;
				for (int k=1;k<sz;k++) {
					while (!q.empty()&&tbl[i][j][q.back()]<=tbl[i][j][k]){
						q.pop_back();
					}
					q.push_back(k);
				}
				for (int k=sz;k<=n;k++) {
					while (!q.empty()&&tbl[i][j][q.back()]<=tbl[i][j][k]){
						q.pop_back();
					}
					q.push_back(k);

					while (!q.empty()&&q.front()<=k-sz) q.pop_front();
					maxZ[i][j][k]=tbl[i][j][q.front()];
					//printf("%d ",maxZ[i][j][k]);
				}
				//printf("\n");
			}
			//printf("\n");
		}
		vector<vector<vector<int> > > maxYZ(n+1,vector<vector<int> >(n+1,vector<int>(n+1)));
		for (int i=1;i<=n;i++) {
			for (int k=sz;k<=n;k++) {
				deque<int> q;
				for (int j=1;j<sz;j++) {
					while (!q.empty()&&maxZ[i][q.back()][k]<=maxZ[i][j][k]){
						q.pop_back();
					}
					q.push_back(j);					
				}
				for (int j=sz;j<=n;j++) {
					while (!q.empty()&&maxZ[i][q.back()][k]<=maxZ[i][j][k]){
						q.pop_back();
					}
					q.push_back(j);
					while (!q.empty()&&q.front()<=j-sz) q.pop_front();
					maxYZ[i][j][k]=maxZ[i][q.front()][k];
				}
			}
		}
		int ans=0;
		for (int j=sz;j<=n;j++) {
			for (int k=sz;k<=n;k++) {
				deque<int> q;
				for (int i=0;i<sz;i++) {
					while (!q.empty()&&maxYZ[q.back()][j][k]<=maxYZ[i][j][k]) q.pop_back();
					q.push_back(i);
				}
				for (int i=sz;i<=n;i++) {
					while (!q.empty()&&maxYZ[q.back()][j][k]<=maxYZ[i][j][k]) q.pop_back();
					q.push_back(i);
					while (!q.empty()&&q.front()<=i-sz) q.pop_front();
					if (maxYZ[q.front()][j][k]==sz) ans++;
				}
			}
		}
		printf("%d ",ans);
	}
	printf("\n");
}

int main () {
	int q;
	scanf("%d",&q);
	while (q--) f();
	return 0;
}
