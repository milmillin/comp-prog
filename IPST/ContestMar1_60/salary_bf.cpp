#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int s[100100];
vector<int> pth[100100];
map<int,int> mic[100100];

int solve(int idx,int mx) {
	auto it = mic[idx].find(mx);
	if (it!=mic[idx].end()) return it->second; 
	if (s[idx]>mx) {
		int sum=1;
		for (auto i:pth[idx]) {
			sum+=solve(i,mx);
		}	
		mic[idx][mx]=sum;
		return sum;
	}
	//change this
	int sum1=1;
	for (auto i:pth[idx]) {
		sum1+=solve(i,mx);
	}
	//not change this
	int sum2=0;
	for (auto i:pth[idx]) {
		sum2+=solve(i,s[idx]);
	}
	sum1=min(sum1,sum2);
	mic[idx][mx]=sum1;
	return sum1;
}

int main () {
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		scanf("%d",&s[i]);
	}
	int a,b;
	for (int i=1;i<n;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
	}
	printf("%d\n",solve(0,1e9));
	return 0;
}
