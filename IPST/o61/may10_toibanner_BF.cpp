#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>

using namespace std;

int tbl[100100];
int n;

struct cluster {
	vector<int> pos;
	int mn,mnsk;
	int sum,sumsk;
	int left,right;

	int size() const {
		return pos.size();
	}

	void invalidate() {
		if (size()==1) {
			mn=0;
			mnsk=1e9;
			sum=0;
			sumsk=0;
			return;
		}
		if (size()==2) {
			mn=0;
			mnsk=0;
			sum=pos[1]-pos[0];
			sumsk=0;
			return;	
		}
		vector<int> left;
		left.push_back(0);
		int nn=pos.size();
		for (int i=1;i<nn;i+=2) {
			left.push_back(pos[i]-pos[i-1]+left.back());
		}	
		vector<int> right;
		for (int i=2;i<nn;i+=2) {
			right.push_back(pos[i]-pos[i-1]);
		}
		right.push_back(0);
		for (int i=right.size()-2;i>=0;i--) {
			right[i]+=right[i+1];
		}		
		
		int ei=min(right.size(),left.size());
		mn=1e9;
		for (int i=0;i<ei;i++) {
			mn=min(mn,left[i]+right[i]);
		}
		sum=left.back();
		sumsk=right.front();

		if (pos.size()==3) {
			mnsk=0;
			return;
		}

		left.clear();
		right.clear();

		left.push_back(0);
		nn=pos.size();
		for (int i=2;i<nn;i+=2) {
			left.push_back(pos[i]-pos[i-1]+left.back());
		}	
		for (int i=3;i<nn;i+=2) {
			right.push_back(pos[i]-pos[i-1]);
		}
		right.push_back(0);
		for (int i=right.size()-1;i>=0;i--) {
			right[i]+=right[i+1];
		}		
		
		ei=min(right.size(),left.size());
		mnsk=1e9;
		for (int i=0;i<ei;i++) {
			mnsk=min(mnsk,left[i]+right[i]);
		}
	}
	
	void insert(int x) {
		pos.push_back(x);
		sort(pos.begin(),pos.end());
		left=pos.front();
		right=pos.back();
		invalidate();
		//printf("ins %d %d\n",sum,sumsk);
	}

	cluster() {
		left=right=0;
		mn=mnsk=0;
		sum=sumsk=0;
	}
};

int blksz;
cluster cl[500];

void add(int pos) {
	cl[pos/blksz].insert(tbl[pos]);
}

int fromleft[500];
int sizeleft[500];
int fromright[500];
int sizeright[500];

int main () {
	scanf("%d",&n);

	blksz=(int)floor(sqrt(n));
	
	//printf("-- %d\n",blksz);

	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
	}	
	int x;
	scanf("%d",&x);
	x--;
	add(x);
	int a,b;
	int blkcnt=(n-1)/blksz+1;
	for (int i=0;i<n/2;i++) {
		scanf("%d%d",&a,&b);
		a--;
		b--;
		add(a);
		add(b);
		memset(fromleft,0,sizeof(fromleft));
		memset(fromright,0,sizeof(fromright));
		int cursize=0;
		for (int i=0;i<blkcnt;i++) {
			//printf("%d,",cursize);
			if (cursize%2) {
				fromleft[i]=cl[i].left-cl[i-1].right;
				//printf("\n--- %d\n",cl[i].sumsk);
				fromleft[i]+=cl[i].sumsk;
				cursize+=cl[i].size();
			} else {
				cursize+=cl[i].size();
				fromleft[i]=cl[i].sum;
			}
			sizeleft[i]=cursize;
			//printf("%d ",fromleft[i]);
			if (i) fromleft[i]+=fromleft[i-1];
		}
		//printf(" -- \n");
		cursize=0;
		for (int i=blkcnt-1;i>=0;i--) {
			fromright[i]=0;
			if (cursize%2) {
				fromright[i]+=cl[i+1].left-cl[i].right;
			}
			if ((cursize+cl[i].size())%2) {
				fromright[i]+=cl[i].sumsk;
			} else {
				fromright[i]+=cl[i].sum;
			}
			cursize+=cl[i].size();
			sizeright[i]=cursize;
			if (i<blkcnt-1) fromright[i]+=fromright[i+1];
		}
		int ans=1e9;
		if (cl[0].size()!=0) {
			int cur=fromright[1];
			if (sizeright[i+1]%2) {
				cur+=cl[1].left-cl[0].right;
			}
			ans=min(ans,cur);
		}
		if (cl[blkcnt-1].size()!=0) {
			int cur=fromleft[blkcnt-2];
			if (sizeleft[i-1]%2) {
				cur+=cl[blkcnt-1].left-cl[blkcnt-2].right;
			}
			ans=min(ans,cur);
		}
		for (int i=1;i<blkcnt-1;i++) {
			if (cl[i].size()==0) continue;
			int cur=fromleft[i-1]+fromright[i+1];
			if (sizeleft[i-1]%2) {
				cur+=cl[i].left-cl[i-1].right;	
			}	
			if (sizeright[i+1]%2) {
				cur+=cl[i+1].left-cl[i].right;
			}
			ans=min(ans,cur);
		}
		//for (int i=0;i<blkcnt;i++) {
			//printf("%d %d\n",fromleft[i],fromright[i]);
		//}
		printf("%d\n",ans);
	}
	return 0;
}
