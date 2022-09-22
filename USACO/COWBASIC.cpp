#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

map<string,int> mp;

bool isNum(const string &x) {
	for (int i=0;i<(int)x.length();i++) {
		if (x[i]<'0'||x[i]>'9') return false;
	}
	return true;
}

struct var {
	int type; //0-var,1-literal,2-operator
	string x;
	int val;
	var(const string &y) {
		if (y[0]=='+') {
			type=2;
		} else if (isNum(y)) {
			type=1;
			val=stoi(y);
		} else {
			type=0;
			x=y;
		}
	}
	int eval() const {
		if (type==0) return mp[x];
		else if (type==1) return val;
		return -1;
	}
};

struct exp {
	vector<var> postfix;	
	exp() {

	}
	exp(vector<string> &x) {
		vector<string> stk;
		for (auto &a:x) {
			if (a=="(") stk.push_back(a);
			else if (a==")") {
				while (stk.back()!="(") {
					postfix.push_back(var(stk.back()));
					stk.pop_back();
				}
				stk.pop_back();
			} else if (a=="+") {
				stk.push_back(a);
			} else {
				postfix.push_back(var(a));
			}
		}
		while (!stk.empty()) {
			postfix.push_back(var(stk.back()));
			stk.pop_back();
		}
		//for (auto &a:postfix) {
			//if (a.type==0) printf("%s ",a.x.c_str());
			//else if (a.type==1) printf("%d ",a.val);
			//else printf("+ ");
		//}
		//printf("\n");
	}
	int eval() const {
		vector<int> a;
		for (auto &i:postfix) {
			if (i.type==2) {
				int x=a.back();
				a.pop_back();
				int y=a.back();
				a.pop_back();
				a.push_back((x+y)%1000000007);
			} else {
				a.push_back(i.eval());
			}
		}
		return a[0];
	}
};

struct statement {
	int type; //0-assignment,1-loop,2-return;
	string variable;
	vector<statement> inner;
	int loopCnt;	
	exp expression;


	void eval() const {
		if (type==0) {
			int tmp=expression.eval();
			//printf("assign %s = %d\n",variable.c_str(),tmp);
			mp[variable]=tmp;
		} else if (type==1){
			//printf("loop %d times\n",loopCnt);
			for (int i=0;i<loopCnt;i++) {
				for (auto &st:inner) {
					st.eval();
				}
			}
		} else {
			printf("%d\n",mp[variable]);
		}
	}
};

int main () {
	freopen("cowbasic.in","r",stdin);
	freopen("cowbasic.out","w",stdout);
	string x;
	statement root;
	root.type=1;
	root.loopCnt=1;
	
	vector<statement*> stk;
	stk.push_back(&root);

	while (getline(cin,x)) {
		stringstream ss(x);
		string a,b,c;
		ss>>a>>b;
		if (a=="}") {
			//printf("end loop\n");
			stk.pop_back();
		} else if (b=="=") {
			//printf("assignment\n");
			statement tmp;
			tmp.type=0;
			tmp.variable=a;
			vector<string> ex;
			while (ss>>c) ex.push_back(c);
			tmp.expression=exp(ex);
			stk.back()->inner.push_back(tmp);
		} else if (b=="MOO") {
			//printf("loop start\n");
			statement tmp;
			tmp.type=1;
			tmp.loopCnt=stoi(a);
			stk.back()->inner.push_back(tmp);
			stk.push_back(&(stk.back()->inner.back()));
		} else if (a=="RETURN") {
			//printf("return\n");
			statement tmp;
			tmp.type=2;
			tmp.variable=b;
			stk.back()->inner.push_back(tmp);
		}
	}
	//printf("start eval\n");
	root.eval();
	return 0;
}
