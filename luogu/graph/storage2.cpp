#include <vector>
#include <iostream>

#define maxn 100
int n, m;
std::vector<int> E[maxn];

void createVe() {
	int u, v;
	std::cin >> u >> v;
	for (int i = 0; i < m; ++i) {
		std::cin >> u >> v;
		E[u].push_back(v);
		E[v].push_back(u);
	}
}
