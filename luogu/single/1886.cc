#include <iostream>
#include <list>
#include <vector>

struct Node {
	int value, idx;
} srcs[10000];

int main(int argc, char *argv[])
{
	int n, k;
	scanf("%d %d", &n, &k);
	std::list<Node> queue;
	std::vector<int> max;
	
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &srcs[i].value);
		srcs[i].idx = i;
	}
	for (int i = 1; i <= n; ++i) {
		while (queue.size() && queue.back().value > srcs[i].value) {
			queue.pop_back();
		}
		queue.push_back(srcs[i]);
		while (queue.size() && queue.front().idx + k <= i) {
			queue.pop_front();
		}
		if (i >= k) {
			printf("%d ", queue.front().value);
		}
	}
	puts("");
	queue.clear();

	for (int i = 1; i <= n; ++i) {
		while (queue.size() && queue.back().value < srcs[i].value) {
			queue.pop_back();
		}
		queue.push_back(srcs[i]);
		while (queue.size() && queue.front().idx + k <= i) {
			queue.pop_front();
		}
		if (i >= k) {
			printf("%d ", queue.front().value);
		}
	}
	return 0;
}
