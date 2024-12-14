#include <iostream>
#include <string.h>
#include <algorithm>
#include <iterator>

int main(int argc, char *argv[])
{
	int n, tmp, m;
	std::cin >> n;
	int data[n + 2];
	memset(data, 0, sizeof(data));
	for (int i = 1; i <= n; ++i) {
		std::cin >> tmp;
		data[i] = tmp + data[i - 1];
	}
	std::cin >> m;


	while (m--) {
		int l, r;
		std::cin >> l >> r;
		printf("%d\n", data[r] - data[l - 1]);
	}
	
	return 0;
}
