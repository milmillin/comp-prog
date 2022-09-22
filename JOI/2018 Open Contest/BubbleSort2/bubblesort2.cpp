#include "bubblesort2.h"

#ifdef debug
#include "grader.cpp"
#endif

#include <algorithm>
#include <set>

int tbl[500100];

bool cmp(int a,int b) {
	if (tbl[a]!=tbl[b]) return tbl[a]<tbl[b];
	return a<b;
}

std::set<int> ids[150];

std::vector<int> countScans(std::vector<int> A,std::vector<int> X,std::vector<int> V){
	int n=A.size();
	
	std::vector<int> id(n);
	int ei=0;
	for (int i=0;i<n;i++) {
		tbl[i]=A[i];
		id[i]=i;
		ei=std::max(ei,tbl[i]);
	}	

	bool isSmall=ei<=100;

	if (isSmall) {
		for (int i=0;i<n;i++) {
			ids[tbl[i]].insert(i);
		}
	}

	int q=X.size();
	std::vector<int> answer(q);


	for (int j=0;j<q;j++) {
		if (isSmall) {
			ids[tbl[X[j]]].erase(X[j]);
			tbl[X[j]]=V[j];
			ids[tbl[X[j]]].insert(X[j]);	
			int cnt=0;
			int mx=0;
			int ans=0;
			for (int i=0;i<=ei;i++) {
				cnt+=ids[i].size();
				if (!ids[i].empty()) mx=std::max(mx,*ids[i].rbegin());
				ans=std::max(ans,mx-cnt+1);
			}
			answer[j]=ans;
		} else {
			tbl[X[j]]=V[j];
			std::sort(id.begin(),id.end(),cmp);
			int mx=0;
			int ans=0;
			for (int i=1;i<n;i++) {
				mx=std::max(mx,id[i-1]);
				ans=std::max(ans,mx-i+1);
			}	

			answer[j]=ans;
		}
	}
	return answer;
}
