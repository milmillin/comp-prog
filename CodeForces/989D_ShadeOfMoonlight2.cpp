#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> pos;
vector<double> neg;

int main () {
	int n,l,w;
	scanf("%d%d%d",&n,&l,&w);
	int a,b;
	for (int i=0;i<n;i++) {
		scanf("%d%d",&a,&b);
		if (b==-1) {
			neg.push_back(a);
		} else {
			pos.push_back(a);
		}
	}	
	sort(pos.begin(),pos.end());
	sort(neg.begin(),neg.end());
	long long ans=0;
	for (auto a:pos) {
		
		//intersect >-l	
		auto b=lower_bound(neg.begin(),neg.end(),(double)(-w*a-a)/(1-w));
	}
	printf("%lld\n",ans);
	return 0;
}
