#include <algorithm>
#include <iostream>
#define INF 0x3f3f3f3f
#define N 1005

int c[N][N], closest[N], lowcost[N], ans[N];
bool visited[N]; // r如果visited[i] = true, 则表示已访问
int n, m;
int prim(int n) {    // 求最小生成树
  visited[1] = true; // 初始化, 集合U中只有一个元素，表示已访问
  lowcost[1] = 0;
  for (int i = 2; i <= n; ++i) { // 初始化
    lowcost[i] = c[1][i];
    closest[i] = 1;
    visited[i] = false;
  }
  for (int i = 1; i < n; ++i) {
    int temp = INF;
    int t = 1;
    for (int j = 1; j <= n; ++j) { // 在V-U集合中寻找lowcost[j]最小的节点
      if (!visited[j] && lowcost[j] < temp) {
        t = j;
        temp = lowcost[j];
      }
    }
    if (t == 1)
      return 0; // 找不到t，跳出循环，不存在最小生成树（非连通图）
    visited[t] = true;                           // 否则，将t加入U集合
    for (int j = 1; j <= n; ++j) {               // 更新lowcost和closest
      if (!visited[j] && c[t][j] < lowcost[j]) { // 借助t更新
        lowcost[j] = c[t][j];                    // 重点
        closest[j] = t;                          // 更新操作
      }
    }
  }
  int sumcost = 0;
  for (int i = 1; i <= n; ++i) {
    sumcost += lowcost[i];
  }
  return sumcost;
}

int main(int argc, char *argv[]) {
  int t, u, v, w;
  std::cin >> t;
  while (t--) {
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        c[i][j] = INF;
      }
    }
    for (int i = 0; i < m; ++i) {
      std::cin >> u >> v >> w;
      c[u][v] = c[v][u] = std::min(c[u][v], w);
    }
    std::cout << prim(n) << std::endl;
  }
  return 0;
}
/**
1
7 12
1 2 23
1 6 28
1 7 36
2 3 20
2 7 1
3 4 15
3 7 4
4 5 3
4 7 9
5 6 17
5 7 16
6 7 25
 */
