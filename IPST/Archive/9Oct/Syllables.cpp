#include <cstdio>
#include <cstring>

using namespace std;

bool isvowel(char x) {
	if (x=='a'||x=='e'||x=='i'||x=='o'||x=='u') return true;
	return false;
}

int main () {
	int n;
	scanf("%d",&n);
	char x[40];
	int len,cnt;
	while (n--) {
		scanf("%s",x);
		len = strlen(x);
		cnt=0;
		for (int i=0;i<len;i++) {
			if (isvowel(x[i])&&!isvowel(x[i+1])) cnt++;
		}
		printf("%d\n",cnt);
	}
	return 0;
}
