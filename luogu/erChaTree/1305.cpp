#include <cstring>
#include <iostream>
#include <map>

struct Node {
  char value;
  Node *left, *right;
};

void pre_order(Node *root) {
  if (!root)
    return;
  std::cout << root->value;
  pre_order(root->left);
  pre_order(root->right);
}

int main(int argc, char *argv[]) {
  Node root;
  int n;
  std::string tmp;
  std::cin >> n;
  std::map<char, Node *> searchMap;
  while (n--) {
    std::getline(std::cin, tmp);
    Node *curr = searchMap[tmp[0]];
    if (curr == nullptr) {
      root.value = tmp[0];
      searchMap[tmp[0]] = &root;

      curr = &root;
    }

    if (tmp[1] != '*') {
      curr->left = new Node();
      memset(curr->left, 0, sizeof(Node));
      curr->left->value = tmp[1];

      searchMap[tmp[1]] = curr->left;
    }

    if (tmp[2] != '*') {
      curr->right = new Node();
      memset(curr->right, 0, sizeof(Node));
      curr->right->value = tmp[2];

      searchMap[tmp[2]] = curr->right;
    }
  }
  pre_order(&root);
  return 0;
}
