#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>

using namespace std;

vector<int> pth[1010];
int val[1010];

struct ei {
	int a,b;
	ei operator+ (const ei &aa) const;
	ei swap() const;
};

ei ei::operator+ (const ei &aa) const {
	return ei{a+aa.a,b+aa.b};
}

ei ei::swap() const {
	return ei{b,a};
}

bool la(const ei &a, const ei &b) {
	if (a.a!=b.a) return a.a<b.a;
	return a.b<b.b;
}

bool lb(const ei &a, const ei &b) {
	if (a.b!=b.b) return a.b<b.b;
	return a.a<b.a;
}

int mic[1010][2];
ei ee[1010][2];

int mem[1010][5010];
int dp(vector<ei> &tt,int idx,int val) {
	//assert(val<2500);
	if (val<0) return 0;
	if (idx<0) return 0;
	if (idx==0) {
		int mn=0;
		if (tt[idx].a<=val) mn=min(mn,tt[idx].b);
		return mn;
	}
	if (mem[idx][val]!=-1) return mem[idx][val];
	int mn=0;
	mn=min(mn,dp(tt,idx-1,val));
	if (tt[idx].a<=val&&tt[idx].a>=0) mn=min(mn,tt[idx].b+dp(tt,idx-1,val-tt[idx].a));
	return mem[idx][val]=mn;
}

int dep(int idx,int col) {
	if (mic[idx][col]!=-1) return mic[idx][col];
	
	ei iB=ei{0,0};
	ei iW=ei{0,0};
	
	vector<ei> bb,ww;	

	for (int i=0;i<(int)pth[idx].size();i++) {
		int b=dep(pth[idx][i],0);
		int w=dep(pth[idx][i],1);
		if (b==0&&w==0) {
			return mic[idx][0]=mic[idx][1]=0;
		} else if (b==0) {
			//wht+=val[pth[idx][i]];
			iB=iB+ee[pth[idx][i]][1];
			iW=iW+ee[pth[idx][i]][1];
		} else if (w==0) {
			iB=iB+ee[pth[idx][i]][0];
			iW=iW+ee[pth[idx][i]][0];
		} else {
			ei &a0=ee[pth[idx][i]][0];
			ei &a1=ee[pth[idx][i]][1];
			if (la(a0,a1)) {
				iB=iB+a0;
				bb.push_back(ei{a1.a-a0.a,a1.b-a0.b});
			} else {
				iB=iB+a1;
				bb.push_back(ei{a0.a-a1.a,a0.b-a1.b});
			}

			if (lb(a0,a1)) {
				iW=iW+a0;
				ww.push_back(ei{a1.a-a0.a,a1.b-a0.b}.swap());
			} else {
				iW=iW+a1;
				ww.push_back(ei{a0.a-a1.a,a0.b-a1.b}.swap());
			}
			if (bb.back().b>=0) bb.pop_back();
			if (ww.back().b>=0) ww.pop_back();
		}
	}

	//memset(mem,-1,sizeof(mem));
	for (int j=0;j<1010;j++) for (int i=0;i<=val[idx]-iB.a;i++) mem[j][i]=-1;
	iB.b+=dp(bb,bb.size()-1,val[idx]-iB.a);
	//memset(mem,-1,sizeof(mem));
	for (int j=0;j<1010;j++) for (int i=0;i<=val[idx]-iW.b;i++) mem[j][i]=-1;
	iW.a+=dp(ww,ww.size()-1,val[idx]-iW.b);

	mic[idx][0]=(iB.a<=val[idx]);
	mic[idx][1]=(iW.b<=val[idx]);
	iB.a=val[idx];
	iW.b=val[idx];
	ee[idx][0]=iB;
	ee[idx][1]=iW;
	return mic[idx][col];
}

int main() {
	int n;
	scanf("%d",&n);
	int x;
	for (int i=2;i<=n;i++) {
		scanf("%d",&x);
		pth[x].push_back(i);
	}
	for (int i=1;i<=n;i++) {
		scanf("%d",&val[i]);
	}
	memset(mic,-1,sizeof(mic));
	//for (int i=1;i<=n;i++) {
		//printf("%d: %d, %d,%d %d, %d,%d\n",i,dep(i,0),ee[i][0].a,ee[i][0].b,dep(i,1),ee[i][1].a,ee[i][1].b);	
		//}

	printf("%sPOSSIBLE\n",(dep(1,0)||dep(1,1))?"":"IM");
}
