#include <bits/stdc++.h>

int need2[] = {0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1};
char vis2[1000000000];

bool isPrime(int n) {
    if (n == 2) return true;
    if (n == 0 || vis2[n] == 1)  return false; else if (vis2[n] == 2) return true;
  if (n % 2 == 0 || n == 1) {
    vis2[n] = 1;
    return false;
  }
  for (int i = 3; i <= std::sqrt(n); ++i) {
    if (n % i == 0) {
      vis2[n] = 1;
      return false;
    }
  }
  vis2[n] = 2;
  return true;
}

bool isVaildDate(std::string &s) {
//   for (int i = 0; i < 4; ++i) 
//     if (s[i] == '-') return true;
    
  char __year[] = {s[0], s[1], s[2], s[3], 0};
  int year = std::atoi(__year); 
  if (year >= 9999 || year <= 1) return false;
  
//   for (int i = 4; i <= 5; ++i) 
//     if (s[i] == '-') return true;
  char mo[] = {s[4], s[5], 0};
  int month = std::atoi(mo);
  if (month <= 0 || month > 12) return false;
  
//   for (int i = 6; i <= 7; ++i) 
//     if (s[i] == '-') return true;
  char __day[] = {s[6], s[7], 0};
  int day = std::atoi(__day);
  
  if (day <= 0 || day > 31 || !isPrime(month * 100 + day) || !isPrime(std::atoi(s.c_str()))) 
    return false;
  if (month == 2) {
    if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) {
      return day <= 29;
    } else 
      return day <= 28;
  }
  return (need2[month] ? day <= 31 : day <= 30);
}

std::string str;
int ans = 0;
bool vis[1000000000];
void d(std::string s) {
  bool f = true;
  for (char &ch : s) {
    if (ch == '-') {
      for (int i = 0; i <= 9; ++i) {
        ch = i + '0';
        // if (isVaildDate(s))
            d(s);
      }
      f = false;
    }
  }
  if (f) {
    int a = std::atoi(s.c_str());
    if (!vis[a] && isVaildDate(s)) {
    // std::cout << "Find " << s << std::endl;
     vis[a] = true;
     ++ans;
    } else {
     vis[a] = false;
    }
  }
}

signed main() {
  int T;
  std::cin >> T;
  while (T--) {
    std::cin >> str;
    ans = 0;
    d(str);
    std::cout << ans << std::endl;
  }
  return 0;
}
