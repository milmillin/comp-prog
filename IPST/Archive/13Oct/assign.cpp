#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

int main () {
	string x,y;
	cin>>x;
	cin>>y;
	
	int j=0;
	int patLev=0;
	int expLev=0;
	
	string ans="";

	for (int i=0;i<x.length();i++) {
		//printf("%d %d\n",i,j);
		if (x[i]==y[j]) {
			if (x[i]=='(') {
				patLev++;
				expLev++;
			} else if (x[i]==')') {
				patLev--;
				expLev--;
			}
			j++;
		} else {
			//printf("Yay\n");
			if (x[i]>='A'&&x[i]<='Z') {
				//printf("eiei\n");
				while (y[j]!=x[i+1]||patLev!=expLev) {
					//printf("%c",y[j]);
					ans+=y[j];
					if (y[j]=='(') expLev++;
					else if (y[j]==')') expLev--;
					j++;
					if (j>=y.length()) {
						printf("no\n");
						return 0;
					}
					if (patLev==expLev&&y[j]==','&&x[i+1]==')') {
						printf("no\n");
						return 0;
					}
					if (patLev==expLev&&y[j]==')'&&x[i+1]==',') {
						printf("no\n");
						return 0;
					}
				}
				//printf("\n");
				ans+='\n';
			} else {
				printf("no\n");
				return 0;
			}
		}
	}
	cout << ans;
}
