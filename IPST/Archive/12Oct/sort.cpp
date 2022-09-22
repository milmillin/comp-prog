#include <cstdio>
#include <algorithm>

using namespace std;

void insert(int *st,int *end) {
	if (st==end) return;
	if (*st>*(st+1)) {
		swap(*(st+1),*st);
		insert(st+1,end);
	}
	return;
}

int tbl[2000];
int n;

void srt(int *st,int *end) {
	if (st==end) return;
	srt(st+1,end);
	insert(st,end);
	//for (int i=0;i<n;i++) {
	//	printf("%d ",tbl[i]);
	//}
	//printf("\n");
}

int main () {
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		scanf("%d",tbl+i);
	}
	srt(tbl,tbl+n-1);
	for (int i=0;i<n;i++) {
		printf("%d\n",tbl[i]);
	}
	return 0;
}
