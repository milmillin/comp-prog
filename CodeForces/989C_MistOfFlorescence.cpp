#include <cstdio>
#include <algorithm>
#include <string>

using namespace std;

int main () {
	int a,b,c,d;
	scanf("%d%d%d%d",&a,&b,&c,&d);
	a--;
	c--;
	int mab=min(a,b);
	string ab;
	for (int i=0;i<mab;i++) {
		ab.push_back('A');
		ab.push_back('B');
	}
	while (ab.size()%49) ab.push_back(ab.back());
	a-=mab;
	b-=mab;
	string eab;
	while (a--) {
		eab.push_back('A');
		eab.push_back('C');
	}
	while (b--) {
		eab.push_back('B');
		eab.push_back('C');
	}
	while (eab.size()%49) eab.push_back(eab.back());

	int rowab=(ab.size()+eab.size())/49;
	rowab*=2;
	rowab++;

	int mcd=min(c,d);
	string cd;
	for (int i=0;i<mcd;i++) {
		cd.push_back('C');
		cd.push_back('D');
	}
	while (cd.size()%49) cd.push_back(cd.back());
	c-=mcd;
	d-=mcd;
	string ecd;
	while (c--) {
		ecd.push_back('C');
		ecd.push_back('A');
	}
	while (d--) {
		ecd.push_back('D');
		ecd.push_back('A');
	}
	while (ecd.size()%49) ecd.push_back(ecd.back());

	int rowcd=(cd.size()+ecd.size())/49;
	rowcd*=2;
	rowcd++;
	printf("%d 50\n",rowcd+rowab);
	for (int i=0;i<ab.size()/49;i++) {
		for (int j=0;j<50;j++) printf("C");
		printf("\n");
		printf("C");
		for (int j=0;j<49;j++) {
			printf("%c",ab[i*49+j]);
		}
		printf("\n");
	}	
	for (int i=0;i<eab.size()/49;i++) {
		for (int j=0;j<50;j++) printf("C");
		printf("\n");
		printf("C");
		for (int j=0;j<49;j++) {
			printf("%c",eab[i*49+j]);
		}
		printf("\n");
	}
	for (int j=0;j<50;j++) printf("C");
	printf("\n");
	for (int i=0;i<cd.size()/49;i++) {
		for (int j=0;j<50;j++) printf("A");
		printf("\n");
		printf("A");
		for (int j=0;j<49;j++) {
			printf("%c",cd[i*49+j]);
		}
		printf("\n");
	}
	for (int i=0;i<ecd.size()/49;i++) {
		for (int j=0;j<50;j++) printf("A");
		printf("\n");
		printf("A");
		for (int j=0;j<49;j++) {
			printf("%c",ecd[i*49+j]);
		}
		printf("\n");
	}
	for (int i=0;i<50;i++) printf("A");
	printf("\n");

	return 0;
}
