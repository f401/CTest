#include <iostream>

int main(int argc, char *argv[])
{
	int data[] = {1, 2, 3, 4, 5};
	int left = 0, right = 5, target = 3;

	while (left <= right) {
		int mid = left + ((right - left) >> 1);
		if (data[mid] < target) {
			mid = right - 1;
		} else if (data[mid] > target) {
			mid = left + 1;
		} else if (data[mid] == target) {
			std::cout << mid << std::endl;
			break;
		} 
	}
	return 0;
}
