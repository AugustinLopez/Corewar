#include <curses.h>

int main(void)
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	int	h, w;
	getmaxyx(stdscr, h, w);
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_CYAN, COLOR_BLACK);
	WINDOW *win = newwin(64, 64 * 3, 0, 0);
	WINDOW *win2= newwin(64, w - 64 * 3, 0, 64 * 3);
	WINDOW *win3= newwin(10, w, 64, 0);
	wattron(win, COLOR_PAIR(1));
	wborder(win, 0,0,0,0,0,0,0,0);
	wattroff(win, COLOR_PAIR(1));
	wattron(win2, COLOR_PAIR(2));
	wborder(win2, 0,0,0,0,0,0,0,0);
	wattroff(win2, COLOR_PAIR(2));
	wattron(win3, COLOR_PAIR(3));
	wborder(win3, 0,0,0,0,0,0,0,0);
	wattroff(win3, COLOR_PAIR(3));
	wmove(win, 2, 2);
	waddch(win, ACS_NEQUAL);
	wattron(win, A_STANDOUT);
	waddstr(win, "Hello World!\n");
	wattroff(win, A_STANDOUT);
	wrefresh(win3);
	wrefresh(win2);
	wrefresh(win);
	sleep(10);
	endwin();
	return (0);
}
