#include <iostream>
#include <vector>
#include <stack>

void method0()
{
	int n, tmp;
	std::cin >> n;
	std::vector<int> src;
	while (n--) {
		std::cin >> tmp;
		src.push_back(tmp);
	}

	int cnt = 0;
	for (int k = 0; k < src.size(); ++k) {
		int i = src[k];
		for (int t = k + 1; t < src.size(); ++t) {
			if (i < src[t]) {
				break;
			}
			cnt++;
		}
	}
	std::cout << cnt;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::stack<int> src;
	int tmp, n, r = 0;
	std::cin >> n;
	while (n--) {
		std::cin >> tmp;
		while (!src.empty() && tmp > src.top())
			src.pop();
		r += src.size();
		src.push(tmp);
	}
	std::cout << r;
	return 0;
}
