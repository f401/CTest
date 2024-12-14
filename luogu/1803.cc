#include <iostream>
#include <map>
#include <queue>
#include <algorithm>

struct Data {
	Data(int start, int end): start(start), end(end) {}
	int start, end;
};

int main(int argc, char *argv[])
{
	int n;
	scanf("%d", &n);
	std::vector<Data> srcs;
	for (int i = 0; i < n; i++) {
		int start, end;
		scanf("%d %d", &start, &end);
		srcs.emplace_back(start, end);
	}
	std::sort(srcs.begin(), srcs.end(), [](const Data& left, const Data& right) {
			return left.end < right.end;
	});
	int result = 0, tmp = 0;
	for (int i = 0; i < n; ++i) {
		if (srcs[i].start >= tmp) {
			tmp = srcs[i].end;
			++result;
		}
	}
	printf("%d", result);
	return 0;
}
