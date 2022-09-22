#include "gap.h"
#include <cmath>
#include <cstdio>
#ifdef debug
#include "grader.cpp"
#endif

#include <vector>
#include <algorithm>

using namespace std;


long long findGap(int T, int N)
{
	if (T==1) {
		vector<long long> tbl;	
		long long mn,mx;
		long long left=0;
		long long rgt=1e18;
		int x=(N+1)/2;
		for (int i=0;i<x;i++) {
			MinMax(left,rgt,&mn,&mx);
			tbl.push_back(mn);
			if (mx!=mn) tbl.push_back(mx);
			left=mn+1;
			rgt=mx-1;	
		}		
		sort(tbl.begin(),tbl.end());
		long long ans=0;
		for (int i=1;i<N;i++) {
			//printf("%lld ",tbl[i]);
			ans=max(ans,tbl[i]-tbl[i-1]);
		}
		//printf("\n");
		return ans;
	} else {
		long long mn,mx;
		MinMax(0,1e18,&mn,&mx);
		if (N==2) return mx-mn;
		double blkSz=(double)(mx-mn-1)/(N-2);
		//long long over=mx-mn-1-(blkSz)*(N-2);
		//printf("%lld \n",blkSz);
		long long ans=0;
		long long left=mn;
		long long a,b;
		//printf("%lld\n",over);
		
		//for (int i=0;i<over;i++) {
			//MinMax(mn+1+i*(blkSz+1),mn+(i+1)*(blkSz+1),&a,&b);
			//if (ans==-1) continue;
			//ans=max(ans,a-left);
			//left=b;
		//}

		for (double i=mn+1;i<mx;i+=blkSz) {
			//if (i+2*blkSz-1>=mx) {
				//MinMax(i,mx-1,&a,&b);
				//if (a==-1) continue;
				//ans=max(ans,a-left);
				//left=b;
				////continue;	
				//break;
			//}
			MinMax(floor(i),floor(i+blkSz-1),&a,&b);
			if (a==-1) continue;
			ans=max(ans,a-left);
			left=b;
		}
		ans=max(ans,mx-left);
		return ans;
	}
	return 0;
}
