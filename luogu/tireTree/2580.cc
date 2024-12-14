#include <bits/stdc++.h>

enum Result { OK, REPEAT, WRONG };

int tried[2000000][27], tot = 1;
char end[2000000];

void insert(const std::string &str) {
  int p = 1;
  for (size_t i = 0; i < str.length(); ++i) {
    int ch = str[i] - 'a';
    if (!tried[p][ch])
      tried[p][ch] = ++tot;
    p = tried[p][ch];
  }
  end[p] = 1;
}

Result search(const std::string &str) {
  int p = 1;
  for (size_t i = 0; i < str.length(); ++i) {
    p = tried[p][str[i] - 'a'];
    if (!p) {
      return WRONG;
    }
  }
  if (end[p] == 1) {
    end[p] = 2;
    return OK;
  } else if (end[p] == 0) {
    return WRONG;
  } else {
    return REPEAT;
  }
}

int main(int argc, char *argv[]) {
  int n;
  std::cin >> n;
  std::string s;
  while (n--) {
    std::cin >> s;
    insert(s);
  }
  std::cin >> n;
  while (n--) {
    std::cin >> s;
    switch (search(s)) {
    case WRONG:
      std::cout << "WRONG" << std::endl;
      break;
    case OK:
      std::cout << "OK" << std::endl;
      break;
    case REPEAT:
      std::cout << "REPEAT" << std::endl;
    }
  }
  return 0;
}
