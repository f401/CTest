#include <iostream>
#define INF 0x3f3f3f3f
#define N 5005

int c[N][N], lowcost[N];
bool visited[N];
int n, m;
long long prim(int n) {
  visited[1] = true;
  lowcost[1] = 0;
  for (int i = 2; i <= n; ++i) {
    lowcost[i] = c[1][i];
    visited[i] = false;
  }
  for (int i = 1; i < n; ++i) {
    int temp = INF;
    int t = 1;
    for (int j = 1; j <= n; ++j) {
      if (!visited[j] && lowcost[j] < temp) {
        temp = lowcost[j];
        t = j;
      }
    }
    if (t == 1) {
      return 0;
    }
    visited[t] = true;
    for (int j = 1; j <= n; ++j) {
      if (!visited[j] && c[t][j] < lowcost[j]) {
        lowcost[j] = c[t][j];
      }
    }
  }
  long long sum = 0;
  for (int i = 1; i <= n; ++i) {
    sum += lowcost[i];
  }
  return sum;
}

int main(int argc, char *argv[]) {
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      c[i][j] = INF;
  int x, y, z;
  while (m--) {

    scanf("%d %d %d", &x, &y, &z);
    c[x][y] = c[y][x] = std::min(z, c[x][y]);
  }
  long long r = prim(n);
  if (r == 0)
    printf("orz");
  else
    printf("%lld", r);
  return 0;
}
