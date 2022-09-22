#include "catdog.h"

#ifdef debug
#include "grader.cpp"
#endif

#include <algorithm>
#include <vector>
#include <cstring>
#include <cassert>

using namespace std;

int x;

vector<int> pth[1010];
int state[1010];

int mCat[1010];
int mDog[1010];
int mNone[1010];


int min3(int x,int y,int z) {
	return min(x,min(y,z));
}

int dDog(int x,int p);
int dNone(int x,int p);

int dCat(int x,int p) {
	if (mCat[x]!=-1) return mCat[x];
	if (state[x]==2) return mCat[x]=1e9;
	int cur=0;
	for (auto i:pth[x]) {
		if (i==p) continue;
		cur+=min3(dCat(i,x),1+dDog(i,x),dNone(i,x));
	}
	return mCat[x]=cur;
}

int dDog(int x,int p) {
	if (mDog[x]!=-1) return mDog[x];
	if (state[x]==1) return mDog[x]=1e9;
	int cur=0;
	for (auto i:pth[x]) {
		if (i==p) continue;
		cur+=min3(1+dCat(i,x),dDog(i,x),dNone(i,x));
	}
	return mDog[x]=cur;
}

int dNone(int x,int p) {
	if (mNone[x]!=-1) return mNone[x];
	if (state[x]!=0) return mNone[x]=1e9;
	int cur=0;
	for (auto i:pth[x]) {
		if (i==p) continue;
		cur+=min3(1+dCat(i,x),1+dDog(i,x),dNone(i,x));
	}
	return mNone[x]=cur;
}

void initialize(int N, std::vector<int> A, std::vector<int> B) {
	assert(N<1010);
	x = A.size();
	for (int i=0;i<x;i++) {
		pth[A[i]].push_back(B[i]);
		pth[B[i]].push_back(A[i]);
	}
}

int solve() {
	memset(mCat,-1,sizeof(mCat));
	memset(mDog,-1,sizeof(mDog));
	memset(mNone,-1,sizeof(mNone));
	return min3(dCat(1,1),dDog(1,1),dNone(1,1));
}

int cat(int v) {
	state[v]=1;
	return solve();
}

int dog(int v) {
	state[v]=2;
	return solve();
}

int neighbor(int v) {
	state[v]=0;
	return solve();
}
