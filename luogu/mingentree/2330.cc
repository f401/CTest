#include <algorithm>
#include <iostream>
#define N 4000
int fa[N], n;

void construct() {
  for (int i = 1; i <= n; ++i) {
    fa[i] = i;
  }
}

int find(int x) {
  if (fa[x] != x) {
    fa[x] = find(fa[x]);
  }
  return fa[x];
}
bool merge(int a, int b) {
  int x = find(a), y = find(b);
  if (x != y) {
    fa[x] = y;
    return true;
  }
  return false;
}

struct Edge {
  int u, v, w;
} e[N * N];

int main(int argc, char *argv[]) {
  int m;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= m; ++i) {
    std::cin >> e[i].u >> e[i].v >> e[i].w;
  }
  std::sort(e + 1, e + 1 + m, [](auto &a, auto &b) { return a.w < b.w; });
  construct();
  int count = 0, max = 0;
  for (int i = 1; i <= m; ++i) {
	  if (merge(e[i].u, e[i].v)) {
		  max = std::max(max, e[i].w);
		  ++count;
	  }
  }
  printf("%d %d", count, max);
  return 0;
}
