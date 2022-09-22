#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

void f() {
	int w,b,m;
	scanf("%d%d%d",&w,&b,&m);
	
	char board[4][4];
	int size[4][4] //0 none 1 white
	memset(board,0,sizeof(board));
	char t,c;
	int r;
	for (int i=0;i<w;i++) {
		scanf(" %c %c%d",&t,&c,&r);
		board[c-'A'][r-1]=t;
	}
	for (int i=0;i<b;i++) {
		scanf(" %c %c%d",&t,&c,&r);
		board[c-'A'][r-1]=t;
	}
	for (int i=0;i<4;i++) {
		for (int j=0;j<4;j++) {
			printf("%c",(board[i][j])?board[i][j]:' ');
		}
		printf("\n");
	}
	

}

int main () {
	int q;
	scanf("%d",&q);
	while (q--) f();
	return 0;
}
