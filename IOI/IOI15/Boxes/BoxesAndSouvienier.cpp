#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

pair<int,int> fnd(vector<int> &a,vector<int>::iterator t) {
	auto tmp = lower_bound(a.begin(),t+1,*t);
	return {t-tmp+1,tmp-a.begin()-1};
}

int lptr,lx;
int rptr,rx;

int updl(int x) {
	if (x==lx) return lptr;
	
}

int main () {
	lx=rx=-1;
	int n,k,l;
	scanf("%d%d%d",&n,&k,&l);
	vector<int> ll,rr;
	int x;
	for (int i=0;i<n;i++) {
		scanf("%d",&x);
		if (x<=l/2) ll.push_back(x);
		else rr.push_back(l-x);
	}
	reverse(rr.begin(),rr.end());
	printf("** %d %d\n",ll.size(),rr.size());
	long long ans=0;
	int curl=ll.size()-1,curr=rr.size()-1;

	while (true) {
		int mx=0;
		if (curl>=0) mx=max(mx,ll[curl]);
		if (curr>=0) mx=max(mx,rr[curr]);
		if (mx<=l/4) break;
		if (curr<0&&curl<0) break;
		if (curr<0||curl<0) break;
		
		bool useL=false;
		bool useR=false;
		int mxx=0;
		for (int i=0;i<k;i++) {
			if (curr<0&&curl<0) break;
			if (curr<0||curl<0) break;
			
			



			if (ll.size()==0&&rr.size()==0) break;
			if (ll.size()==0) {
				mxx=max(mxx,rr.back());
				rr.pop_back();
				useR=true;
			} else if (rr.size()==0) {
				mxx=max(mxx,ll.back());
				ll.pop_back();
				useL=true;
			} else {
				if (rr.back()>ll.back()) {
					mxx=max(mxx,rr.back());
					rr.pop_back();
					useR=true;
				} else {
					mxx=max(mxx,ll.back());
					ll.pop_back();
					useL=true;
				}
			}
		}
		
		//printf("%d %d\n",useL,useR);
		if (useL&&useR) {
			ans+=l;
			printf("b %d\n",l);
		}
		else if (useL||useR) {
		   	ans+=2*mxx;
			printf("a %d\n",mxx);
		}
	}
	for (int i=ll.size()-1;i>=0;i-=k) {
		ans+=ll[i]*2;
		printf("c %d\n",ll[i]);
	}
	for (int i=rr.size()-1;i>=0;i-=k) {
		ans+=rr[i]*2;
		printf("d %d\n",rr[i]);
	}
	printf("%lld\n",ans);
	return 0;
}
