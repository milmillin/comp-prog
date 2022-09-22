#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

typedef struct {
	int val,bea;
} flower;

vector<flower> high,lo;

int mem1[110][110][110];
int mem2[110][110][110];

int beauty(int m,int amt,int idx) {
	if (amt==0) return 0;
	if (idx<0) return -1e9;
	//if (m<=0) return 0;
	if (mem1[m][amt][idx]!=-1) return mem1[m][amt][idx];
	//if (amt==0) return 0;
	int sum=beauty(m,amt,idx-1);
	if (m>=high[idx].val) sum=max(sum,beauty(m-high[idx].val,amt-1,idx-1)+high[idx].bea);
	return mem1[m][amt][idx]=sum;
}

int beauty2(int m,int amt,int idx) {
	if (amt==0) return 0;
	if (idx<0) return -1e9;
	//if (idx<0) return 0;
	//if (m<=0) return 0;
	if (mem2[m][amt][idx]!=-1) return mem2[m][amt][idx];
	//if (amt==0) return 0;
	int sum=beauty2(m,amt,idx-1);
	if (m>=lo[idx].val) sum=max(sum,beauty2(m-lo[idx].val,amt-1,idx-1)+lo[idx].bea);
	return mem2[m][amt][idx]=sum;
}

int m;
int memAns[110][110][4];
int anss(int black,int white,int st) {
	if (black>high.size()) return 0;
	if (white>lo.size()) return 0;
	if (memAns[black][white][st]!=-1) return memAns[black][white][st];
	int sum=0;
	for (int i=0;i<=m;i++) {
		sum=max(sum,beauty(i,black,high.size()-1)+beauty2(m-i,white,lo.size()-1));
	}
	//printf("%d %d %d\n",black,white,sum);
	if (st==0) {
		//black;
		return memAns[black][white][st]=max(sum,max(anss(black+1,white,2),anss(black,white+1,1)));
	} else if (st==1) {
		//white
		return memAns[black][white][st]=max(sum,max(anss(black+1,white,0),anss(black,white+1,3)));
	} else if (st==2) {
		//bb
		return memAns[black][white][st]=max(sum,anss(black,white+1,1));
	} else if (st==3) {
		//ww
		return memAns[black][white][st]=max(sum,anss(black+1,white,0));
	}
}

int main () {
	int k;
	scanf("%d%d",&m,&k);
	int a,b,c;
	for (int i=0;i<k;i++) {
		scanf("%d%d%d",&a,&b,&c);
		if (c) {
			high.push_back(flower{a,b});
		} else {
			lo.push_back(flower{a,b});
		}
	}
	memset(mem1,-1,sizeof(mem1));
	memset(mem2,-1,sizeof(mem2));
	memset(memAns,-1,sizeof(memAns));
	printf("%d\n",max(anss(1,0,0),anss(0,1,1)));	
	return 0;
}
