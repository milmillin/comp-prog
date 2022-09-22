#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

char buf[1000100];
int tbl[100][1000100];

int main () {
	scanf("%s",buf+1);	
	int n=strlen(buf+1);
	for (int i=1;i<=n;i++) {
		tbl[0][i]=buf[i]-'0';
	}
	for (int j=1;j<100;j++) {
		for (int i=1;i<=n;i++) {
			if (tbl[j-1][i]>=2) {
				tbl[j][i]=tbl[j-1][i]-2;
			} else {
				tbl[j][i]=tbl[j-1][i];
			}
			if (tbl[j-1][i-1]>=2) {
				tbl[j][i]++;
			}
			if (tbl[j-1][i+1]>=2) {
				tbl[j][i]++;
			}
			printf("%c",tbl[j][i]?tbl[j][i]+'0':' ');
		}
		printf("\n");
	}

	return 0;
}
