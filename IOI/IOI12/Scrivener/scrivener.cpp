#ifdef debug
#include "grader.cpp"
#endif

#include <cstdlib>

struct node {
	char x;
	int pos;
	node* left[21];									
};

node* version[1000100];
int curVer=0;
int curIdx=1;
char last;

void Init() {
	version[0]=new node();
	version[0]->x=0;
	version[0]->pos=-1;
	for (int i=0;i<21;i++) version[0]->left[i]=version[0];	
}

void TypeLetter(char L) {
  //last = L;
	version[curIdx]=new node();
	version[curIdx]->x=L;
	version[curIdx]->pos=version[curVer]->pos+1;
	version[curIdx]->left[0]=version[curVer];
	for (int i=1;i<21;i++) version[curIdx]->left[i]=version[curIdx]->left[i-1]->left[i-1];	
	curVer=curIdx;
	curIdx++;
}

void UndoCommands(int U) {
	//version[curIdx]=new node();
	version[curIdx]=version[curIdx-U-1];
	curVer=curIdx;
	curIdx++;
}

char GetLetter(int P) {
	node* cur=version[curVer];
	int dif=cur->pos-P;
	for (int i=0;i<21;i++) {
		if (dif&(1<<i)) {
			cur=cur->left[i];
		}
	}
	return cur->x;
}
