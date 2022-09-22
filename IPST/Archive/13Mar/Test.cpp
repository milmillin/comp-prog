#include <cstdio>
#include <vector>

using namespace std;

struct ei {
	int x,y;
};
vector<ei> tbl;

int main () {
	for (int i=0;i<10;i++) {
		tbl.push_back(ei{i,i+1});
		//printf("%d\n",tbl[i]);
		//tbl.push_back(5);
	}

	for (int i=0;i<10;i++) {
		printf("%d %d\n",tbl[i].x,tbl[i].y);
	}
	int n;
	for (int i=0;i<10;i++) {
		printf("%d\n",tbl[i].x);	
		tbl.push_back(ei{1,2});	
		scanf("%d",&n);		
	}	
	return 0;
}
