#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include <set>

using namespace std;

int main () {
	//freopen("eng_dicts.txt","r",stdin);
	ifstream fil;
	fil.open("eng_dicts.txt");
	printf("yay\n");
	string x;
	set<string> dict;
	while (!fil.eof()) {
		getline(fil,x);
		//dict.insert(x);
		cout << x << endl;
	}
	//for (set<string>::iterator it=dict.begin();it!=dict.end();it++) {
	//	cout << *it << endl;
	//}
	return 0;
}
