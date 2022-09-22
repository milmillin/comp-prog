#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

int p[100100];
int par[100100];
vector<int> pth[100100];

struct pp {
	int jj,tt;
	long long dif() const;
	//void operator= (const pp &b);
	//bool operator< (const pp &b);
};

pp operator+ (const pp &a, const pp &b) {
	return pp{a.jj+b.jj,a.tt+b.tt};
}

pp operator- (const pp &a, const pp &b) {
	return pp{a.jj-b.jj,a.tt-b.tt};
}

//void pp::operator= (const pp &b) {
	//jj=b.jj;
	//tt=b.tt;
//}

long long pp::dif () const {
	return abs(jj-tt);
}

bool operator< (const pp &a, const pp &b) {
	//return this->dif()<b.dif();
	return a.dif()<b.dif();
}

struct ei {
	bool calc;
	int cnt;
	pp m1,m2;
};

vector<vector<ei> > mic00(100100,vector<ei>(200));
vector<vector<ei> > mic01(100100,vector<ei>(200));
vector<vector<ei> > mic10(100100,vector<ei>(200));
vector<vector<ei> > mic11(100100,vector<ei>(200));

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

ei dp00(int idx,int left);
ei dp01(int idx,int left);
ei dp10(int idx,int left);
ei dp11(int idx,int left);

ei dp00 (int idx,int left) {
	if (mic00[idx][left].calc) return mic00[idx][left];
	pp con = {p[idx],p[idx]};
	for (int i=0;i<(int)pth[idx].size();i++) {
		if (pth[idx][i]==par[idx]) continue;
		add(mic00[idx][left],dp00(pth[idx][i],left).m1+con);
		add(mic00[idx][left],dp01(pth[idx][i],left).m1+con);
	}
	return mic00[idx][left];
}


ei dp01 (int idx,int left) {
	if (mic01[idx][left].calc) return mic01[idx][left];
	for (int i=0;i<(int)pth[idx].size();i++) {
		if (pth[idx][i]==par[idx]) continue;
		add(mic01[idx][left],dp10(pth[idx][i],left).m1);
		add(mic01[idx][left],dp11(pth[idx][i],left).m1);
	}
	return mic01[idx][left];	
}

ei dp10 (int idx,int left) {
	if (mic10[idx][left].calc) return mic10[idx][left];
	int sum=p[idx];
	for (int i=0;i<(int)pth[idx].size();i++) {
		if (pth[idx][i]==par[idx]) continue;
		sum+=p[pth[idx][i]];
	}
	pp con = pp{p[idx],sum};
	for (int i=0;i<(int)pth[idx].size();i++) {
		if (pth[idx][i]==par[idx]) continue;
		add(mic10[idx][left],dp00(pth[idx][i],left-1).m1);
		add(mic10[idx][left],dp01(pth[idx][i],left-1).m1);
	}
	return mic10[idx][left];
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

