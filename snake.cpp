#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>

using namespace std;

constexpr int width = 16;
constexpr int height = 16;
constexpr int fps = 1;
constexpr double tick = 1 / fps;
string buffer;

struct Pos
{
	int x;
	int y;
	Pos(int px, int py)
	{
		if (px >= 0) x = px % width;
		else x = px + width;
		if (py >= 0) y = py % height;
		else y = py + width;
	}
	bool operator==(Pos& that) { if (x == that.x&&y == that.y)return true; return false; }
};

enum Dir { up, rt, dn, lt };
enum Col { no = 0, eat = 1, die = 2 };

class Snake
{
public:
	vector<Pos> body;
	Dir d;
	Snake(Pos pos) :body{ pos }, d{ Dir::rt } {}
	void setdir(Dir dir) { d = dir; }
	void update(bool eat)
	{
		switch (d)
		{
		case Dir::up:
			body.push_back(Pos((*(body.end() - 1)).x, (*(body.end() - 1)).y - 1));
			break;
		case Dir::dn:
			body.push_back(Pos((*(body.end() - 1)).x, (*(body.end() - 1)).y + 1));
			break;
		case Dir::lt:
			body.push_back(Pos((*(body.end() - 1)).x - 1, (*(body.end() - 1)).y));
			break;
		case Dir::rt:
			body.push_back(Pos((*(body.end() - 1)).x + 1, (*(body.end()-1)).y));
			break;
		}
		if (!eat)
			body.erase(body.begin());
	}
};

class Berry
{
public:
	Berry(Pos pos) :body{ pos } {}
	vector<Pos> body;
};

inline void flush() { system("cls"); }
inline char getInput()
{
	if (_kbhit())
		return (char)_getch();
	return 0;
}
inline void writeBuffer(Pos& pos)
{
	buffer.at(pos.y*(width+1) + pos.x) = '*';
}

void draw(vector<Pos>& body)
{
	for (auto each : body)
		writeBuffer(each);
}
Col collision(vector<Pos>& snake, vector<Pos>& berry)
{
	Col res = Col::no;
	vector<Pos>::iterator head = snake.begin();
	vector<Pos>::iterator b = berry.begin();
	if (*head == *b) res = Col::eat;
	for_each(head + 1, snake.end(), [head, b, &res](Pos node) {
		if (node == *head) res = Col::die;
	});
	return res;
}

int main()
{
	for (int i = 0; i<height; ++i) { buffer.insert(i*(width + 1), width, ' ');buffer.push_back('\n'); }
	Snake snake{ Pos{ 8, 8 } };
	Berry berry{ Pos{ rand() % width, rand() % height } };

	auto beginTime = clock();
	for (;;)
	{
		beginTime = clock();

		switch (collision(snake.body, berry.body))
		{
		case Col::die:
			return -1;
		case Col::eat:
			snake.update(true);
			berry.body.clear();
			berry.body.push_back(Pos(rand() % width, rand() % height));
			break;
		case Col::no:
			snake.update(false);
			break;
		}
		draw(snake.body);
		draw(berry.body);
		flush();
		cout << buffer << endl;
		// system("pause");
		while (tick > (double)((clock() - beginTime) / CLOCKS_PER_SEC))
		{
			switch (getInput())
			{
			case 'w':
				snake.setdir(Dir::up);
				break;
			case 'a':
				snake.setdir(Dir::lt);
				break;
			case 's':
				snake.setdir(Dir::dn);
				break;
			case 'd':
				snake.setdir(Dir::rt);
				break;
			}
		}
		buffer.clear();
		for (int i = 0; i<height; ++i) { buffer.insert(i*(width + 1), width, ' '); buffer.push_back('\n'); }
	}
	return 0;
}
