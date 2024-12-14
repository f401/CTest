#include <queue>
#include <iostream>


class MyQueue {
	public:
		void push(int x) {

		}
		void pop() {}
		bool empty() {}
		int front() {}
		size_t size() {}
};

int main(int argc, char *argv[])
{
	std::ios::sync_with_stdio(false);
	MyQueue src;
	int n;
	std::cin >> n;
	while (n--) {
		int op;
		std::cin >> op;
		switch (op) {
			case 1:
			{
				int value;
				std::cin >> value;
				src.push(value);
			}
			break;
		    case 2:
				if (!src.empty())
					src.pop();
				else
					std::cout << "ERR_CANNOT_POP" << std::endl;
				break;
			case 3:
				if (!src.empty()) {
					std::cout << src.front() << std::endl;
				} else {
					std::cout << "ERR_CANNOT_QUERY" << std::endl;
				}
				break;
			case 4:
				std::cout << src.size() << std::endl;
				
		}
	}
	return 0;
}
