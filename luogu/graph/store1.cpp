#include <iostream>

const int N = 300;
bool src[N][N];
int n, m;// 节点数，边数

void createAM() {
	std::cin >> n >> m;
	for (int i = 0; i < n; ++i) 
		for (int j = 0; j < n; ++j)
			src[n][m] = 0;
	int u, v;
	for (int i = 0; i < m; ++i) {
		std::cin >> u >> v;
		src[u][v] = src[v][u] = 1;
	}
}

void print() {
	std::cout << "Out grapth" << std::endl;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j)
			std::cout << src[i][j] << "\t";
		std::cout << "\n";
	}
}

int main(int argc, char *argv[])
{
	createAM();
	print();
	return 0;
}
