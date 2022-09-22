#include <cstdio>
#include <queue>

using namespace std;

int main () {
	int n,l,h;
	scanf("%d%d%d",&n,&l,&h);
	int a,b,x,y;
	double cut;
	priority_queue<int> q;
	for (int i=0;i<n;i++) {
		scanf("%d",&a);
		for (int j=0;j<a;j++) {
			scanf("%d",&b);
			q.push(b);
		}
		scanf("%d%d",&x,&y);
		cut = (double)x/y*h+l;
		while (!q.empty()&&(double)q.top()>=cut) q.pop();
		printf("%d\n",q.size());
	}
	return 0;
}
