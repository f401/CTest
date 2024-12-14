#include <iostream>
#include <cmath>
const int N = 300000;

int F[N][21], a[N];
int n;

void ST_Create() {// N log2 N
  for (int i = 1; i <= n; ++i) {
    F[i][0] = a[i];
  }
  int k = log2(n);
  for (int j = 1; j <= k; ++j) {
    for (int i = 1; i <= n - (1 << j) + 1; ++i) {
      F[i][j] = std::max(F[i][j - 1], F[i + (1 << (j - 1))][j - 1]);
    }
  }
}

int ST_Query(int l, int r) {
	int k = log2(r - l + 1);
	return std::max(F[l][k], F[r - (1 << k) + 1][k]);
}
int main(int argc, char *argv[])
{
	int m, tmp;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &tmp);
		a[i] = tmp;
	}
	ST_Create();
	for (int i = 1; i <= m; ++i) {
		int x, y;
		scanf("%d %d", &x, &y);
		printf("%d\n", ST_Query(x, y));
	}
	return 0;
}
