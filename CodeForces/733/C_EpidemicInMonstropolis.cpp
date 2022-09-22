#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int wgt[600];

int main() {
	int n;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		scanf("%d",&wgt[i]);
	}
	int k;
	scanf("%d",&k);
	int x;
	int cur=1;
	int curr;
	int sum=0;
	int st;
	bool dif;
	vector<int> ans1;
	vector<char> ans2;
	for (int i=0;i<k;i++) {
		scanf("%d",&x);
		sum=0;
		curr=0;
		st=cur;
		dif=false;
		while (cur<=n) {
			sum+=wgt[cur];
			//printf("%d\n",sum);
			//printf("%d\n",cur);
			if (curr&&wgt[cur]!=wgt[cur-1])dif=true;
			if (sum>x) {
				//printf("a\n");
				printf("NO\n");
				return 0;
			} else if (sum==x) {
				//check repeat
				if (curr&&dif==false) {
					//printf("b");
					printf("NO\n");
					return 0;
				}
				curr++;
				cur++;
				break;
			}
			curr++;
			cur++;
		}
		if (sum!=x) {
			//printf("c\n");
			printf("NO\n");
			return 0;
		}
		int maxx=0;
		int idx=-1;
		int idx2=-1;
		for (int j=st;j<cur;j++) {
			maxx=max(maxx,wgt[j]);
		}
		
		for (int j=st;j<cur;j++) {
			if (wgt[j]==maxx) {
				if (j!=cur-1&&wgt[j]!=wgt[j+1])	{
					for (int k=j;k<cur-1;k++) {
						ans1.push_back(j+i-st+1);
						ans2.push_back('R');
					}
					for (int k=j;k>st;k--) {
						ans1.push_back(k+i-st+1);
						ans2.push_back('L');
					}
					break;
				}
				if (j!=st&&wgt[j]!=wgt[j-1]) {
					for (int k=j;k>st;k--) {
						ans1.push_back(k+i-st+1);
						ans2.push_back('L');
					}
					for (int k=j;k<cur-1;k++) {
						ans1.push_back(i+1);
						ans2.push_back('R');
					}
					break;
				}
			}
		}

		//for (int j=idx;j>=2;j--) {
			//ans1.push_back(j+i);
			//ans2.push_back('L');
		//}
		//for (int j=0;j<left;j++) {
			//ans1.push_back(i+1);
			//ans2.push_back('R');
		//}
	}
	if (cur!=n+1) {
		printf("NO\n");
		return 0;
	}
	printf("YES\n");
	for (int i=0;i<ans1.size();i++) {
		printf("%d %c\n",ans1[i],ans2[i]);
	}
	return 0;
}
