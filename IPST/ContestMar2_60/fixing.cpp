#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main () {
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	int last,x;
	int sum=0;
	vector<int> a;	
	for (int i=0;i<m;i++) {
		scanf("%d",&x);
		if (i) {
			sum+=x-last-1;
			a.push_back(x-last-1);
		}
		last=x;
	}	
	sort(a.begin(),a.end());
	for (int i=0;i<k-1;i++) {
		if (i==a.size()) break;
		sum-=a[a.size()-1-i];
		//printf("%d\n",a[a.size()-1-i]);
	}
	printf("%d\n",sum);
	return 0;
}
