#include <cstdio>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

vector<int> pth[100];
vector<int> stk;
bool visit[100];
bool noSplit[100];
int n=0;
int cnt[100];


void recur(int idx) {
	stk.push_back(idx);
	visit[idx]=true;

	//for (int i=0;i<(int)stk.size();i++) {
		//printf("%d ",stk[i]);
	//}
	//printf("\n");

	if (idx==n) {
		for (int i=0;i<(int)stk.size();i++) {
			cnt[stk[i]]++;
		}
	} else {
		for (int i=0;i<(int)pth[idx].size();i++) {
			if (visit[pth[idx][i]]) {
				//printf("---%d\n",pth[idx][i]);
				int cur=stk.size()-1;
				while (stk[cur]!=pth[idx][i]) {
					noSplit[stk[cur]]=true;
					cur--;
					//printf("--%d\n",stk[cur]);
				}
				noSplit[stk[cur]]=true;
				//printf("--%d\n",stk[cur]);
				continue;
			}
			recur(pth[idx][i]);
		}
	}

	visit[idx]=false;
	stk.pop_back();
}

int main () {
	int xx;
	while (true) {
		scanf("%d",&xx);
		if (xx==-1) break;
		if (xx==-2) {
			n++;
		} else {
			pth[n].push_back(xx);
		}
	}

	recur(0);
	int cntt=0;
	for (int i=1;i<n;i++) {
		if (cnt[i]==cnt[0]) cntt++;
	}
	printf("%d ",cntt);
	for (int i=1;i<n;i++) {
		if (cnt[i]==cnt[0]) {
			printf("%d ",i);
		}
	}
	printf("\n");
	cntt=0;
	for (int i=1;i<n;i++) {
		if (!noSplit[i]&&cnt[i]==cnt[0]) cntt++;
	}
	printf("%d ",cntt);
	for (int i=1;i<n;i++) {
		if (!noSplit[i]&&cnt[i]==cnt[0]) {
			printf("%d ",i);
		}
	}
	printf("\n");
	return 0;
}
