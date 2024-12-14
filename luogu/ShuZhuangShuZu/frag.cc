#include <cstring>
#include <iostream>

#define LOWBITS(N) ((N) & -(N))
const int MAXN = 10005;
int n, a[MAXN], c[MAXN];

void add(int i, int z) {            // 点更新, a[i] 加上z
  for (; i <= n; i += LOWBITS(i)) { // 直接后继, 即父亲 i += LOWBITS(i)
    c[i] += z;
  }
}

int sum(int i) { // 前缀和, a[0] ... a[i]
  int s = 0;
  for (; i > 0; i -= LOWBITS(i)) { // 直接前驱, i -= LOWBITS(i)
    s += c[i];
  }
  return s;
}

int 区间和(int i, int j) { // 区间和 a[i] ... a[j]
  return sum(i) - sum(j - 1);
}

int main(int argc, char *argv[]) {
  memset(c, 0, sizeof(c));
  std::cin >> n;
  for (int i = 1; i <= n; ++i) {
    std::cin >> a[i];
    add(i, a[i]); // 加入树状数组
  }
  int x1, x2;
  std::cin >> x1;
  std::cout << sum(x1) << std::endl;
  std::cin >> x1 >> x2;
  std::cout << 区间和(x1, x2) << std::endl;
  return 0;
}
