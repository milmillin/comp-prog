#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

int main () {
    int n;
    scanf("%d",&n);
    string x;
    cin>>x;
    int maxLen=0;
    bool isIn=false;
    int wordCnt=0;
    int stk=0;
    bool isWord=false;
    for (int i=0;i<x.length();i++) {
        if (x[i]=='(') {
            maxLen=max(maxLen,stk);
            stk=0;
            isIn=true;
            continue;
        } else if (x[i]==')') {
            isIn=false;
//            if (isWord) wordCnt++;
//            isWord=false;
            stk=0;
            continue;
        }
        if (!isIn) {
            if (x[i]=='_') {
                maxLen=max(maxLen,stk);
                stk=0;
            } else {
                stk++;
                maxLen=max(maxLen,stk);
            }
        } else {
            if (x[i]!='_'&&(x[i+1]==')'||x[i+1]=='_')) wordCnt++;
//            if (x[i]!='_') {
//                isWord=true;
//            } else {
//                if (isWord) wordCnt++;
//                isWord=false;
//            }
        }
    }
    printf("%d %d\n",maxLen,wordCnt);
    return 0;
}
