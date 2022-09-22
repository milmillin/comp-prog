#include <cstdio>
#include <string>
#include <algorithm>
#include <iostream>
#include "messy.h"

using namespace std;

string gen(int n, int val) {
	string ans="";
	while (val) {
		ans.push_back(val%2+'0');
		val/=2;
	}
	while (ans.length()<n) {
		ans.push_back('0');
	}
	reverse(ans.begin(),ans.end());
	return ans;
}

string gen01(int n,int one) {
	string ans="";
	for (int i=0;i<n-one;i++) {
		ans.push_back('1');
	}
	for (int i=0;i<one;i++) {
		ans.push_back('0');
	}
	return ans;
}

vector<int> restore_permutation(int n, int w, int r) {
	//int* result = (int*)malloc(sizeof(int)*200);
	vector<int> result(200);
	string tmp;
	for (int i=0;i<n;i++) {
		tmp=gen01(n,i);
		//cout<<tmp<<endl;
		add_element(tmp);
	}
	compile_set();
	//cout<<"yay\n";
	string chk=gen01(n,n);
	for (int i=0;i<n;i++) {
		for (int j=0;j<n;j++) {
			if (chk[j]=='1') continue;
			chk[j]='1';
			//cout << chk << endl;
			if (check_element(chk)) {
				//cout << chk << endl;
				result[j]=i;
				break;
			}
			chk[j]='0';
		}
	}
	return result;
}
/*
int res[200];

int main () {
	restore_permutation(8,1,1,res);
	return 0;
}
*/
