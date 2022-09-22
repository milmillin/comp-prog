#include <cstdio>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct node {
	char x;
	node *par;
	vector<node*> chd;
	vector<bool> con;
	int dp0,dp1;
};

node* null = new node{'0',NULL,vector<node*>(),vector<bool>(256,false),0,0};
node *root;

void print(node *cur) {
	printf("%c",cur->x);
	for (int i=0;i<(int)cur->chd.size();i++) {
		print(cur->chd[i]);
	}
}

void uni(vector<bool> &a, vector<bool> &b) {
	for (int i=0;i<(int)a.size();i++) {
		a[i]=a[i]||b[i];
	}
}


void initContains(node *a) {
	if (a->x>='a'&&a->x<='z') {
		a->con[a->x-'a']=true;
		return;
	}
	for (int i=0;i<(int)a->chd.size();i++) {
		initContains(a->chd[i]);
		uni(a->con,a->chd[i]->con);
	}
}

pair<int,int> mic(node *a) {
	if (a->x!='+') return mic(a->chd[0]);
	//sel
	auto left = mic(a->chd[0]);
	auto rgt = mic(a->chd[1]);

	int mx1=1;
	if (isupper(a->chd[0]->x)&&a->chd[0]->con[tolower(a->chd[0]->x)-'a']) {
		mx1+=max(left.first,left.second);
	} else {
		mx1+=max(left.first,left.second)+max(rgt.first,rgt.second);
	}

	int mx0;
	mx0=max(left.first,left.second)+max(rgt.first,rgt.second);
}


int main () {
	string x;
	cin >> x;
	int n = x.length();

	null->par=null;
	
	node *tmp;

	root = new node{'-',null,vector<node*>(),vector<bool>(256,false),0,0};
	node *cur=root;
	//printf("%c\n",root->x);
	for (int i=0;i<n;i++) {
		//printf("%d %c\n",i,x[i]);
		tmp = new node{x[i],cur,vector<node*>(),vector<bool>(256,false),0,0};
		cur->chd.push_back(tmp);
		cur=cur->chd.back();	
		while (true) {
			//printf("%c %d\n",cur->x,cur->chd.size());
			//break;
			if (cur->x>='a'&&cur->x<='z') cur=cur->par;
			else if (cur->x=='+') {
				if (cur->chd.size()==2) cur=cur->par;
				else {
					//printf("yeah\n");
					break;
				}
			} else {
				if (cur->chd.size()==1) cur=cur->par;
				else break;
			}
		}
	}
	
	initContains(root->chd[0]);
	return 0;
}
