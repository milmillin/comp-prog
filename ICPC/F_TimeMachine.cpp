#include <cstdio>
#include <vector>
#include <string>
#include <map>
#include <iostream>

using namespace std;

int main () {
	string x;
	cin >> x;
	int n;
	scanf("%d",&n);
	map <string,int> ei;
	ei["JAN"]=1;
	ei["FEB"]=2;
	ei["MAR"]=3;
	ei["APR"]=4;
	ei["MAY"]=5;
	ei["JUN"]=6;
	ei["JUL"]=7;
	ei["AUG"]=8;
	ei["SEP"]=9;
	ei["OCT"]=10;
	ei["NOV"]=11;
	ei["DEC"]=12;
	vector<string> eu(12);
	eu[0]="JAN";
	eu[1]="FEB";
	eu[2]="MAR";
	eu[3]="APR";
	eu[4]="MAY";
	eu[5]="JUN";
	eu[6]="JUL";
	eu[7]="AUG";
	eu[8]="SEP";
	eu[9]="OCT";
	eu[10]="NOV";
	eu[11]="DEC";

	int now = ei[x]-1;
	now+=n;
	now%=12;
	now = (now+12)%12;
	cout << eu[now] << "\n";
	return 0;
}
