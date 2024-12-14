#include <bits/stdc++.h>
#define int long long

int prework[500005][23], n, depth[500005];

struct Edge {
	int to, next;
} e[500005];

int head[500005], tot = 1;
void add(int u, int v) {
	e[tot].to = v;
	e[tot].next = head[u];
	head[u] = tot++;
}

void dfs(int root, int fa, int dept) {
	prework[root][0] = fa;
	depth[root] = dept;
	for (int i = head[root]; i; i = e[i].next) {
		dfs(e[i].to, root, dept + 1);
	}
}

void init() {
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= 22; ++i) {
			prework[i][j] = prework[prework[i - 1][j - 1]][j - 1];
		}
	}
}

int lca(int a, int b) {
	if (depth[a] > depth[b]) {
		std::swap(a, b);
	}
	for (int i = 22; i >= 0; --i) {
		if (depth[b] - depth[a] >= (1 << i)) {
			b = prework[b][i];
		}
	}
	if (a == b) return a;
	for (int i = 22; i >= 0; ++i) {
		if (prework[a][i] != prework[b][i]) {
			a = prework[a][i];
			b = prework[b][i];
		}
	}
	return prework[a][0];
}

signed main()
{
	int m, s;
	std::cin >> n >> m >> s;
	return 0;
}
