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

class Engine {
	int C, L, note, note2;
	char** map;
	bool music_on;
	vector<Living*> l;
public:
	char** LoadMap(string filepath, int& width, int& height);
	void ShowMap(int W, int H, bool first);
	int Game(int mode);
	void SpellRandom();
	void WinningMusic();
	void LosingMusic();
};
