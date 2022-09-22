#include <cmath>
#include <cstdio>
#include <iterator>
#include <vector>
#include <map>
#include <set>


using namespace std;

int h[100100];
long long w[100100];
long long dp[100100];

struct line{
	long long m,c;
	double left;
};

bool operator< (const line &a, const line &b) {
	if (a.m!=b.m) return a.m>b.m;
	return a.c<b.c;
}

double inter(const line &a, const line &b) {
	return (double)(a.c-b.c)/(b.m-a.m);
}

//vector<line> tbl;

map<long long,line> mm;
set<pair<long long,line> > bb;

typedef map<long long,line>::iterator iter_dl;
typedef set<pair<long long,line> >::iterator iter_sdl;

bool bad(line &l1, line &l2, line &l3) {
	return (l3.c-l1.c)*(l1.m-l2.m)<=(l2.c-l1.c)*(l1.m-l3.m);
}

void add(long long m,long long c) {
	//printf("adding %lld %lld\n",m,c);
	pair<iter_dl,bool> res = mm.insert({-m,line{m,c,-2e9}});
	if (!res.second) {
		res.first->second=line{m,min(c,res.first->second.c),-2e9};	
	}
	iter_dl l3 = res.first;
	iter_dl l1,l2,l4,l5;

	while (true) {
		if (l3==mm.begin()) break;
		l2=prev(l3);
		if (l2==mm.begin()) break;
		l1=prev(l2);
		
		if (bad(l1->second,l2->second,l3->second)) {
			//delete l2
			iter_sdl tmp = bb.find({floor(l2->second.left),l2->second});
			mm.erase(l2);
			bb.erase(tmp);
		} else break;
	}

	while (true) {
		if (l3==prev(mm.end())) break;
		l4=next(l3);
		if (l4==prev(mm.end())) break;
		l5=next(l4);

		if (bad(l3->second,l4->second,l5->second)) {
			//delete l4
			iter_sdl tmp = bb.find({floor(l4->second.left),l4->second});
			mm.erase(l4);
			bb.erase(tmp);
		} else break;
	}

	if (l3!=prev(mm.end())) {
		l4=next(l3);
		iter_sdl iter = bb.find({floor(l4->second.left),l4->second});
		bb.erase(iter);
		double ii = inter(l3->second,l4->second);
		//printf("bb %f\n",ii);
		l4->second.left=ii;
		bb.insert({floor(ii),l4->second});
	}
	if (l3!=mm.begin()) {
		l2=prev(l3);
		double ii = inter(l2->second,l3->second);
		l3->second.left=ii;
		//printf("aa %f\n",ii);
		bb.insert({floor(ii),l3->second});
	} else {
		//printf("cc -2e9\n");
		bb.insert({-2e9,l3->second});
	}
	//printf("done\n");
}


int pnt=0;

long long query(long long x) {
	//printf("querying %lld\n",x);
	line tt = line {(long long)-2e9,(long long)-2e9,0};
	iter_sdl cur = prev(bb.upper_bound({x,tt}));
	//printf("%lld %lld\n",cur->second.m,cur->second.c);
	return x*cur->second.m+cur->second.c;
}

int main () {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d",&h[i]);
	}
	for (int i=1;i<=n;i++) {
		scanf("%lld",&w[i]);
		w[i]+=w[i-1];
	}
	add(-2*h[1],h[1]*h[1]-w[1]);
	long long cost=0;
	for (int i=2;i<=n;i++) {
		//for (int j=0;j<tbl.size();j++) {
			//printf("%lld %lld\n",tbl[j].m,tbl[j].c);
		//}
		for (auto it:bb) {
			printf("%lld ",it.first);
		}
		printf("\n*****\n");
		//for (auto it:mm) {
			//printf("%lld %lld %f\n",it.second.m,it.second.c,it.second.left);
		//}
		//printf("*****\n");
		cost=query(h[i])+h[i]*h[i]+w[i-1];
		//printf("yay\n");
		//printf("**%lld %d\n",query(h[i]),pnt);
		if (i<n) add(-2*h[i],h[i]*h[i]-w[i]+cost);
		//printf("-- %lld \n",cost);
	}
	//printf("\n");
	printf("%lld\n",cost);
	return 0;
}
