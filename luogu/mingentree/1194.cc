#include <algorithm>
#include <cstring>
#include <iostream>
#include <iterator>
#include <vector>
#define N 10005

class DSU final {
public:
  DSU(int n) : n(n) {
    memset(fa, 0, N);
    for (int i = 0; i <= n; ++i) {
      fa[i] = i;
    }
  }

  int find(int x) noexcept {
    if (fa[x] != x) {
      fa[x] = find(fa[x]);
    }
    return fa[x];
  }

  bool merge(int a, int b) noexcept {
    int p = find(a);
    int q = find(b);
    if (p != q) {
      fa[q] = p;
      return true;
    }
    return false;
  }

private:
  int fa[N];
  int n;
};

struct Edge {
  int u, v, w;
  friend std::ostream &operator<<(std::ostream &input, const Edge &edge) {
    input << "Edge { u: " << edge.u << ", v: " << edge.v << ", w: " << edge.w
          << "}";
    return input;
  }
};
std::vector<Edge> e;

class Kruskal final {
public:
  Kruskal(int n, int edgeCount) : dsu(n), n(edgeCount) {}

  int run() noexcept {
    int ans = 0, count = 0;
    for (int i = 1; i <= n; ++i) {
      if (dsu.merge(e[i].u, e[i].v)) {
        ans += e[i].w;
        ++count;
        if (count == n) {
          return ans;
        }
      }
    }
    return ans;
  }

private:
  int n;
  DSU dsu;
};

int main(int argc, char *argv[]) {
  int a, b;
  scanf("%d %d", &a, &b);
  e.push_back({});
  for (int i = 1; i <= b; ++i) {
    e.push_back({0, i, a});
    for (int j = 1; j <= b; ++j) {
      int tmp;
      scanf("%d", &tmp);
      if (i < j && tmp != 0) {
        e.push_back({i, j, tmp});
      }
    }
  }
  std::sort(e.begin(), e.end(),
            [](const auto &a, const auto &b) { return a.w < b.w; });
  printf("%d", Kruskal(b, e.size() - 1).run());
  return 0;
}
