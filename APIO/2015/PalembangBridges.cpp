#include <cstdio>
#include <set>
#include <algorithm>

using namespace std;

pair<int,int> ei[100100];
long long tmp[100100];

template <typename T,typename U>
long long work(T first, T last, U op) {
	op(first,0);
	multiset<int> ms;
	multiset<int>::iterator mid;
	
	ms.insert(first->first);
	ms.insert(first->second);
	mid = ms.begin();

	long long sum=first->second-first->first;
	op(++first,sum);

	while (first!=last) {
		ms.insert(first->first);
		ms.insert(first->second);
		sum+=abs(*mid-first->first);
		sum+=abs(*mid-first->second);

		if (first->second<*mid) {
			mid--;
		} else if (first->first>=*mid) {
			sum+=*mid*2;
			mid++;
			sum-=*mid*2;
		}
		op(++first,sum);
	}
	return sum;
}


int main () {
	int k,n;
	scanf("%d%d",&k,&n);
	char a,b;
	int x,y;
	long long ans=0;	
	int sz=0;
	for (int i=0;i<n;i++) {
		scanf(" %c%d %c%d",&a,&x,&b,&y);
		if (a==b) {
			ans+=abs(x-y);
		} else {
			ans+=1;
			ei[sz++]=minmax(x,y);
		}
	}
	sort(ei,ei+sz,[](const pair<int,int> &a, const pair<int,int> &b) {
			return a.first+a.second<b.first+b.second;
			});
	if (sz) {
		if (k==1) {
			ans+=work(ei,ei+sz,[](pair<int,int> *a, long long b) {});
		} else {
			work(ei,ei+sz,[](pair<int,int> *a,long long b) {
				tmp[a-ei]=b;	
					});
			using R=reverse_iterator<pair<int,int>*>;
			work(R(ei+sz),R(ei),[](R a, long long b) {
				tmp[a.base()-ei]+=b;	
					});
			ans+=*min_element(tmp,tmp+sz);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
