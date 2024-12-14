#include <cstring>
#include <iostream>
#include <queue>

#define INF (0x3f3f3f3f)

long dist[320000], head[320000], cost[320000];
int n, b;

struct {
  int to, w, next;
} edges[5000000];
struct Node {
  int idx;
  long dist;

  friend bool operator<(const Node &left, const Node &right) {
    return right.dist < left.dist;
  }
};
int cnt;

void addedge(int u, int v, int w) {
  edges[++cnt].w = w;
  edges[cnt].next = head[u];
  edges[cnt].to = v;
  head[u] = cnt;
}

std::priority_queue<Node> queue;

bool dijs(bool *visited, int start, int cst) {
  if (cost[1] > cst) return false;
  for (int i = 1; i <= n; ++i) {
    dist[i] = INF;
  }
  dist[start] = 0;
  queue.push({start, 0});
  while (queue.size()) {
    const Node &tmp = queue.top();
    int idx = tmp.idx;
    queue.pop();
    if (visited[idx]) {
      continue;
    }
    visited[idx] = true;
    for (int i = head[idx]; i; i = edges[i].next) {
      int y = edges[i].to;
      // dist[y] = std::min(dist[y], edges[i].w + dist[idx]);
      if (dist[y] > edges[i].w + dist[idx] && cost[y] <= cst) {
        dist[y] = edges[i].w + dist[idx];
        if (!visited[y]) {
          queue.push({y, dist[y]});
        }
      }
    }
  }
  return dist[n] <= b;
}

int main(int argc, char *argv[]) {
  int m, tmp, totalCost = 0, minCost = INF;
  scanf("%d %d %d", &n, &m, &b);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &tmp);
    cost[i] = tmp;
    totalCost = std::max(totalCost, tmp);
	minCost = std::min(minCost, tmp);
  }
  int u, v, w;
  for (int i = 1; i <= m; ++i) {
    scanf("%d %d %d", &u, &v, &w);
    addedge(u, v, w);
    addedge(v, u, w);
  }
  bool visited[n + 5];
  memset(visited, 0, sizeof(visited));

  ++totalCost;
  int left = minCost - 1, right = totalCost;
  while (left + 1 != right) {
    int mid = (left + right) >> 1;
    memset(visited, 0, sizeof(visited));
    if (dijs(visited, 1, mid)) {
      right = mid;
    } else {
      left = mid;
    }
  }
  if (right != totalCost)
    std::cout << right;
  else
    std::cout << "AFK";
  return 0;
}
