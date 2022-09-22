#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

struct ei {
	int h;
	int val;
};

int tbl[1300][1300];
int fwc[600][100001];
int fwr[100001];

int qsr[1300][1300];
int qsc[1300][1300];

int mic[1300][1300];

void add(int* fw,int idx,int val) {
	while (idx<100100) {
		//printf("-- %d\n",idx);
		fw[idx]=min(fw[idx],val);
		idx+=idx&-idx;
	}
}

int get(int* fw,int idx) {
	int ans=1e9;
	while (idx) {
		//printf("-- %d\n",idx);
		ans=min(ans,fw[idx]);
		idx-=idx&-idx;
	}		
	return ans;
}

int main () {
	int r,c;
	scanf("%d%d",&r,&c);	
	for (int i=1;i<=r;i++) {
		for (int j=1;j<=c;j++) {
			scanf("%d",&tbl[i][j]);
		}
	}

	for (int i=1;i<=r;i++) {
		for (int j=1;j<=c;j++) {
			qsr[i][j]=tbl[i][j]+qsr[i][j-1];
			qsc[i][j]=tbl[i][j]+qsc[i-1][j];
		}
	}
	//printf("yy\n");
	
	memset(fwr,63,sizeof(fwr));
	memset(fwc,63,sizeof(fwc));	
	add(fwr,tbl[1][1]+1,0-qsr[1][1]);
	add(fwc[1],tbl[1][1]+1,0-qsr[1][1]);
	//printf("yay\n");
	
	for (int i=1;i<=r;i++) {
		for (int j=1;j<=c;j++) {
			if (i==1&&j==1) continue;
			//printf("%d %d\n",i,j);
			//int ans=1e9;
			mic[i][j]=1e9;
			mic[i][j]=min(mic[i][j],get(fwr,tbl[i][j])+qsr[i][j-1]);
			mic[i][j]=min(mic[i][j],get(fwc[j],tbl[i][j])+qsc[i-1][j]);
			//printf("%d,%d,%d ",mic[i][j],get(fwr[i],tbl[i][j]),get(fwc[j],tbl[i][j]));
			
			add(fwr,tbl[i][j]+1,mic[i][j]-qsr[i][j]);	
			add(fwc[j],tbl[i][j]+1,mic[i][j]-qsc[i][j]);
		}
		memset(fwr,63,sizeof(fwr));
		//printf("\n");
	}
	printf("%d\n",mic[r][c]);
	return 0;
}
