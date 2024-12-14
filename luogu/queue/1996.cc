#include <iostream>
#include <queue>

int main(int argc, char *argv[])
{
	int n, m;
	scanf("%d %d", &n, &m);
	std::queue<int> src;
	for (int i = 1; i <= n; ++i)
		src.push(i);
	int index = 1;
	while (src.size()) {
		int f = src.front();
		src.pop();
		if (index++ == m) {
			index = 1;
			std::cout << f << " ";
		} else {
			src.push(f);
		}
	}
	return 0;
}
