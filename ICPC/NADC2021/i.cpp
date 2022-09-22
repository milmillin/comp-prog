#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

vector<string> split(const string& s, const string& delim) {
  size_t start = 0;
  size_t end = s.find(delim);
  vector<string> res;
  while (end != string::npos) {
    res.push_back(s.substr(start, end - start));
    start = end + delim.length();
    end = s.find(delim, start);
  }
  res.push_back(s.substr(start, end));
  return res;
}

vector<int> proc(const string& s) {
  vector<string> aa = split(s, ",");
  vector<int> res;
  for (auto& ss: aa) {
    vector<string> bb = split(ss, "-");
    if (bb.size() == 1) {
      res.push_back(stoi(bb[0]));
    } else {
      int s = stoi(bb[0]);
      int t = stoi(bb[1]);
      for (int i = s; i <= t; i++) {
        res.push_back(i);
      }
    }
  }
  return res;
}

int main() {
  int n;
  cin >> n;
  string h, m, s;
  vector<int> hh;
  vector<int> mm;
  vector<int> ss;

  int cnt = 0;
  vector<bool> hasWork(86401, false);

  for (int i = 0; i < n; i++) {
    cin >> h >> m >> s;
    hh.clear();
    if (h == "*") {
      for (int k = 0; k < 24; k++) hh.push_back(k);
    } else {
      hh = proc(h);
    }
    mm.clear();
    if (m == "*") {
      for (int k = 0; k < 60; k++) mm.push_back(k);
    } else {
      mm = proc(m);
    }
    ss.clear();
    if (s == "*") {
      for (int k = 0; k < 60; k++) ss.push_back(k);
    } else {
      ss = proc(s);
    }
    cnt += hh.size() * mm.size() * ss.size();
    for (int hhh : hh) {
      for (int mmm : mm) {
        for (int sss : ss) {
          hasWork[hhh * 3600 + mmm * 60 + sss] = true;
        }
      }
    }
  }
  int ans = 0;
  for (int i = 0; i < 86400; i++) {
    if (hasWork[i]) ans++;
  }
  printf("%d %d\n", ans, cnt);
}
