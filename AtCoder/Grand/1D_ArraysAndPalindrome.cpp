#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	vector<int> odd;
	deque<int> even;
	int x;
	for (int i=0;i<m;i++) {
		scanf("%d",&x);
		if (m==1) {
			if (x==1) {
				printf("1\n1\n1\n");
				return 0;
			}
			printf("%d\n2\n%d %d\n",x,x-1,1);
			return 0;
		}
		if (x%2) odd.push_back(x);
		else even.push_back(x);
	}
	if (odd.size()>2) {
		printf("Impossible\n");
		return 0;
	}
	if (odd.size()>0) {
		even.push_front(odd[0]);
	}
	if (odd.size()>1) {
		even.push_back(odd[1]);
	}
	for (auto it:even) {
		printf("%d ",it);
	}
	even.front()--;
	even.back()++;
	if (even.front()==0) even.pop_front();
	printf("\n%d\n",even.size());
	for (auto it:even) {
		printf("%d ",it);
	}
	printf("\n");
	return 0;
}
