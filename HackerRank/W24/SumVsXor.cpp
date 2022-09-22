#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;


int main(){
    long long n;
    cin >> n;
	if (n==0) {
		printf("1\n");
		return 0;
	}
    long long i=1ll<<62;
    while ((n&i)==0) i=i>>1;
	i--;
    i=i^(n&i);
    //printf("%lld\n",i);
	long long ans=1;
    for (int ii=0;ii<63;ii++) {
        if (i&(1ll<<ii)) ans*=2;
    }
    printf("%lld\n",ans);
    return 0;
}

