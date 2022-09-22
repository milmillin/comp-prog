#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

char buf[300];

int main () {
	scanf("%s",buf);
	int n=strlen(buf);
	string x;
	for (int i=1;i<n-1;i++) {
		x.push_back(buf[i-1]);
		x.push_back(buf[i]);
		x.push_back(buf[i+1]);
		sort(x.begin(),x.end());
		if (x=="ABC") {
			printf("Yes\n");
			return 0;
		}
		x.clear();
	}
	printf("No\n");
	return 0;
}
