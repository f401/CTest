#include <iostream>
#include <queue>

struct aa {
	int a, b;
};

bool operator<(const aa &l, const aa &r) {
	if (l.a != r.a)
		return l.a > r.a; // 右边参数优先级更高
	return l.b < r.b;
}

int main(int argc, char *argv[])
{
	std::priority_queue<aa> a;
	int n, x;
	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		std::cin >> x;
		a.push({x, i});
	}
	while (a.size()) {
		std::cout << a.top().a << " " << a.top().b << std::endl;
		a.pop();
	}
	return 0;
}
