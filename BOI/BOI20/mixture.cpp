#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <cassert>
#include <set>

using namespace std;

long long gcd(long long a, long long b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}

struct Vector {
  long long x, y, z;

  Vector(long long x_, long long y_, long long z_) {
    /*
    long long g = gcd(x_, gcd(y_, z_));
    if (g < 0) g = -g;

    if (x_ < 0) g = -g;
    if (x_ == 0 && y_ < 0) g = -g;
    if (x_ == 0 && y_ == 0 && z_ < 0) g = -g;

    if (g != 0) {
      x = x_ / g;
      y = y_ / g;
      z = z_ / g;
    } else {
      x = y = z = 0;
    }
    */
    x = x_;
    y = y_;
    z = z_;
  }

  Vector(): x(0), y(0), z(0) {}

  Vector cross(const Vector& r) const {
    return Vector(
        y * r.z - z * r.y,
        z * r.x - x * r.z,
        x * r.y - y * r.x);
  }

  const bool operator< (const Vector& r) const {
    if (x != r.x) return x < r.x;
    if (y != r.y) return y < r.y;
    return z < r.z;
  }

  const bool operator== (const Vector& r) const {
    //return x == r.x && y == r.y && z == r.z;
    Vector c = cross(r);
    return c.x == 0 && c.y == 0 && c.z == 0;
  }

  const bool operator!= (const Vector& r) const { return !operator==(r); }
};

class SpanBF {
  vector<Vector> eiei;
  Vector spc;

public:
  SpanBF(Vector spc_): spc(spc_) { }

  void add(Vector v) {
    eiei.push_back(v);
  }

  void remove(Vector v) {
    int n = eiei.size();
    for (int i = 0; i < n; i++) {
      if (eiei[i] == v) {
        eiei.erase(eiei.begin() + i);
        return;
      }
    }
    // eiei.erase(find(eiei.begin(), eiei.end(), v));
  }

  bool query1() {
    int n = eiei.size();
    for (int i = 0; i < n; i++) {
      if (eiei[i] == spc) {
        return true;
      }
    }
    return false;
    // return find(eiei.begin(), eiei.end(), spc) != eiei.end();
  }

  bool query2() {
    int n = eiei.size();
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        if (eiei[i].cross(spc) == spc.cross(eiei[j])) return true;
      }
    }
    return false;
  }

  bool query3() {
    int n = eiei.size();
    if (n < 3) return false;
    Vector plane;
    bool foundPlane = false;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        if (!foundPlane) {
          if (eiei[i] != eiei[j]) {
            plane = eiei[i].cross(eiei[j]);
            foundPlane = true;
          }
        } else {
          if (eiei[i].cross(eiei[j]) != plane) return true;
        }
      }
    }
    return false;
  }
};

class Span3 {
private:
  set<Vector> buffer;

  int workingSize = 0;
  set<Vector> inPlane;
  Vector thePlane;
  Vector outPlane;
  bool outPlaneExist = false;

  void fillWorking() {
    while (!outPlaneExist && !buffer.empty()) {
      auto it = buffer.begin();
      Vector toAdd = *it;
      buffer.erase(it);

      const Vector& u = *inPlane.begin();
      if (u.cross(toAdd) == thePlane) {
        inPlane.insert(toAdd);
      } else {
        outPlane = toAdd;
        outPlaneExist = true;
      }
      workingSize++;
    }
  }

  void print() {
    printf("buffer:\n");
    for (auto& v : buffer) {
      printf("-- %lld %lld %lld\n", v.x, v.y, v.z);
    }
    printf("inPlane:\n");
    for (auto& v : inPlane) {
      printf("-- %lld %lld %lld\n", v.x, v.y, v.z);
    }
    printf("thePlane: %lld %lld %lld\n", thePlane.x, thePlane.y, thePlane.z);
    printf("outPlane: %lld %lld %lld\n", outPlane.x, outPlane.y, outPlane.z);
    printf("outPlaneExist: %d\n", outPlaneExist);
    fflush(stdout);
  }

public:
  void add(Vector v) {
    if (workingSize == 0) {
      inPlane.insert(v);
      workingSize++;
    } else if (workingSize == 1) {
      const Vector& u = *inPlane.begin();
      inPlane.insert(v);
      thePlane = u.cross(v);
      workingSize++;
    } else {
      buffer.insert(v);
      fillWorking();
    }
#ifdef DEBUG
    print();
#endif
  }

  void remove(Vector v) {
    auto it = buffer.find(v);
    if (it != buffer.end()) {
      buffer.erase(it);
      return;
    }

    if (outPlaneExist && outPlane == v) {
      outPlaneExist = false;
      workingSize--;
      fillWorking();
      return;
    }

    it = inPlane.find(v);
    if (it != inPlane.end()) {
      inPlane.erase(it);
      workingSize--;
      if (inPlane.size() == 1 && outPlaneExist) {
        outPlaneExist = false;
        const Vector& u = *inPlane.begin();
        inPlane.insert(outPlane);
        thePlane = u.cross(outPlane);
        fillWorking();
      }
    }
#ifdef DEBUG
    print();
#endif
  }

  bool query() {
    return outPlaneExist;
  }
};

class Span {
private:
  Vector spc;
  map<Vector, int> cnt;

  // span 2
  map<Vector, int> plane;
  int hist1 = 0;
  int hist2 = 0;

  Span3 span3;

public:
  Span(const Vector& spc_): spc(spc_) {}

  void add(Vector v) {
    int& c = cnt[v];
    c++;
    if (c > 1) return;

    // span 3
    span3.add(v);

    if (v == spc) return;

    // span 2
    Vector p = spc.cross(v);
    int& tt = plane[p];
    tt++;
    if (tt == 1) {
      hist1++;
    } else if (tt == 2) {
      hist1--;
      hist2++;
    }
  }

  void remove(Vector v) {
    int& c = cnt[v];
    assert(c > 0);
    c--;
    if (c > 0) return;

    span3.remove(v);

    if (v == spc) return;

    // span 2
    Vector p = spc.cross(v);
    int& tt = plane[p];
    tt--;
    if (tt == 0) {
      hist1--;
    } else if (tt == 1) {
      hist2--;
      hist1++;
    }
  }

  bool query1() {
    return cnt[spc] > 0;
  }

  bool query2() {
    return hist2 > 0;
  }

  bool query3() {
    return span3.query();
  }
};

int main() {
  int a, b, c;
  scanf("%d%d%d", &a, &b, &c);
  SpanBF span(Vector(a, b, c));
  vector<Vector> shelf;
  int n;
  scanf("%d", &n);
  char x;
  while (n--) {
    scanf(" %c", &x);
    if (x == 'A') {
      scanf("%d%d%d", &a, &b, &c);
      Vector v(a, b, c);
#ifdef DEBUG
      printf("--> add %d : %lld %lld %lld\n", (int)shelf.size(), v.x, v.y, v.z);
#endif
      span.add(v);
      shelf.push_back(v);
    } else {
      scanf("%d", &a);
#ifdef DEBUG
      Vector& v = shelf[a - 1];
      printf("--> rem : %lld %lld %lld\n", v.x, v.y, v.z);
#endif
      span.remove(shelf[a - 1]);
    }

#ifdef DEBUG
    printf("%d %d %d\n", span.query1(), span.query2(), span.query3());
#else
    if (span.query1()) printf("1\n");
    else if (span.query2()) printf("2\n");
    else if (span.query3()) printf("3\n");
    else printf("0\n");
#endif
    fflush(stdout);
  }

  return 0;
}
