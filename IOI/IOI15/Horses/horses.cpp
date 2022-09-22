#include "horses.h"
#include <algorithm>
#include <vector>
#include <cstdio>

using namespace std;

const int mod = 1000000007;

struct number {
	long long val;
	bool overflow;
	number() {
		val=0;
		overflow=false;
	}
	number(long long _val) {
		val=_val;
		overflow=false;
	}

	number(long long _val,bool _of) {
		val=_val;
		overflow=_of;
	}
	bool operator< (const number &r) const {
		if (overflow||r.overflow) {
			return r.overflow;
		}
		return val<r.val;
	}

	number operator+(const number &r) const {
		return number((val+r.val)%mod,(val+r.val)>=mod||overflow||r.overflow);
	}
	number operator-(const number &r) const {
		return number(((val-r.val)%mod+mod)%mod,(val-r.val)<0||overflow||r.overflow);
	}
	number operator*(const number &r) const {
		return number((val*r.val)%mod,(val*r.val)>=mod||overflow||r.overflow);
	}
	number& operator=(const long long _val) {
		val=_val%mod;
		overflow=_val>=mod;
		return *this;
	}
};

struct node {
	number xval;
	number ymax;
	number pre;
	number suf;	
	void combine(const node &l,const node &r) {
		xval=l.xval*r.xval;
		if (l.ymax<l.suf*r.pre*r.ymax) {
			//choose right
			ymax=r.ymax;
			pre=l.xval*r.pre;
			suf=r.suf;
		} else {
			//choose left
			ymax=l.ymax;
			pre=l.pre;
			suf=l.suf*r.xval;	
		}
	}
};

node seg[2000100];
number x[500100];
number y[500100];
int n;

void build(int idx,int l,int r) {
	if (l+1==r) {
		seg[idx].xval=x[l];
		seg[idx].pre=x[l];
		seg[idx].suf=1;
		seg[idx].ymax=y[l];
		return;
	}					
	int m=(l+r)>>1;
	build(idx*2+1,l,m);
	build(idx*2+2,m,r);
	seg[idx].combine(seg[idx*2+1],seg[idx*2+2]);
}

void update(int idx,int l,int r,int k) {
	if (k<l||k>=r) return;
	if (l+1==r) {
		seg[idx].xval=x[l];
		seg[idx].pre=x[l];
		seg[idx].suf=1;
		seg[idx].ymax=y[l];
		return;
	}
	int m=(l+r)>>1;
	update(idx*2+1,l,m,k);
	update(idx*2+2,m,r,k);
	seg[idx].combine(seg[idx*2+1],seg[idx*2+2]);
}

//void print(int idx,int l,int r) {
	//printf("%d %d: %lld %lld %lld %lld\n",l,r,seg[idx].xval.val,seg[idx].ymax.val,seg[idx].suf.val,seg[idx].pre.val);
	//if (l+1==r) return;
	//int m=(l+r)>>1;
	//print(idx*2+1,l,m);
	//print(idx*2+2,m,r);
//}

int init(int N, int X[], int Y[]) {
	n=N;
	for (int i=0;i<n;i++) {
		x[i]=X[i];
		y[i]=Y[i];
	}
	build(0,0,n);
	//print(0,0,n);
	return (seg[0].pre*seg[0].ymax).val;
}

int updateX(int pos, int val) {	
	x[pos]=val;
	update(0,0,n,pos);
	return (seg[0].pre*seg[0].ymax).val;
}

int updateY(int pos, int val) {
	y[pos]=val;
	update(0,0,n,pos);
	return (seg[0].pre*seg[0].ymax).val;
}
