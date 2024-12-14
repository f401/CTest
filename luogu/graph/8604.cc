#include <iostream>

struct Edge {
  int to, next;
} edge[10000];

int head[1000];

int cnt = 1;
// 无向图调用两次 add(u, v, w); add(v, u, w);
// 添加一条边u, v
void add(int u, int v) {
  edge[cnt].to = v;
  edge[cnt].next = head[u];
  head[u] = cnt++;
}

int n, m, x, y, w, count = 0;
int result[10000];

void dfs(bool *visited, int u, int v) {
  if (u == v) {
    count++;
    for (int i = 1; i <= n; ++i) {
      if (visited[i]) {
        result[i]++;
      }
    }
    return;
  }
  for (int i = head[u]; i; i = edge[i].next) {
    if (!visited[edge[i].to]) {
      visited[edge[i].to] = 1;
      dfs(visited, edge[i].to, v);
      visited[edge[i].to] = 0;
    }
  }
}

int main(void) {
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= m; ++i) {
    scanf("%d %d", &x, &y);
    add(x, y);
    add(y, x);
  }
  int u, v;
  scanf("%d %d", &u, &v);
  bool visited[10000];
  dfs(visited, u, v);
  if (cnt < 0) {
	  printf("-1");
  } else {
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		if (result[i] == count) {
			ans ++;
		}
	}
	ans--;
	printf("%d", ans);
  }
  return 0;
}
