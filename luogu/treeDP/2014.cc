#include <bits/stdc++.h>
#define MAXN 1500

struct {
	int to, next, w;
} e[MAXN << 1];

int head[MAXN], tot = 1;

void add(int u, int v, int w) {
	e[tot].to = v;
	e[tot].next = head[u];
	e[tot].w = w;
	head[u] = tot++;
}

int m, f[MAXN][MAXN];

void dfs(int u) {
	for (int i = head[u]; i; i = e[i].next) {
		int v = e[i].to;
		dfs(v);
		for (int j = m; j; --j) {
			for (int k = 0; k < j; ++k) {
				f[u][j] = std::max(f[u][j], f[u][j - k - 1] + f[v][k] + e[i].w);
			}
		}
	}
}

int main(int argc, char *argv[])
{
	int n;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		int s, k;
		scanf("%d %d", &s, &k);
		add(s, i, k);
	}
	dfs(0);
	printf("%d", f[0][m]);
	return 0;
}
