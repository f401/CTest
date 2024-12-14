#include <iostream>

std::string in_order, post_order;

void generateTree(int inOrderStart, int inOrderEnd, int postOrderStart, int postOrderEnd) {
	char rootChar = post_order[postOrderEnd]; 
	std::cout << rootChar;

	int k = in_order.find(rootChar);
	int count = k - inOrderStart;// 左子树个数
	if (k > inOrderStart) generateTree(inOrderStart, k - 1, postOrderStart, postOrderStart + count - 1);
	if (k < inOrderEnd) generateTree(k + 1, inOrderEnd, postOrderStart + count, postOrderEnd - 1);
}

int main() {
  std::getline(std::cin, in_order);
  std::getline(std::cin, post_order);
  size_t len = post_order.length() - 1;
  generateTree(0, len, 0, len);
  return 0;
}
