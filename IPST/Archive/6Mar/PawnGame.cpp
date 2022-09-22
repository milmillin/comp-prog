#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int f[10000];
vector<int> mrk;

int main () {
	f[0]=0;
	f[1]=1;
	f[2]=1;
	f[3]=2;
	for (int i=4;i<1000;i++) {
		mrk.clear();
		mrk.push_back(f[i-2]);
		for (int j=0;j<i-3;j++) {
			mrk.push_back(f[j]^f[i-j-3]);
		}
		sort(mrk.begin(),mrk.end());
		int cur=0;
		for (int i=0;i<mrk.size();i++) {
			if (mrk[i]>cur) break;
			if (mrk[i]==cur) cur++;
		}
		f[i]=cur;
		//printf("%d: %d\n",i,f[i]);
	}
	int n;
	scanf("%d",&n);
	if (n<81) {
		printf("%s\n",(f[n%34])?"White":"Black");
	} else {
		printf("%s\n",(f[(n-81)%34+81])?"White":"Black");
	}
	return 0;
}
