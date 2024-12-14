#include <cstring>
#include <iostream>
#include <queue>

int n, m, x, y;
struct Position {
  int line, col;
};

int arr[404][404];

int off[][2] = {{-1, -2}, {1, -2}, {-1, 2}, {1, 2},
                {-2, -1}, {-2, 1}, {2, 1},  {2, -1}};
__attribute__((always_inline)) inline bool
isValidPos(const Position &pos) noexcept {
  return !(pos.line <= 0 || pos.col <= 0 || pos.line > n || pos.col > m);
}

void bfs(const Position &start) {
  std::queue<Position> queue;
  queue.push(start);
  bool visited[n + 2][m + 2];
  memset(visited, 0, sizeof(visited));
  while (queue.size()) {
    const Position &pos = queue.front();
    if (!isValidPos(pos)) {
      queue.pop();
      continue;
    }
    for (int i = 0; i < 8; ++i) {
      int *o = off[i];
      Position target{pos.line + o[0], pos.col + o[1]};
      if (!isValidPos(target) || visited[target.line][target.col]) {
        continue;
      }
      visited[target.line][target.col] = true;
      if (!arr[target.line][target.col]) {
        arr[target.line][target.col] = arr[pos.line][pos.col] + 1;
      } else {
        arr[target.line][target.col] =
            std::min(arr[pos.line][pos.col] + 1, arr[target.line][target.col]);
      }
      queue.push(target);
    }

    queue.pop();
  }
}

int main(int argc, char *argv[], char *envp[]) {
  scanf("%d %d %d %d", &n, &m, &x, &y);
  bfs({x, y});
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (i == x && j == y) {
        printf("0\t");
      } else if (arr[i][j] == 0) {
        printf("-1\t");
      } else {
        printf("%d\t", arr[i][j]);
      }
    }
    puts("");
  }
  return 0;
}
