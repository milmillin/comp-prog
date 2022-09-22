#include <cstdio>
#include <vector>

using namespace std;

typedef vector<int> num;

num* add(num &a, num &b) {
	num *tmp = new num();
	int car=2e9;
	int c1=0,c2=0;
	while (c1<a.size()&&c2<b.size()) {
		if (car==a[c1]&&a[c1]==b[c2]) {
			car=a[c1]+1;
			tmp->push_back(a[c1]);
			c1++;
			c2++;
		} else if (car==a[c1]&&a[c1]<b[c2]) {
			car=a[c1]+1;
			c1++;
		} else if (car==b[c2]&&b[c2]<a[c1]) {
			car=b[c2]+1;
			c2++;
		} else if (car<a[c1]&&car<b[c2]) {
			tmp->push_back(car);
			car=2e9;
		} else if (a[c1]<b[c2]) {
			tmp->push_back(a[c1]);
			c1++;
		} else if (b[c2]<a[c1]) {
			tmp->push_back(b[c2]);
			c2++;
		} else if (a[c1]==b[c2]) {
			car=a[c1]+1;
			c1++;
			c2++;
		}
	}
	return tmp;
}

bool operator< (const num *a, const num *b) {
	int c1=a.size()-1,c2=b.size()-1;
	while (c1&&c2) {
		if (a[c1]!=b[c2]) return a[c1]<b[c2];
		else {
			c1--;
			c2--;
		}
	}
	return false;
}



int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	
	return 0;
}
