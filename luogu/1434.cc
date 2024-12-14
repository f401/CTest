#include <bits/stdc++.h>
// #define int short
const int N = 101;
int g[N][N];

int dx[] = {0, 1, -1, 0};
int dy[] = {1, 0, 0, -1};
int f[N][N];
const int NN = 4;
int r, c;

int dfs(int x, int y) {
    if (f[x][y] != -1) return f[x][y];
    int cnt = 1;
    for (int i = 0; i < NN; ++i) {
        int _dx = dx[i] + x, _dy = dy[i] + y;
        if (_dx > 0 && _dy > 0 && _dx <= r && _dy <= c && g[_dx][_dy] < g[x][y]) {
            cnt = std::max(cnt, dfs(_dx, _dy) + 1);
        }
    }
    f[x][y] = cnt;
    return cnt;
}

signed main() {
  std::cin >> r >> c;
  memset(f, -1, sizeof f);
  for (int i = 1; i <= r; ++i) {
    for (int j = 1; j <= c; ++j) {
      std::cin >> g[i][j];
    }
  }
  int ans = 0;
  for (int i = 1; i <= r; ++i) 
    for (int j = 1; j <= c; ++j)
      ans = std::max(ans, dfs(i, j));
  std::cout << ans;
  return 0;
}
