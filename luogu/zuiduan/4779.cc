#include <iostream>
#include <queue>

const int INF = 0x3f3f3f;
int cnt, head[100010], p[100010];
bool visited[100010];
long long dist[100010];
int n, m, s, t;
struct e {
	int to, nextt, w;
} edge[200010];

void addnode(int u, int v, int w) {
	edge[++cnt].to = v;
	edge[cnt].w = w;
	edge[cnt].to = head[u];
	head[u] = cnt;
}

struct Node {
	long long dist;
	int pos;
};


struct cmp {
	bool operator() (const Node &left, const Node &right) const noexcept {
		return right.dist < left.dist;
	}
};

void dijk() {
	dist[s] = 0;
	std::priority_queue<Node, std::vector<Node>, cmp> queue;  
	queue.push({0, s});
	while (queue.size()) {
		Node tmp = queue.top();
		queue.pop();
		int x = tmp.pos;
		if (visited[x]) continue;
		visited[x] = true;
		for (int i = head[x]; i; i = edge[i].nextt) {
			int y = edge[i].to;
			if (dist[y] > dist[x] + edge[i].w) {
				dist[y] = dist[x] + edge[i].w;
			}
			if (!visited[y]) {
				queue.push({dist[y], y});
			}
		}
	}
}

int main(int argc, char *argv[])
{
	std::cin >> n >> m >> s;
	for (int i = 1; i <= n; ++i) {
		dist[i] = INF;
	}
	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		addnode(u, v, w);
	}
	dijk();
	for (int i = 1; i <= m; ++i) {
		printf("%lld ", dist[i]);
	}
	return 0;
}


