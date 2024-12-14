#include <iostream>

const int N = 100;
const int INF = 0x3f3f3f3f;
int G[N][N], dist[N][N]; // G为邻接矩阵, dist为i到j的最短距离
int p[N][N];
int n, m;

void Flyod() {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == j) {
        dist[i][j] = 0; // 自己到自己最短距离为0
      } else {
        dist[i][j] = G[i][j];
      }
      if (dist[i][j] < INF && i != j) {
        p[i][j] = i; // 如果i, j之间有边，则将j的前驱置为i
      } else {
        p[i][j] = -1; // 如果i, j之间无边, 则将j的前驱置为-1
      }
    }
  }
  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (dist[i][k] + dist[k][j] < dist[i][j]) { // 从i经k到j的路径更短
          dist[i][j] = dist[i][k] + dist[k][j];     // 更新dist[i][j]
          p[i][j] = p[j][k];                        // 更新j的前驱
        }
      }
    }
  }
}

void Print() {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			std::cout << dist[i][j] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			std::cout << p[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}

void DisplayPath(int s, int t) {
	if (p[s][s] != -1) {
		DisplayPath(s, p[s][t]);
		std::cout << p[s][t] << "---";
	}
}

int main(int argc, char *argv[])
{
	int u, v, w;
	std::cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			G[i][j] = INF;
		}
	}
	for (int i = 0; i < m; ++i) {
		std::cin >> u >> v >> w;
		G[u][v] = std::min(G[u][v], w);
	}
	Flyod();
	Print();
	std::cin >> u >> v;
	std::endl(std::cout);
	DisplayPath(u, v);
	std::endl(std::cout);
	std::cout << dist[u][v];
	return 0;
}
