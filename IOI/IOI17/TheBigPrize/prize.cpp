#include <bits/stdc++.h>
#include "prize.h"
//#include "grader.cpp"

using namespace std;

pair<int,int> mem[200100];
bool asked[200100];

pair<int,int> askk(int i) {
	if (asked[i]) return mem[i];
	vector<int> res = ask(i);
	asked[i]=true;
	return mem[i]={res[0],res[1]};
}

int ab5=0;


int solve(int ll,int rr) {
	pair<int,int> reL=askk(ll),reM,reR=askk(rr);
	int five = rr-ll-1-reL.second+reR.second;
	if (ll==rr) return -1;
	if (rr-ll-1==five) return -1;
	if (five==0) {
		for (int i=ll;i<rr;i++) {
			auto res=askk(i);
			if (res.first+res.second==0) return i;
		}
		return -1;
	}
	
	int mid=(ll+rr)/2;
	int midd;
	for (int i=0;;i++) {
		bool ss=false;
		if (mid+i<rr) {
			auto res=askk(mid+i);
			if (res.first+res.second==0) return mid+i;
			if (res.first+res.second==ab5) {
				reM=res;
				midd=mid+i;
				break;
			}
			ss=true;
		}
		if (mid-i>ll) {
			auto res=askk(mid-i);
			if (res.first+res.second==0) return mid-i;
			if (res.first+res.second==ab5) {
				reM=res;
				midd=mid-i;
				break;
			}
			ss=true;
		}
		//assert(ss);
	}
	return max(solve(ll,midd),solve(midd,rr));
}

int find_best(int n) {
	if (n<=5000) {
		for (int i=0;i<n;i++) {
			if (askk(i).first+askk(i).second==0) return i;
		}
	}
	for (int i=0;i<500;i++) {
		auto res=askk(i);
		if (res.first+res.second==0) return i;
		ab5=max(ab5,res.first+res.second);
	}
	
	pair<int,int> reL,reR;
	int l,r;
	for (int i=0;i<500;i++) {
		auto res=askk(i);
		if (res.first+res.second==0) return i;
		if (res.first+res.second==ab5) {
			l=i;
			reL=res;
			break;
		}
	}

	for (int i=0;i<500;i++)	{
		auto res=askk(n-i-1);
		if (res.first+res.second==0) return n-i-1;
		if (res.first+res.second==ab5) {
			r=n-i-1;
			reR=res;
			break;
		}
	}
	int aa= solve(l,r);
	//assert(aa!=-1);
	return aa;
}
