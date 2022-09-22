#include "xylophone.h"

#ifdef debug
#include "grader.cpp"
#endif

#include <algorithm>

int tbl[6010];

void solve(int N) {
	tbl[1]=0;
	tbl[2]=query(1,2);
	int q1,q2;
	int qlast;
	bool inc;
	for (int i=3;i<=N;i++) {
		q1=query(i-1,i);
		q2=query(i-2,i);
		inc=tbl[i-1]>tbl[i-2];
		qlast=abs(tbl[i-1]-tbl[i-2]);				
		if (q2==qlast||q2==q1) {
			//change direction
			tbl[i]=tbl[i-1]+(inc?-1:1)*q1;
		} else {
			//same direction
			tbl[i]=tbl[i-1]+(inc?1:-1)*q1;
		}
	}

	int mx=0;
	int mxId=-1;
	int mn=N+1;
	int mnId=-1;
		
	for (int i=1;i<=N;i++) {
		if (tbl[i]>mx) {
			mx=tbl[i];
			mxId=i;
		}
		if (tbl[i]<mn) {
			mn=tbl[i];
			mnId=i;
		}
	}

	if (mnId>mxId) {
		for (int i=1;i<=N;i++) tbl[i]=-1*tbl[i];
		
		mn=-mx;
	}

	for (int i=1;i<=N;i++) {
		answer(i,tbl[i]-mn+1);
	}	
}
