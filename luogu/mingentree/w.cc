#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#define inf 0x3f3f3f3f
#define N 1005
using namespace std;
int fa[N], n, m, k;

struct Edge {
  int u, v, w;
} e[10005];

bool cmp(Edge x, Edge y) { return x.w < y.w; }

void init(int n) {
  for (int i = 1; i <= n; i++)
    fa[i] = i;
}

int find(int x) {
  if (x != fa[x])
    fa[x] = find(fa[x]);
  return fa[x];
}

bool merge(int a, int b) {
  int p = find(a), q = find(b);
  if (p == q)
    return false;
  fa[q] = p;
  return true;
}

int kruskal(int n) {
  int ans = 0, cnt = 0;
  for (int i = 1; i <= m; i++)
    if (merge(e[i].u, e[i].v)) {
      ans += e[i].w, cnt++;
      if (cnt >= n - k)
        return ans;
    }
  return ans;
}

int main() {
  scanf("%d%d%d", &n, &m, &k);
  init(n);
  for (int i = 1; i <= m; i++)
    scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
  sort(e + 1, e + m + 1, cmp);
  printf("%d", kruskal(n));
  return 0;
}
