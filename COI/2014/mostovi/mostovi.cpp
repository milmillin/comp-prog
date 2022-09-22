#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <set>

using namespace std;

set<int> up;
set<int> dn;

map<int,int> brup;
map<int,int> brdn;

int n,m;

int nxt(int a) {
	if (a>n) {
		auto res=dn.lower_bound(a);
		if (res==dn.end()) return 2e9+1;
		return *res;
	} else {
		auto res=up.lower_bound(a);
		if (res==up.end()) return 2e9+1;
		return *res;
	}
}

int prv(int a) {
	if (a>n) {
		auto res=dn.lower_bound(a);
		if (res==dn.begin()) return -2e9-1;
		res--;
		return *res+1;
	} else {
		auto res=up.lower_bound(a);
		if (res==up.begin()) return -2e9-1;
		res--;
		return *res+1;
	}
}

pair<int,int> nxtbr(int a) {
	if (a>n) {
		auto res=brdn.lower_bound(a);
		if (res==brdn.end()) return {2e9+2,-1};
		return *res;
	} else {
		auto res=brup.lower_bound(a);
		if (res==brup.end()) return {2e9+2,-1};
		return *res;
	}
}

pair<int,int> prvbr(int a) {
	if (a>n) {
		auto res=brdn.upper_bound(a);
		if (res==brdn.begin()) return {-2e9-2,-1};
		res--;
		return *res;
	} else {
		auto res=brup.upper_bound(a);
		if (res==brup.begin()) return {-2e9-2,-1};
		res--;
		return *res;
	}
}

bool check(int a,int b) {
	if (a>n&&b>n) {
		//same side
		if (b>a) {
			//follow dir
			return nxt(a)>=b;
		} else {
			//rev dir
			auto nbr=nxtbr(a);
			int ll=nxt(a);
			if (nbr.first>ll) return false;
			auto pbr=prvbr(b);
			int rr=prv(b);
			if (pbr.first<rr) return false;
			return nxt(nbr.second)>=pbr.second;			
		}
	} else {
		//op side
		//find all bridges reachable by a
		auto nla=nxtbr(a);
		int ll=nxt(a);
		if (nla.first>ll) return false; //no bridge
		auto nra=prvbr(ll);
		//find all bridges reaching b
		auto nrb=prvbr(b);
		int rr=prv(b);
		if (nrb.first<rr) return false; // no bridge
		auto nlb=nxtbr(rr);
		//printf("%d %d %d %d\n",nla.first,nra.first,nlb.first,nrb.first);
		//printf("%d %d\n",ll,rr);
		if (nla.second<nlb.first||nra.second>nrb.first) return false;
		return true;
	}

}

int main () {
	scanf("%d%d",&n,&m);
	char x;
	int a,b;

	up.insert(0);
	up.insert(n);
	dn.insert(n);
	dn.insert(n*2);

	for (int i=0;i<m;i++) {
		scanf(" %c%d%d",&x,&a,&b);
		if (a>n) a=3*n-a+1;
		if (b>n) b=3*n-b+1;

		//printf("-- %d %d\n",a,b);
		
		if (x=='A') {
			//add
			if (a>b) swap(a,b);
			brup[a]=b;
			brdn[b]=a;

			//printf("add %d %d\n",a,b);
		} else if (x=='B') {
			//block
			if (a>n) {
				dn.insert(a);
				//printf("insert dn %d\n",a);
			} else {
				up.insert(a);
				//printf("insert up %d\n",a);
			}
		} else {
			//check
			printf("%s\n",check(a,b)?"DA":"NE");
		}
	}		
	return 0;
}

