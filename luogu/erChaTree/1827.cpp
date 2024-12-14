#include <iostream>

std::string preorder;
std::string inorder;

void helper(int preorderStart, int preorderEnd, int inorderStart, int inorderEnd) {
	char root = preorder[preorderStart];

	if (preorderStart > preorderEnd || inorderStart > inorderEnd) return;


	int k = inorder.find(root);
	int leftTreeCount = k - inorderStart;
	helper(preorderStart + 1, preorderStart + leftTreeCount, inorderStart, k - 1);

	helper(preorderStart + leftTreeCount + 1, preorderEnd, k + 1, inorderEnd);
	std::cout << root;
}

int main(int argc, char *argv[])
{
	std::cin >> inorder >> preorder;
	size_t len = preorder.length() - 1;
	helper(0, len, 0, len);
	return 0;
}
