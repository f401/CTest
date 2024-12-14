#include <climits>
#include <cstring>
#include <iostream>

#define INF (0x3f3f3f3f)

int n, m, start;

struct Node;

struct NodeEdge {
  NodeEdge() { memset(this, 0, sizeof(NodeEdge)); }
  Node *to;
  NodeEdge *next;
  int weight;
};

struct Node {
  Node() { memset(this, 0, sizeof(Node)); }

  int value;
  NodeEdge *info;

  inline bool isEmpty() const { return value == 0; }

  void appendTo(Node *next, int weight) {
    if (this->info == nullptr) {
      this->info = new NodeEdge();
      this->info->to = next;
      this->info->weight = weight;
      this->info->next = nullptr;
    } else {
      /*NodeEdge *edge = this->info;
      while (edge->next != nullptr) {
        if (edge->to == next) {
          edge->weight = std::max(weight, edge->weight);
          return;
        }
        edge = edge->next;
      }
      if (edge->to == next) {
        edge->weight = std::max(edge->weight, weight);
        return;
      }
      edge->next = new NodeEdge();
      edge->next->to = next;
      edge->next->weight = weight;
	  */
	  NodeEdge *edge = new NodeEdge();
	  edge->to = next;
	  edge->weight = weight;
	  edge->next = this->info;
	  this->info = edge;
    }
  }

  std::pair<bool, NodeEdge *>
  canAchieveDirectly(const Node *another) const noexcept {
    NodeEdge *info = this->info;
    while (info != nullptr) {
      if (info->to == another)
        return std::make_pair(true, info);
      info = info->next;
    }
    return std::make_pair(false, nullptr);
  }

  friend std::ostream &operator<<(std::ostream &input, const Node &node) {
    input << "Node { value: " << node.value << ", subs: ";
    NodeEdge *target = node.info;
    while (target != nullptr) {
      input << target->to->value << " ";
      target = target->next;
    }
    return input;
  }
};

long long distances[20000];

void dij(bool *visited, const Node *srcs, int u) {
  for (int i = 1; i <= n; ++i) {
    distances[i] = INF;
  }
  distances[u] = 0;

  /*  NodeEdge *node = srcs[u].info;
    while (node != nullptr) {
      distances[node->to->value] = node->weight;
      node = node->next;
    }*/

  int k = u;
  long long min = INF;
  while (!visited[k]) {
    visited[k] = true;
    NodeEdge *edge = srcs[k].info;
    while (edge != nullptr) {
      if (!visited[edge->to->value] &&
          distances[edge->to->value] > distances[k] + edge->weight) {
        distances[edge->to->value] = distances[k] + edge->weight;
      }
      edge = edge->next;
    }
	min = INF;
    for (int j = 1; j <= n; ++j) {
      if (!visited[j] && distances[j] < min) {
        min = distances[j];
        k = j;
      }
    }
  }
}

int main(int argc, char *argv[]) {
  int u, v, w;
  scanf("%d %d %d", &n, &m, &start);
  Node srcs[n + 5];
  while (m--) {
    scanf("%d %d %d", &u, &v, &w);
    if (srcs[u].isEmpty()) {
      srcs[u].value = u;
    }
    if (srcs[v].isEmpty()) {
      srcs[v].value = v;
    }
    srcs[u].appendTo(&srcs[v], w);
  }
  bool visited[n + m];
  memset(visited, 0, sizeof(visited));
  dij(visited, srcs, 1);
  for (int i = 1; i <= n; ++i) {
    if (distances[i] != INF)
      std::cout << distances[i] << " ";
    else
      std::cout << 2147483647 << " ";
  }
  for (int i = 1; i <= n; ++i) {
    std::cout << srcs[i] << std::endl;
  }
  return 0;
}
