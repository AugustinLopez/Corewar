#include <ncurses.h>

int main(void)
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	int	h, w;
	getmaxyx(stdscr, h, w);
	WINDOW *win = newwin(w, h, 0, 0);
	printf("hi\n");
	sleep(2);
	endwin();
	return (0);
}
