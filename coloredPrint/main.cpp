#include "Color.hpp"
#include <stdio.h>

int main(int argc, char *argv[])
{
	std::cout << "aa"_c.withGreen().withHighlight().withUnderline() << std::endl;
	return 0;
}
