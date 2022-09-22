#include <cstdio>
#include <algorithm>

using namespace std;

int tbl[3010][3010];

struct node {
	int r1,c1,r2,c2,val;
	node *q1,*q2,*q3,*q4;
};

node* newNode(int r1,int c1,int r2,int c2) {
	node* nd=new node;
	nd->r1=r1;
	nd->r2=r2;
	nd->c1=c1;
	nd->c2=c2;
	if (r1==r2&&c1==c2) {
		nd->q1=nd->q2=nd->q3=nd->q4=NULL;
		nd->val=tbl[r1][c1];
		return nd;
	}
	int mr=(r1+r2)>>1;
	int mc=(c1+c2)>>1;
	nd->q1=newNode(r1,c1,mr,mc);
	nd->q2=newNode(r1,mc+1,mr,c2);
	nd->q3=newNode(mr+1,c1,r2,mc);
	nd->q4=newNode(mr+1,mc+1,3000,3000);
	nd->val=max(max(nd->q1->val,nd->q2->val),max(nd->q3->val,nd->q4->val));
	return nd;
}

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++) {
		int r1,c1,r2,c2;
		scanf("%d%d%d%d",&r1,&c1,&r2,&c2);
		tbl[r1][c1]++;
		tbl[r1][c2+1]--;
		tbl[r2+1][c1]--;
		tbl[r2+1][c2+1]++;
	}
	
	for (int i=1;i<=3000;i++) {
		int cur=0;
		for (int j=1;j<=3000;j++) {
			cur+=tbl[i][j];
			tbl[i][j]=cur;
		}
	}
	for (int j=1;j<=3000;j++) {
		int cur=0;
		for (int i=1;i<=3000;i++) {
			cur+=tbl[i][j];
			tbl[i][j]=cur;
		}
	}
	
	int tree=newNode(1,3000,1,3000);

	for (int i=1;i<=50;i++) {
		for (int j=1;j<=50;j++) {
			printf("%d ",tbl[i][j]);
		}
		printf("\n");
	}
	return 0;
}
