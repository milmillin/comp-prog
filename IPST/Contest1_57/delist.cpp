#include <cstdio>
#include <map>
#include <vector>

using namespace std;

struct node {
	int val;
	node* next;
	vector<int> res;
	vector<int> deres;
};

struct list {
	node* begin;
	node* end;
	int size;

	void empty() {
		begin=end=NULL;
		size=0;
	}

	void insert(int val) {
		if (size==0) {
			begin=end=new node{val,NULL};
			size++;
		} else {
			node* tmp=new node{val,NULL};
			end->next=tmp;
			end=tmp;
			size++;
		}
	}

	void insert(list &l) {
		if (l.size==0) return;
		end->next=l.begin;
		end=l.end;
		size+=l.size;
		l.empty();
	}
};

list tbl[1000100];
map<int,int> mp;

int main () {
	int k,m;
	scanf("%d%d",&k,&m);
	int n,x;
	for (int i=1;i<=k;i++) {
		scanf("%d",&n);
		for (int j=0;j<n;j++) {
			scanf("%d",&x);
			tbl[i].insert(x);
		}
	}
	int a,b,c;
	for (int i=0;i<m;i++) {
		scanf("%d%d%d",&a,&b,&c);
		if (a==1) {
			if (tbl[b].size==0) continue;
			tbl[b].begin->res.push_back(c);
			tbl[b].end->deres.push_back(c);
		} else {
			if (tbl[c].size==0) continue;
			tbl[b].insert(tbl[c]);
		}
	}
	for (int i=1;i<=k;i++) {
		if (tbl[i].size==0) continue;
		for (node* it=tbl[i].begin;;) {
			for (auto& a:it->res) {
				mp[a]++;
			}
			if (!mp[it->val]) printf("%d\n",it->val);
			for (auto &a:it->deres) {
				mp[a]--;
			}
			if (it==tbl[i].end) break;
			it=it->next;
		}
	}
	return 0;
}
