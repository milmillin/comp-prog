#include <cstdio>
#include <algorithm>

using namespace std;

int main () {
	long long a,b,c;
	scanf("%I64d%I64d%I64d",&a,&b,&c);
	long long maxx = max(a,max(b,c));
	long long spc=3*(maxx-1);

	int cnt=0;
	if (a==maxx) spc-=maxx-1;
	else spc-=a;
	if (b==maxx) spc-=maxx-1;
	else spc-=b;
	if (c==maxx) spc-=maxx-1;
	else spc-=c;

	printf("%I64d\n",spc);
	/*
	if (a==maxx) {
		if (b==maxx) {
			spc-=(maxx-1);
			if (c==maxx) {
				printf("0\n");
			} else {
				spc-=c;
				printf("%I64d\n",spc);
			}
		} else {
			spc-=b;
			if (c==maxx) {
				spc-=(maxx-2);
				printf("%I64d\n",spc);
			} else {
				spc-=c;
				printf("%I64d\n",spc);
			}
		}
	} else {
		
	}
	printf("%I64d\n",spc);
	*/
	return 0;
}
