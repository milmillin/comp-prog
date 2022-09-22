#include <cstdio>

using namespace std;

int freq[30];
int idx[30];

char tbl[3][20];

char org[30];

int main () {
	char x;
	int dif;
	int fst,lst;
	//int maxx=0;
	for (int i=0;i<27;i++) {
		scanf(" %c",&x);
		org[i]=x;
		
		if (freq[x-'A']) {
			fst=idx[x-'A'];
			lst=i;
			dif=lst-fst;
		}
		idx[x-'A']=i;
		freq[x-'A']++;
	}
	if (dif==1) {
		printf("Impossible\n");
		return 0;
	}
	if (dif%2) {
		dif/=2;
		int cur=fst;
		for (int i=12-dif;i>=0&&cur>=0;i--,cur--) {
			tbl[1][i]=org[cur];
		}
		if (cur>=0) {
			for (int i=0;cur>=0;i++,cur--) {
				tbl[0][i]=org[cur];
			}
		}
		cur=fst+1;
		for (int i=13-dif;i<13;i++,cur++) {
			tbl[0][i]=org[cur];
		}
		for (int i=12;i>=12-dif;i--,cur++) {
			tbl[1][i]=org[cur];
		}
		for (int i=12-dif;i>=0&&cur<27;i--,cur++) {
			tbl[0][i]=org[cur];
		}
		for (int i=0;cur<27;cur++,i++) {
			tbl[1][i]=org[cur];
		}
	} else {
		dif--;
		dif/=2;
		int cur=fst;
		for (int i=12-dif;i>=0&&cur>=0;i--,cur--) {
			tbl[1][i]=org[cur];
		}
		if (cur>=0) {
			for (int i=0;cur>=0;i++,cur--) {
				tbl[0][i]=org[cur];
			}
		}
		cur=fst+1;
		for (int i=12-dif;i<13;i++,cur++) {
			tbl[0][i]=org[cur];
		}
		for (int i=12;i>=12-dif;i--,cur++) {
			tbl[1][i]=org[cur];
		}
		for (int i=11-dif;i>=0&&cur<27;i--,cur++) {
			tbl[0][i]=org[cur];
		}
		for (int i=0;cur<27;cur++,i++) {
			tbl[1][i]=org[cur];
		}
	}
	
	for (int i=0;i<2;i++) {
		for (int j=0;j<13;j++) {
			printf("%c",tbl[i][j]);
		}
		printf("\n");
	}
	/*
	for (int i=0;i<26;i++) {
		printf("%d ",freq[i]);
	}
	printf("\n");
	*/
	return 0;
}
