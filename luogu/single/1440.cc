#include <deque>
#include <iostream>
#include <list>

struct Node {
  int idx, value;
} srcs[19989513];

int main(int argc, char *argv[]) {
  int n, m;
  scanf("%d %d", &n, &m);
  scanf("%d", &srcs[1].value);
  srcs[1].idx = 1;

  std::deque<Node> queue;
  puts("0");
  queue.push_back(srcs[1]);
  for (int i = 2; i <= n; ++i) {
    srcs[i].idx = i;
	scanf("%d", &srcs[i].value);
    printf("%d\n", queue.front().value);
    while (queue.size() && queue.back().value > srcs[i].value) {
      queue.pop_back();
    }

    if (queue.size() && queue.front().idx + m == i) {
      queue.pop_front();
    }
    queue.push_back(srcs[i]);
  }
  return 0;
}
