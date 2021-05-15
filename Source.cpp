#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <list>


using namespace sf;
using namespace std;


// Создаем окно
float width = 300.0f;
float height = 600.0f;
RenderWindow window(VideoMode(width, height), "SFML Works!");


class Paint {
public:
	void rect(float width, float height, float x, float y,
		int color[], float size_outline, int color_outline[]) {
		RectangleShape square(Vector2f(width, height));
		square.move(x, y);
		square.setOutlineThickness(size_outline);
		int r = color[0], g = color[1], b = color[2];
		square.setFillColor(Color(r, g, b));
		r = color_outline[0];
		g = color_outline[1];
		b = color_outline[2];
		square.setOutlineColor(Color(r, g, b));
		window.draw(square);
	}
};


class Game {
public:
	void draw(vector <vector <int>> board) {
		Paint Draw;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 20; j++) {
				if (board[i][j] == 0) {
					// Отрисовка пустой клетки
					int color[3] = { 0, 0, 0 };
					int outline_color[3] = { 255, 255, 255 };
					Draw.rect(width / 10, height / 20, (9 - i) * width / 10, (19 - j) * height / 20,
						color, 1.0f, outline_color);
				}
				else if (board[i][j] == 1) {
					// Отрисовка активной клетки
					int color[3] = { 255, 0, 0 };
					int outline_color[3] = { 255, 255, 255 };
					Draw.rect(width / 10, height / 20, (9 - i) * width / 10, (19 - j) * height / 20,
						color, 1.0f, outline_color);
				}
				else if (board[i][j] == 2) {
					// Отрисовка заполненной клетки
					int color[3] = { 150, 150, 150 };
					int outline_color[3] = { 255, 255, 255 };
					Draw.rect(width / 10, height / 20, (9 - i) * width / 10, (19 - j) * height / 20,
						color, 1.0f, outline_color);
				}
				else if (board[i][j] == 3) {
					int color[3] = { 0, 0, 200 };
					int outline_color[3] = { 255, 255, 255 };
					Draw.rect(width / 10, height / 20, (9 - i) * width / 10, (19 - j) * height / 20,
						color, 1.0f, outline_color);
				}
			}
		}
	}

	vector <vector <vector <int>>> create_figure(vector <vector <int>> board, int rand_figure) {
		std::mt19937 engine;
		engine.seed(std::time(nullptr));
		int r = engine() % 7;
		if (r != rand_figure) {
			rand_figure = r;
		}
		else {
			while (r == rand_figure) {
				r = engine() % 6;
			}
			rand_figure = r;
		}
		if (rand_figure == 0) {
			// :..
			int randx = engine() % 8 + 2;
			board[randx][20] = 1;
			board[randx][19] = 1;
			board[randx - 1][19] = 3;
			board[randx - 2][19] = 1;
		}
		else if (rand_figure == 1) {
			// ..:
			int randx = engine() % 8;
			board[randx][20] = 1;
			board[randx][19] = 1;
			board[randx + 1][19] = 3;
			board[randx + 2][19] = 1;
		}
		else if (rand_figure == 2) {
			// ::
			int randx = engine() % 9;
			board[randx][20] = 1;
			board[randx + 1][20] = 1;
			board[randx][19] = 1;
			board[randx + 1][19] = 1;
		}
		else if (rand_figure == 3) {
			// .:.
			int randx = engine() % 8;
			board[randx + 1][20] = 1;
			board[randx][19] = 1;
			board[randx + 1][19] = 1;
			board[randx + 2][19] = 3;
		}
		else if (rand_figure == 4) {
			// Ступеньки
			int randx = engine() % 8;
			board[randx + 2][20] = 1;
			board[randx + 1][20] = 1;
			board[randx + 1][19] = 1;
			board[randx][19] = 3;
		}
		else if (rand_figure == 5) {
			// Обратные ступеньки
			int randx = engine() % 8;
			board[randx][20] = 1;
			board[randx + 1][20] = 1;
			board[randx + 1][19] = 1;
			board[randx + 2][19] = 3;
		}
		vector <vector <vector <int>>> output(2, vector <vector <int>>(10, vector <int>(23)));
		vector <vector <int>> output_rand(1, vector <int>(1));
		output_rand[0][0] = rand_figure;
		output[0] = board;
		output[1] = output_rand;
		return output;
	}

	vector <int> find(vector <vector <int>> board) {
		vector <int> pos(2);
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 23; j++) {
				if (board[i][j] == 1 || board[i][j] == 3) {
					pos[0] = i;
					pos[1] = j;
					return pos;
				}
			}
		}
		pos[0] = -1;
		return pos;
	}

	vector <vector <int>> get_full_pos(vector <vector <int>> board) {
		vector <int> pos(2);
		int x, y;
		pos[0] = -1;
		vector <vector <int>> full_pos(5, vector <int>(2));
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 23; j++) {
				if (board[i][j] == 1 || board[i][j] == 3) {
					pos[0] = i;
					pos[1] = j;
					break;
				}
			}
			if (pos[0] != -1) {
				break;
			}
		}
		for (int i = 0; i < 5; i++) {
			full_pos[i][0] = -1;
		}
		for (int i = -3; i <= 3; i++) {
			for (int j = -3; j <= 3; j++) {
				x = pos[0] + i;
				y = pos[1] + j;
				if (x >= 0 && x <= 9 && y >= 0 && y <= 22) {
					if (board[x][y] == 1 || board[x][y] == 3) {
						for (int k = 0; k < 5; k++) {
							if (full_pos[k][0] == -1) {
								full_pos[k][0] = x;
								full_pos[k][1] = y;
								break;
							}
						}
					}
				}
			}
		}
		return full_pos;
	}

	vector <vector <int>> move(vector <vector <int>> board, vector <int> pos) {
		vector <vector <int>> figure(5, vector <int>(2));
		for (int i = 0; i < 5; i++) {
			figure[i][0] = -1;
		}
		bool freeze = false;
		for (int i = -3; i <= 3; i++) {
			for (int j = -3; j <= 3; j++) {
				if (pos[0] + i >= 0 && pos[0] + i <= 9 && pos[1] + j >= 0 && pos[1] + j <= 22) {
					if (board[pos[0] + i][pos[1] + j] == 1 || board[pos[0] + i][pos[1] + j] == 3) {
						for (int i1 = 0; i1 < 5; i1++) {
							if (figure[i1][0] == -1) {
								figure[i1][0] = pos[0] + i;
								figure[i1][1] = pos[1] + j;
								break;
							}
						}
						if (pos[1] + j - 1 >= 0) {
							if (board[pos[0] + i][pos[1] + j - 1] == 2) {
								freeze = true;
							}
						}
						if (pos[1] + j == 0) {
							freeze = true;
						}
					}
				}
			}
		}
		for (int i = 0; i < 5; i++) {
			if (figure[i][0] == -1) {
				break;
			}
			if (freeze) {
				board[figure[i][0]][figure[i][1]] = 2;
			}
			else if (board[figure[i][0]][figure[i][1]] == 1) {
				board[figure[i][0]][figure[i][1]] = 0;
				board[figure[i][0]][figure[i][1] - 1] = 1;
			}
			else {
				board[figure[i][0]][figure[i][1]] = 0;
				board[figure[i][0]][figure[i][1] - 1] = 3;
			}
		}
		return board;
	}

	vector <vector <int>> turn(vector <vector <int>> board, vector <int> pos, int way) {
		int x, y;
		int turn = true;
		vector <vector <int>> move(5, vector <int>(2));
		for (int i = 0; i < 5; i++) {
			move[i][0] = -1;
		}
		for (int i = 3; i >= -3; i--) {
			for (int j = 3; j >= -3; j--) {
				if (way == -1) {
					x = pos[0] + i * -1;
					y = pos[1] + j * -1;
				}
				else {
					x = pos[0] + i;
					y = pos[1] + j;
				}
				if (x >= 0 && x <= 9 && y > 0 && y <= 22) {
					if ((board[x][y] == 1 || board[x][y] == 3) && x + way <= 9 && x + way >= 0
						&& board[x + way][y] != 2 && board[x + way][y - 1] != 2) {
						for (int k = 0; k < 5; k++) {
							if (move[k][0] == -1) {
								move[k][0] = x;
								move[k][1] = y;
								break;
							}
						}
					}
					else if (board[x][y] == 1 || board[x][y] == 3) {
						turn = false;
						break;
					}
				}
			}
			if (not turn) {
				break;
			}
		}
		if (turn) {
			for (int i = 0; i < 5; i++) {
				if (move[i][0] == -1) {
					break;
				}
				if (board[move[i][0]][move[i][1]] == 1) {
					board[move[i][0] + way][move[i][1]] = 1;
				}
				else {
					board[move[i][0] + way][move[i][1]] = 3;
				}
				board[move[i][0]][move[i][1]] = 0;
			}
		}
		return board;
	}

	vector <vector <int>> reverse(vector <vector <int>> board, vector <vector <int>> full_pos) {
		int px, py, x1, x2, y1, y2;
		int c;
		bool rev = true;
		vector <vector <int>> new_pos (5, vector <int> (4));
		for (int i = 0; i < 4; i++) {
			new_pos[i][0] = -1;
		}
		for (int i = 0; i < 4; i++) {
			if (board[full_pos[i][0]][full_pos[i][1]] == 3) {
				px = full_pos[i][0];
				py = full_pos[i][1];
			}
		}
		for (int i = 0; i < 4; i++) {
			if (board[full_pos[i][0]][full_pos[i][1]] != 3) {
				x1 = full_pos[i][0];
				y1 = full_pos[i][1];
				x2 = px + py - y1;
				y2 = x1 + py - px;
				if (x2 >= 0 && x2 <= 9 && y2 >= 1 && y2 <= 22) {
					if (board[x2][y2] != 2 && board[x2][y2 - 1] != 2) {
						for (int k = 0; k < 4; k++) {
							if (new_pos[k][0] == -1) {
								new_pos[k][0] = x1;
								new_pos[k][1] = y1;
								new_pos[k][2] = x2;
								new_pos[k][3] = y2;
								break;
							}
						}
					}
					else {
						rev = false;
						break;
					}
				}
				else {
					rev = false;
					break;
				}
			}
		}
		if (rev) {
			for (int i = 0; i < 3; i++) { 
				x1 = new_pos[i][0];
				y1 = new_pos[i][1];
				x2 = new_pos[i][2];
				y2 = new_pos[i][3];
				c = board[x2][y2];
				board[x2][y2] = board[x1][y1];
				board[x1][y1] = c;
			}
		}
		return board;
	}

	vector <vector <int>> check_rows(vector <vector <int>> board) {
		bool row;
		int y, move_down = 0, destroy_row = -1;
		for (int j = 0; j < 23; j++) {
			row = true;
			for (int i = 0; i < 10; i++) {
				if (board[i][j] != 2) {
					row = false;
					break;
				}
			}
			if (row) {
				move_down++;
				for (int i = 0; i < 10; i++) {
					board[i][j] = 0;
				}
				if (destroy_row == -1) {
					destroy_row = j;
				}
			}
		}
		if (destroy_row != -1) {
			for (int j = destroy_row + 1; j < 23; j++) {
				for (int i = 0; i < 10; i++) {
					if (board[i][j] == 2) {
						cout << j - move_down << "." <<"\n";
						board[i][j] = 0;
						board[i][j - move_down] = 2;
					}
				}
			}
		}
		return board;
	}

	bool game_cycle() {
		// Переменные
		bool figure = false; // Есть ли фигура на поле
		bool row = false; // Выстроил ли игрок ряд
		int rand_figure = -1; // Номер фигуры на поле
		int p = 0; // Кадров прорисованно
		int t = 0; // Кадр на котором сделано действие
		int default_speed = 10; // Скорость игры
		int speed = 10; // Скорость игры в данный момент
		vector <vector <int>> full_pos(5, vector <int> (2));
		vector <int> pos(2); // Кординаты "живой" клетки
		// Создаем поле
		vector <vector <int>> board(10, vector <int> (23));
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 23; j++) {
				board[i][j] = 0;
			}
		}
		// Главный цикл
		bool run = true;
		while (window.isOpen() && run)
		{
			// События
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed) {
					window.close();
				}
				if (event.type == Event::KeyReleased && p != t) {
					t = p;
					if (event.key.code == Keyboard::Left || event.key.code == Keyboard::A) {
						board = turn(board, pos, 1);
					}
					else if (event.key.code == Keyboard::Right || event.key.code == Keyboard::D) {
						board = turn(board, pos, -1);
					}
					else if (event.key.code == Keyboard::Down || event.key.code == Keyboard::S) {
						speed = 1;
					}
					else if (event.key.code == Keyboard::Space) {
						if (rand_figure != 2 && figure) {
							board = reverse(board, get_full_pos(board));
						}
					}
				}
			}
			// Логика
			if (not figure) {
				// Создание новой фигуры
				speed = default_speed;
				figure = true;
				vector <vector <vector <int>>> output(2, vector <vector <int>>(10, vector <int>(23)));
				output = create_figure(board, rand_figure);
				board = output[0];
				rand_figure = output[1][0][0];
				pos = find(board);
			}
			if (p % speed == 0) {
				// Движение
				board = move(board, pos);
			}
			// Получаем x, y "живой" клетки
			pos = find(board);
			if (pos[0] == -1) {
				// Не нашли "живой" клетки
				figure = false;
				// Проверяем не проиграл ли игрок
				for (int i = 0; i < 10; i++) {
					if (board[i][19] == 2) {
						run = false;
						break;
					}
				}
				// Проверяем не выстроил ли игрок ряд
				board = check_rows(board);
			}
			// Отрисовка
			draw(board);
			window.setFramerateLimit(30);
			p += 1;
			window.display();
		}
		window.close();
		if (run) {
			return false;
		}
		return true;
	}
};


int main()
{
	Game game;
	if (not game.game_cycle()) {
		cout << "You lose";
	}
	return 0;
}