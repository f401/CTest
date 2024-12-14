#include <bits/stdc++.h>

#define int long long

int f[500000][23], n;

void build() {
  for (int j = 1; j <= log2(n); ++j) {
    for (int i = 1; i <= n; ++i) {
      f[i][j] = std::max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
    }
  }
}

signed main() {
  int m;
  scanf("%lld %lld", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%lld", f[i]);
  }
  build();
  while (m--) {
    int l, r;
    scanf("%lld %lld", &l, &r);
    int k = log2(r - l + 1);
    printf("%lld\n", std::max(f[l][k], f[r - (1 << k) + 1][k]));
  }
  return 0;
}
