#include <cstdio>

using namespace std;

void print2(int r,int c) {
	printf("%d %d 1\n",r+1,c);
}

void print23(int r,int c) {
	printf("%d %d 1\n",r+1,c);
	printf("%d %d 3\n",r,c+2);
}

void print23mn(int r,int c,int m,int n) {
	for (int i=0;i<m;i++) {
		for (int j=0;j<n;j++) {
			print23(r+i*2,c+j*3);
		}
	}
}

void print6(int r,int c) {
	printf("%d %d 1\n",r+1,c);
	printf("%d %d 1\n",r+3,c+2);
	printf("%d %d 1\n",r+5,c+4);
	printf("%d %d 1\n",r+5,c);
	printf("%d %d 1\n",r+4,c+1);
	printf("%d %d 2\n",r+2,c);
	printf("%d %d 4\n",r+5,c+3);
}

void print9(int r,int c) {
	printf("%d %d 1\n",r+1,c);
	printf("%d %d 1\n",r+3,c+2);
	printf("%d %d 3\n",r+4,c+4);
	printf("%d %d 1\n",r+6,c+5);
	printf("%d %d 1\n",r+8,c+7);
	printf("%d %d 1\n",r+6,c);
	printf("%d %d 1\n",r+8,c);
	printf("%d %d 1\n",r+6,c+3);
	printf("%d %d 1\n",r+8,c+4);
	printf("%d %d 2\n",r+2,c);
	printf("%d %d 3\n",r+7,c+6);
	printf("%d %d 4\n",r+4,c+1);
	printf("%d %d 4\n",r+5,c+2);
	printf("%d %d 4\n",r+7,c+2);
	printf("%d %d 4\n",r+8,c+3);
}

void print(int n) {
	if (n==2) {
		print2(1,1);
		return;
	}
	if (n==6) {
		print6(1,1);
		return;
	}
	if (n==9) {
		print9(1,1);
		return;
	}
	if (n%6==2||n%6==5) {
		n-=2;
		print2(1+n,1+n);
		print23mn(1+n,1,1,n/3);
		print(n);
		return;
	}
	
	n-=6;
	print6(1+n,1+n);
	print23mn(1+n,1,3,n/3);
	print(n);
	return;
}

int main() {
	int n;
	scanf("%d",&n);
	if (n%6==1||n%6==4||n==3||n==5) {
		printf("NO\n");
		return 0;
	}
	print(n);
	return 0;
}
