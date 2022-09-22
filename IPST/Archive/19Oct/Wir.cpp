#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int tbl[100100];
vector<int> mark;

int main () {
	int n,k;
	scanf("%d%d",&n,&k);
	vector<int> dif;
	vector<int> hgt;
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
		while (!hgt.empty()&&hgt.back()>=tbl[i]) {
			hgt.pop_back();
			dif.pop_back();
		}
		
		if (!dif.empty()) {
			//printf("yay\n");
			dif.push_back(max(tbl[i]-hgt.back(),dif.back()));
		} else dif.push_back(0);
		hgt.push_back(tbl[i]);
		/*
		for (int i=0;i<hgt.size();i++) {
			printf("%d %d\n",hgt[i],dif[i]);
		}
		*/
		if (dif.back()) {
			mark.push_back(-dif.back()+1);
		}
	}
	sort(mark.begin(),mark.end());
	/*
	for (int i=0;i<mark.size();i++) {
		printf("%d ",mark[i]);
	}
	printf("\n");
	*/
	int x;
	for (int i=0;i<k;i++) {
		scanf("%d",&x);
		printf("%d\n",upper_bound(mark.begin(),mark.end(),-x)-mark.begin());
	}
	return 0;
}
