#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <cassert>

using namespace std;

// 11110000

const int maxn = 2048;

vector<int> compress(const string &res) {
	vector<int> ans;
	int cur = 1;
	int cnt = 0;
	for (auto c : res) {
		if (c - '0' != cur) {
			ans.push_back(cnt);
			cur = c - '0';
			cnt = 1;
		} else {
			cnt++;
		}
	}
	ans.push_back(cnt);
	return ans;
}

string ask(int n, int intv) {
	string query = "";
	int cur = 1;
	for (int i = 0; i < maxn; i += intv) {
		for (int j = 0; j < intv; j++) {
			query.push_back((char)('0' + cur));
		}
		cur ^= 1;
	}
	string toAsk = query.substr(0, n);
	printf("%s\n", toAsk.c_str());
	fflush(stdout);

	string response;
	cin >> response;
	query = query.substr(n);
	response += query;
	
	return response;
}

int b[6][maxn];

void f() {
	int n, x, f;
	scanf("%d%d%d", &n, &x, &f);
	memset(b, 0, sizeof(b));

	vector<int> cnt = compress(ask(n, 16));
	for (int i = 0; i < (int)cnt.size(); i++) {
		b[4][i] = 16 - cnt[i];
		//fprintf(stderr, "%d ", b[4][i]);
	}
	//fprintf(stderr, "\n");

	for (int k = 3; k >= 0; k--) {
		int size = 1 << k;
		int numBlock = maxn / size;

		string response = ask(n, size);

		int idx = 0;
		for (int i = 0; i < numBlock / 2; i++) {
			int cnt1 = 0;
			int cnt0 = 0;
			string now;
			for (int j = 0; j < size * 2 - b[k + 1][i]; j++) {
				now.push_back(response[idx++]);
			}
			int cur = 0;
			int nowSize = (int)now.length();
			while (cur < nowSize && now[cur] == '1') {
				cnt1++;
				cur++;
			}
			while (cur < nowSize && now[cur] == '0') {
				cnt0++;
				cur++;
			}
			b[k][i * 2] = size - cnt1;
			b[k][i * 2 + 1] = size - cnt0;
		}
		

		//for (int j = 0; j < numBlock; j++) {
			//fprintf(stderr, "%d ", b[k][j]);
		//}
		//fprintf(stderr, "\n");
	}

	for (int i = 0; i < maxn; i++) {
		if (b[0][i]) {
			printf("%d ", i);
		}
	}
	printf("\n");
	fflush(stdout);

	int verdict;
	scanf("%d", &verdict);
	assert(verdict == 1);
}

int main () {
	int q;
	scanf("%d", &q);
	while (q--) {
		f();
	}
	return 0;
}
