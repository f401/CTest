#include <iostream>
#include <string.h>

#define INSERT(DATA, L, R, C)                                                  \
  do {                                                                         \
    DATA[L] += C;                                                              \
    DATA[R + 1] -= C;                                                          \
  } while (0)

bool checkNegative(int *data) {
	
}

int main(int argc, char *argv[]) {
  int n, m, tmp;
  scanf("%d %d", &n, &m);
  int data[n + 1], real[n + 1];
  memset(data, 0, sizeof(data));
  memset(real, 0, sizeof(real));

  for (int i = 1; i <= n; ++i) {
    scanf("%d", &tmp);
    data[i] = tmp - data[i - 1];
  }
  int d, s, t;
  while (m--) {
    scanf("%d %d %d", &d, &s, &t);
    INSERT(data, s, t, -d);
  }
  return 0;
}
