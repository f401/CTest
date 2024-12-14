#include <bits/stdc++.h>

int mp[60][60];
bool v[60][60][4];

int deg[60][60];

struct Pos {
  int x, y;
};

enum Dir { Up, Down, Left, Right };

struct S {
  int x, y, stp;
  Dir dir;
};

signed main() {
  memset(deg, 0x3f, sizeof deg);
  int n, m;
  std::cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) {
      int tmp;
      std::cin >> tmp;
      if (tmp == 1)
        mp[i][j] = mp[i + 1][j] = mp[i][j + 1] = mp[i + 1][j + 1] = 1;
    }
  Pos start, end;
  std::cin >> start.x >> start.y >> end.x >> end.y;
  char ch;
  while (!isalpha(ch = getchar()))
    ;
  Dir sDir;
  switch (ch) {
  case 'E':
    sDir = Right;
    break;
  case 'W':
    sDir = Left;
    break;
  case 'N':
    sDir = Up;
    break;
  case 'S':
    sDir = Down;
    break;
  }
  std::queue<S> queue;
  queue.push({start.x + 1, start.y + 1, 0, sDir});
  while (queue.size()) {
    S top = queue.front();
    queue.pop();
    if (v[top.x][top.y][top.dir] || top.x <= 1 || top.x >= n + 1 || top.y <= 1 ||
        top.y >= m + 1 || mp[top.x][top.y]) {
      // printf("Perform cont; %d %d %d %d %d %d\n", v[top.x][top.y][top.dir],
      // top.x <= 0, top.x > n, top.y <= 0, top.y > m, mp[top.x][top.y]);
      continue;
    }
   // printf("Checked %d %d, dir: %d, stp: %d\n", top.x, top.y, top.dir, top.stp);
    deg[top.x][top.y] = std::min(deg[top.x][top.y], top.stp);
    v[top.x][top.y][top.dir] = true;
    if (top.x == end.x + 1 && top.y == end.y + 1) {
      std::cout << top.stp << std::endl;
	  
      for (int i = 1; i <= n + 1; ++i) {
        for (int j = 1; j <= m + 1; ++j)
          printf("%2d ", deg[i][j] == 1061109567 ? 0 : deg[i][j]);
        putchar('\n');
      }
      return 0;
    }
    switch (top.dir) {
    case Left:
      if (!mp[top.x][top.y - 1]) {
        queue.push({top.x, top.y - 1, top.stp + 1, Left});
        if (!mp[top.x][top.y - 2]) {
          queue.push({top.x, top.y - 2, top.stp + 1, Left});
          if (!mp[top.x][top.y - 3])
            queue.push({top.x, top.y - 3, top.stp + 1, Left});
        }
      }
      queue.push({top.x, top.y, top.stp + 1, Up});
      queue.push({top.x, top.y, top.stp + 1, Down});
      break;
    case Right:
      if (!mp[top.x][top.y + 1]) {
        queue.push({top.x, top.y + 1, top.stp + 1, Right});
        if (!mp[top.x][top.y + 2]) {
          queue.push({top.x, top.y + 2, top.stp + 1, Right});
          if (!mp[top.x][top.y + 3]) {
            queue.push({top.x, top.y + 3, top.stp + 1, Right});
          }
        }
      }
      queue.push({top.x, top.y, top.stp + 1, Up});
      queue.push({top.x, top.y, top.stp + 1, Down});
      break;
    case Up:
      if (!mp[top.x - 1][top.y]) {
        queue.push({top.x - 1, top.y, top.stp + 1, Up});
        if (!mp[top.x - 2][top.y]) {
          queue.push({top.x - 2, top.y, top.stp + 1, Up});
          if (!mp[top.x - 3][top.y]) {
            queue.push({top.x - 3, top.y, top.stp + 1, Up});
          }
        }
      }
      queue.push({top.x, top.y, top.stp + 1, Left});
      queue.push({top.x, top.y, top.stp + 1, Right});
      break;
    case Down:
      if (!mp[top.x + 1][top.y]) {
        queue.push({top.x + 1, top.y, top.stp + 1, Down});
        if (!mp[top.x + 2][top.y]) {
          queue.push({top.x + 2, top.y, top.stp + 1, Down});
          if (!mp[top.x + 3][top.y]) {
            queue.push({top.x + 3, top.y, top.stp + 1, Down});
          }
        }
      }
      queue.push({top.x, top.y, top.stp + 1, Left});
      queue.push({top.x, top.y, top.stp + 1, Right});
      break;
    }
  }
  printf("-1");
  return 0;
}
