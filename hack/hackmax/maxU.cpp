#include "libCpp.h"

int main() {
	slowprint("Hi, my friend.\n\n");
	delay();

	slowprint("Can I trust you? ");
	delay();
	delay();

	slowprint("Let's talk about it.\n");
	delay();

	slowprint("You need just to enter the date, ");
	if (slowprint("what very important for me:\n") != 120) return 0;
	delay();

	if (DateAsking() !=  499) return 0;

	slowprint("\nWell, you're good. But there is one thing.\n\n");
	delay();

	slowprint("I want to tell you about our friendship.\n\n");
	delay();
	delay();

	slowprint("Why are we both the same?\n");
	delay();
	delay();

	slowprint("I don't know a man who can understand me like you. ");
	slowprint("It's a really strange bond. And I thank You for that.\n");
	delay();

	slowprint("Our talks, jokes, problems - all this is important for me.\n");
	delay();

	slowprint("It's not a Declaration of love, ");
	slowprint("but it's appeal to the best friend.\n\nTo you, Max.\n\n");
	delay();
	delay();

	slowprint("Just a few things go through all the life with us.\n");
	delay();

	slowprint("But our friendship is really something ");
	slowprint("that will stay with us forever. ");
	delay();
	delay();
	delay();

	slowprint("Remember this.\n\n");
	delay();
	delay();
	delay();

	slowprint("And your last task. Enter the name of my first cat:\n");
	delay(); // 562

	CatAsking();
}
