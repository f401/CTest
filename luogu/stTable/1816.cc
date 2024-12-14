#include <iostream>
#include <cmath>

int F[300000][20];
int src[300000];

int m, n;

void CreateSTTable() 
{
	for (int i = 1; i <= m; ++i) {
		F[i][0] = src[i];
	}

	int k = log2(m);
	for (int j = 1; j <= k; ++j) {
		for (int i = 1; i <= m - (1 << j) + 1; ++i) {
			F[i][j] = std::min(F[i][j - 1], F[i + (1 << (j - 1))][j - 1]);
		}
	}
}

int QuerySTTable(int l, int r) 
{
	int k = log2(r - l + 1);
	return std::min(F[l][k], F[r - (1 << k) + 1][k]);
}

int main(int argc, char *argv[])
{
	scanf("%d %d", &m, &n);
	for (int i = 1; i <= m; ++i) {
		int tmp;
		scanf("%d", &tmp);
		src[i] = tmp;
	}
	CreateSTTable();
	for (int i = 1; i <= n; ++i) {
		int l, r;
		scanf("%d %d", &l, &r);
		printf("%d ", QuerySTTable(l, r));
	}
	return 0;
}
