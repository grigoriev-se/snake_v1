#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <string>
#include <vector>

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

int ROW = 10;
int COL = 10;

class apple {
public:
	int x, y;

	void generate_pos() {
		x = 1 + (rand() % (COL - 2));
		y = 1 + (rand() % (ROW - 2));
	}
};

class snake {
public:
	std::vector<int> x, y;

	void move(int xdir, int ydir) {
		int snake_size = x.size();
		while (snake_size-1 != 0) {
			x[snake_size-1] = x[snake_size-2];
			y[snake_size-1] = y[snake_size-2];
			snake_size -= 1;
		}
		x[0] += xdir;
		y[0] -= ydir; // - since calculated from upper left corner.
	}

	void generate_tail(apple apple) {
		x.push_back(apple.x);
		y.push_back(apple.y);
		cout << "Tail generated\n";
	}
};


void generate_board(snake snake, apple apple) {
	// Generate board
	int tail_counter = 0;

	for (int rows = 0; rows < (ROW); ++rows) {
		for (int cols = 0; cols < (COL); ++cols) {
			if (snake.x[0] == cols && snake.y[0] == rows) {
				cout << "O";
			}
			//// This part incorrectly generates the snake tail
			// FIX THIS - almost works
			//if (snake.x[tail_counter] == cols && snake.y[tail_counter] == rows) {
			//	cout << "S";
			//	tail_counter += 1;
			//}

			else if (rows == 0 || rows == (ROW - 1)) {
				cout << "#";
			}
			else if (cols == 0 || cols == (COL - 1)) {
				cout << "#";
			}
			// Put either " " or snake
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
	int snake_size = snake.x.size();
	while (snake_size != 0) {
		if (snake.x[snake_size - 1] == 0) {
			snake.x[snake_size - 1] = (COL - 2);
		}
		else if (snake.x[snake_size - 1] == (COL - 1)) {
			snake.x[snake_size - 1] = 1;
		}
		else if (snake.y[snake_size - 1] == 0) {
			snake.y[snake_size - 1] = (ROW - 2);
		}
		else if (snake.y[snake_size - 1] == (ROW - 1)) {
			snake.y[snake_size - 1] = 1;
		}
		snake_size -= 1;
	}
	return snake;
}


// Will not be necessary in future
bool run_game(int a) {
	if (a < 50) return true;
	else return false;
}

int main() {
	int a = 0;
	int xdir, ydir;

	char key;
	int value;

	snake snake;
	apple apple;

	srand((unsigned)time(NULL));
	snake.x.push_back(1 + (rand() % (COL - 2)));
	snake.y.push_back(1 + (rand() % (ROW - 2)));
	apple.generate_pos();

	while (run_game(a) == true) {
		if (apple.x == snake.x[0] && apple.y == snake.y[0]) {
			apple.generate_pos(); // Generates a new position
			snake.generate_tail(apple); // Puts an apple in the tail
		}
		//for (int ii = 0; ii < tail.size; ++ii) {
		//	tail.move(snake, ii);
		//}

		cout << "head_x: " << snake.x[0] << "\n";
		cout << "head_y: " << snake.y[0] << "\n";
		cout << "Snake size: " << snake.x.size() << "\n";

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

	cout << "You died, your score: " << snake.x.size() << "\n";

	return 0;
}