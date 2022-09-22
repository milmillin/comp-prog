#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> pos;
vector<int> neg;

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
	int lo,hi;
	int mid;
	int left,rgt;
	int zero;
	long long ans=0;
	for (auto i:pos) {
		printf("-- %d\n",i);
		if (i<0) {
			zero=lower_bound(neg.begin(),neg.end(),-i)-neg.begin();
			lo=lower_bound(neg.begin(),neg.end(),i)-neg.begin();
			hi=zero;
			printf("%d %d\n",hi,lo);
			while (lo<hi) {
				mid=(lo+hi)>>1;
				b=neg[mid];
				double now=(double)(i+b)/2+w*(double)(b-i)/2;
				printf("%d %f\n",b,now);
				if (now>=(double)-l) {
					hi=mid;
				} else {
					lo=mid+1;
				}
			}
			ans+=zero-hi;
		}
		lo=lower_bound(neg.begin(),neg.end(),i)-neg.begin();
		zero=lo;
		hi=neg.size();
		while (lo<hi) {
			mid=(lo+hi+1)>>1;
			b=neg[mid];
			double now = ((double)(i+b)/2)-((double)(b-i)/2*w);
			printf("%d %d %f\n",mid,b,now);
			if (now<=0) {
				lo=mid;
			} else {
				hi=mid-1;
			}
		}	
		ans+=lo-zero;
		printf("%d %d\n",i,lo-zero);
	}
	printf("%lld\n",ans);
	return 0;
}
