#include <cstdio>
#include <algorithm>

using namespace std;

char buf[4010];

bool work(int a,int b,int len1,int len2) {
	int len=min(len1,len2);
	for (int i=0;i<len;i++) {
		//printf("%c %c\n",buf[a+i],buf[b+i]);
		if (buf[a+i]=='.'&&buf[b+i]=='.') return true;
		if (buf[a+i]!=buf[b+i]) return true;
	}
	return false;
}

void adjust(int a,int b,int len1,int len2) {
	int len=min(len1,len2);
	for (int i=0;i<len;i++) {
		if (buf[a+i]==buf[b+i]&&buf[a+i]!='.') continue;
		else if (buf[a+i]=='.'&&buf[b+i]=='.') {
			buf[a+i]='1';
			buf[b+i]='0';
		} else if (buf[a+i]=='.') {
			if (buf[b+i]=='1') buf[a+i]='0';
			else buf[a+i]='1';
		} else {
			if (buf[a+i]=='1') buf[b+i]='0';
			else buf[b+i]='1';
		}
	}
}

void print() {
	for (int i=0;buf[i]!=0;i++) {
		if (buf[i]!='.') printf("%c",buf[i]);
		else printf("1");
	}
	printf("\n");
}

int main () {
	int n,p;
	scanf("%d%d",&n,&p);
	scanf("%s",buf);	
	int round=n/p;
	for (int i=1;i<round;i++) {
		if (work((i-1)*p,i*p,p,p)) {
			adjust((i-1)*p,i*p,p,p);
			print();
			return 0;
		}
	}
	if (round) {
		if (work((round-1)*p,round*p,p,n%p)) {
			adjust((round-1)*p,round*p,p,n%p);
			print();
			return 0;
		}
	}
	printf("No\n");
	return 0;
}
