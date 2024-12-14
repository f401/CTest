#include <queue>
#include <iostream>

int main(int argc, char *argv[])
{
	int n, tmp;
	std::cin >> n;
	std::priority_queue<int, std::vector<int>, std::greater<>> src;
	while (n--) {
		std::cin >> tmp;
		src.push(tmp);
	}
	int cost = 0;
	while (src.size() > 1) {
		int top = src.top();
		src.pop();
		int a = src.top();
		src.pop();
		cost += a + top;
		src.push(a + top);
	}
	std::cout << cost;
	return 0;
}
