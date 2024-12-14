#include <bits/stdc++.h>

char map[200][200];
// bool vis[200][200];
int tmp[200][200][200];
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
int dstX, dstY, ans = 0, t, n, m;

int dfs(int x, int y, int stp) {
  if (stp > t) {
    return 0;
  }
  if (tmp[x][y][stp] != -1) {
    return tmp[x][y][stp];
  }
  if (x == dstX and y == dstY && stp == t) {
    ++ans;
    tmp[x][y][stp] = 1;
    return 1;
  }
  // vis[x][y] = true;
  int cnt = 0;
  for (int i = 0; i < 4; ++i) {
    int _dx = x + dx[i], _dy = y + dy[i];
    if (x > 0 && y > 0 && x <= n && y <= m && map[_dx][_dy] == '.') {
      cnt += dfs(_dx, _dy, stp + 1);
    }
  }
  tmp[x][y][stp] = cnt;
  // vis[x][y] = false;
  return cnt;
}

signed main() {
  std::cin >> n >> m >> t;
  memset(tmp, -1, sizeof(tmp));
  // for (int i = 0; i <= m + 1; ++i) {
  //     for (int j = 0; j <= n + 1; ++j)
  // map[j][i] = '*';
  // }
  for (int i = 1; i <= n; ++i) {
    // std::string src;
    // std::cin >> src;
    for (int j = 1; j <= m; ++j) {
      std::cin >> map[i][j];
    }
  }
  int sx, sy;
  std::cin >> sx >> sy >> dstX >> dstY;
  ;
  std::cout << dfs(sx, sy, 0);
  return 0;
}
