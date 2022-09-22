#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> tbl[10];
int res[10];

bool contain(const vector<int> &a, const int val) {
	for (int i=0;i<(int)a.size();i++) {
		if (a[i]==val) return true;
	}
	return false;
}

vector<int> unionn(const vector<int> &a, const vector<int> &b) {
	vector<int> res=a;
	for (int i=0;i<(int)b.size();i++) {
		if (contain(a,b[i])) continue;
		res.push_back(b[i]);
	}
	sort(res.begin(),res.end());
	return res;
}

vector<int> intersect(const vector<int> &a, const vector<int> &b) {
	vector<int> res;
	for (int i=0;i<(int)a.size();i++) {
		if (!contain(b,a[i])) continue;
		res.push_back(a[i]);
	}
	return res;
}

int maxDep;

void prep(int l,int r,int dep) {
	if (l+1==r) return;
	maxDep=max(maxDep,dep);
	int m=(l+r)>>1;
	vector<int> tmp;
	for (int i=l;i<m;i++) {
		tmp.push_back(i);
	}
	tbl[dep]=unionn(tbl[dep],tmp);
	prep(l,m,dep+1);
	prep(m,r,dep+1);
}

int n,x,y,xy;

vector<int> comp(const vector<int> &a) {
	vector<int> res;
	for (int i=0;i<n;i++) {
		if (contain(a,i)) continue;
		res.push_back(i);
	}
	return res;
}

vector<int> minn(const vector<int> &a,const vector<int> &b) {
	vector<int> res;
	for (int i=0;i<(int)a.size();i++) {
		if (contain(b,a[i])) continue;
		res.push_back(a[i]);
	}
	return res;
}

int askk(vector<int> &a) {
	if (a.size()==0) return 0;
	printf("? %d ",a.size());
	for (int i=0;i<(int)a.size();i++) {
		printf("%d ",a[i]+1);
	}
	printf("\n");
	fflush(stdout);
	int xx;
	scanf("%d",&xx);
	if (xx==y||xx==xy) return 1;
	return 0;
}

int main () {

	scanf("%d%d%d",&n,&x,&y);
	prep(0,n,0);
	//for (int i=0;i<=maxDep;i++) {
		//for (int j=0;j<(int)tbl[i].size();j++) {
			//printf("%d ",tbl[i][j]);
		//}
		//printf("\n");
	//}
	//printf("%d\n",maxDep);
	xy=x^y;
	int idx=-1;
	for (int i=0;i<=maxDep;i++) {
		if (askk(tbl[i])) res[i]=1,idx=i;
		else res[i]=0;	
	}
	
	vector<int> a=tbl[idx];
	vector<int> b=comp(tbl[idx]);
	int l=0,r=n;
	int dep=0;
	vector<int> last=tbl[idx];
	while (a.size()>1) {
		int m=(l+r)>>1;
		if (dep==idx) {
			r=m;
			dep++;
			continue;
		}
		vector<int> tmp;
		//printf("--> ");
		for (int i=0;i<(int)last.size();i++) {
			//printf("%d ",last[i]);
			if (last[i]<m&&last[i]>=l) tmp.push_back(last[i]);
		}
		//printf("\n");
		int cur=askk(tmp);
		if (cur==1) {
			a=tmp;
			r=m;
			if (res[dep]==1) {
				b=intersect(b,comp(tbl[dep]));	
			} else {
				b=intersect(b,tbl[dep]);
			}
		} else {
			a=minn(last,tmp);
			tmp=minn(last,tmp);
			l=m;
			if (res[dep]==1) {
				b=intersect(b,tbl[dep]);	
			} else {
				b=intersect(b,comp(tbl[dep]));
			}
		}
		dep++;
		swap(tmp,last);
	}
	while (b.size()>1) {
		assert(dep<=maxDep);
		if (dep==idx) {
			dep++;
			continue;
		}
		vector<int> tmp=intersect(b,tbl[dep]);
		if (askk(tmp)) {
			b=tmp;
		} else {
			b=minn(b,tmp);
		}
		dep++;
	}
	int aa=a[0],bb=b[0];
	//assert(b.size()<=2);

	//if (b.size()>1) {
		//vector<int> tmp;
		//tmp.push_back(b[0]);
		//if (askk(tmp)) bb=b[0];
		//else bb=b[1];	
	//} else {
		//bb=b[0];
	//}
	printf("! %d %d\n",min(aa,bb)+1,max(aa,bb)+1);
	return 0;
}
