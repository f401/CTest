#include <algorithm>
#include <iostream>
const int MAXN = 1010;
int d[MAXN], a[MAXN];

int main(int argc, char *argv[])
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
	}
	int len = 1;
	d[1] = a[1];
	for (int i = 2; i <= n; i++) {
		if (a[i] == d[len]) {
			continue;
		}
		if (a[i] > d[len]) {
			d[++len] = a[i];
		} else {
			*std::lower_bound(d + 1, d + 1 + len, a[i]) = a[i];
		}
	}
	printf("%d", len);
	return 0;
}
