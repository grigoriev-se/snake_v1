#include <iostream>
#include <stdlib.h>

class snake {
public:
	int x, y;

	void Move(int xdir, int ydir) {
		x += xdir;
		y += ydir;
	}
};

void generate_board(snake snake) {
	// Generate board
	for (int rows = 0; rows < 20; ++rows) {
		for (int cols = 0; cols < 39; ++cols) {
			if (rows == 0 || rows == 19) {
				std::cout << "#";
			}
			else if (cols == 0 || cols == 38) {
				std::cout << "#";
			}
			// Put either " " or snake
			else if (snake.x == rows && snake.y == cols){
				std::cout << "O";
			}
			else
			{
				std::cout << " ";
			}
		}
		std::cout << "\n";
	}
}

bool check_boundaries(snake snake) {
	if (snake.x != 0 && snake.x != 19 && snake.y != 0 && snake.y != 39)
	{
		return true;
	}
	else
		return false;
}

// Will not be necessary in future
bool run_game(int a) {
	if (a < 10) return true;
	else return false;
}

int main() {
	int a = 0;
	int xdir = 1, ydir = 0;
	snake snake;
	snake.x = 10;
	snake.y = 10;

	while (run_game(a) == true) {
		generate_board(snake);
		snake.Move(xdir, ydir);
		check_boundaries(snake);
		system("CLS");
		a += 1;
	}

	return 0;
}