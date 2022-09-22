#include <cstdio>
#include <vector>

using namespace std;

char tbl[50][50];

struct p {
	int r,c;
	p operator+ (const p &a) {
		return p{r+a.r,c+a.c};
	}
};

vector<vector<p>> type1;
vector<vector<p>> type2;
vector<vector<p>> type3;
vector<vector<p>> type4;
vector<vector<p>> type5;
int cnt[10];

char& at(p idx) {
	return tbl[idx.r][idx.c];
}

bool find (vector<vector<p>> &type,p now) {
	for (auto &ii:type) {
		bool ok=true;
		for (auto &jj:ii) {
			if (at(now)!=at(now+jj)) ok=false;
		}
		if (ok) {
			//printf("sth found at %d %d\n",now.r,now.c);
			at(now)=0;
			for (auto &jj:ii) {
				at(now+jj)=0;
			}
			return true;
		}
	}
	return false;
}

int main () {
	vector<p> fig11;
	fig11.push_back(p{0,1});
	fig11.push_back(p{1,0});
	fig11.push_back(p{1,1});
	type1.push_back(fig11);
	vector<p> fig21;
	fig21.push_back(p{0,1});
	fig21.push_back(p{0,2});
	fig21.push_back(p{0,3});
	type2.push_back(fig21);
	vector<p> fig22;
	fig22.push_back(p{1,0});
	fig22.push_back(p{2,0});
	fig22.push_back(p{3,0});
	type2.push_back(fig22);
	vector<p> fig31;
	fig31.push_back(p{0,1});
	fig31.push_back(p{1,0});
	fig31.push_back(p{1,-1});
	type3.push_back(fig31);
	vector<p> fig32;
	fig32.push_back(p{1,0});
	fig32.push_back(p{1,1});
	fig32.push_back(p{2,1});
	type3.push_back(fig32);
	vector<p> fig41;
	fig41.push_back(p{0,1});
	fig41.push_back(p{1,1});
	fig41.push_back(p{1,2});
	type4.push_back(fig41);
	vector<p> fig42;
	fig42.push_back(p{1,-1});
	fig42.push_back(p{1,0});
	fig42.push_back(p{2,-1});
	type4.push_back(fig42);
	vector<p> fig51;
	fig51.push_back(p{1,-1});
	fig51.push_back(p{1,0});
	fig51.push_back(p{1,1});
	type5.push_back(fig51);
	vector<p> fig52;
	fig52.push_back(p{1,0});
	fig52.push_back(p{1,1});
	fig52.push_back(p{2,0});
	type5.push_back(fig52);
	vector<p> fig53;
	fig53.push_back(p{0,1});
	fig53.push_back(p{1,1});
	fig53.push_back(p{0,2});
	type5.push_back(fig53);
	vector<p> fig54;
	fig54.push_back(p{1,-1});
	fig54.push_back(p{1,0});
	fig54.push_back(p{2,0});
	type5.push_back(fig54);


	int r,c;
	scanf("%d%d",&r,&c);
	for (int i=0;i<r;i++) {
		for (int j=0;j<c;j++) {
			scanf(" %c",&tbl[i+5][j+5]);
		}
	}

	for (int i=5;i<r+5;i++) {
		for (int j=5;j<c+5;j++) {
			if (tbl[i][j]=='.'||tbl[i][j]==0) continue;
			if (find(type1,p{i,j})) cnt[1]++;
			else if (find(type2,p{i,j})) cnt[2]++;
			else if (find(type3,p{i,j})) cnt[3]++;
			else if (find(type4,p{i,j})) cnt[4]++;
			else if (find(type5,p{i,j})) cnt[5]++;

		}
	}
	for (int i=1;i<=5;i++) {
		printf("%d\n",cnt[i]);
	}

	return 0;
}
