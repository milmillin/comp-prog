#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

char a[5]={'0','0','0','1',0};
char b[5]={'0','0','1','1',0};
char c[5]={'0','1','1','1',0};

int main () {
	vector<int> tbl;
	tbl.push_back(0);
	tbl.push_back(1);
	tbl.push_back(2);
	tbl.push_back(3);
	
	do {
		printf("%d%d%d%d %c%c%c%c %c%c%c%c %c%c%c%c\n",tbl[0],tbl[1],tbl[2],tbl[3],a[tbl[0]],a[tbl[1]],a[tbl[2]],a[tbl[3]],b[tbl[0]],b[tbl[1]],b[tbl[2]],b[tbl[3]],c[tbl[0]],c[tbl[1]],c[tbl[2]],c[tbl[3]]);
	} while (next_permutation(tbl.begin(),tbl.end()));

	return 0;
}
