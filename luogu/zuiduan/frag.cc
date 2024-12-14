#include <algorithm>
#include <iostream>
#include <stack>

using namespace std;
const int N = 1005;
const int INF = 0x3f3f3f3f;
int G[N][N], dist[N]; // G为邻接矩阵, dist为源点到结点i的最短路径长度
int p[N];             // p[i] 表示源点到结点i的最短路径上i的前驱
int n, m;             // n 为节点数, m为边数
bool flag[N]; // 如果flag[i]等于true, 说明节点i已经添加到s集合中

void dijkstra(int u) {
  for (int i = 1; i <= n; ++i) {
    dist[i] = G[u][i];
    flag[i] = false;
    if (dist[i] == INF) {
      p[i] = -1; // 初始化为无穷大，说明源点与结点i不相邻
    } else {
      p[i] = u; // 说明结点i与源点相邻，设置i的前驱为u
    }
  }
  dist[u] = 0;
  flag[u] = true; // 初始时，集合s中只有源点u
  for (int i = 1; i < n; ++i) {
    int temp = INF, t = u;
    for (int j = 1; j <= n; ++j) {
      if (!flag[j] && dist[j] < temp) { // 在集合V-S中寻找距离u最近的结点t
        t = j;
        temp = dist[j];
      }
    }
    if (t == u)
      return;                      // 找不到，跳出循环
    flag[t] = true;                // 否则，将t加入S集合
    for (int j = 1; j <= n; ++j) { // 更新t的邻接点j的最短路劲长度，松弛操作
      if (!flag[j] && dist[j] > dist[t] + G[t][j]) {
        dist[j] = dist[t] + G[t][j];
        p[j] = t;
      }
    }
  }
}

void print() {
  for (int i = 1; i <= n; ++i) {
    if (i != 1) {
      cout << " ";
    }
    if (dist[i] == INF) {
      cout << "impossible";
    } else {
      cout << dist[i];
    }
  }
  cout << endl;
}

void findp(int u) { // 输出源点到u的最短距离，递归
  if (u == -1)
    return;
  findp(p[u]);
  cout << u << "\t";
}

void findpath(int u) {
  cout << "源点为: " << u << endl;
  cout << "最短路径为: " << endl;
  for (int i = 1; i <= n; ++i) {
    findp(i);
    cout << "最小路径为: " << dist[i] << endl;
  }
}

void findpath2(int u) { // 输出源点到其他节点胡最短路径，利用stack
  int x;
  stack<int> s;
  cout << "源点为: " << u << endl;
  cout << "最短路径为: " << endl;
  for (int i = 1; i <= n; ++i) {
    x = p[i];
    while (x != -1) {
      s.push(x);
      x = p[x];
    }
    while (s.size()) {
      cout << s.top() << "----";
      s.pop();
    }
    cout << i << "\t最短路径为: " << dist[i] << endl;
  }
}

int main(int argc, char *argv[]) {
  int u, v, w, st;//
  int t;
  cin >> n >> m;
  for (int i = 1; i <= t; ++i)
    for (int j = 1; j <= t; ++j)
      G[i][j] = INF;
  for (int i = 1; i <= m; ++i) {
    cin >> u >> v >> w;
    G[u][v] = min(G[u][v], w);
  }
  cin >> st;
  dijkstra(st);
  print();
  //findpath(st);
  //findpath2(st);
  return 0;
}
