#include <iostream>
#include <cstring>

struct Edge {
	int to, next, w;
} edges[1000];

int head[1000];
int count = 1;
int n, m, result;

void add(int from, int to, int weight) 
{
	edges[count].to = to;
	edges[count].w = weight;
	edges[count].next = head[from];
	head[from] = count++;
}

void dfs(bool *visited, int current, int currWeight) 
{
	if (currWeight > result) {
		result = currWeight;
	}
	for (int index = head[current]; index; index = edges[index].next) {
		if (!visited[edges[index].to]) {
			visited[edges[index].to] = true;
			dfs(visited, edges[index].to, currWeight + edges[index].w);
			visited[edges[index].to] = false;
		}
	}
}

int main(int argc, char *argv[])
{
	scanf("%d %d", &n, &m);
	int x, y, w;
	while (m--) {
		scanf("%d %d %d", &x, &y, &w);
		add(x, y, w);
		add(y, x, w);
	}
	bool visited[n + 5];
	for (int i = 1; i <= n; ++i) {
		memset(visited, 0, sizeof(visited));
		visited[i] = true;
		dfs(visited, i, 0);
	}
	printf("%d", result);
	return 0;
}
