#include <iostream>

struct Node {
	char data;
	int left, right;
} a[100];	

void pre_order(int start) {
	if (!a[start].data)
		return;
	std::cout << a[start].data;
	pre_order(a[start].left);
	pre_order(a[start].right);
}

void in_order(int root) {
	if (!root)
		return;
	in_order(a[root].left);
	std::cout << a[root].data << std::endl;
	in_order(a[root].right);
}

void post_order(int root) {
	if (!root)
		return;
	post_order(a[root].left);
	post_order(a[root].right);
	std::cout << a[root].data << std::endl;
}

int main(int argc, char *argv[])
{
	a[1] = {'A', 2, 3};
	a[2] = {'B', 4, 0};
	a[3] = {'C', 5, 6};
	a[4] = {'D', 7, 8};
	a[5] = {'E', 0, 9};
	a[6] = {'F', 0, 0};
	a[7] = {'G', 0, 0};
	a[8] = {'H', 0, 0};
	a[9] = {'I', 0, 0};
	post_order(1);
	return 0;
}
