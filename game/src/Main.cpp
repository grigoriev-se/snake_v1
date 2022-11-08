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

int ROW = 5;
int COL = 7;

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
		while (snake_size - 1 != 0) {
			x[snake_size - 1] = x[snake_size - 2];
			y[snake_size - 1] = y[snake_size - 2];
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

class board {

public:
	vector<string> generate_new() {
		int AREA = ROW * COL;
		std::vector<string> board(AREA, " ");
		std::fill(board.begin(), board.begin() + COL, "#");
		std::fill(board.end() - COL, board.end(), "#");
		for (int jj = 1; jj < ROW - 1; ++jj) {
			board[COL * jj] = "#";
			board[COL * (jj + 1) - 1] = "#";
		}
		return board;
	}

	void plot_board(vector<string> board_vector, apple apple) {
		cout << "plot_board:\n";
		// Update the apple:
		cout << "Apple coordinates (x,y): " << apple.x << " " << apple.y << ". \n";
		board_vector[apple.y * (COL -1) + apple.y + apple.x] = "Q";
		for (int x = 0; x < board_vector.size(); ++x) {
			cout << board_vector[x];
			if ((x + 1) % COL == 0) {
				cout << "\n";
			}
		}
	}

	vector<string> update_board(vector<string> board_vector, snake snake, apple apple) {
		// Update the snake and tail positions:

		cout << "FOR LOOP:\n";
		for (int rows = 0; rows < (ROW); ++rows) {
			for (int cols = 0; cols < (COL); ++cols) {
				if (snake.x[0] == cols && snake.y[0] == rows) {
					cout << "O";
				}
				else if (rows == 0 || rows == (ROW - 1)) {
					cout << "#";
				}
				else if (cols == 0 || cols == (COL - 1)) {
					cout << "#";
				}
				// Put either " " or apple
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
		return board_vector;
	}
};

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
	board board;

	srand((unsigned)time(NULL));
	snake.x.push_back(1 + (rand() % (COL - 2)));
	snake.y.push_back(1 + (rand() % (ROW - 2)));
	apple.generate_pos();

	vector<string> board_vector = board.generate_new();
	board_vector = board.update_board(board_vector, snake, apple);

	while (run_game(a) == true) {
		if (apple.x == snake.x[0] && apple.y == snake.y[0]) {
			snake.generate_tail(apple); // Puts an apple in the tail
			apple.generate_pos(); // Generates a new position
		}
		for (int ii = 0; ii < snake.x.size(); ++ii) {
			cout << "Snake tail (x,y): " << snake.x[ii] << "," << snake.y[ii] << "\n";

		}
		//for (int ii = 0; ii < tail.size; ++ii) {
		//	tail.move(snake, ii);
		//}

		//cout << "head (x,y): " << snake.x[0] << "," << snake.y[0] << "\n";
		cout << "Snake size: " << snake.x.size() << "\n";

		board_vector = board.update_board(board_vector, snake, apple);
		board.plot_board(board_vector, apple);
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