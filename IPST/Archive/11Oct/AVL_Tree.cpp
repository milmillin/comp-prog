#include <cstdio>
#include <vector>
#include <cstdlib>

using namespace std;

class node {
	public:
		int val,hgt;
		node *left,*right,*par;
		node() {
			hgt=0;
			left=right=nullptr;;
			par=this;
		}
		node(int x) {
			hgt=0;
			val=x;
			left=right=nullptr;
			par=this;
		}
};

class AVL {
	private:
		node* root;
	protected:	
		int getHgt(node *a) {
			if (a==nullptr) return -1;
			return a->hgt;
		}
		
		int getBalance(node *a) {
			if (a==nullptr) return 0;
			return getHgt(a->left)-getHgt(a->right);
		}

		bool _push(node *a,vector<bool> &isRgt) {
			node* cur = root;
			while (true) {
				if (a->val==cur->val) return false;
				else if (a->val>cur->val) {
					isRgt.push_back(true);
					if (cur->right==nullptr) {
						cur->right=a;
						a->par=cur;
						return true;
					} else cur=cur->right;
				} else {
					isRgt.push_back(false);
					if (cur->left==nullptr) {
						cur->left=a;
						a->par=cur;
						return true;
					} else cur=cur->left;
				}
			}
		}

		node* leftRotate(node* a) {
			node* tmpB = a->right;
			node* tmpPar = a->par;
			a->right=tmpB->left;
			tmpB->par=tmpB;
			if (tmpB->left!=nullptr) tmpB->left->par=a;
			tmpB->left=a;
			a->par=tmpB;
			a->hgt=max(getHgt(a->left),getHgt(a->right))+1;
			tmpB->hgt=max(getHgt(tmpB->left),getHgt(tmpB->right))+1;
			if (a==root) root=tmpB;
			else tmpB->par=tmpPar;
			return tmpB;
		}

		node* rightRotate(node* a) {
			node* tmpB = a->left;
			node* tmpPar = a->par;
			a->left=tmpB->right;
			tmpB->par=tmpB;
			if (tmpB->right!=nullptr) tmpB->right->par=a;
			tmpB->right=a;
			a->par=tmpB;
			a->hgt=max(getHgt(a->left),getHgt(a->right))+1;
			tmpB->hgt=max(getHgt(tmpB->left),getHgt(tmpB->right))+1;
			if (a==root) root=tmpB;
			else tmpB->par=tmpPar;
			return tmpB;			
		}
	public:
		bool find (int x) {
			node* cur=root;
			while (cur!=nullptr) {
				if (x==cur->val) return true;
				else if (x<cur->val) cur=cur->left;
				else if (x>cur->val) cur=cur->right;
			}
			return false;
		}
		void insert(int x) {
			//printf("%d\n",x);
			//Create Node
			node* a = new node(x);
			
			//Perform BST
			vector<bool> isRgt;
			if (root==nullptr) {
				root=a;
				return;
			} else {
				bool inserted=_push(a,isRgt);
			}
			//printf("Done insertion\n");
			//Balance
			node* cur=a->par;
			int balan;
			
			isRgt.pop_back();	

			while (true) {
				//printf("-%d\n",cur->val);
				cur->hgt=max(getHgt(cur->left),getHgt(cur->right))+1;
				balan=getBalance(cur);
				
				//system("pause");

				if (balan>1 && x < cur->left->val) {
					//left left
					//printf("LL\n");
					cur=rightRotate(cur);
				} else if (balan>1 && x > cur->left->val) {
					//left right
					//printf("LR\n");
					cur->left = leftRotate(cur->left);
					cur=rightRotate(cur);
				} else if (balan<-1 && x <cur->right->val) {
					//right left
					//printf("RL\n");
					cur->right = rightRotate(cur->right);
					cur=leftRotate(cur);
				} else if (balan<-1 && x >cur->right->val) {
					//right right;
					//printf("RR\n");
					cur=leftRotate(cur);
				}

				//printf("%s\n",(isRgt.back())?"right":"left");
				//isRgt.pop_back();
				if (cur==root) break;	

				if (isRgt.back()) {
					cur->par->right=cur;
				} else {
					cur->par->left=cur;
				}

				isRgt.pop_back();
				
				//printf("Yay\n");

				cur=cur->par;
			}
						
		}

		node* getRoot() {
			return root;
		}

		AVL() {
			root=nullptr;
		}
};

int main () {
	/*
	AVL avl;
	avl.insert(1);
	avl.insert(2);
	avl.insert(3);
	printf("%d\n",avl.getRoot()->hgt);
	*/
	AVL avl;
	int n,m;
	scanf("%d%d",&n,&m);
	int x;
	for (int i=0;i<n;i++) {
		scanf("%d",&x);
		avl.insert(x);
		//printf("root: %d\n",avl.getRoot()->val);
	}
	for (int i=0;i<m;i++) {
		scanf("%d",&x);
		printf("%c\n",(avl.find(x))?'y':'n');
	}
	return 0;
}
