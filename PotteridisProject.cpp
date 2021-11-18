// PotteridisProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "Engine.h"
#include "lib/curses.h"
using namespace std;

void InitScreen(int W, int H);
WINDOW* wm;

int main() {
	Engine e;
	string filepath = "./map.txt";
	int C, L;
	e.LoadMap(filepath, C, L);
	InitScreen(C, L);
	e.Game();
	refresh();
	endwin();  /* End curses mode */
	return 0;
}

void InitScreen(int W, int H) {
	initscr(); /* Start curses mode */
	start_color();
	cbreak();
	noecho();
	nonl();
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);
	curs_set(0);
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_BLACK);
	init_pair(5, COLOR_YELLOW, COLOR_BLACK);
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
	color_set(2, 0);
	mvprintw(0, 11, "*** HARRY POTTER AND THE FROZEN CUP ***");
	refresh();
	color_set(1, 0);
	refresh();
	wm = newwin(H + 2, W + 2, 1, 0);
	clearok(wm, true);
	scrollok(wm, false);
	wcolor_set(wm, 1, 0);
	keypad(wm, TRUE);
	werase(wm);
	mvprintw(11, 11, "*** PRESS ANY KEY TO START THE GAME ***");
	wborder(wm, 0, 0, 0, 0, 0, 0, 0, 0);
	wrefresh(wm);
	getch();
	mvprintw(11, 11, "                                       ");
	werase(wm);
	wborder(wm, 0, 0, 0, 0, 0, 0, 0, 0);
	wrefresh(wm);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
