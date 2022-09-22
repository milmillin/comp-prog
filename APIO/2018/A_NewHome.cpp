#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct store {
	int x,a,b;
};

int n,k,q;
int main () {
	scanf("%d%d%d",&n,&k,&q);
	vector<store> tbl(n);
	for (int i=0;i<n;i++) {
		scanf("%d%d%d",&tbl[i].x,&tbl[i].a,&tbl[i].b);
	}	
	return 0;
}
