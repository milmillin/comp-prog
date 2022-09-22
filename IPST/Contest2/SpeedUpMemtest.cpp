#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

struct edge{
	int idx,wgt;
};

struct ei {
	int idx;
	long long wgt;
	int lev,last;
};

bool operator< (const ei &a, const ei &b) {
	return a.wgt>b.wgt;
}

priority_queue<ei> q;
vector<edge> pth[100100];
bool isSpc[100100];
int id[100100];
int spc[20];
long long dis[100100][10];

int main () {
	
	return 0;
}
