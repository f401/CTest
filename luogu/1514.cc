#include <bits/stdc++.h>

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
const int DCNT = 4;

int map[600][600];
bool vis[600][600];

template <typename T> void gmin(T &&a, T &&b) { a = std::min(a, b); }

template <typename T> void gmax(T &&a, T &&b) { a = std::max(a, b); }

struct Node {
  int v, idx;
  friend bool operator<(const Node &lhs, const Node &rhs) {
    return lhs.v < rhs.v;
  }
};

struct Pos {
  int x, y;
  friend bool operator<(const Pos &lhs, const Pos &rhs) {
    return lhs.x != rhs.x ? lhs.x < rhs.x : lhs.y > rhs.y;
  }
};

signed main() {
  int n, m;
  std::cin >> n >> m;
  std::priority_queue<Node> free;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      int tmp;
      std::cin >> tmp;
      if (i == 1)
        free.push({tmp, j});
      map[i][j] = tmp;
    }
  }
  while (free.size()) {
    Node _top = free.top();
    free.pop();
    std::queue<Pos> queue;
    if (vis[1][_top.idx])
      continue;
    queue.push({1, _top.idx});
    while (queue.size()) {
      Pos top = queue.front();
      queue.pop();
      if (vis[top.x][top.y])
        continue;
      vis[top.x][top.y] = true;
      for (int i = 0; i < DCNT; ++i) {
        int _dx = top.x + dx[i], _dy = top.y + dy[i];
        if (_dx > 0 && _dy > 0 && _dx <= n && _dy <= m &&
            map[_dx][_dy] < map[top.x][top.y]) {
          queue.push({_dx, _dy});
        }
      }
    }
  }
  int ans = 0;
  for (int i = 1; i <= m; ++i)
    if (!vis[n][i])
      ++ans;
  if (ans != 0)
    printf("0\n%d", ans);
  else {
    std::vector<Pos> ranges;
    std::vector<int> xPts;
    for (int i = 1; i <= m; ++i) {
      int l = 0x3f3f3f3f, r = 0;
      std::queue<Pos> queue;
      queue.push({1, i});
      while (queue.size()) {
        Pos top = queue.front();
        queue.pop();
        if (top.x == n) {
          gmin(l, top.y);
          gmax(r, top.y);
        }
        for (int i = 0; i < DCNT; ++i) {
          int _dx = top.x + dx[i], _dy = top.y + dy[i];
          if (_dx > 0 && _dy > 0 && _dx <= n && _dy <= m &&
              map[_dx][_dy] < map[top.x][top.y]) {
            queue.push({_dx, _dy});
          }
        }
      }
      if (l != 0x3f3f3f3f && r != 0) {
        ranges.push_back({l, r});
	  }
    }
	std::sort(ranges.begin(), ranges.end());
    fprintf(stderr, "range Size: %ld\n", ranges.size());
    int cnt = 0, st = 1, k = 0;
    while (st <= m && k < ranges.size()) {
		int mx = -1;
		while (k < ranges.size() && ranges[k].x <= st) {
			gmax(mx, ranges[k].y);
			++k;
		}
		st = mx + 1;
		++cnt;
    }
    printf("1\n%d", cnt);
  }
  return 0;
}
