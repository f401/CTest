#include <iostream>
#include <queue>

#define PARENT(N) (N >> 1)
#define CHILD_LEFT(N) (N * 2)
#define CHILD_RIGHT(N) (N * 2 + 1)

int size = 0;
int heap[500000];

void repairUp(int from) {
  if (from != 1 && heap[PARENT(from)] > heap[from]) {
    std::swap(heap[PARENT(from)], heap[from]);
    repairUp(PARENT(from));
  }
}

void insert(int value) {
  heap[++size] = value;
  repairUp(size);
}

void repairDown(int from) {
  if(CHILD_LEFT(from) > size)
	  return ;
  int tar = CHILD_LEFT(from);
  if (CHILD_RIGHT(from) <= size) {
	  tar = heap[CHILD_LEFT(from)] > heap[CHILD_RIGHT(from)] ? CHILD_RIGHT(from) : CHILD_LEFT(from);
  }
  if (heap[tar] < heap[from]) {
	  std::swap(heap[tar], heap[from]);
	  repairDown(tar);
  }
}

void removeRoot() {
  std::swap(heap[1], heap[size--]);
  repairDown(1);
}

int main(int argc, char *argv[]) {
  int n, op;
  std::cin >> n;
  while (n--) {
    std::cin >> op;
    switch (op) {
    case 1: {
      int v;
      std::cin >> v;
      insert(v);
    } break;
    case 3: {
      removeRoot();
    } break;
    case 2:
      std::cout << heap[1] << std::endl;
    }
  }
  return 0;
}
