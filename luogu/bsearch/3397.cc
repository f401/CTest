#include <iostream>

int a[1000][1000];

void insert(int x1, int y1, int x2, int y2, int c) {
	a[x1][y1] += c;
	a[x2 + 1][y1] -= c;
	a[x1][y2 + 1] -= c;
	a[x2 + 1][y2 + 1] += c;
}

int main(int argc, char *argv[])
{
	int n, m;
	scanf("%d %d", &n, &m);
	while (m--) {
		int x1, y1, x2, y2;
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		insert(x1, y1, x2, y2, 1);
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
			std::cout << a[i][j] << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}
