#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int tbl[100100];

int main() {
	int n,k;
	scanf("%d%d",&n,&k);
	vector<int> dif;
	
	int a;
	int b;

	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
		if (i) {
			dif.push_back(tbl[i]-tbl[i-1]-1);
		}
		if (!i) a=tbl[i];
		b=tbl[i];
	}
	sort(dif.begin(),dif.end());
	//for (int i=0;i<n-1;i++) {
		//printf("%d\n",dif[i]);
	//}
	int ans=b-a;
	//printf("%d %d\n",a,b);
	for (int i=0;i<k-1;i++) {
		//printf("i %d\n",i);
		//printf("%d\n",dif[n-i-2]);
		ans-=dif[n-i-2];	
	}		
	printf("%d\n",ans+1);
	return 0;
}
