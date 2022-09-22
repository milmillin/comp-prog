#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

int a,b;

int mem[200000];
vector<int> ans;

bool can(int x) {
	if (x<0) return false;
	if (x==0) return true;
	if (mem[x]!=-1) return mem[x];
	return mem[x]=(can(x-a)||can(x-b));
}

int main () {
	int q,x;
	memset(mem,-1,sizeof(mem));
	scanf("%d%d%d",&a,&b,&q);
//	for (int i=1;i<10000;i++) {
//		if (can(i)) ans.push_back(i);
//	}
//	int cur=9999;
//	do {
//		cur++;
//		if (can(cur)) ans.push_back(cur);
//	} while (!can(cur));
	int cur;
	for (int i=0;i<q;i++) {
		scanf("%d",&x);
		for (cur=x;can(cur)==false;cur++) {}
		printf("%d\n",cur);
		//printf("%d\n",*lower_bound(ans.begin(),ans.end(),x));
	}
	return 0;
}
