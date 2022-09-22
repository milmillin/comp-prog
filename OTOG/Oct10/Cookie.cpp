#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

struct node {
	int val;
	node *l,*r;
};

int ans[100100];
char x[100100];
int cnt=1;

void dep (node *idx) {
	if (idx==NULL) return;
	if (idx->val==-1) return;
	dep (idx->l);
	//printf("** %d\n",idx->val);
	ans[idx->val]=cnt++;
	dep (idx->r);
}


int main () {
	node* root=new node {-1,NULL,NULL};
	int n;
	scanf("%d",&n);
	//string x;
	node* cur=root;
	for (int i=0;i<n;i++) {
		cur=root;
		scanf("%s",x);
		for (int j=0;x[j]!=0;j++) {
			//printf("** %d\n",cur->val);
			if (x[j]=='*') cur->val=i;
			else if (x[j]=='R') {
				if (cur->r==NULL) cur->r=new node{-1,NULL,NULL};
				cur=cur->r;
			} else if (x[j]=='L') {
				if (cur->l==NULL) cur->l=new node {-1,NULL,NULL};
				cur=cur->l;
			}
		}
	}
	dep(root);
	for (int i=0;i<n;i++) {
		printf("%d\n",ans[i]);
	}
	return 0;
}
