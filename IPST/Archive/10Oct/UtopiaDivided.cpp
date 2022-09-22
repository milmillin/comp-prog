#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int signX[] = {0,1,-1,-1,1};
int signY[] = {0,1,1,-1,-1};

int changeX[20000];
int changeY[20000];

typedef struct {
	int* val;
} block;

vector<block> eiei;

bool operator< (const block &a, const block &b) {
	return abs(*(a.val))<abs(*(b.val));
}

int main () {
	int n;
	scanf("%d",&n);
	vector<int> tbl(2*n);
	for (int i=0;i<2*n;i++) {
		scanf("%d",&tbl[i]);
	}
	sort(tbl.begin(),tbl.end());
	int x,y;
	x=y=0;
	int qrd;
	int curQrd=0;
	for (int i=0;i<n;i++) {
		scanf("%d",&qrd);
		changeX[i]=(signX[qrd]-signX[curQrd]);
		changeY[i]=(signY[qrd]-signY[curQrd]);
		curQrd=qrd;
//		if (qrd==1) {
//			//++
//
//		} else if (qrd==2) {
//			//-+
//
//		} else if (qrd==3) {
//			//--
//
//		} else if (qrd==4) {
//			//+-
//
//		}
	}

	for (int i=0;i<n;i++) {
		eiei.push_back(block{&changeX[i]});
		eiei.push_back(block{&changeY[i]});
		//printf("%d %d\n",changeX[i],changeY[i]);
	}
	sort(eiei.begin(),eiei.end());
	int sum;
	int anss;
	for (int i=0;i<2*n;i++) {
		sum = *(eiei[i].val);
		int* a = eiei[i].val;
		//printf("%d\n",sum);
		*a = tbl[i]*((sum>=0)?1:-1);
	}
	for (int i=0;i<n;i++) {
		printf("%d %d\n",changeX[i],changeY[i]);
	}
	return 0;
}
