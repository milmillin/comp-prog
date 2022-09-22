#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

char buf[3000];
int n;

bool check(int x) {
	int cur=0;
	for (int i=0;i<x;i++) {
		if (buf[cur]==buf[i]) {
			cur++;
		} else {
			return false;
		}
	}
	for (int i=0;cur<n;i++) {
		if (buf[cur]==buf[i]) {
			cur++;
		} else {
			return false;
		}
	}
	return true;
}

void f() {
	scanf("%s",buf);
	n=strlen(buf);
	int id=-1;
	for (int i=1;i<n;i++) {
		if (buf[i]==buf[0]) {
			id=i;
			break;
		}		
	}
	if (id==-1) {
		printf("Impossible\n");
	} else {
		if (check(id)) {
			printf("Impossible\n");
		} else {
			for (int i=0;i<id;i++) {
				printf("%c",buf[i]);
			}
			printf("%s\n",buf);
		}
	}
}

int main () {
	int q;
	scanf("%d",&q);
	for (int i=1;i<=q;i++) {
		printf("Case #%d: ",i);
		f();
	}
	return 0;
}
