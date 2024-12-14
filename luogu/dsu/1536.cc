#include <iostream>
#define MAXN 500000

namespace dsu {
int fa[MAXN];

int find(int x) {
  if (x != fa[x])
    fa[x] = find(fa[x]);
  return fa[x];
}

void combine(int x, int y) {
  int a = find(x);
  int b = find(y);
  if (a != b)
    fa[b] = a;
}

void constructor(int n) {
  for (int i = 1; i <= n; ++i) {
    fa[i] = i;
  }
}
} // namespace dsu

int main(int argc, char *argv[]) {
  for (;;) {
    int n, m;
    scanf("%d", &n);
	if (n == 0) {
		return 0;
	}
	scanf("%d", &m);
    dsu::constructor(n);
    for (int i = 1; i <= m; ++i) {
      int x, y;
      scanf("%d %d", &x, &y);
      dsu::combine(x, y);
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
      if (i == dsu::find(i))
        ++ans;
    }
    printf("%d\n", ans - 1);
  }
  return 0;
}
