#include <iostream>
#include <cstring>
#define MAXN 1000
int n, fa[MAXN], x, y, z, m;

int DSU_Find(int x) {
	if (fa[x] != x )
		fa[x] = DSU_Find(fa[x]);
	return fa[x];;
}

void DSU_Combine(int x, int y) {
	int a = DSU_Find(x);
	int b = DSU_Find(y);
	if (a != b)
		fa[b] = a;
}

int main(int argc, char *argv[])
{
	std::cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		fa[i] = i;
	}
	for (int i = 1; i <= m; ++i) {
		std::cin >> z >> x >> y;
		if (z == 1) {
			DSU_Combine(x, y);
		} else {
			if (DSU_Find(x) == DSU_Find(y)) 
				printf("Y");
			else
				printf("N");
		}
	}
	return 0;
}
