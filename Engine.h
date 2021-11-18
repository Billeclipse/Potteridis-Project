#include <iostream>
#include <string>
#include <vector>
#include "lib/curses.h"
#include "time.h"
#include "Treasure.h"
#include "Living.h"
#include "Harry.h"
#include "Classmates.h"
using namespace std;

class Engine{
	int C, L;
	char **map;
	vector<Living*> l;
public:	
	char** LoadMap(string filepath,int &width,int &height);
	void Game();
};
