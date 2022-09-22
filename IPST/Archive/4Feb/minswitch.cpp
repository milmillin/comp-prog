#include <cstdio>

using namespace std;

int deg[10100];
bool used[10100];

vector<int> pth[10100];

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	int a,b;
	for (int i=0;i<m;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		pth[b].push_back(a);
		deg[a]++;
		deg[b]++;
	}
	
	vector<int> ans;
	while (true) {
		for (int i=1;i<=n;i++) {
			if (used[i]) continue;
			if (deg[i]==1) {
				used[i]=true;
				
			}
		}		
	}

	return 0;
}
