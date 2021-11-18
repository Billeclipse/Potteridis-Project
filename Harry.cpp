#include "Harry.h"

int Harry::GetMove(char **MapPart,int move){
	switch (move){
	case KEY_UP:
		if (MapPart[3 - 1][3] == ' '){
			y = y - 1;
			return 1;
		}
		else if (MapPart[3 - 1][3] == 'T')
			return 2;
		break;
	case KEY_DOWN:
		if (MapPart[3 + 1][3] == ' '){
			y = y + 1;
			return 1;
		}
		else if (MapPart[3 + 1][3] == 'T')
			return 2;
		break;
	case KEY_RIGHT:
		if (MapPart[3][3 + 1] == ' '){
			x = x + 1;
			return 1;
		}
		else if (MapPart[3][3 + 1] == 'T')
			return 2;
		break;
	case KEY_LEFT:
		if (MapPart[3][3 - 1] == ' '){
			x = x - 1;
			return 1;
		}
		else if (MapPart[3][3 - 1] == 'T')
			return 2;
		break;
	case 27:
		return 1;
		break;
	case -1:
		return 1;
		break;
	}
	return 0;
}

void Harry::ShowTempMap(int W, int H){
	for (int i = 0; i < 7; i++){
		for (int j = 0; j < 7; j++) {
			if (y + i <= H + 2  && x + j <= W + 2  && y + i > 2 && x + j > 2) {
				if (TempMap[i][j] == 'H')
					color_set(3, 0);
				else if (TempMap[i][j] == 'C')
					color_set(6, 0);
				else if (TempMap[i][j] == 'T')
					color_set(5, 0);
				else
					color_set(1, 0);
				mvprintw(y + i + 2 - 3, x + j + 1 - 3, "%c", TempMap[i][j]);
			}
		}
	}
}