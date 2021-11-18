#ifndef Living_H
#define Living_H
#include <iostream>
#include <string>
#include "lib/curses.h"
using namespace std;

class Living{
protected:	
	int x;
	int y;	
	char **TempMap;
public:	
	Living();
	void virtual Init(char **map, int C, int L);
	int virtual GetMove(char **MapPart, int move) = 0;
	int getX();
	int getY();
	void CreateTempMap(char **map);
	char** getTempMap();
};
#endif