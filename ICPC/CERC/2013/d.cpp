#include <cstdio>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <queue>

using namespace std;

struct state{
  int id;
  int dis;
  int hop;
  int t;
  int line;
};

struct pathinfo{
  int to;
  int dis;
  int line;
};

void f() {
  string tmp;
  string tok;
  getline(cin, tok); // blankline

  string stops;
  getline(cin, stops);
  stringstream ss_stops(stops);
  ss_stops >> tmp; // Stops:

  vector<string> names;
  map<string, int> id;
  while (ss_stops >> tok) {
    if (tok.back() == ',') tok.pop_back();
    id[tok] = names.size();
    names.push_back(tok);
  }

  int n_stops = names.size();

  string lines;
  getline(cin, lines);
  stringstream ss_lines(lines);
  ss_lines >> tmp; // Lines:

  int n_lines = 0;
  while (ss_lines >> tok) n_lines++;

  vector<vector<int>> routes(n_lines);

  vector<int> line_count(n_stops, 0);

  for (int i = 0; i < n_lines; i++) {
    string route;
    getline(cin, route);
    stringstream ss_route(route);
    ss_route >> tmp; // <name>
    ss_route >> tmp; // route:
    while (ss_route >> tok) {
      if (tok.back() == ',') tok.pop_back();
      int stop_id = id[tok];
      line_count[stop_id]++;
      routes[i].push_back(stop_id);
    }
  }

  int start, stop;
  string pos;
  getline(cin, pos);
  stringstream ss_pos(pos);
  ss_pos >> tmp; // <name>
  ss_pos >> tmp; // lives
  ss_pos >> tmp; // at
  ss_pos >> tok;
  if (tok.back() == ',') tok.pop_back();
  start = id[tok];

  getline(cin, pos);
  stringstream ss_pos2(pos);
  ss_pos2 >> tmp; // <name>
  ss_pos2 >> tmp; // lives
  ss_pos2 >> tmp; // at
  ss_pos2 >> tok;
  if (tok.back() == ',') tok.pop_back();
  stop = id[tok];

  vector<vector<pathinfo>> pth(n_stops);
  map<pair<int, int>, pair<int, vector<int>>> path; // (from, to) -> (dis, [line])

  for (int i = 0; i < n_lines; i++) {
    int last = 0;
    int last_stop = routes[i].front();
    for (int j = 1; j < (int)routes[i].size(); j++) {
      int cur_stop = routes[i][j];
      if (line_count[cur_stop] > 1 || cur_stop == start || cur_stop == stop) {
        pair<int, int> cur_path = {last_stop, cur_stop};
        auto it = path.find(cur_path);
        if (it == path.end()) {
          path.insert({cur_path, {j - last, vector<int>{i}}});
        } else {
          if (j - last > it->second.first) {
            it->second = {j - last, vector<int>{i}};
          } else if (j - last == it->second.first) {
            it->second.second.push_back(i);
          }
        }
        last = j;
        last_stop = cur_stop;
      }
    }
  }

  for (auto& p : path) {
    for (int l : p.second.second) {
      pth[p.first.first].push_back(pathinfo{p.first.second, p.second.first, l});
      pth[p.first.second].push_back(pathinfo{p.first.first, p.second.first, l});
    }
  }

  vector<pair<int, int>> dis(n_stops, {0, 100100}); // dis, hop
  queue<state> q;
  q.push(state{start, 0, 0});
  dis[start] = {0, 0};
  while (!q.empty()) {
    state now = q.front();
    q.pop();

    if (now.dis != dis[now.id].first || now.hop != dis[now.id].second) continue;

    for (auto& p : pth[now.id]) {
      int next = p.first;
      int next_dis = now.dis + p.second;
      int next_hop = now.hop + 1;
      if (dis[next].second < next_hop) continue;
      if (dis[next].first >= next_dis) continue;
      dis[next].first = next_dis;
      dis[next].second = next_hop;
      q.push(state{next, next_dis, next_hop});
    }
  }

  int res_lines = dis[stop].second;
  int res_minutes = dis[stop].first;
  cout << "optimal travel from " << names[start] << " to " <<  names[stop] << ": " <<
    res_lines << (res_lines > 1 ? " lines, " : " line, ") <<
    res_minutes << (res_minutes > 1 ? " minutes\n" : " minute\n");
}

int main() {
  int q;
  string tok;
  getline(cin, tok);
  stringstream ss(tok);
  ss >> q;
  while (q--) {
    f();
  }
  return 0;
}
