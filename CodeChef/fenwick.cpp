#include <stdio.h>

#include <algorithm>
#include <vector>

using namespace std;

// Fenwick Tree.
// Performs point update and range query.
// Index starts at 0.
template <typename T>
class Fenwick {
 private:
  vector<T> data_;

 public:
  // data[idx] += val
  void Add(int idx, T val) {
    for (idx++; idx < (int)data_.size(); idx += (idx & -idx)) data_[idx] += val;
  }

  Fenwick(int n) : data_(n + 1, 0) {}
  Fenwick(const vector<T> &data) : data_(data.size() + 1, 0) {
    for (int i = 0; i < (int)data.size(); i++) Add(i, data[i]);
  }

  // [0, idx]
  T GetPrefixSum(int idx) const {
    T ret = 0;
    for (idx++; idx; idx -= (idx & -idx)) ret += data_[idx];
    return ret;
  }

  // [l, r)
  T GetSum(int l, int r) const {
    return GetPrefixSum(r - 1) - GetPrefixSum(l - 1);
  }

  // data[idx]
  T Get(int idx) const { return GetPrefixSum(idx) - GetPrefixSum(idx - 1); }

  // data[idx] = val
  void Set(int idx, T val) { Add(idx, val - Get(idx)); }
};