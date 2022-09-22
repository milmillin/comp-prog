#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

struct board {
	vector<int> tbl;
	int sc;
	int& operator[] (int idx) {
		return tbl[idx];
	}

	const int& operator[] (int idx) const {
		return tbl[idx];
	}

	bool has(int idx) {
		for (auto i:tbl) {
			if (i==idx) return true;
		}
		return false;
	}

	void print() const {
		for (auto i:tbl) {
			printf("%d ",i);
		}
		printf("\n");
	}
};

bool operator< (const board &a, const board &b) {
	if (a.sc!=b.sc) return a.sc<b.sc;
	return a.tbl<b.tbl;
}

int n;

bool operator== (const board &a, const board &b) {
	for (int i=0;i<n;i++) {
		if (a[i]!=b[i]) return false;
	}
	return true;
}


int getRand() {
	return rand()%n;
}

void eval(board &x) {
	int cnt=0;
	for (int i=0;i<n;i++) {
		for (int j=i+1;j<n;j++) {	
			if (j-i==abs(x[i]-x[j])) cnt++;
		}
	}
	x.sc=cnt;
}

board createRandom() {
	board tmp;
	for (int i=0;i<n;i++) {
		while (true) {
			int x=getRand();
			if (!tmp.has(x)) {
				tmp.tbl.push_back(x);
				break;
			}
		}	
	}
	eval(tmp);
	return tmp;
}

board combine(board &a, board &b) {
	board tmp;
	for (int i=0;i<n/2;i++) {
		tmp.tbl.push_back(a[i]);
	}
	for (int i=0;i<n;i++) {
		if (tmp.has(b[i])) continue;
		tmp.tbl.push_back(b[i]);
	}
	eval(tmp);
	return tmp;
}

board mutate(board &a) {
	board tmp;
	for (auto i:a.tbl) {
		tmp.tbl.push_back(i);
	}
	int aa=getRand();
	int bb=getRand();
	swap(tmp.tbl[aa],tmp.tbl[bb]);	
	//aa=getRand();
	//bb=getRand();
	//swap(tmp.tbl[aa],tmp.tbl[bb]);	
	return tmp;
}

int main () {
	srand(time(0));
	scanf("%d",&n);
	int pool_size=2000;
	int cmb_size=25;

	vector<board> pool;
	for (int i=0;i<pool_size;i++) {
		pool.push_back(createRandom());
	}
	sort(pool.begin(),pool.end());
	int sc=1000000;	
	int gen=0;
	while (pool[0].sc>0) {
		if (gen%100==0) {
			printf("Gen %d\n",gen);
			//for (int i=99;i>0;i-=2) {
				//pool.erase(pool.begin()+i);
			//}
			for (int i=0;i<10;i++) {
				printf("%d => ",pool[i].sc);
				for (int j=0;j<n;j++) {
					printf("%d ",pool[i][j]);
				}
				printf("\n");
			}
		}
		if (pool[0].sc<sc) {
			sc=pool[0].sc;
			printf("%d\n",sc);
			pool[0].print();
		}
		//printf("%d\n",pool[0].sc);
		for (int i=0;i<cmb_size;i++) {
			for (int j=0;j<cmb_size;j++) {
				//if (i==j) continue;
				pool.push_back(combine(pool[i],pool[pool.size()-1-j]));
				if (i==j) continue;
				pool.push_back(combine(pool[i],pool[j]));
			}
		}	
		int nn=pool.size();
		for (int i=0;i<nn;i++) {
			pool.push_back(mutate(pool[i]));	
		}
		for (int i=0;i<100;i++) pool.push_back(createRandom());
		sort(pool.begin(),pool.end());
		pool.erase(unique(pool.begin(),pool.end()),pool.end());
		while (pool.size()>pool_size) pool.pop_back();
		gen++;
	}
	for (auto &i:pool) {
		if (i.sc==0) i.print();
		else break;
	}
	return 0;
}
