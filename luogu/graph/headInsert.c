#include <stdio.h>

struct Edge {
	int w, to, next;
} edge[10000];

int head[1000];

int cnt = 1;
// 无向图调用两次 add(u, v, w); add(v, u, w);
// 添加一条边u, v
void add(int u, int v, int w) {
	edge[cnt].to = v;
	edge[cnt].w = w;
	edge[cnt].next = head[u];
	head[u] = cnt++;
}

int n, m, x, y, w;

void printg() {
	for (int v = 0; v <= n; ++v) {
		printf("%d :", v);
		for (int i = head[v]; i; i = edge[i].next) {
			int v1 = edge[i].to, w1 = edge[i].w;
			printf("[%d %d, next: %d]\t", v1, w1, edge[i].next);
		}
		puts("");
	}
}

int main(void)
{
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d %d", &x, &y, &w);
		add(x, y, w);
		add(y, x, w);
	}
	printg();
	return 0;
}
