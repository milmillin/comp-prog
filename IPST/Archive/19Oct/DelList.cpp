#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>

using namespace std;

struct ei{
	int val,idx;
	//int del;
	//vector<int> del;
};

unordered_map<int,int> mp;

bool operator< (const ei &a, const ei &b) {
	return a.val<b.val;
}

bool cmp (const ei &a, const ei &b) {
	return a.idx<b.idx;
}

vector<ei> item[100100];

int reff[100100];

vector<int> rem[100100];
vector<int> del[100100];
int nxt[100100];
int endd[100100];

int main () {
	int n,k;
	ios_base::sync_with_stdio(false);
	//scanf("%d%d",&n,&k);
	cin>>n>>k;
	int m;
	for (int i=1;i<=n;i++) {
		//scanf("%d",&m);
		cin>>m;
		int x;
		for (int j=0;j<m;j++) {
			//scanf("%d",&x);
			cin>>x;
			item[i].push_back(ei{x,j});
		}
		//sort(item[i].begin(),item[i].end());
		reff[i]=i;
		nxt[i]=-1;
		endd[i]=i;
	}
	int a,b,c;
	for (int i=0;i<k;i++) {
		//scanf("%d%d%d",&a,&b,&c);
		cin>>a>>b>>c;
		if (a==1) {
			//erase c from b;
			int cur=reff[b];
			if (reff[b]==-1) continue;
			rem[reff[b]].push_back(c);
			del[endd[reff[b]]].push_back(c);
			//while (cur!=-1) {
				//lower_bound(item[cur].begin(),item[cur].end(),ei{c,0,0})->del++;
				//upper_bound(item[cur].begin(),item[cur].end(),ei{c,0,0})->del--;
			//	cur=nxt[cur];
			//}
		} else {
			//b appends c
			if (reff[b]==-1) {
				swap(reff[b],reff[c]);
			} else {
				nxt[endd[reff[b]]]=reff[c];
				endd[reff[b]]=endd[reff[c]];
				reff[c]=-1;
				//printf("**%d\n",c);
			}
		}
	}
	//printf("yay\n");
	for (int i=1;i<=n;i++) {
		int cur=reff[i];
		//printf("--%d\n",cur);
		while (cur!=-1) {
			/*
			int now=0;
			for (int j=0;j<item[cur].size();j++) {
				now+=item[cur][j].del;
				item[cur][j].del=now;
			}
			sort(item[cur].begin(),item[cur].end(),cmp);
			for (int j=0;j<item[cur].size();j++) {
				if (item[cur][j].del) continue;
				printf("%d\n",item[cur][j].val);
			}
			*/
			for (int j=0;j<rem[cur].size();j++) {
				mp[rem[cur][j]]++;
			}
			for (int j=0;j<item[cur].size();j++) {
				if (mp[item[cur][j].val]) continue;
				printf("%d\n",item[cur][j].val);
			}
			for (int j=0;j<del[cur].size();j++) {
				mp[del[cur][j]]--;
			}
			cur=nxt[cur];
		}
	}
	return 0;
}
