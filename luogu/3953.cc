#include <bits/stdc++.h>
#define int long long
#define INF 0x3f3f3f3f3f3f3f3f
const int N = 1e6+5;

struct Edge {
	int to, next, w;

	void reset() { memset(this, 0, sizeof(Edge)); }
} e1[N], e2[N], e3[N];
int head1[N], head2[N], head3[N], dfn[N], low[N], dist1[N], dist2[N], k, p, f[N][55];
bool vis[N], instk[N], belongZero[N];

template <typename T> void gmax(T &&a, T &&b) { a = std::max(a, b); }
template <typename T> void gmin(T &&a, T &&b) { a = std::min(a, b); }

int n;

class Graph final {
public:
  Graph(int *head, Edge *e) : _head(head), _e(e), tot(0) {
    for (int i = 0; i <= n; ++i) {
      _head[i] = 0;
	  _e[i].reset();
    }
  }

  void dijstr(int start, int *dist, bool *vis) noexcept {
	  for (int i = 0; i <= n; ++i) dist[i] = INF, vis[i] = 0;
	  dist[start] = 0;
	  std::priority_queue<Node> queue;
	  queue.push({start, 0});
	  while (queue.size()) {
	  	  Node top = queue.top(); queue.pop();
		  int u = top.to;
		  if (vis[u]) continue;
		  vis[u] = true;
		  for (int e = _head[u]; e; e = _e[e].next) {
			  int v = _e[e].to, w = _e[e].w;
			  if (dist[v] > dist[u] + w) {
				  dist[v] = dist[u] + w;
				  queue.push({v, dist[v]});
			  }
		  }
	  }
  }

  void add(int u, int v, int w) {
	_e[++tot].to = v;
	_e[tot].w = w;
	_e[tot].next = _head[u];
	_head[u] = tot;
  }

  void tarjan(int root, int& cnt, int *dfn, int *low, bool *instk, bool *belongZero, std::stack<int> &stk) {
	  dfn[root] = low[root] = ++cnt, instk[root] = true;
	  stk.push(root);
	  for (int e = _head[root]; e; e = _e[e].next) {
		  int v = _e[e].to;
		  if (!dfn[v]) {
			  tarjan(v, cnt, dfn, low, instk, belongZero, stk);
			  gmin(low[root], low[v]);
		  } else if (instk[v]) gmin(low[root], dfn[v]);
	  }
	  if (dfn[root] == low[root]) {
		  if (stk.top() == root) { instk[root] = false, stk.pop(); return void(); }
		  int now = 0;
		  do {
			  now = stk.top(), stk.pop();
			  instk[now] = false;
			  belongZero[root] = true;
		  } while(now != root);
	  }
  }

private:
  int *_head, tot;
  Edge *_e;
  struct Node {
	  int to, v;
	  friend bool operator<(const Node &l, const Node &r) { return l.v > r.v; }
  };
};

int dfs(int root, int k) { // left k
	if (f[root][k] != INF)  {return f[root][k]; }
	f[root][k] = 0;
	//fprintf(stderr, "head2[%lld]=%lld\n", root, head2[root]);
	for (int e = head2[root]; e; e = e2[e].next) {
		int v = e2[e].to, left = dist1[root] - dist1[v] - e2[e].w + k;
		if (left >= 0) 
			(f[root][k] += dfs(v, left)) %= p;
		//fprintf(stderr, "Travel from %lld to %lld, left %lld, d1: %lld, d2: %lld, w: %lld\n", root, v, left, dist1[root], dist2[root], e2[e].w);
	}
	//fprintf(stderr, "root: %lld, k: %lld, f: %lld\n", root, k, f[root][k]);
	return f[root][k];
}

signed main() {
	int __T;
	std::cin >> __T;
	while (__T--) {
		int m;
		std::cin >> n >> m >> k >> p;
	    for (int i = 0; i <= n; ++i) dfn[i] = low[i] = instk[i] = belongZero[i] = 0;
		Graph g1(head1, e1), g2(head2, e2), g3(head3, e3);
		while (m--) {
			int u, v, w;
			std::cin >> u >> v >> w;
			g1.add(u, v, w);
			g2.add(v, u, w);
			if (w == 0) g3.add(u, v, w);
		}
		g1.dijstr(1, dist1, vis), g2.dijstr(n, dist2, vis);
		{
			int cnt = 0;
			std::stack<int> st;
			for (int i = 1; i <= n; ++i)
				if (!dfn[i]) g3.tarjan(i, cnt, dfn, low, instk, belongZero, st);
		}
		bool flg = false;
		for (int i = 1; i <= n; ++i) 
			if (belongZero[i] && dist1[i] + dist2[i] <= dist1[n] + k) { puts("-1"); flg = true; break; }
		if (flg) continue;
		memset(f, 0x3f, sizeof f);
		int ans = 0;
		f[1][0] = 1;
		for (int i = 0; i <= k; ++i) (ans += dfs(n, i)) %= p;
		std::cout << ans << std::endl;
	}
	return 0;
}
