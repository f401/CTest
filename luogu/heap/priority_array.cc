#include <queue>
#include <iostream>
#include <algorithm>

int a[] = {1231,31131,1231312,312312,31331,3,123,34,234,223,13};

int main(int argc, char *argv[]) {
	std::priority_queue<int, std::vector<int>, std::greater<>> que;
	std::priority_queue<int, std::vector<int>, std::less<>> que2;
	for (int i = 0; i < sizeof(a) / sizeof(int); ++i) {
		que.push(a[i]);
	}
	while (que.size()) {
		std::cout << que.top() << std::endl;
		que.pop();
	}
	return 0;
}
