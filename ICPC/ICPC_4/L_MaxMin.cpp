#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int isMore (string &a, string &b) {
	int n=min(a.length(),b.length());
	for (int i=0;i<n;i++) {
		if (a[i]>b[i]) return 2;
		else if (a[i]<b[i]) return 0;
	}
	if (a.length()>b.length()) return 2;
	else if (a.length()==b.length()) return 1;
	else return 0;
}

int isMore2 (string &a, string &b) {
	int n = a.length();
	for (int i=n-1;i>=0;i--) {
		if (a[i]>b[i]) return 2;
		else if (a[i]<b[i]) return 0;
	}
	return 1;
}

int main () {
	string x;
	cin >> x;
	x+=".0";
	int n = x.length();
	
	string front_max_rev = "";
	string back_max = "";

	for (int i=1;i<n-1;i++) {
		if (x[i]!='.') continue;
		string cur_front_rev="";
		string cur_back="";
		
		int pos = i-1;
		while (pos>=0&&x[pos]!='.') {
			cur_front_rev+=x[pos];
			pos--;
		}
		while (cur_front_rev.size()&&cur_front_rev.back()=='0') cur_front_rev.pop_back();
		pos = i+1;
		while (pos<n&&x[pos]!='.') {
			cur_back+=x[pos];
			pos++;
		}
		while (cur_back.size()&&cur_back.back()=='0') cur_back.pop_back();

		//printf("** %d\n",pos);
		//cout << cur_front_rev<< endl << cur_back << endl;

		if (cur_front_rev.length()>front_max_rev.length()) {
			front_max_rev = cur_front_rev;
			back_max = cur_back;
		} else if (cur_front_rev.length()==front_max_rev.length()) {
			int res = isMore2(cur_front_rev,front_max_rev);
			
			if (!res) continue;
			if (res==2) {
				front_max_rev = cur_front_rev;
				back_max = cur_back;
				continue;
			}
			
			if (isMore(cur_back,back_max)==2) {
				front_max_rev = cur_front_rev;
				back_max = cur_back;
			}

		}
	}
	reverse(front_max_rev.begin(),front_max_rev.end());
	cout << front_max_rev;
	if (back_max.length()) cout << "." << back_max;
	cout << "\n";

	//find int min
	int mn=10;
	vector<int> zeroPos;
	for (int i=0;i<n;i++) {
		if (x[i]=='.') continue;
		if (x[i]=='0') {
			if (i>n-3) continue;
			if (x[i+1]=='.') {
				zeroPos.push_back(i+2);
			}
			continue;
		}
		mn=min(mn,x[i]-'0');
	}

	string candidate_min="";
	for (int i=0;i<(int)zeroPos.size();i++){
		string cur="";
		int pos=zeroPos[i];
		while (pos<n&&x[pos]=='0') {
			cur+='0';
			pos++;
		}
		if (pos!=n&&x[pos]!='.') {
			cur+=x[pos];
		} else continue;
		if (cur.length()>candidate_min.length()) {
			candidate_min=cur;
		} if (cur.length()==candidate_min.length()) {
			if (cur.back()<candidate_min.back()) {
				candidate_min=cur;
			}
		}
	}
	if (candidate_min.length()) {
		cout << "0." << candidate_min <<"\n";
	} else {
		printf("%d\n",mn);
	}
	return 0;
}
