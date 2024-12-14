#include <cstring>
#include <iostream>
#include <list>

struct Node;

struct NodeInfo {
  NodeInfo() { memset(this, 0, sizeof(NodeInfo)); }
  Node *curr;
  NodeInfo *next;
};

struct Node {
  Node() { memset(this, 0, sizeof(Node)); }

  int value;
  NodeInfo *info;

  bool isEmpty() const { return value == 0; }

  void appendTo(Node *next) {
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

  friend std::ostream &operator<<(std::ostream &input, const Node &node) {
    input << "Node { value: " << node.value << ", subs: ";
    NodeInfo *target = node.info;
    while (target != nullptr) {
      input << target->curr->value << " ";
      target = target->next;
    }
    return input;
  }
};

void dfs(bool *visited, Node *curr) {
  visited[curr->value] = true;
  printf("%d ", curr->value);
  NodeInfo *target = curr->info;
  while (target != nullptr) {
    if (!visited[target->curr->value])
      dfs(visited, target->curr);
    target = target->next;
  }
}

void bfs(bool *visited, Node *curr) {
  std::list<Node *> targets;
  targets.push_back(curr);
  while (targets.size()) {
    Node *top = targets.front();

    if (!visited[top->value]) {
      visited[top->value] = true;
      printf("%d ", top->value);

      NodeInfo *target = top->info;
      while (target != nullptr) {
        targets.push_back(target->curr);
        target = target->next;
      }
    }
    targets.pop_front();
  }
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
    memset(&visited, 0, sizeof(visited));
    dfs(visited, &nodes[1]);
    memset(&visited, 0, sizeof(visited));
    puts("");
    bfs(visited, &nodes[1]);
  return 0;
}
