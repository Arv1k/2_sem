#include <cstdio>

//extern "C" int _Sum(int a, int b);

extern "C" int _printui(const char*, ...);

int main() {
	int a = 15;
	int b = 25;
	// int c = 0;
	// c = Sum(a, b);

	//printf("%d\n", c);
	_printui("Max pid#r %x %d, I %s %x %d %% %c\n", a, b, "love", 3802, 100, 31);
}
