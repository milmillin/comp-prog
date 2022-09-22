#include <cstdio>
#include <list>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

int main () {
    int n;
    scanf("%d",&n);
    char cmd;
    string s;
    list<string> word;
    word.push_back("XX");
    list<string>::iterator cur=word.begin();
    list<string>::iterator tmp;
//    for (list<string>::iterator i=word.begin();i!=word.end();i++) {
//        cout << *i << " ";
//        if (i==cur) cout << "| ";
//    }
    for (int i=0;i<n;i++) {
        scanf(" %c",&cmd);
        if (cmd=='i') {
            cin>>s;
            cur=word.insert(++cur,s);
        } else if (cmd=='l') {
            if (cur==word.begin()) continue;
            cur--;
        } else if (cmd=='r') {
            tmp = word.end();
            tmp--;
            if (cur==tmp) continue;
            cur++;
        } else if (cmd=='b') {
            if (cur==word.begin()) continue;
            cur = word.erase(cur);
            cur--;
        } else if (cmd=='d') {
            tmp = word.end();
            tmp--;
            if (cur==tmp) continue;
            cur = word.erase(++cur);
            cur--;
        }
    }
    tmp = word.begin();
    tmp++;
    for (list<string>::iterator i=tmp;i!=word.end();i++) {
        cout << *i << " ";
        //if (i==cur) cout << "| ";
    }
    printf("\n");
    return 0;
}
