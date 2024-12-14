#include <cstring>
#include <iostream>
#define MAXN 10000
int fa[MAXN], n;

int DSU_Find(int x) {
	if (fa[x] != x) {
		fa[x] = DSU_Find(fa[x]);
	}
	return fa[x];;
}

void DSU_Combine(int x, int y) {
	int a = DSU_Find(x);
	int b = DSU_Find(y);
	if (a != b) {
		fa[b] = a;
	}
}

int main(int argc, char *argv[])
{
	int m, p;
	scanf("%d %d %d", &n, &m, &p);
	for (int i = 1; i <= n; ++i) {
		fa[i] = i;
	}
	while (m--) {
		int x, y;
		scanf("%d %d", &x, &y);
		DSU_Combine(x, y);
	}

	while (p--) {
		int x, y;
		scanf("%d %d", &x, &y);
		if (DSU_Find(x) == DSU_Find(y)) {
			printf("Yes\n");
		} else {
			printf("No\n");
		}
	}

	return 0;
}
