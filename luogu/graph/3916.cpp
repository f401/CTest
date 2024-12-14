
#include <cstring>
#include <iostream>
#include <list>

struct Node;

struct NodeInfo {
  NodeInfo() noexcept { memset(this, 0, sizeof(NodeInfo)); }
  Node *curr;
  NodeInfo *next;
};

struct Node {
  Node() noexcept { memset(this, 0, sizeof(Node)); }

  int value;
  NodeInfo *info;

  bool isEmpty() const noexcept { return value == 0; }

  void appendTo(Node *next) noexcept {
    if (this->info == nullptr) {
      this->info = new NodeInfo();
      this->info->curr = next;
    } else {
      if (this->info->curr->value > next->value) {
        NodeInfo *newRoot = new NodeInfo();
        newRoot->next = this->info;
        newRoot->curr = next;
        this->info = newRoot;
        return;
      }
      NodeInfo *target = this->info;
      while (target->next != nullptr &&
             target->next->curr->value <= next->value) {
        target = target->next;
      }
      NodeInfo *tmp = new NodeInfo();
      tmp->curr = next;
      tmp->next = target->next;
      target->next = tmp;
    }
  }

  friend std::ostream &operator<<(std::ostream &input, const Node &node) noexcept {
    input << "Node { value: " << node.value << ", subs: ";
    NodeInfo *target = node.info;
    while (target != nullptr) {
      input << target->curr->value << " ";
      target = target->next;
    }
    return input;
  }
};

int dfs(bool *visited, Node *curr) noexcept {
  visited[curr->value] = true;
  NodeInfo *target = curr->info;
  int max = curr->value;
  while (target != nullptr) {
    if (!visited[target->curr->value])
      max = std::max(dfs(visited, target->curr), max);
    target = target->next;
  }
  return max;
}

int main(int argc, char *argv[]) {
  int n, m;
  scanf("%d %d", &n, &m);
  Node nodes[n + 2];
  int x, y;
  for (int i = 1; i <= m; ++i) {
    scanf("%d %d", &x, &y);
    if (nodes[x].isEmpty()) {
      nodes[x].value = x;
    }
    if (nodes[y].isEmpty()) {
      nodes[y].value = y;
    }
    nodes[x].appendTo(&nodes[y]);
  }
  bool visited[n + 2];
  for (int i = 1; i <= n; ++i) {
    memset(&visited, 0, sizeof(visited));
    printf("%d ", dfs(visited, &nodes[x]));
  }
  return 0;
}
