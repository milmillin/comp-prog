#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

class Tree {
	struct Node {
		int cnt;
		Node* chd[26];
		
		Node(): cnt(0) {
			for (int i = 0; i < 26; i++) {
				chd[i] = NULL;
			}
		}

		~Node() {
			for (int i = 0; i < 26; i++) {
				delete chd[i];
			}
		}
	};

	Node* _root;

	//node not NULL
	void _add(Node* node, const string &str, const int id) {
		if (id == (int)str.size()) return;

		int index = str[id] - 'A';

		if (!(node -> chd[index])) {
			node -> chd[index] = new Node();
		}
		node -> chd[index] -> cnt++;
		
		_add(node -> chd[index], str, id + 1);
	}

	int _dp(Node* node) {
		if (!node) return 0;
		int sumLook = 0;
		for (int i = 0; i < 26; i++) {
			sumLook += _dp(node -> chd[i]);
		}
		int now = (node -> cnt - sumLook >= 2) ? 2 : 0;
		return now + sumLook;
	}

	public:
	Tree(): _root(new Node()) {}
	~Tree() {
		delete _root;
	}

	void Add(const string &str) {
		_add(_root, str, 0);
	}

	int GetAns() {
		int ans = 0;
		for (int i = 0; i < 26; i++) {
			ans += _dp(_root -> chd[i]);
		}
		return ans;
	}
};

void f() {
	int n;
	scanf("%d", &n);
	Tree t;
	string x;
	for (int i = 0; i < n; i++) {
		cin >> x;
		reverse(x.begin(), x.end());
		t.Add(x);
	}
	printf("%d\n", t.GetAns());
	fflush(stdout);
}

int main () {
	int q;
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		printf("Case #%d: ", i);
		f();
	}
	return 0;
}
