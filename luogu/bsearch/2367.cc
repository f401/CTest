#include <algorithm>
#include <iostream>
#include <iterator>
#include <string.h>
#include <vector>

int main(int argc, char *argv[]) {
  int n, p, tmp;
  scanf("%d %d", &n, &p);
  int src[n + 1], chafen[n + 1];
  memset(src, 0, sizeof(src));
  memset(chafen, 0, sizeof(chafen));
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &tmp);
	src[i] = tmp;
	chafen[i] = src[i] - src[i - 1];
  }
  while (p--) {
    int x, y, z;
    scanf("%d %d %d", &x, &y, &z);
    chafen[x] += z;
    chafen[y + 1] -= z;
  }

  int min = 101;
  for (int i = 1; i <= n; ++i) {
    chafen[i] += chafen[i - 1];
    min = std::min(min, chafen[i]);
  }
  std::cout << min;

  return 0;
}
