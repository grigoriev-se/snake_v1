#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <string>

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

int ROW = 10;
int COL = 10;

class snake {
public:
	int x, y;

	void move(int xdir, int ydir) {
		x += xdir;
		y -= ydir; // - since calculated from upper left corner.
	}
};

class apple {
public:
	int x, y;

	void generate_pos() {
		x = 1 + (rand() % (COL - 2));
		y = 1 + (rand() % (ROW - 2));
	}
};

void generate_board(snake snake, apple apple) {
	// Generate board
	for (int rows = 0; rows < (ROW); ++rows) {
		for (int cols = 0; cols < (COL); ++cols) {
			if (rows == 0 || rows == (ROW - 1)) {
				cout << "#";
			}
			else if (cols == 0 || cols == (COL - 1)) {
				cout << "#";
			}
			// Put either " " or snake
			else if (snake.x == cols && snake.y == rows) {
				cout << "O";
			}
			else if (apple.x == cols && apple.y == rows) {
				cout << "d";
			}
			else
			{
				cout << " ";
			}
		}
		cout << "\n";
	}
	cout << "\nPress UP/DOWN/LEFT/RIGHT keys: ";

}

snake check_boundaries(snake snake) {
	if (snake.x == 0) {
		snake.x = (COL - 2);
	}
	else if (snake.x == (COL - 1)) {
		snake.x = 1;
	}
	else if (snake.y == 0) {
		snake.y = (ROW - 2);
	}
	else if (snake.y == (ROW - 1)) {
		snake.y = 1;
	}
	return snake;
}

// Will not be necessary in future
bool run_game(int a) {
	if (a < 50) return true;
	else return false;
}

int main() {
	int a = 0, score = 0;
	int xdir, ydir;

	char key;
	int value;

	snake snake;
	srand((unsigned)time(NULL));
	snake.x = 1 + (rand() % (COL - 2));
	snake.y = 1 + (rand() % (ROW - 2));

	
	apple apple;
	apple.generate_pos();

	while (run_game(a) == true) {
		if (apple.x == snake.x && apple.y == snake.y) {
			apple.generate_pos();
			score += 1;
		}
		cout << "x: " << snake.x << "\n";
		cout << "y: " << snake.y << "\n";
		cout << "Your score: " << score << "\n";
		generate_board(snake, apple);

		key = _getch();
		value = key;

		// Run around the board.
		switch (_getch()) {
		case KEY_UP:
			xdir = 0;
			ydir = 1;
			break;
		case KEY_DOWN:
			xdir = 0;
			ydir = -1;
			break;
		case KEY_LEFT:
			xdir = -1;
			ydir = 0;
			break;
		case KEY_RIGHT:
			xdir = 1;
			ydir = 0;
			break;
		}

		snake.move(xdir, ydir);
		snake = check_boundaries(snake);

		system("CLS");
		a += 1;
	}

	cout << "You died, your score: " << score << "\n";

	return 0;
}