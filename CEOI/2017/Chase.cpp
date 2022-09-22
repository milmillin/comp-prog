#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

int p[100100];
int par[100100];
vector<int> pth[100100];

struct pp {
	long long jj,tt;
	long long dif() const;
	void operator= (const pp &b);
	bool operator< (const pp &b);
};

pp operator+ (const pp &a, const pp &b) {
	return pp{a.jj+b.jj,a.tt+b.tt};
}

pp operator- (const pp &a, const pp &b) {
	return pp{a.jj-b.jj,a.tt-b.tt};
}

void pp::operator= (const pp &b) {
	jj=b.jj;
	tt=b.tt;
}

long long pp::dif () const {
	return abs(jj-tt);
}

bool pp::operator< (const pp &b) {
	return this->dif()<b.dif();
}

struct ei {
	bool calc;
	int cnt;
	pp m1,m2;
};

ei mic00[100100][200];
ei mic01[100100][200];
ei mic10[100100][200];
ei mic11[100100][200];

void add(ei &a, pp x) {
	if (a.cnt==0) {
		a.m1=x;
		a.cnt=1;
	} else {
		if (!(x<a.m1)) {
			a.m2=a.m1;
			a.m1=x;
			a.cnt=2;
		} else if (a.cnt==2&&!(x<a.m2)) {
			a.m2=x;
		}
	}
}

ei dp00 (int idx,int left) {
	if (mic00[idx][left].calc) return mic00[idx][left];
	for (int i=0;i<(int)pth[idx].size();i++) {
		if (pth[idx][i]==par[idx]) continue;
	}
}


ei dp01 (int idx,int left) {
	if (mic01[idx][left].calc) return mic01[idx][left];
	
}

ei dp10 (int idx,int left) {
	if (mic10[idx][left].calc) return mic10[idx][left];
	
}

ei dp11 (int idx,int left) {
	if (mic11[idx][left].calc) return mic11[idx][left];
	
}

void findPar(int idx) {
	for (int i=0;i<(int)pth[idx].size();i++) {
		if (pth[idx][i]==par[idx]) continue;
		par[pth[idx][i]]=idx;
		findPar(pth[idx][i]);
	}
}

int main () {
	int n,v;
	scanf("%d%d",&n,&v);
	for (int i=1;i<=n;i++) {
		scanf("%d",&p[i]);
	}
	int a,b;
	for (int i=2;i<=n;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		pth[b].push_back(a);
	}
	par[1]=1;
	findPar(1);
	return 0;
}
