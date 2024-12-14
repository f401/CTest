#include <iostream>
#include <stack>

struct Node {
  int height, value, index, recv;

  friend std::ostream &operator<<(std::ostream &input, const Node &node) {
    input << "height: " << node.height << ", index: " << node.index
          << ", recv: " << node.recv;
    return input;
  }
} srcs[11000000];

int main(int argc, char *argv[]) {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d %d", &srcs[i].height, &srcs[i].value);
    srcs[i].index = i;
    srcs[i].recv = 0;
  }
  std::stack<Node *> heightQueue;
  for (int i = 1; i <= n; ++i) {
    Node &currentNode = srcs[i];

    /*if (heightQueue.size() && heightQueue.top()->height < currentNode.height) {
      int j = 1;
      while (heightQueue.size()) {
		if (j++ <= 2)
   	     currentNode.recv += heightQueue.top()->value;
		heightQueue.pop();
      }
    } else if (heightQueue.size() &&
               heightQueue.top()->height > currentNode.height) {
      Node *top = heightQueue.top();
      top->recv += currentNode.value;
      heightQueue.pop();
      if (heightQueue.size()) {
        heightQueue.top()->recv += currentNode.value;
      }
      heightQueue.push(top);
    }
	*/
	while (heightQueue.size() && heightQueue.top()->height < currentNode.height) {
   	    currentNode.recv += heightQueue.top()->value;
		heightQueue.pop();
	}
	if (heightQueue.size() &&
        heightQueue.top()->height > currentNode.height)
		heightQueue.top()->recv += currentNode.value;
    heightQueue.push(&currentNode);
  }

  int max = 0;
  for (int i = 1; i <= n; ++i) {
    max = std::max(max, srcs[i].recv);
  }
  std::cout << max;

  return 0;
}
