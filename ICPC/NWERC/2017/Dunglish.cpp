#include <cstdio>
#include <algorithm>
#include <string>
#include <map>
#include <iostream>

using namespace std;

string tbl[50];
int id[50];

int cor[100100];
int all[100100];

map<string,int> comp;
map<string,int> _cor;
map<string,int> _all;

map<string,string> trans;

int main () {
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		cin >> tbl[i];
	}
	int m;
	scanf("%d",&m);
	string d,e,c;
	for (int i=0;i<m;i++) {
		cin >> d >> e >> c;
		trans[d]=e;
		comp[d];
		if (c=="correct") {
			_cor[d]++;
			_all[d]++;
		} else {
			_all[d]++;
		}
	}

	int cur=0;
	for (auto &i:comp) {
		i.second=cur++;
	}

	for (int i=0;i<n;i++) {
		id[i]=comp[tbl[i]];
	}

	for (auto &i:_cor) {
		cor[comp[i.first]]=i.second;
	}

	for (auto &i:_all) {
		all[comp[i.first]]=i.second;
	}

	//count correct
	long long correct=1;
	for (int i=0;i<n;i++) {
		correct*=cor[id[i]];
	}

	long long wrong=1;
	for (int i=0;i<n;i++) {
		wrong*=all[id[i]];
	}
	wrong-=correct;

	if (wrong+correct==1) {
		for (int i=0;i<n;i++) {
			cout << trans[tbl[i]] << " ";
		}
		printf("\n");
		printf("%s\n",wrong?"incorrect":"correct");
	} else {
		printf("%lld correct\n%lld incorrect\n",correct,wrong);

	}

	return 0;
}
