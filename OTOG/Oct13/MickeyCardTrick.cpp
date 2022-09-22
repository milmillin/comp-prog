#include <cstdio>

using namespace std;

bool used[10][10];

void p(int i,int j,int k) {
	used[i][j]=true;
	printf("%d %d %d\n",i,j,k);
}

int main () {
	for (int i=1;i<=8;i++) {
		for (int j=i+1;j<=8;j++) {
			for (int k=j+1;k<=8;k++) {
				if (!used[i][j]) p(i,j,k);
				else if (!used[j][i]) p(j,i,k);
				else if (!used[i][k]) p(i,k,j);
				else if (!used[k][i]) p(k,i,j);
				else if (!used[j][k]) p(j,k,i);
				else if (!used[k][j]) p(k,j,i);
				else printf("fuck\n");
			}
		}
	}
	return 0;
}
