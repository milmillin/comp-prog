#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

struct aa {
	int to;
	int idx;
};

struct ee {
	int from;
	int to;
};

bool visit[300];
int par[300];

vector<aa> pth[300];
vector<ee> edge;


int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	int a,b;
	for (int i=0;i<n;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(aa{b,i});
		pth[b].push_back(aa{a,i});
		edge.push_back(ee{a,b});
	}

	return 0;
}
