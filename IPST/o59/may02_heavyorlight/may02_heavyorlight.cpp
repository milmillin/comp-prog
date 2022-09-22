#include "hollib.h"
#ifdef debug
#include "hollib.cpp"
#endif

#include <cassert>

//using namespace std;

int tbl[500];

bool ask(int l,int r) {
	int m=(l+r)>>1;
	int res = hol_weight(m-l,tbl+l,r-m,tbl+m);
	return res!=0;
}

void f() {
	int n=hol_init();
	int l=0;
	int r=n;
	int sz;
	while (r-l>=4) {
		sz=(r-l)>>2;
		if (ask(l,l+sz*2)) {
			r=l+sz*2;
		} else if (ask(l+sz*2,l+sz*4)) {
			l=l+sz*2;
		} else {
			l=sz*4;
		}
	}
	if (r-l==3) {
		int res=hol_weight(1,tbl+l,1,tbl+l+1);
		if (res==0) {
			res=hol_weight(1,tbl+l,1,tbl+l+2);
			assert(res!=0);
			if (res==1) {
				hol_answer(1);
			} else {
				hol_answer(2);
			}
			return;
		}
		r--;
	}
	assert(r-l==2);
	if (r-l==2) {
		int res=hol_weight(1,tbl+l,1,tbl+((l)?0:n-1));
		if (res==-1) {
			hol_answer(1);
			return;
		} else if (res==1) {
			hol_answer(2);
			return;
		} else {
			res=hol_weight(1,tbl+l+1,1,tbl);
			if (res==-1) {
				hol_answer(1);
			} else {
				hol_answer(2);
			}
			return;
		}
	}
	assert(false);
}

int main () {
	for (int i=0;i<500;i++) tbl[i]=i;
	int q = hol_init_all();
	while (q--) {
		f();
	}
	return 0;
}
