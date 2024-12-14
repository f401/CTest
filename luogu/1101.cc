#include <iostream>
#include <map>
#include <vector>

const char EXAMPLE[] = "yizhong";
int n, count = 0;
char table[150][150];
char resultTable[150][150];

enum Direction {
  LEFT,
  RIGHT,
  UP,
  DOWN,
  LEFT_UP,
  RIGHT_UP,
  LEFT_DOWN,
  RIGHT_DOWN
};

struct Position {
  int line, col;
};

std::vector<Position> yChars;

std::map<Direction, Position> offsets{
    {LEFT, {0, -1}},     {RIGHT, {0, 1}},     {DOWN, {1, 0}},
    {UP, {-1, 0}},       {LEFT_UP, {-1, -1}}, {LEFT_DOWN, {1, -1}},
    {RIGHT_UP, {-1, 1}}, {RIGHT_DOWN, {1, 1}}};

bool dfs(int line, int col, int cnt, Direction direction) {
  if (line <= 0 || col <= 0 || line > n || col > n ||
      table[line][col] != EXAMPLE[cnt]) {
    return false;
  }
  if (table[line][col] == 'g' && cnt == 6) {
    ++count;
    resultTable[line][col] = 'g';
    return true;
  }
  const Position &off = offsets[direction];
  if (dfs(line + off.line, col + off.col, cnt + 1, direction)) {
    resultTable[line][col] = table[line][col];
    return true;
  }
  return false;
}

int main(int argc, char *argv[]) {
  scanf("%d", &n);
  char tmp;
  for (int i = 1; i <= n; ++i) {
    getchar();
    for (int j = 1; j <= n; ++j) {
      char curr = getchar();
      if (curr == 'y') {
        yChars.push_back({i, j});
      }
      table[i][j] = curr;
    }
  }
  for (const Position &pos : yChars) {
    dfs(pos.line, pos.col, 0, UP);
    dfs(pos.line, pos.col, 0, DOWN);
    dfs(pos.line, pos.col, 0, RIGHT);
    dfs(pos.line, pos.col, 0, LEFT);
    dfs(pos.line, pos.col, 0, LEFT_UP);
    dfs(pos.line, pos.col, 0, LEFT_DOWN);
    dfs(pos.line, pos.col, 0, RIGHT_UP);
    dfs(pos.line, pos.col, 0, RIGHT_DOWN);
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (resultTable[i][j] != 0) {
        printf("%c", resultTable[i][j]);
      } else {
        printf("*");
      }
    }
    puts("");
  }
  return 0;
}
