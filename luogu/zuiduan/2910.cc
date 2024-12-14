#include <iostream>
#include <vector>

const int N = 1000;
const int INF = 0x3f3f3f3f;
int n, m;
int G[N][N], dist[N][N];

void flyord() {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      dist[i][j] = i == j ? 0 : G[i][j];
    }
  }
  for (int k = 0; k < n; ++k)
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        if (dist[i][k] + dist[k][j] < dist[i][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
        }
}

int main(int argc, char *argv[]) {
  scanf("%d %d", &n, &m);
  std::vector<int> mustVisit;
  int tmp;
  while (m--) {
    std::cin >> tmp;
    mustVisit.push_back(tmp);
  }
  int u, v, w;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &G[i][j]); // 输入距离
    }
  }
  flyord();
  int cnt = 0;
  for (int i = 1; i < mustVisit.size() ; ++i) {
	cnt += dist[mustVisit[i - 1] - 1][mustVisit[i] - 1];
  }
  std::cout << cnt;
  return 0;
}
