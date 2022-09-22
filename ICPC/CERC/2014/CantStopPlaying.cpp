#include <cstdio>
#include <cassert>
#include <cstring>

//bool config[8200];
//bool newconfig[8200];
int par[1010][8200];
char dir[1010][8200];
int sum[1010];
bool work[8200];

int large[8200];
int small[8200];

bool insertL(int cur,int nw,int sum,int &out) {
	if (cur&&nw>small[cur]) {
		out=-1;
		return false;
	}
	if (work[cur+nw]&&cur+nw>=large[sum-cur]) {
		out=0;
		return true;
	}
	out=cur+nw;
	return true;
}

//set<int> config;
//set<int> newconfig;
//

char ans[1010];
int anscnt;

void f() {
	int n;
	scanf("%d",&n);
	int x;
	scanf("%d",&x);	
	sum[0]=x;
	for (int i=0;i<=x;i++) par[0][i]=-1;
	par[0][x]=0;

	for (int i=1;i<n;i++) {
		scanf("%d",&x);
		sum[i]=sum[i-1]+x;
		for (int j=0;j<=sum[i];j++) par[i][j]=-1;
		for (int j=0;j<=sum[i-1];j++) {
			if (par[i-1][j]==-1) continue;
			int out;
			bool res=insertL(j,x,sum[i-1],out);
			if (res) {
				par[i][out]=j;
				dir[i][out]='l';
			}
			res=insertL(sum[i-1]-j,x,sum[i-1],out);
			if (res) {
				par[i][sum[i]-out]=j;
				dir[i][sum[i]-out]='r';
			}
		}
		//for (int j=0;j<=sum[i];j++) {
			//if (par[i][j]==-1) continue;
			//printf("[ ");
			//int cur=j;
			//while (cur) {
				//printf("%d ",small[cur]);
				//cur-=small[cur];
			//}
			//printf("| ");
			//cur=sum[i]-j;
			//while (cur) {
				//printf("%d ",large[cur]);
				//cur-=large[cur];
			//}
			//printf("]\n");
		//}
	}
	if (!work[sum[n-1]]) {
		printf("no\n");
		return;
	}
	int cur;
	if (par[n-1][sum[n-1]]!=-1) {
		cur=sum[n-1];	
	} else if(par[n-1][0]!=-1) {
		cur=0;		
	} else {
		printf("no\n");
		return;
	} 

	anscnt=n-1;
	ans[n]=0;
	for (int i=n-1;i>0;i--) {
		ans[anscnt--]=dir[i][cur];
		cur=par[i][cur];
	}
	ans[anscnt--]='r';
	printf("%s\n",ans);
	return;
}

int main () {
	large[0]=small[0]=0;
	for (int i=1;i<8200;i++) {
		small[i]=i%2?1:(2*small[i/2]);
	}
	for (int i=1;i<8200;i++) {
		large[i]=small[i]==i?i:large[i-small[i]];
	}
	for (int i=1;i<8200;i<<=1) {
		work[i]=true;
	}
	int q;
	scanf("%d",&q);
	for (int i=0;i<q;i++) {
		f();
	}
	return 0;
}
