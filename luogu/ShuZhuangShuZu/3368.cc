#include <iostream>
#define LOWBITS(N) ((N) & -(N))
#define MAXN (500000)
int n;
int c[MAXN], src[MAXN];

void add(int i, int value) {
	for (; i <= n; i += LOWBITS(i)) {
		c[i] += value;
	}
}

void add(int l, int r, int value) {
	add(l, value);
	add(r + 1, -value);
}

int getsum(int l) {
	int s = 0;
	for (; l > 0; l -= LOWBITS(l)) {
		s += c[l];
	}
	return s;
}

int main(int argc, char *argv[])
{
	int m, tmp;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &tmp);
		src[i] = tmp;
		add(i, src[i] - src[i -1]);
	}
	int op;
	while (m--) {
		scanf("%d", &op);
		if (op == 1) {
			int x, y, k;
			scanf("%d %d %d", &x, &y, &k);
			add(x, y, k);
		} else {
			int q;
			scanf("%d", &q);
			printf("%d\n", getsum(q));
		}
	}
	return 0;
}
