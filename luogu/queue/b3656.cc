#include <iostream>
#include <list>
#include <map>

int main(int argc, char *argv[]) {
  int n;
  std::cin >> n;
  std::map<int, std::list<int>> srcs;
  std::string op;
  while (n--) {
    std::cin >> op;
    int a;
    std::cin >> a;
    if (op == "pop_back") {
      if (srcs[a].size())
        srcs[a].pop_back();
    } else if (op == "push_back") {
      int x;
      std::cin >> x;
      srcs[a].push_back(x);
    } else if (op == "push_front") {
      int x;
      std::cin >> x;
      srcs[a].push_front(x);
    } else if (op == "pop_front") {
      if (srcs[a].size())
        srcs[a].pop_front();
    } else if (op == "size") {
      std::cout << srcs[a].size() << std::endl;
    } else if (op == "front") {
      if (srcs[a].size())
        std::cout << srcs[a].front() << std::endl;
    } else if (op == "back") {
      if (srcs[a].size())
        std::cout << srcs[a].back() << std::endl;
    }
  }
  return 0;
}
