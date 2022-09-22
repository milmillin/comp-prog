#include <cstdio>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct node {
	char x;
	node *par;
	vector<node*> chd;
};

node* null = new node{'0',NULL,vector<node*>()};
node *root;

node* copy(node *id,node *par) {
	node *tmp = new node{id->x,par,vector<node*>()};
	for (int i=0;i<(int)id->chd.size();i++) {
		tmp->chd.push_back(copy(id->chd[i],tmp));
	}
	return tmp;
}

bool change=false;

void replace (node* id, char val, node* to) {
	for (int i=0;i<(int)id->chd.size();i++) {
		if (id->chd[i]->x==val) {
			id->chd[i] = copy(to,id);
			change=true;
		} else {
			if (id->chd[i]->x==toupper(val)) continue;
			replace(id->chd[i],val,to);
		}
	}
}

void mmmm(node *cur,int id) {
	if (cur->x=='+'&&cur->chd[0]->x>='A'&&cur->chd[0]->x<='Z') {
		replace(cur->chd[0],tolower(cur->chd[0]->x),cur->chd[1]);
		node* par = cur->par;
		par->chd[id]=cur->chd[0]->chd[0];
		cur->chd[0]->chd[0]->par=par;
		mmmm(cur->chd[0]->chd[0],id);
	} else {
		for (int i=0;i<(int)cur->chd.size();i++) {
			mmmm(cur->chd[i],i);
		}
	}
}

void print(node *cur) {
	printf("%c",cur->x);
	for (int i=0;i<(int)cur->chd.size();i++) {
		print(cur->chd[i]);
	}
}

int main () {
	string x;
	cin >> x;
	int n = x.length();

	null->par=null;
	
	node *tmp;

	root = new node{'-',null,vector<node*>()};
	node *cur=root;
	//printf("%c\n",root->x);
	for (int i=0;i<n;i++) {
		//printf("%d %c\n",i,x[i]);
		tmp = new node{x[i],cur,vector<node*>()};
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
	
	while (true) {
		change=false;
		mmmm(root->chd[0],0);
		if (!change) break;
	}
	print(root->chd[0]);
	printf("\n");
	return 0;
}
