#include <iostream>
#include <algorithm>
#define N 20005
int fa[N], n;

void construct() {
	for (int i = 1; i <= n; ++i) {
		fa[i] = i;
	}
}

int find(int x) {
	if (x != fa[x]) {
		fa[x] = find(fa[x]);
	}
	return fa[x];
}

bool combine(int a, int b) {
	int x = find(a), 
		y = find(b);
	if (x != y) {
		fa[y] = x;
		return true;
	}
	return false;
}

struct Edge {
	int u, v, w;
} e[N * N];

int main(int argc, char *argv[])
{
	int m, k;
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= m; ++i) {
		std::cin >> e[i].u >> e[i].v >> e[i].w;
	}
	std::sort(e + 1, e + m + 1, [](const auto &a, const auto &b) {
		return a.w < b.w;
	});
	construct();
	int ans = 0;
	int count = 0;
	for (int i = 1; i <= m; ++i) {
		if (combine(e[i].u, e[i].v)) {
			ans += e[i].w;
			if (++count >= n - k) break;
		}
	}
	printf("%d", ans);
	return 0;
}
