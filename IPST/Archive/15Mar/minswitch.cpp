#include <cstdio>
#include <vector>

using namespace std;

vector<int> pth[10100];
int deg[10100];
vector<int> stk;
vector<int> anss;
int ans=2e9;
bool sel[10100];
int bulb[100100][2];
int n,m;

bool chk() {
	for (int i=0;i<m;i++) {
		if (!sel[bulb[i][0]]&&!sel[bulb[i][1]]) return false;
	}
	return true;
}

void printAns() {
	//printf("%d\n",stk.size());
	//for (int i=0;i<(int)stk.size();i++) {
		//printf("%d\n",stk[i]);
	//}
	anss=stk;
}

bool solve(int idx) {
	if (stk.size()>20) return false;
	if (idx>n) return false;
	if (stk.size()>ans) return false;
	//printf("--%d\n",idx);
	//for (int i=0;i<(int)stk.size();i++) {
		//printf("%d ",stk[i]);
	//}
	//printf("\n");
	//idx not selected
	int tmp=0;
	if (!sel[idx]) {
		for (int i=0;i<(int)pth[idx].size();i++) {
			if (pth[idx][i]<idx) {
				if (!sel[pth[idx][i]]) {
					while (tmp--) {
						sel[stk.back()]=false;
						stk.pop_back();
					}
					return false;
				}
			} else {
				if (!sel[pth[idx][i]]) {
					stk.push_back(pth[idx][i]);
					tmp++;
				}
				sel[pth[idx][i]]=true;
			}
		}
		if (chk()) {
			if (stk.size()<ans) {
				anss=stk;
				ans=stk.size();
			}
			//return false;
		}
		solve(idx+1);
		while (tmp--) {
			sel[stk.back()]=false;
			stk.pop_back();
		}
	}
	//idx selected
	tmp=0;
	//printf("select %d\n",idx);
	if (!sel[idx]) {
		stk.push_back(idx);
		tmp++;
	}
	sel[idx]=true;
	if (chk()) {
		if (stk.size()<ans) {
			anss=stk;
			ans=stk.size();
		}
		//return false;
	}
	solve(idx+1);
	if (tmp) {
		sel[idx]=false;
		stk.pop_back();
	}
	//printf("end %d\n",idx);
	//for (int i=0;i<(int)stk.size();i++) {
		//printf("%d ",stk[i]);
	//}
	//printf("\n");
	return false;
}

int main () {
	scanf("%d%d",&n,&m);
	int a,b;
	for (int i=0;i<m;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		pth[b].push_back(a);
		bulb[i][0]=a;
		bulb[i][1]=b;
		deg[a]++;
		deg[b]++;
	}
	solve(1);
	printf("%d\n",anss.size());
	for (int i=0;i<(int)anss.size();i++) {
		printf("%d\n",anss[i]);
	}
	return 0;
}
