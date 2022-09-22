#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

int tbl[100];

int main() {
    string x;
    cin >> x;
    int n = x.length();
    for (int i=0;i<n-1;i++) {
        scanf("%d",&tbl[n-i-1]);
    }
	long long ans=1;
	for (int i=n-1;i>=0;i--) {
		if (tbl[i]==0) {
			//printf("%d\n",(x[i]-'0'+1-(tbl[i+1])));
			ans*=(x[i]-'0'+1-(tbl[i+1]));
		} else{
			//printf("%d\n",(19-(10+x[i]-'0'-tbl[i+1])));
			ans*=(19-(10+x[i]-'0'-tbl[i+1]));
		}
	}
	printf("%lld\n",ans);
}
