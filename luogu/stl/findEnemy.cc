#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main(int argc, char *argv[]) {
  int a, b, c;
  scanf("%d %d %d", &a, &b, &c);
  std::vector<std::string> s1, s2, s3;
  std::string str;
  while (a--) {
    std::cin >> str;
    s1.push_back(str);
  }
  while (b--) {
    std::cin >> str;
    s2.push_back(str);
  }
  while (c--) {
    std::cin >> str;
    s3.push_back(str);
  }

  s1.erase(std::remove_if(s1.begin(), s1.end(),
                          [&](auto &c) {
                            return std::find(s3.begin(), s3.end(), c) !=
                                   s3.end();
                          }),
           s1.end());
  bool o = true;
  for (std::string &src : s2) {
    if (std::find(s1.begin(), s1.end(), src) != s1.end()) {
      std::cout << src << " ";
	  o = false;
    }
  }

  if (o) {
	  std::cout << "No enemy spy.";
  }
  return 0;
}
