#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <queue>

using namespace std;

int random(int a,int b) {
	return a + (rand() % (int)(b - a + 1));
}

int par[100100];
bool used[100100];

bool sel[100100];

int main () {
	freopen("10.in","w",stdout);
	int n=10;
	int m=100;
	srand(time(NULL));
	printf("%d %d\n",n,m);
	queue<int> q;
	used[1]=true;
	q.push(1);
	int cnt=n-1;
	int now;
	while (!q.empty()) {
		now=q.front();
		q.pop();
		int chd=random(1,4);
		for (int i=0;i<chd&&cnt;i++) {
			int tmp=random(1,n);
			while (used[tmp]) tmp=random(1,n);
			par[tmp]=now;
			used[tmp]=true;
			cnt--;
			q.push(tmp);
		}
	}
	for (int i=2;i<=n;i++) {
		printf("%d\n",par[i]);
	}
	int selCnt=0;
	for (int i=0;i<m;i++) {
		int cmd=random(1,3);
		while ((cmd==1&&selCnt==n-1)||(cmd==2&&selCnt==0)) cmd=random(1,3);
		printf("%d ",cmd);
		if (cmd==1) {
			int tmp=random(2,n);
			while (sel[tmp]) tmp=random(2,n);
			sel[tmp]=true;
			selCnt++;
			printf("%d\n",tmp);
		} else if (cmd==2) {
			int tmp=random(2,n);
			while (!sel[tmp]) tmp=random(2,n);
			sel[tmp]=false;
			selCnt--;
			printf("%d\n",tmp);
		} else {
			int tmp=random(1,n);
			printf("%d\n",tmp);
		}
	}
	return 0;
}
