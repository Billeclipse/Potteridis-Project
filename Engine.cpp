#include "Engine.h"
#include <fstream>
#include <iostream>
#include "lib/curses.h"
#include <time.h>
#include <Windows.h>
#define num_of_enemies 3
#define movement_time_in_secs 1

char** Engine::LoadMap(string filepath, int& width, int& height) {
	ifstream file(filepath);
	width = 0, height = 0;
	string line;
	if (file.is_open())
	{
		getline(file, line);
		width = atoi(line.c_str());
		getline(file, line);
		height = atoi(line.c_str());

		map = new char* [height];
		for (int i = 0; i < height; i++)
			map[i] = new char[width];
		int row = 0;
		while (getline(file, line))
		{
			for (int i = 0; i < width; i++)
			{
				map[row][i] = line[i];
			}
			row++;
		}
		file.close();
	}
	C = width;
	L = height;
	return map;
}

void Engine::ShowMap(int W, int H, bool first) {
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (map[i][j] == 'H')
				color_set(3, 0);
			else if (map[i][j] == 'C')
				color_set(6, 0);
			else if (map[i][j] == 'T')
				color_set(5, 0);
			else
				color_set(1, 0);
			mvprintw(i + 2, j + 1, "%c", map[i][j]);
		}
		if (first == true) {
			cout << endl;
		}
	}
}

int Engine::Game(int mode) {
	time_t t;
	Treasure c;
	int j, m = 0;
	double seconds_since_start;
	bool bs_on = false;
	note = 0;
	note2 = 3000;
	music_on = true;
	l.push_back(new Harry);
	for (j = 0; j < num_of_enemies; j++)
		l.push_back(new Classmates);
	char** TempMap;
	int i, exit, move = 0, moveC = 0;
	c.Init(map, C, L);
	map[c.getY()][c.getX()] = 'T';
	l[0]->Init(map, C, L);
	map[l[0]->getY()][l[0]->getX()] = 'H';
	for (i = 1; i < l.size(); i++) {
		l[i]->Init(map, C, L);
		map[l[i]->getY()][l[i]->getX()] = 'C';
	}
	//l[0]->InitMap(map, C, L); //HarryMap
	//l[0]->ShowMap(C, L); //HarryMap
	l[0]->CreateTempMap(map);
	dynamic_cast<Harry*> (l[0])->ShowTempMap(C, L); //General
	refresh();
	timeout(100);
	time_t start = time(0);
	do {
		//l[0]->CreateTempMap(map);	//HarryMap	
		//l[0]->SaveMap(); //HarryMap
		do {
			move = getch();
			map[l[0]->getY()][l[0]->getX()] = ' ';
			exit = l[0]->GetMove(l[0]->getTempMap(), move);
			if (exit == 1 && music_on == true)
				Beep(250, 22);
			if (exit == 4) {
				bs_on = true;
				mvprintw(L + 3, 51, "                            ");
				color_set(4, 0);
				mvprintw(L + 3, 61, "* cheats activated");
				refresh();
				color_set(1, 0);
			}
			if (exit == 5) {
				if (m % 2 == 0) {
					music_on = false;
					mvprintw(L + 3, 7, "  ");
					refresh();
					color_set(4, 0);
					mvprintw(L + 3, 7, "off");
					refresh();
					color_set(1, 0);
				}
				else {
					music_on = true;
					mvprintw(L + 3, 7, "   ");
					refresh();
					color_set(3, 0);
					mvprintw(L + 3, 7, "on");
					refresh();
					color_set(1, 0);
				}
				m++;
			}
			if (exit == 3 && bs_on == true) {
				SpellRandom();
			}
			if (exit == 2) {
				timeout(200);
				i = 0;
				for (j = 2; j < 26; j++) {
					mvprintw(11, j - 1, " ");
					mvprintw(11, j, "YOU");
					mvprintw(11, 52 - j + 2 + 3, " ");
					mvprintw(11, 52 - j + 2, "WON");
					refresh();
					if (music_on == true)
						WinningMusic();
					Sleep(50);
				}
				Sleep(250);
				mvprintw(20, 17, "PRESS SPACE FOR NEXT ROUND");
				mvprintw(21, 17, "PRESS ESC TO EXIT THE GAME");
				while (true) {
					color_set(i % 6, 0);
					mvprintw(11, 18, "****** YOU WON!!! ******");
					refresh();
					i++;
					if (getch() == 27)
						return 0;
					else if (getch() == 32)
						return 1;
				}
			}
		} while (exit == 0);
		map[l[0]->getY()][l[0]->getX()] = 'H';
		if (mode == 0) {
			seconds_since_start = difftime(time(0), start);
			if (seconds_since_start >= movement_time_in_secs) {
				start = time(0);
				for (i = 1; i < l.size(); i++) {
					l[i]->CreateTempMap(map);
					if ((dynamic_cast<Classmates*>(l[i])->CanMove(l[i]->getTempMap()))) {
						srand((unsigned)time(&t));
						do {
							moveC = rand() % 4 + 1;
							mvprintw(l[i]->getY() + 2, l[i]->getX() + 1, "%c", ' ');
							map[l[i]->getY()][l[i]->getX()] = ' ';
							exit = l[i]->GetMove(l[i]->getTempMap(), moveC);
							if (exit == 2) {
								ShowMap(C, L, false); //GlobalMap
								timeout(200);
								i = 0;
								for (j = 2; j < 27; j++) {
									mvprintw(11, j - 1, " ");
									mvprintw(11, j, "YOU");
									mvprintw(11, 54 - j + 2 + 4, " ");
									mvprintw(11, 54 - j + 2, "LOST");
									refresh();
									if (music_on == true)
										LosingMusic();
									Sleep(50);
								}
								Sleep(250);
								mvprintw(20, 17, "PRESS SPACE FOR NEXT ROUND");
								mvprintw(21, 17, "PRESS ESC TO EXIT THE GAME");
								while (true) {
									color_set(i % 6, 0);
									mvprintw(11, 19, "****** YOU LOST!!! ******");
									refresh();
									i++;
									if (getch() == 27)
										return 0;
									else if (getch() == 32)
										return 2;
								}
							}
						} while (exit == 0);
						map[l[i]->getY()][l[i]->getX()] = 'C';
					}
				}
			}
		}
		else if (mode == 1) {
			seconds_since_start = difftime(time(0), start);
			if (seconds_since_start >= movement_time_in_secs) {
				start = time(0);
				for (i = 1; i < l.size(); i++) {
					l[i]->CreateTempMap(map);
					if ((dynamic_cast<Classmates*>(l[i])->CanMove(l[i]->getTempMap()))) {
						do {
							mvprintw(l[i]->getY() + 2, l[i]->getX() + 1, "%c", ' ');
							map[l[i]->getY()][l[i]->getX()] = ' ';
							exit = dynamic_cast<Classmates*>(l[i])->GetMoveHard(map);
							if (exit == 2) {
								ShowMap(C, L, false); //GlobalMap
								timeout(200);
								i = 0;
								for (j = 2; j < 27; j++) {
									mvprintw(11, j - 1, " ");
									mvprintw(11, j, "YOU");
									mvprintw(11, 54 - j + 2 + 4, " ");
									mvprintw(11, 54 - j + 2, "LOST");
									refresh();
									if (music_on == true)
										LosingMusic();
									Sleep(50);
								}
								Sleep(250);
								mvprintw(20, 17, "PRESS SPACE FOR NEXT ROUND");
								mvprintw(21, 17, "PRESS ESC TO EXIT THE GAME");
								while (true) {
									color_set(i % 6, 0);
									mvprintw(11, 19, "****** YOU LOST!!! ******");
									refresh();
									i++;
									if (getch() == 27)
										return 0;
									else if (getch() == 32)
										return 2;
								}
							}
						} while (exit == 0);
						map[l[i]->getY()][l[i]->getX()] = 'C';
					}
				}
			}
		}
		l[0]->CreateTempMap(map);
		//l[0]->ShowMap(C, L); //HarryMap
		dynamic_cast<Harry*> (l[0])->ShowTempMap(C, L); //General
		//ShowMap(C, L, false); //GlobalMap
		if (bs_on == true) {
			color_set(3, 0);
			mvprintw(6, 66, "Harry:");
			refresh();
			color_set(1, 0);
			mvprintw(7, 66, "            ");
			mvprintw(7, 66, "X= %d Y= %d", l[0]->getX(), l[0]->getY());
			refresh();
			color_set(5, 0);
			mvprintw(8, 66, "Treasure:");
			refresh();
			color_set(1, 0);
			mvprintw(9, 66, "X= %d Y= %d", c.getX(), c.getY());
			refresh();
			if (num_of_enemies <= 6) {
				j = 0;
				for (i = 1; i < l.size(); i++) {
					color_set(6, 0);
					mvprintw(10 + j, 66, "Classmate %d:", i);
					refresh();
					j = j + 2;
				}
				color_set(1, 0);
				j = 0;
				for (i = 1; i < l.size(); i++) {
					mvprintw(11 + j, 66, "            ");
					mvprintw(11 + j, 66, "X= %d Y= %d", l[i]->getX(), l[i]->getY());
					j = j + 2;
				}
			}
		}
	} while (move != 27);
	return 0;
}

void Engine::SpellRandom() {
	int i, newx, newy;
	time_t t;
	srand((unsigned)time(&t));
	do {
		newx = rand() % C;
		newy = rand() % L;
	} while (map[newy][newx] != ' ');
	for (i = 1; i < l.size(); i++) {
		if (l[0]->getY() == l[i]->getY() && (l[0]->getX() + 1) == l[i]->getX()) {
			map[l[i]->getY()][l[i]->getX()] = ' ';
			l[i]->setY(newy);
			l[i]->setX(newx);
			if (music_on == true)
				Beep(3000, 100);
		}
		else if (l[0]->getY() == l[i]->getY() && (l[0]->getX() - 1) == l[i]->getX()) {
			map[l[i]->getY()][l[i]->getX()] = ' ';
			l[i]->setY(newy);
			l[i]->setX(newx);
			if (music_on == true)
				Beep(3000, 100);
		}
		else if ((l[0]->getY() - 1) == l[i]->getY() && l[0]->getX() == l[i]->getX()) {
			map[l[i]->getY()][l[i]->getX()] = ' ';
			l[i]->setY(newy);
			l[i]->setX(newx);
			if (music_on == true)
				Beep(3000, 100);
		}
		else if ((l[0]->getY() + 1) == l[i]->getY() && l[0]->getX() == l[i]->getX()) {
			map[l[i]->getY()][l[i]->getX()] = ' ';
			l[i]->setY(newy);
			l[i]->setX(newx);
			if (music_on == true)
				Beep(3000, 100);
		}
		else if (l[0]->getY() == l[i]->getY() && (l[0]->getX() - 2) == l[i]->getX()) {
			map[l[i]->getY()][l[i]->getX()] = ' ';
			l[i]->setY(newy);
			l[i]->setX(newx);
			if (music_on == true)
				Beep(3000, 100);
		}
		else if (l[0]->getY() == l[i]->getY() && (l[0]->getX() + 2) == l[i]->getX()) {
			map[l[i]->getY()][l[i]->getX()] = ' ';
			l[i]->setY(newy);
			l[i]->setX(newx);
			if (music_on == true)
				Beep(3000, 100);
		}
		else if ((l[0]->getY() - 2) == l[i]->getY() && l[0]->getX() == l[i]->getX()) {
			map[l[i]->getY()][l[i]->getX()] = ' ';
			l[i]->setY(newy);
			l[i]->setX(newx);
			if (music_on == true)
				Beep(3000, 100);
		}
		else if ((l[0]->getY() + 2) == l[i]->getY() && l[0]->getX() == l[i]->getX()) {
			map[l[i]->getY()][l[i]->getX()] = ' ';
			l[i]->setY(newy);
			l[i]->setX(newx);
			if (music_on == true)
				Beep(3000, 100);
		}
	}
}

void Engine::WinningMusic() {
	Beep(note, 100);
	note += 200;
}

void Engine::LosingMusic() {
	Beep(note2, 100);
	note2 -= 200;
}