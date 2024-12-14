#include <iostream>

int a[101], b[101];

using namespace std;

int main(int argc, char *argv[])
{
	int n, m, tmp;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n;++i) {
		std::cin >> tmp;
		b[i] = a[i] - a[i - 1];
	}
	int l, r, c;
	while (m--) {
		b[l] += c;
		b[l + 1] -= c;
	}
	return 0;
}
