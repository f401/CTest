#include <bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define int long long

long long g[2000][2000], dist[2000000];
std::vector<std::pair<int, int>> tmpG[2000][2000];

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, -1, 0, 1}, DIRS = 4;

struct Edge {
  int to, next, w;
} e[4000000];
int tot, head[4000000], m;
void add(int u, int v, int w) {
  e[++tot].to = v;
  e[tot].w = w;
  e[tot].next = head[u];
  head[u] = tot;
}

struct Node {
  int weight, to;
  friend bool operator<(const Node &l, const Node &r) {
    return l.weight > r.weight;
  }
};

int p(int x, int y) { return (x - 1) * m + y; }

bool vis[2000000];

void dijstra() {
  std::priority_queue<Node> queue;
  dist[p(1, 1)] = 0;
  queue.push({0, p(1, 1)});
  while (queue.size()) {
    Node node = queue.top();
    queue.pop();
    if (vis[node.to])
      continue;
    vis[node.to] = true;
    for (int i = head[node.to]; i; i = e[i].next) {
      int v = e[i].to, w = e[i].w;
      if (dist[v] > dist[node.to] + w) {
        dist[v] = dist[node.to] + w;
        printf("Got point from %lld to %lld w %lld\n", node.to, v, dist[v]);
        queue.push({dist[v], v});
      }
    }
  }
}

bool has(int i, int j, int &dX, int &dY) {
  for (auto [x, y] : tmpG[dX][dY])
    if (g[i][j] == g[x][y]) {
      dX = x, dY = y;
      return true;
    }
  return false;
}

signed main() {
  memset(dist, 0x3f, sizeof dist);
  int n;
  std::cin >> m >> n;
  while (n--) {
    int x, y, c;
    std::cin >> x >> y >> c;
    g[x][y] = c + 1;
  }
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= m; ++j) {
      for (int k = 0; k < DIRS; ++k) {
        int dX = i + dx[k], dY = j + dy[k];
        if (tmpG[dX][dY].size()) {
          for (auto [x, y] : tmpG[dX][dY])
            add(p(x, y), p(i, j), 2 + (g[i][j] != g[x][y]));
          if (g[i][j] != 0) {
            if (g[i][j] == g[dX][dY]) {
              add(p(dX, dY), p(i, j), 0);
              // printf("Link0 (%lld, %lld)(%lld) and (%lld, %lld)(%lld)\n", dX,
              // dY,
              //        p(dX, dY), i, j, p(i, j));
            } else if (g[dX][dY]) {
              add(p(dX, dY), p(i, j), 1);
              // printf("Link1 (%lld, %lld)(%lld) and (%lld, %lld)(%lld)\n", dX,
              // dY,
              //        p(dX, dY), i, j, p(i, j));
            } else {
              // printf("Link2 (%lld, %lld)(%lld) and (%lld, %lld)(%lld)\n", i,
              // j,
              //        p(i, j), dX, dY, p(dX, dY));
              tmpG[dX][dY].push_back({i, j});
            }
          }
        }
      }
    }
    if (tmpG[m][m].size()) {
      for (auto [x, y] : tmpG[m][m])
        add(p(x, y), p(m, m), 2);
    }

    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= m; ++j) {
        printf("%lld ", g[i][j]);
      }
      putchar('\n');
    }
    dijstra();
    std::cout << (dist[p(m, m)] == INF ? -1 : dist[p(m, m)]);
    return 0;
  }
