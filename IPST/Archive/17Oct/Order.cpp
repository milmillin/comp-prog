#include <cstdio>
#include <vector>

using namespace std;

int pre[2000];
int post[2000];
vector<int> pth[2000];
int par[2000];

void recur(int idx) {
	if (pth[idx].size()) recur(pth[idx][0]);
	printf("%d\n",idx);
	if (pth[idx].size()>=2) recur(pth[idx][1]);
}

int main () {
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		scanf("%d",&pre[i]);
	}
	for (int i=0;i<n;i++) {
		scanf("%d",&post[i]);
	}
	int root=pre[0];
	par[root]=root;
	int cur=root;
	int x;
	int curPost=0;
	for (int i=1;i<n;i++) {
		pth[cur].push_back(pre[i]);
		par[pre[i]]=cur;
		cur=pre[i];
		if (post[curPost]==cur) {
			cur=par[cur];
			curPost++;
		}
	}
	recur(root);
	return 0;
}
