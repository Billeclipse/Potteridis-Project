#include <iostream>
#include <string>
#include "lib/curses.h"
using namespace std;

class Treasure{
	int x;
	int y;
public:
	void Init(char **map, int C, int L);
	int getX();
	int getY();
};