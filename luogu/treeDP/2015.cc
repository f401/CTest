#include <bits/stdc++.h>

struct {
  int v, w, next;
} e[300];

int head[105], tot = 1;

void add(int u, int v, int w) {
  e[tot].v = v;
  e[tot].next = head[u];
  e[tot].w = w;
  head[u] = tot++;
}

int n, q, f[105][105];

void dfs(int root, int fa) {
  for (int i = head[root]; i; i = e[i].next) {
    int v = e[i].v;
    if (v == fa)
      continue;
    dfs(v, root);
    for (int j = q; j; --j)
      for (int k = 0; k < j; ++k)
        f[root][j] = std::max(f[root][j], f[root][j - k - 1] + f[v][k] + e[i].w);
  }
}

int main(int argc, char *argv[]) {
  scanf("%d %d", &n, &q);
  for (int i = 1; i < n; ++i) {
    int x, y, z;
    scanf("%d %d %d", &x, &y, &z);
    add(x, y, z);
    add(y, x, z);
  }
  dfs(1, 0);
  printf("%d", f[1][q]);

  return 0;
}
