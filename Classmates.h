#include "Living.h"

class Classmates : public Living{
public:
	int GetMove(char **MapPart, int move);
	bool CanMove(char **MapPart);
};