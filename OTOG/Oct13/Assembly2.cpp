#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

int a[6]={243,81,27,9,3,1};
int cnt[6];

int a2[8]={128,64,32,16,8,4,2,1};
int cnt2[8];
int op;

vector<string> ans;

void zero() {
	//printf("ZER X\n");
	ans.push_back("ZER X");
	op++;
}

void prn() {
	//printf("PRN X\n");
	ans.push_back("PRN X");
	op++;
}

void one() {
	//printf("ONE X\n");
	ans.push_back("ONE X");
	op++;
}

void push() {
	//printf("PUH X\n");
	ans.push_back("PUH X");
	op++;
}

void pop() {
	//printf("POP X\n");
	ans.push_back("POP X");
	op++;
}

void add() {
	//printf("ADD X\n");
	ans.push_back("ADD X");
	op++;
}

void f2(int x) {
	op=0;
	memset(cnt,0,sizeof(cnt));
	int cntt=0;
	int sig=-1;
	for (int i=0;i<8;i++) {
		cnt2[i]=x/a2[i];
		x%=a2[i];
		if (sig==-1&&cnt2[i]!=0) sig=i;
		//printf("%d ",cnt[i]);
		cntt+=cnt2[i];
	}
	printf("sig %d\n",sig);
	int addCnt=0;
	for (int i=7;i>=0;i--) {
		printf("aa %d\n",a2[i]);
		if (i==7) {
			one();
		} else {
			push();
			push();
			add();
			pop();
		}
		for (int j=0;j<cnt[i];j++) {
			push();
			addCnt++;
			printf("++\n");
		}
		if (sig==i) break;
	}
	for (int i=1;i<addCnt;i++) {
		add();
	}
	pop();
	prn();
	//printf("-- %d\n",op);
}

void f(int x) {
	op=0;
	memset(cnt,0,sizeof(cnt));
	int cntt=0;
	int sig=-1;
	for (int i=0;i<6;i++) {
		cnt[i]=x/a[i];
		x%=a[i];
		if (sig==-1&&cnt[i]!=0) sig=i;
		//printf("%d ",cnt[i]);
		cntt+=cnt[i];
	}
	int addCnt=0;
	for (int i=5;i>=0;i--) {
		if (i==5) {
			one();
		} else {
			push();
			push();
			push();
			add();
			add();
			pop();
		}
		for (int j=0;j<cnt[i];j++) {
			push();
			addCnt++;
		}
		if (sig==i) break;
	}
	for (int i=1;i<addCnt;i++) {
		add();
	}
	pop();
	prn();
	//printf("-- %d\n",op);
}

int main () {
	//int mx=0;
	//for (int i=0;i<256;i++) {
		//f(i);
		//int a=op;
		//f2(i);
		//int b=op;
		//mx=max(mx,min(a,b));
	//}
	//printf("max %d\n",mx);
	vector<string> tmp;
	for (int x=11;x<12;x++) {
		if (x==0) {
			printf("ZER X\nPRN X\n");
			continue;
		}
		ans.clear();
		f(x);
		tmp=ans;
		ans.clear();
		f2(x);
		if (ans.size()<tmp.size()) {
			printf("aa\n");
			for (auto &i:ans) {
				cout << i << endl;
			}
		} else {
			printf("bb\n");
			for (auto &i:tmp) {
				cout << i << endl;
			}
		}

	}
	return 0;
}
