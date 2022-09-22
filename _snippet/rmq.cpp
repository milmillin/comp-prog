#include <vector>
#include <cmath>

using namespace std;

// A helper class for Range Minimum/Maximum Query (RMQ).
// Ties are broken by the index.
// Needs <cmath>.
template <class T>
class RMQ {
  private:
    int n, lvl_cnt;
    vector<T> data;
    vector<vector<int>> minIndex;
    vector<vector<int>> maxIndex;

    // You may choose your choice of log2 here
    static int _log(int w) { return (int) log2(w); }
  public:
    RMQ(const vector<T> &a) :
      data(a),
      n(a.size()),
      lvl_cnt(_log(n) + 1),
      minIndex(lvl_cnt, vector<int>(n, 0)),
      maxIndex(lvl_cnt, vector<int>(n, 0))
    {
      // Base Case
      for(int i = 0; i < n; i++) {
        maxIndex[0][i] = minIndex[0][i] = i;
      }
      // General Case
      for(int lvl = 1; lvl < lvl_cnt; lvl++) {
        for(int i = 0; i < n; i++) {
          minIndex[lvl][i] = minIndex[lvl - 1][i];
          maxIndex[lvl][i] = maxIndex[lvl - 1][i];
          int pt = 1 << (lvl - 1);
          if(i + pt < n) {
            if (data[minIndex[lvl - 1][i + pt]] < data[minIndex[lvl][i]])
              minIndex[lvl][i] = minIndex[lvl - 1][i + pt];
            if (data[maxIndex[lvl - 1][i + pt]] >= data[maxIndex[lvl][i]])
              maxIndex[lvl][i] = maxIndex[lvl - 1][i + pt];
          }
        }
      }
    }

    // [l, r)
    int GetMinIndex(int l, int r) const {
      int sz = r - l;
      int m = _log(sz);
      int pt = 1 << m;
      if (pt == sz) return minIndex[m][l];
      int c1 = minIndex[m][l];
      int c2 = minIndex[m][r - pt];
      if (data[c1] <= data[c2]) return c1; else return c2;
    }

    int GetMaxIndex(int l, int r) const {
      int sz = r - l;
      int m = _log(sz);
      int pt = 1 << m;
      if (pt == sz) return maxIndex[m][l];
      int c1 = maxIndex[m][l];
      int c2 = maxIndex[m][r - pt];
      if (data[c1] > data[c2]) return c1; else return c2;
    }

    T getMinValue(int l, int r) const { return data[GetMinIndex(l, r)]; }
    T getMaxValue(int l, int r) const { return data[GetMaxIndex(l, r)]; }
};
