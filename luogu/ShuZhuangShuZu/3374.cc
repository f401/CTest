#include <iostream>

#define LOWBITS(N) ((N) & -(N))
const int MAXN = 10005;
int n, a[MAXN], c[MAXN];

void add(int i, int z) {
	for (; i <= n; i += LOWBITS(i)) {
		c[i] += z;
	}
}

int sum(int i) {
	int s = 0;
	for (; i > 0; i -= LOWBITS(i)) {
		s += c[i];
	}
	return s;
}

int sum(int i, int j) {
	return sum(j) - sum(i - 1);
}

int main(int argc, char *argv[])
{
	int m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		int tmp;
		scanf("%d", &tmp);
		a[i] = tmp;
		add(i, tmp);
	}

	while (m--) {
		int op, x, k;
		scanf("%d %d %d", &op, &x, &k);
		if (op == 1) {
			add(x, k);
		} else {
			printf("%d\n", sum(x, k));
		}
	}
	return 0;
}
