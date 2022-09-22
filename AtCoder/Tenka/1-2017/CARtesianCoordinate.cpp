#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

struct line {
	double m,c;
	int id;
	double eval (double x) const {
		return m*x+c;
	}
};

bool operator< (const line &a, const line &b) {
	return a.m<b.m;
}

vector<line> tbl;
vector<line> tbl2;

double xx;
bool cmp(const line &a, const line &b) {
	double aa=a.eval(xx);
	double bb=b.eval(xx);
	if (aa!=bb) return aa>bb;
	return a.id>b.id;
}

int bit[100100];

void add(int idx,int val) {
	while (idx<100100) {
		bit[idx]+=val;
		idx+=(idx&-idx);
	}
}

int get(int idx) {
	int sum=0;
	while (idx) {
		sum+=bit[idx];
		idx-=(idx&-idx);
	}
	return sum;
}

struct ei {
	double val;
	int id;
};

bool operator<(const ei &a, const ei &b) {
	if (a.val!=b.val) return a.val>b.val;
	return a.id>b.id;
}

vector<ei> tmp;
int inter(double x) {
	//xx=x;
	for (int i=0;i<(int)tbl.size();i++) {
		tmp[i]=ei{tbl[i].eval(x),tbl[i].id};
	}
	sort(tmp.begin(),tmp.end());
	memset(bit,0,sizeof(bit));
	int cnt=0;
	for (int i=(int)tmp.size()-1;i>=0;i--) {
		//printf("%d,%f ",tmp[i].id,tmp[i].eval(x));
		cnt+=get(tmp[i].id);
		add(tmp[i].id,1);
	}
	return cnt;
}

int main () {
	int n;
	scanf("%d",&n);
	tmp=vector<ei>(n);
	int a,b,c;
	for (int i=0;i<n;i++) {
		scanf("%d%d%d",&a,&b,&c);
		tbl.push_back(line{-1.0*a/b,1.0*c/b,0});
		tbl2.push_back(line{-1.0*b/a,1.0*c/a,0});
	}
	sort(tbl.begin(),tbl.end());
	sort(tbl2.begin(),tbl2.end());

	for (int i=0;i<n;i++) {
		tbl[i].id=i+1;
		tbl2[i].id=i+1;
	}

	int k=(n*(n-1)/2+1)/2;
	double lo=-1e9,hi=1e9;
	double eps=1e-9;
	while (abs(hi-lo)>eps) {
		double mid=(lo+hi)/2;
		if (inter(mid)>=k) hi=mid;
		else lo=mid;
	}
	double xxx=lo;
	lo=-1e9;
	hi=1e9;
	tbl=tbl2;
	while (abs(hi-lo)>eps) {
		double mid=(lo+hi)/2;
		if (inter(mid)>=k) hi=mid;
		else lo=mid;
	}
	printf("%.9f %.9f\n",xxx,lo);

	return 0;
}
