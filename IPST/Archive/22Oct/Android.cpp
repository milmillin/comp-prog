#include <cstdio>
#include <queue>

using namespace std;

int mem[1010];
int lastUsed[1010];
bool isOpen[1010];
deque<int> prog,timee;

int main () {
	int p,s,m;
	scanf("%d%d%d",&p,&s,&m);
	for (int i=1;i<=p;i++) {
		scanf("%d",&mem[i]);
	}
	int x;
	for (int i=0;i<s;i++) {
		scanf("%d",&x);
		if (isOpen[x]) {
			lastUsed[x]=i;
			prog.push_back(x);
			timee.push_back(i);
			continue;
		}
		while (m<mem[x]) {
			while (!prog.empty()&&(!isOpen[prog.front()]||timee.front()<lastUsed[prog.front()])) {
				//printf("pop %d\n",prog.front());
				prog.pop_front();
				timee.pop_front();
			}
			m+=mem[prog.front()];
			isOpen[prog.front()]=false;
			//printf("close %d\n",prog.front());
			prog.pop_front();
			timee.pop_front();
		}
		isOpen[x]=true;
		m-=mem[x];
		//printf("open %d\n",x);
		prog.push_back(x);
		timee.push_back(i);
		lastUsed[x]=i;
		//printf("%d\n",m);
	}
	printf("%d\n",m);
	return 0;
}

