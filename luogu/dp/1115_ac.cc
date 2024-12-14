#include <iostream>
#include <map>
#include <algorithm>
#define MAXN 10000

int d[MAXN], a[MAXN], b[MAXN], map[MAXN];

int main(int argc, char *argv[])
{
	int n;
	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
		map[a[i]] = i;
	}

	for (int i = 1; i <= n; ++i) {
		std::cin >> b[i];
	}
	int len = 1;
	d[1] = map[b[1]];
	for (int i = 1; i <= n; ++i) {
		if (map[b[i]] == d[len]) continue;
		if (map[b[i]] > d[len])
			d[++len] = map[b[i]];
		else
			*std::lower_bound(d + 1, d + 1 + len, map[b[i]]) = map[b[i]];
	}
	std::cout << len << std::endl;
	return 0;
}
