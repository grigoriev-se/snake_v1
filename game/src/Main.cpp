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
	for (int rows = 0; rows < 19; ++rows) {
		for (int cols = 0; cols < 19; ++cols) {
			if (rows == 0 || rows == 18) {
				std::cout << "#";
			}
			else if (cols == 0 || cols == 18) {
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
	if (snake.x != 0 && snake.x != 19 && snake.y != 0 && snake.y != 19)
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
	int score = 0;
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
		score += 1;
	}
	
	std::cout << "You died, your score: " << score << "\n";

	return 0;
}