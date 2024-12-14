#include <algorithm>
#include <iostream>
#include <queue>
#include <iterator>

std::vector<long> queue;
long n, m;
inline bool __chk(int mid) {
  long sum = 0;
  for (int i = 0; i < n; ++i) {
    if (queue[i] > mid) {
      sum += queue[i] - mid;
      if (sum >= m) {
        return true;
      }
    } else {
      break;
    }
  }
  return sum >= m;
}

int main(int argc, char *argv[]) {
  long tmp, max = -1;
  scanf("%ld %ld", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%ld", &tmp);
    queue.push_back(tmp);
    max = std::max(max, tmp);
  }
  std::sort(queue.begin(), queue.end(), std::greater<>());
  long left = 0, right = max;
  while (left + 1 != right) {
    long mid = (left + right) >> 1;
    if (__chk(mid)) {
      left = mid;
    } else {
      right = mid;
    }
  }
  printf("%ld", left);
  return 0;
}
