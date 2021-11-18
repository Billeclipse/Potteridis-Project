#include "Engine.h"
#include <fstream>
#include <iostream>
#include "lib/curses.h"
#include <time.h>
#include <Windows.h>
#define num_of_enemies 7
#define movement_time_in_secs 1

char** Engine::LoadMap(string filepath,int &width,int  &height){
	ifstream file(filepath);
	width=0, height=0;
	string line;
	if (file.is_open())
	{
		getline(file, line);
		width = atoi(line.c_str());
		getline(file, line);
		height = atoi(line.c_str());

		map = new char*[height];
		for (int i = 0; i < height; i++)
			map[i] = new char[width];
		int row=0;
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

void Engine::Game(){
	time_t t;
	Treasure c;
	int j;
	double seconds_since_start;
	l.push_back(new Harry);
	for (j = 0; j < num_of_enemies; j++)
		l.push_back(new Classmates);
	char **TempMap;
	int i, exit, move = 0, moveC=0;
	c.Init(map, C, L);
	map[c.getY()][c.getX()] = 'T';
	l[0]->Init(map, C, L);
	map[l[0]->getY()][l[0]->getX()]='H';
	for (i = 1; i < l.size(); i++){
		l[i]->Init(map, C, L);
		map[l[i]->getY()][l[i]->getX()] = 'C';
	}	
	l[0]->CreateTempMap(map);
	dynamic_cast<Harry*> (l[0])->ShowTempMap(C, L);
	refresh();
	timeout(100);
	time_t start = time(0);
	do{
		do{
			move = getch();
			map[l[0]->getY()][l[0]->getX()] = ' ';
			exit = l[0]->GetMove(l[0]->getTempMap(), move);
			if (exit == 2){
				timeout(100);
				i = 0;
				for (j = 2; j < 26; j++){
					mvprintw(11, j - 1, " ");
					mvprintw(11, j, "YOU");
					mvprintw(11, 52 - j + 2 + 3, " ");
					mvprintw(11, 52 - j + 2, "WON");
					refresh();
					Sleep(50);
				}
				Sleep(250);
				mvprintw(21, 17, "PRESS ESC TO EXIT THE GAME");
				while (true){
					color_set(i % 6, 0);
					mvprintw(11, 18, "****** YOU WON!!! ******");
					refresh();
					i++;
					 if (getch()==27)
						return;
				}				
			}
		} while (exit == 0);
		map[l[0]->getY()][l[0]->getX()] = 'H';
		seconds_since_start = difftime(time(0), start);
		if (seconds_since_start >= movement_time_in_secs) {
			start = time(0);
			for (i = 1; i < l.size(); i++){
				l[i]->CreateTempMap(map);
				if ((dynamic_cast<Classmates*>(l[i])->CanMove(l[i]->getTempMap()))){
					srand((unsigned)time(&t));
					do{
						moveC = rand() % 4 + 1;
						mvprintw(l[i]->getY() + 2, l[i]->getX() + 1, "%c", ' ');
						map[l[i]->getY()][l[i]->getX()] = ' ';
						exit = l[i]->GetMove(l[i]->getTempMap(), moveC);
						if (exit == 2){
							timeout(100);
							i = 0;
							for (j = 2; j < 27; j++){
								mvprintw(11, j - 1, " ");
								mvprintw(11, j, "YOU");
								mvprintw(11, 54 - j + 2 + 4, " ");
								mvprintw(11, 54 - j + 2, "LOST");
								refresh();
								Sleep(50);
							}
							Sleep(250);
							mvprintw(21, 17, "PRESS ESC TO EXIT THE GAME");
							while (true){
								color_set(i % 6, 0);
								mvprintw(11, 19, "****** YOU LOST!!! ******");
								refresh();
								i++;
								if (getch() == 27)
									return;
							}					
						}
					} while (exit == 0);
					map[l[i]->getY()][l[i]->getX()] = 'C';
				}
			}
		}
		l[0]->CreateTempMap(map);
		dynamic_cast<Harry*> (l[0])->ShowTempMap(C, L);
		refresh();
	} while (move != 27);
}