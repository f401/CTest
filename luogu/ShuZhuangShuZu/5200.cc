#include <iostream>
#define LOWBIT(N) ((N) & -(N))
constexpr inline const int MAXN = 500000;

int n, a[MAXN], c[MAXN];

void add(int i, int k) {
  for (; i <= n; i += LOWBIT(i)) {
    c[i] += k;
  }
}

int sum(int v) {
  int r = 0;
  for (; v > 0; v -= LOWBIT(v)) {
    r += c[v];
  }
  return r;
}

int main(int argc, char *argv[]) {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  int k = n - 1;
  while (k > 0 && a[k] < a[k + 1])
    k--;
  printf("%d\n", k);
  for (int i = k + 1; i <= n; i++) {
    add(a[i], 1);
  }
  for (int i = 1; i <= k; i++) {
    printf("%d ", k - i + sum(a[i]));
    add(a[i], 1);
  }
  return 0;
}
