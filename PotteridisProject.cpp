// PotteridisProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
#include "Engine.h"
#include "lib/curses.h"
using namespace std;

int InitScreen(int W, int H);
int PickMode();
WINDOW* wm;
WINDOW* wn;

int main() {
	//Engine e;
	Engine e[10];
	vector<string> filepath;
	int i, C, L, game_on, mode, sum_won = 0, sum_lost = 0;
	for (i = 0; i < 10; i++)
		filepath.push_back("./map.txt");
	/*e.LoadMap(filepath, C, L);
	InitScreen(C, L);
	e.ShowMap(C, L,true); //GlobalMap
	e.Game();*/
	i = 0;
	do {
		e[i].LoadMap(filepath[i], C, L);
		mode = InitScreen(C, L);
		mvprintw(2, 66, "Round: %d", i + 1);
		mvprintw(4, 66, "Won: %d", sum_won);
		mvprintw(5, 66, "Lost: %d", sum_lost);
		refresh();
		//if (i==0)
		//	e[i].ShowMap(C, L, true); //GlobalMap
		//else
		//	e[i].ShowMap(C, L, false); //GlobalMap
		game_on = e[i].Game(mode);
		if (game_on == 1)
			sum_won++;
		else if (game_on == 2)
			sum_lost++;
		i++;
		if (i >= 10) {
			wclear(wm);
			wborder(wm, 0, 0, 0, 0, 0, 0, 0, 0);
			wcolor_set(wm, 4, 0);
			mvwprintw(wm, 10, 22, "*** GAME OVER ***");
			if (sum_won > sum_lost) {
				wcolor_set(wm, 3, 0);
				mvwprintw(wm, 14, 23, "*** YOU WON ***");
			}
			else if (sum_won < sum_lost) {
				wcolor_set(wm, 4, 0);
				mvwprintw(wm, 14, 22, "*** YOU LOST ***");
			}
			else {
				wcolor_set(wm, 5, 0);
				mvwprintw(wm, 14, 22, "*** ITS A TIE ***");
			}
			wcolor_set(wm, 1, 0);
			mvwprintw(wm, 20, 16, "PRESS ANY KEY TO EXIT THE GAME");
			refresh();
			wgetch(wm);
		}
		endwin();  /* End curses mode */
	} while (game_on != 0 && i < 10);
	endwin();  /* End curses mode */
	return 0;
}

int InitScreen(int W, int H) {
	initscr(); /* Start curses mode */
	int mode = 0;
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
	mode = PickMode();
	wn = newwin(H + 2, 15, 1, W + 4);
	mvprintw(4, 25, "          ");
	mvprintw(5, 25, "    ");
	mvprintw(6, 25, "    ");
	wclear(wn);
	wborder(wn, 0, 0, 0, 0, 0, 0, 0, 0);
	color_set(3, 0);
	mvprintw(0, 65, "*** Stats ***");
	color_set(4, 0);
	mvprintw(H + 3, 51, "*press backspace for cheats");
	color_set(1, 0);
	mvprintw(3, 66, "Mode:");
	if (mode == 0)
		mvprintw(3, 72, "Easy");
	else
		mvprintw(3, 72, "Hard");
	wrefresh(wn);
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
	wclear(wm);
	wborder(wm, 0, 0, 0, 0, 0, 0, 0, 0);
	wrefresh(wm);
	mvprintw(H + 3, 1, "Music:");
	refresh();
	color_set(3, 0);
	mvprintw(H + 3, 7, "on");
	color_set(1, 0);
	refresh();
	return mode;
}

int PickMode() {
	int move, mode = 0;
	wn = newwin(11, 15, 3, 23);
	clearok(wn, true);
	scrollok(wn, false);
	wcolor_set(wn, 1, 0);
	keypad(wn, FALSE);
	werase(wn);
	wborder(wn, 0, 0, 0, 0, 0, 0, 0, 0);
	wrefresh(wn);
	mvprintw(4, 25, "Pick Mode:");
	color_set(2, 0);
	mvprintw(5, 25, "Easy");
	color_set(1, 0);
	mvprintw(6, 25, "Hard");
	refresh();
	move = getch();
	while (move != 13) {
		if (move == KEY_DOWN) {
			color_set(1, 0);
			mvprintw(5, 25, "Easy");
			color_set(2, 0);
			mvprintw(6, 25, "Hard");
			color_set(1, 0);
			mode = 1;
		}
		else if (move == KEY_UP) {
			color_set(2, 0);
			mvprintw(5, 25, "Easy");
			color_set(1, 0);
			mvprintw(6, 25, "Hard");
			mode = 0;
		}
		move = getch();
	}
	return mode;
}