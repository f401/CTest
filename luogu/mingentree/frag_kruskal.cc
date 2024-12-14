#include <algorithm>
#include <iostream>

#define N 1005
int fa[N];
int n, m;
struct Edge {
  int u, v, w;
} e[N * N];

static void init(int n) {
  for (int i = 1; i < n; i++) {
    fa[i] = i;
  }
}

static int find(int x) {
  if (x != fa[x])
    fa[x] = find(fa[x]);
  return fa[x];
}

static bool merge(int a, int b) {
  int p = find(a);
  int q = find(b);
  if (p == q) {
    return false;
  }
  fa[q] = p;
  return true;
}

static int kruskal(int n) {
  int ans = 0, cnt = 0;
  for (int i = 0; i < m; i++) {
    if (merge(e[i].u, e[i].v)) {
      ans += e[i].w;
      ++cnt;
      if (cnt == n - 1) {
        return ans;
      }
    }
  }
  return 0;
}

int main(int argc, char *argv[]) {
  int t;
  std::cin >> t;
  while (t--) {
    std::cin >> n >> m;
    init(n);
    for (int i = 0; i < m; i++) {
      std::cin >> e[i].u >> e[i].v >> e[i].w;
    }
    std::sort(e, e + m, [](const auto &a, const auto &b) { return a.w < b.w; });
	std::cout << kruskal(n) << std::endl;
  }
  return 0;
}
