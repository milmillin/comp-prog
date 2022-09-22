#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

bool fck[510][510][510];
bool used[510];
//int mat[510][510];
int mx,mn;
int n,m;

bool check(int st,int t) {
	for (int i=0;i<n;i++) {
		if (fck[(st-i+mx)%mx][i][t]) return false;			
	}	
	return true;
}

vector<pair<int,int>> fill(int st,int t) {
	//int cnt=0;
	vector<pair<int,int>> tmp;
	for (int i=0;i<n;i++) {
		if ((st-i+mx)%mx>=m) continue;
		tmp.push_back({(st-i+mx)%mx+1,i});
		//mat[t][i]=(st+i)%mx+1;
	}	
	return tmp;
}

int main () {
	int k;
	scanf("%d%d%d",&m,&n,&k);
	int a,b,c;
	for (int i=0;i<k;i++) {
		scanf("%d%d%d",&a,&b,&c);
		a--;
		b--;
		c--;
		fck[a][b][c]=true;
	}
	mn=min(m,n);
	mx=max(m,n);
	printf("%d\n",mx);
	for (int i=0;i<mx;i++) {
		for (int j=0;j<mx;j++) {
			if (used[j]) continue;
			if (!check(j,i)) continue;			
			auto cnt = fill(j,i);
			printf("%d ",cnt.size());
			for (auto &ii:cnt) {
				printf("%d %d ",ii.first,ii.second+1);
			}
			printf("\n");
			used[j]=true;
			break;
		}
	}
	return 0;
}
