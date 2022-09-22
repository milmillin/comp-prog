#include <cstdio>
#include <cassert>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

string ei[40];

vector<int> prefix(string &pat) {
	int n = pat.size();
	vector<int> f(n + 1);
	f[0] = -1;
	int k;
	for (int i = 1; i < n; i++) {
		k = f[i - 1];
		while (pat[k + 1] != pat[i] && k >= 0) k = f[k];
		if (k == -1 && pat[0] != pat[i]) f[i] = -1;
		else f[i]=k+1;
	}
	return f;
}

int match(string &text, string &pat, vector<int> &f) {
	int n = pat.size();
	int m = text.size();

	int cnt = 0;

	int k=-1;

	for (int i = 0; i < m; i++) {
		while (pat[k + 1] != text[i] && k >= 0)k = f[k];
		if (k == -1 && pat[0] != text[i]) k = -1;
		else k++;

		if (k == n - 1) {
			cnt++;
		}
	}
	return cnt;
}

int main () {
	int n;
	scanf("%d", &n);
	string x;
	cin >> x;
	ei[0] = "0";
	ei[1] = "1";
	if (n<=1) {
		if (ei[n] == x) printf("1\n");
		else printf("0\n");
		return 0;
	}
	int cur = 2;
	while (true) {
		ei[cur] = ei[cur - 1] + ei[cur - 2];
		cur++;
		if(ei[cur - 1].size() >= x.size()) break;
	}
	ei[cur] = ei[cur - 1] + ei[cur - 2];
	
	if (n < cur - 1) {
		printf("0\n");
		return 0;
	}

	string a = ei[cur - 1];
	string b = ei[cur];

	vector<int> pre = prefix(x);

	int ma = match(a, x, pre);
	//cout << a << " " << ma << endl;
	int mb = match(b, x, pre);
	//cout << b << " " << mb << endl;
	string tmp = a.substr(a.size() - x.size() + 1) + b.substr(0, x.size() - 1);
	int mab = match(tmp, x, pre);
	//cout << tmp << " " << mab << endl;
	tmp = b.substr(b.size() - x.size() + 1) + b.substr(0, x.size() - 1);
	int mbb = match(tmp, x, pre);
	//cout << tmp << " " << mbb << endl;
	tmp = b.substr(b.size() - x.size()+1) + a.substr(0, x.size() - 1);
	int mba = match(tmp, x, pre);
	//cout << tmp << " " << mba << endl;


	if (n == cur - 1) {
		printf("%d\n", ma);
		return 0;
	} else if (n == cur) {
		printf("%d\n", mb);
		return 0;
	}

	int s1 = 1;
	int e1 = 1;
	int s2 = 2;
	int e2 = 2;
	long long m1 = ma;
	long long m2 = mb;
	int s3, e3;
	long long m3;
	for (int i = cur+1; i <= n; i++) {
		s3 = s2;
		e3 = e1;
		m3 = m2 + m1;
		//printf("%d %d\n", e2, s1);
		if (e2 == 1 && s1 == 2) m3 += mab;
		else if (e2 == 2 && s1 == 2) m3 += mbb;
		else if (e2 == 2 && s1 == 1) m3 += mba;
		else assert(false);
		s1 = s2;
		e1 = e2;
		m1 = m2;
		s2 = s3;
		e2 = e3;
		m2 = m3;
	}
	printf("%lld\n", m2);	
	return 0;
}
