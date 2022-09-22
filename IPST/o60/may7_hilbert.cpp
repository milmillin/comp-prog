#include <cstdio>
#include <algorithm>

using namespace std;

long long sz[40];
long long len[40];

long long askLen(int x,int y,int k) {
	//printf("ask %d %d %d\n",x,y,k);
	if (k==1) {
		if (x==1) {
			if (y==1) return 0;
			return 1;
		} else {
			if (y==1) return 3;
			return 2;
		}
	}
	bool isRgt=x>sz[k-1]+1;
	bool isUp=y>sz[k-1]+1;
	if (!isRgt&&!isUp) return askLen(x,y,k-1);
	if (k%2) {
		if (isUp) {
			y-=sz[k-1]+1;
			if (isRgt) x-=sz[k-1]+1;
			int xn=y;
			int yn=x;
			long long tmp=askLen(xn,yn,k-1);
			return len[k-1]+1+tmp+((isRgt)?len[k-1]+1:0);
		}							
		x-=sz[k-1]+1;
		int xn=sz[k-1]-x+2;
		int yn=sz[k-1]-y+2;
		return len[k-1]*3+3+askLen(xn,yn,k-1);
	} else {
		if (isRgt) {
			x-=sz[k-1]+1;
			if (isUp) y-=sz[k-1]+1;
			int xn=y;
			int yn=x;
			long long tmp=askLen(xn,yn,k-1);
			return len[k-1]+1+tmp+((isUp)?len[k-1]+1:0);
		}
		y-=sz[k-1]+1;
		int xn=sz[k-1]-x+2;
		int yn=sz[k-1]-y+2;
		return len[k-1]*3+3+askLen(xn,yn,k-1);
	}
}

pair<int,int> askXY(long long l,int k) {
	if (k==1) {
		if (l==0) return {1,1};
		if (l==1) return {1,2};
		if (l==2) return {2,2};
		if (l==3) return {2,1};
	}
	if (l<=len[k-1]) return askXY(l,k-1);
	if (l>=len[k-1]*3+3) {
		auto tmp=askXY(l-len[k-1]*3-3,k-1);
		tmp.first=sz[k-1]-tmp.first+2;
		tmp.second=sz[k-1]-tmp.second+2;
		if (k%2==0) {
			return {tmp.first,sz[k-1]+1+tmp.second};
		} else {
			return {sz[k-1]+1+tmp.first,tmp.second};
		}
	}
	bool ex=false;
	if (l>=len[k-1]*2+2) {
		ex=true;
		l-=len[k-1]*2+2;
	} else {
		l-=len[k-1]+1;
	}	
	auto tmp=askXY(l,k-1);	
	if (k%2) {
		//tmp.first=sz[k-1]-tmp.first+2;
		if (ex) return {tmp.second+sz[k-1]+1,tmp.first+sz[k-1]+1}; 
		else return {tmp.second,tmp.first+sz[k-1]+1};
	} else {
		//tmp.second=sz[k-1]-tmp.second+2;
		if (ex) return {tmp.second+sz[k-1]+1,tmp.first+sz[k-1]+1};
		else return {tmp.second+sz[k-1]+1,tmp.first};
	}
}

int main () {
	sz[1]=1;
	len[1]=3;
	for (int i=2;i<32;i++) {
		sz[i]=sz[i-1]*2+1;
		len[i]=len[i-1]*4+3;
		//printf("%lld\n", sz[i]);
	}
	int q;
	scanf("%d",&q);
	int a,b;
	long long c;
	while (q--) {
		scanf("%d",&a);
		if (a==1) {
			scanf("%d%d",&a,&b);
			printf("%lld\n",askLen(a,b,31));	
		} else {
			scanf("%lld",&c);
			auto tmp=askXY(c,31);
			printf("%d %d\n",tmp.first,tmp.second);
		}
	}
	return 0;
}
