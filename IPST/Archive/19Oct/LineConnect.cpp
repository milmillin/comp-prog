#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;



int tbl[100100];
int part[100100];
vector<int> pth[100100];
int now;

bool visit[100100];

void recur(int idx) {
	visit[idx]=true;
	part[idx]=now;
	for (int i=0;i<pth[idx].size();i++) {
		if (visit[pth[idx][i]]) continue;
		recur(pth[idx][i]);
	}
}

vector<int> p1,p2;

int main () {
	int n;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		scanf("%d",&tbl[i]);
	}
	int a,b;
	for (int i=0;i<n-2;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		pth[b].push_back(a);
	}
	int max1,min1,max2,min2;
	max1=min1=max2=min2=-1;
	for (int i=1;i<=n;i++) {
		if (visit[i]) continue;
		now++;
		recur(i);
	}
	for (int i=1;i<=n;i++) {
		if (part[i]==1) {
			p1.push_back(tbl[i]);
		} else {
			p2.push_back(tbl[i]);
		}
	}
	//sort(p1.begin(),p1.end());
	sort(p2.begin(),p2.end());

	int minn=2e9;
	for (int i=0;i<p1.size();i++) {
		//minn=min(minn,min(abs((*upper_bound(p2.begin(),p2.end(),p1[i]))-p1[i]),abs((*upper_bound(p2.begin(),p2.end(),p1[i])-1)-p1[i])));
		vector<int>::iterator cur = upper_bound(p2.begin(),p2.end(),p1[i]);
		if (cur!=p2.end()) minn=min(minn,abs(*cur-p1[i]));
		if (cur!=p2.begin()) minn=min(minn,abs(*(cur-1)-p1[i]));
		//printf("%d %d\n",p1[i],minn);
	}
	printf("%d\n",minn);
	//printf("%d %d %d %d\n",max1,min1,max2,min2);
	return 0;
}
