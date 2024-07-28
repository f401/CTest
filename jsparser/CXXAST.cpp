namespace m {

constexpr int add(int a, int b) {
	return a + b;
}

};

int main(int argc, char *argv[])
{
	constexpr int c = m::add(1, 2);
	return 0;
}
