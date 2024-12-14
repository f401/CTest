#include <iostream>
#include <stack>
int main(int argc, char *argv[]) {
  std::string src, tmp;
  std::getline(std::cin, src);
  std::stack<int> nums;
  for (char c : src) {
    if (c >= '0' && c <= '9') {
      tmp.push_back(c);
    } else if (c == '.') {
      nums.push(std::atoi(tmp.data()));
	  tmp.clear();
	} else if (c == '@') {
	  break;
    } else {
      int num1 = nums.top();
      nums.pop();
      int num2 = nums.top();
      nums.pop();
      switch (c) {
      case '+':
        nums.push(num1 + num2);
        break;
      case '-':
        nums.push(num2 - num1);
        break;
      case '*':
        nums.push(num1 * num2);
        break;
      case '/':
        nums.push(num2 / num1);
        break;
      }
    }
  }
  std::cout << nums.top();
  return 0;
}
