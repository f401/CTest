#include <iostream>
#include <map>
#include <cmath>


int F  [3000000][40];
int MIN[3000000][40];
int src[3000000];

int n;

void ST_Create() {
	for (int i = 1; i <= n; ++i) {
		F[i][0] = src[i];
		MIN[i][0] = src[i];
	}
	int k = log2(n);
	for (int j = 1; j <= k; ++j) {
		for (int i = 1; i <= n - (1 << j) + 1; ++i) {
			F[i][j] = std::max(F[i][j - 1], F[i + (1 << (j - 1))][j - 1]);
			MIN[i][j] = std::min(MIN[i][j - 1], MIN[i + (1 << (j - 1))][j - 1]);
		}
	}
}

int ST_Query(int l, int r) {
	int k = log2(r - l + 1);
	return std::max(F[l][k], F[r - (1 << k) + 1][k]);
}

int ST_Query_min(int l, int r) {
	int k = log2(r - l + 1);
	return std::min(MIN[l][k], MIN[r - (1 << k) + 1][k]);
}

int main(int argc, char *argv[])
{
	int q, tmp;
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d", &tmp);
		src[i] = tmp;
	}
	ST_Create();
	while (q--) {
		int l, r;
		scanf("%d %d", &l, &r);
		printf("%d\n", ST_Query(l,r) - ST_Query_min(l, r));
	}

	return 0;
}
