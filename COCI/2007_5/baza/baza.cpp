#include <cstdio>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;


string a[30010];
string sorted[30010];

int beg[40];
int endd[40];

int bound(char x,int j,int l,int r) {
	int mid;	
	while (l<r) {
		mid=(l+r)>>1;
		if (sorted[mid][j]>=x) {
			r=mid;
		} else {
			l=mid+1;
		}
	}
	return r;
}

string stk;
int search(const char *x,int j,int l,int r) {
	beg[j]=endd[j]=-1;	
	if (x[j]==0) {
		if (sorted[l][j]==0) return l;
		return -1;
	}
	stk.push_back(x[j]);	
	int left=bound(x[j],j,l,r);
	int rgt=bound(x[j]+1,j,l,r);
	//int left=lower_bound(sorted+l,sorted+r,stk)-sorted;
	//stk.back()++;
	//int rgt=lower_bound(sorted+l,sorted+r,stk)-sorted;
	//stk.back()--;
	beg[j]=left;
	endd[j]=rgt;
	if (left==rgt) return -1;
	return search(x,j+1,left,rgt);
}

int counter[30010][40];
int before[30010][40];
int id[30010];

int main () {
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		cin >> a[i];
		sorted[i]=a[i];
	}
	sort(sorted,sorted+n);
	for (int i=0;i<n;i++) {
		stk.clear();
		int res=search(a[i].c_str(),0,0,n);
		id[res]=i;
		//printf("%d\n",res);
		for (int j=0;beg[j]<endd[j];j++) {
			before[res][j]=++counter[beg[j]][j];
		}
	}
	int q;
	scanf("%d",&q);
	char x[40];
	for (int i=0;i<q;i++) {
		scanf("%s",x);
		stk.clear();
		int res=search(x,0,0,n);
		//printf("-- %d\n",res);
		int sum=0;
		if (res==-1) {
			sum+=n;	
			for (int j=0;beg[j]<endd[j];j++) {
				sum+=counter[beg[j]][j];
			}
		} else {
			sum+=id[res]+1;
			for (int j=0;beg[j]<endd[j];j++) {
				sum+=before[res][j];
			}
		}
		printf("%d\n",sum);
	}
	return 0;
}
