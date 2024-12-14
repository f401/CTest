#include <cmath>
#include <iostream>

struct Node {
	int value, idx;
} data[5000];

int helper(int start, int end) {
  if (start + 1 != end) {
    for (int i = start; i < end; i += 2) {
      Node &left = data[i];
      Node &right = data[i + 1];
	  if (left.value > right.value) {
		  data[i >> 1].value = left.value;
		  data[i >> 1].idx = left.idx;
	  } else {
		  data[i >> 1].value = right.value;
		  data[i >> 1].idx = right.idx;
	  }
    }
    return helper(start >> 1, end >> 1);
  } else {
	Node &left = data[start << 1];
	Node &right = data[(start << 1) + 1];
	return left.value > right.value ? right.idx : left.idx;
  }
}

int main(int argc, char *argv[]) {
  int n, tmp;
  scanf("%d", &n);
  int count = 2 << (n - 1);
  for (int i = count, j = 1; i < count * 2; ++i, ++j) {
    scanf("%d", &tmp);
    data[i].value = tmp; 
	data[i].idx = j;
  }
  std::cout << helper(count, count * 2);
  return 0;
}
