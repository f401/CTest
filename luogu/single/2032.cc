#include <iostream>
#include <list>
#include <map>

struct node {
  int value, idx;

  friend std::istream &operator>>(std::istream &input, node &nod) {
    input >> nod.value;
    return input;
  }
} a[1000000];

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  unsigned int n, k, i = 0;
  std::cin >> n >> k;
  std::list<node> src;
  for (unsigned int i = 1; i <= n; ++i) {
	  std::cin >> a[i], a[i].idx = i;
  }

  for (unsigned int i = 1; i <= n; ++i) {
	  while (src.size() && src.back().value <= a[i].value) {
		  src.pop_back();
	  }
	  src.push_back(a[i]);
	  if (src.front().idx <= i - k) {
		  src.pop_front();
	  }

	  if (i >= k) {
		  std::cout << src.front().value << std::endl;
	  }
  }
  return 0;
}
