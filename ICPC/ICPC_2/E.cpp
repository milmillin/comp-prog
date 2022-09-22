#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

struct fk {
	char x;
	int num;
	bool ext;
};

void f() {
	char x[10100];
	char y[10100];
	memset(x,0,sizeof(x));
	memset(y,0,sizeof(y));
	scanf("%s",x);
	scanf("%s",y);
	int xx=strlen(x);
	int yy=strlen(y);
	
	vector<fk> tbl;
	tbl.reserve(10100);

	int a=0,b=0;
	char last=0;
	while (a<xx) {
		if (x[a+1]=='*') {
			if (x[a]!=last) {
				tbl.push_back(fk{x[a],0,true});
			} else {
				tbl.back().ext=tbl.back().ext||true;
			}
			last=x[a];
			a+=2;
		} else if (x[a+1]=='+') {
			if (x[a]!=last) {
				tbl.push_back(fk{x[a],1,true});
			} else {
				tbl.back().num++;
				tbl.back().ext=tbl.back().ext||true;
			}
			last=x[a];
			a+=2;
		} else {
			if (x[a]!=last) {
				tbl.push_back(fk{x[a],1,false});
			} else {
				tbl.back().num++;
			}
			last=x[a];
			a++;
		}
	}
	bool cont = 0;
	int lastvalid = 0;
	for(int i = 0; i< (int) tbl.size(); i++)
	{
		char want = tbl[i].x;
		int mn = tbl[i].num;
		bool ext = tbl[i].ext;
		if(cont) while(mn && b< yy && y[b] == tbl[i-1].x) b++;
		for(int j = 0; j< (int) mn; j++)
		{
			if(b == yy || y[b] != want) 
			{
				printf("NO\n");
				return;
			}
			b++;
		}
		//printf("%d\n", b);
		lastvalid = i;
		cont = ext;
	}
	if(b != yy && cont)
	{
		while(b< yy && tbl.back().x == y[b]) b++;
	}
	if (b==yy) printf("YES\n");
	else printf("NO\n");
}

int main () {
	int q;
	scanf("%d",&q);
	while (q--) {
		f();
	}
	return 0;
}
