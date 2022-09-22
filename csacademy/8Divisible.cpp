#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int cnt[20];

struct ei {
    string x;
    string xx;
};

bool operator< (const ei &a, const ei &b) {
    if (a.x!=b.x) return a.x>b.x;
    return a.xx<b.xx;
}

vector<ei> tbl;
char buf[30];

int main () {
	string x;
	cin >> x;
	if (x.length()==1) {
		printf("%d\n",(x[0]=='8')?8:-1);
		return 0;
	}
	if (x.length()==2) {
		int aa=x[0]-'0';
		int bb=x[1]-'0';
		if (bb<aa) swap(aa,bb);
		for (int i=0;i<100;i+=8) {
			int a=i%10;
			int b=i/10;
			if (b!=0&&min(a,b)==aa&&max(a,b)==bb) {
				printf("%d\n",i);
				return 0;
			}
		}
		printf("-1\n");
		return 0;
	}
	for (int i=0;i<x.size();i++) {
		cnt[x[i]-'0']++;
	}
	string a,b;
	for (int i=0;i<1000;i+=8) {
		sprintf(buf,"%03d",i);
		a=buf;
		b=a;
		sort(b.begin(),b.end());
		tbl.push_back(ei{b,a});
	}
	sort(tbl.begin(),tbl.end());
	for (auto &a:tbl) {
		//cout << a.xx << endl;
		for (auto &b:a.x) {
			cnt[b-'0']--;
		}
		bool work=true;
		for (int i=0;i<10;i++) {
			if (cnt[i]<0) {
				work=false;
				break;
			}
		}
		if (work) {
			work=false;
			for (int i=1;i<10;i++) {
				if (cnt[i]>0) {
					printf("%d",i);
					cnt[i]--;
					work=true;
					break;
				}
			}
			if (!work&&cnt[0]==0) {
				int cnt=0;
				while (a.xx[cnt]=='0') cnt++;
				if (cnt==0) {
					cout << a.xx << endl;
					return 0;
				}
			}
		}
		if (work) {
			for (int i=0;i<cnt[0];i++) {
				printf("0");
			}
			for (int i=1;i<10;i++) {
				for (int j=0;j<cnt[i];j++) {
					printf("%d",i);
				}
			}
			cout << a.xx;
			printf("\n");
			return 0;
		}
		for (auto &b:a.x) {
			cnt[b-'0']++;
		}
	}
	printf("-1\n");
	return 0;
}
