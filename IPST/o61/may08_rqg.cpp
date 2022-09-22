#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

int cnt=0;

struct kb {
	int d,col,x,y;
};

//vector<kb> aa;

void print2(int x,int y,int offx,int offy,int col) {
	cnt++;
	if (x==0&&y==0) {
		printf("%d %d %d %d\n",1,col,offx,offy);
		//aa.push_back(kb{1,col,offx,offy});
	} else if (x==1&&y==0) {
		printf("%d %d %d %d\n",2,col,offx,offy);
		//aa.push_back(kb{2,col,offx,offy});
	} else if (x==0&&y==1) {
		printf("%d %d %d %d\n",3,col,offx,offy);
		//aa.push_back(kb{3,col,offx,offy});
	} else if (x==1&&y==1) {
		printf("%d %d %d %d\n",4,col,offx,offy);	
		//aa.push_back(kb{4,col,offx,offy});
	} else {
		assert(false);
	}
}

void print(int lev,int x,int y,int offx,int offy,int col,int col3) {
	//printf("-- %d %d %d %d %d\n",lev,x,y,offx,offy);
	if (lev==2) {
		print2(x,y,offx,offy,col);
		return;
	}
	int m=lev/2;
	//printf("%d\n",m);
	int d=0;
	if (x<m) {
		if (y<m) d=1;
		else d=3;
	} else {
		if (y<m) d=2;
		else d=4;
	}

	//top left
	if (d==1) print(lev/2,x,y,offx,offy,col,col3);
	//top right
	if (d==2) print(lev/2,x-m,y,offx+m,offy,col3,col);
	//bot left
	if (d==3) print(lev/2,x,y-m,offx,offy+m,col3,col);
	//bot right
	if (d==4) print(lev/2,x-m,y-m,offx+m,offy+m,col,col3);

	//top left
	if (d!=1) print(lev/2,m-1,m-1,offx,offy,col,col3);
	//top right
	if (d!=2) print(lev/2,0,m-1,offx+m,offy,col3,col);
	//bot left
	if (d!=3) print(lev/2,m-1,0,offx,offy+m,col3,col);
	//bot right
	if (d!=4) print(lev/2,0,0,offx+m,offy+m,col,col3);

	if (d==1) print2(0,0,offx+m-1,offy+m-1,2);
	if (d==2) print2(1,0,offx+m-1,offy+m-1,2);
	if (d==3) print2(0,1,offx+m-1,offy+m-1,2);
	if (d==4) print2(1,1,offx+m-1,offy+m-1,2);
}

void printn(int lev,int x,int y,int offx,int offy) {
	if (lev<=4) {
		print(lev,x,y,offx,offy,1,3);
		return;
	}
	int m=lev/2;

	int d=0;
	if (x<m) {
		if (y<m) d=1;
		else d=3;
	} else {
		if (y<m) d=2;
		else d=4;
	}

	//top left
	if (d==1) printn(lev/2,x,y,offx,offy);
	//top right
	if (d==2) printn(lev/2,x-m,y,offx+m,offy);
	//bot left
	if (d==3) printn(lev/2,x,y-m,offx,offy+m);
	//bot right
	if (d==4) printn(lev/2,x-m,y-m,offx+m,offy+m);

	//top left
	if (d!=1) printn(lev/2,m-1,m-1,offx,offy);
	//top right
	if (d!=2) printn(lev/2,0,m-1,offx+m,offy);
	//bot left
	if (d!=3) printn(lev/2,m-1,0,offx,offy+m);
	//bot right
	if (d!=4) printn(lev/2,0,0,offx+m,offy+m);

	if (d==1) print2(0,0,offx+m-1,offy+m-1,2);
	if (d==2) print2(1,0,offx+m-1,offy+m-1,2);
	if (d==3) print2(0,1,offx+m-1,offy+m-1,2);
	if (d==4) print2(1,1,offx+m-1,offy+m-1,2);
}

char tbl[2000][2000];

char eiei[4]={'.','e','x','o'};

int main () {
	int n;
	int x,y;
	scanf("%d%d%d",&n,&x,&y);
	x--;
	y--;
	printn(1<<n,x,y,1,1);
	//for (auto &i:aa) {
		//if (i.d!=2) tbl[i.x+1][i.y]=eiei[i.col];
		//if (i.d!=1) tbl[i.x][i.y]=eiei[i.col];
		//if (i.d!=4) tbl[i.x+1][i.y+1]=eiei[i.col];
		//if (i.d!=3) tbl[i.x][i.y+1]=eiei[i.col];
	//}
	//int nn=1<<n;
	//for (int j=1;j<=nn;j++) {
		//for (int i=1;i<=nn;i++) {
			//printf("%c",tbl[i][j]);
		//}
		//printf("\n");		
	//}
	//printf("%d\n",cnt);
	return 0;
}
