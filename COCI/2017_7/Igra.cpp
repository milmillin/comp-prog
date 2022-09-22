#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

int xa,xb,xc;
int ya,yb,yc;

bool check() {
	if (xa<0||xb<0||xc<0) return false;
	if (xb+xc<ya) return false;
	if (xa+xc<yb) return false;
	if (xa+xb<yc) return false;
	return true;
}

int main () {
	int n;
	scanf("%d",&n);
	string x;
	cin >> x;
	string y;
	cin >> y;
	xa=xb=xc=ya=yb=yc=0;
	for (int i=0;i<n;i++) {
		if (x[i]=='a') xa++;
		else if (x[i]=='b') xb++;
		else if (x[i]=='c') xc++;
		if (y[i]=='a') ya++;
		else if (y[i]=='b') yb++;
		else if (y[i]=='c') yc++;
	}
	string ans;
	for (int i=0;i<n;i++) {
		if (y[i]=='a') {
			xb--;
			ya--;
			if (check()) ans.push_back('b');
			else {
				xb++;
				xc--;
				ans.push_back('c');
			}
		} else if (y[i]=='b') {
			xa--;
			yb--;
			if (check()) ans.push_back('a');
			else {
				xa++;
				xc--;
				ans.push_back('c');
			}
		} else {
			xa--;
			yc--;
			if (check()) ans.push_back('a');
			else {
				xa++;
				xb--;
				ans.push_back('b');
			}
		}
	}
	cout << ans << '\n';
	return 0;
}
