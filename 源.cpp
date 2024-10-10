//下1左2上3右4
//1墙0路3入口4出口
//坐标从0开始
//int Row;//行
//int Col;//列
#include<iostream>
using namespace std;
class CoordinateAndDecoration {
public:
	int Coordinate[2] = { 1,1 };
	int Decoration = 0;
	CoordinateAndDecoration(int t[2], int dir) {
		Coordinate[0] = t[0];
		Coordinate[1] = t[1];
		Decoration = dir;
	}
	CoordinateAndDecoration() {}
	~CoordinateAndDecoration() {
	}
};

class Maze {
public:
	int** Board;
	int Row;//行
	int Col;//列
	int Begin[2] = { 1,1 };
	int End[2] = { 1,1 };

	Maze(int Col, int Row) :Row(Row), Col(Col) {
		Board = new int* [Row];
		for (int i = 0; i < Row; i++) {
			int* p = new int[Col];
			for (int j = 0; j < Col; j++) {
				cin >> p[j];
				if (p[j] == 3) {
					Begin[0] = i; Begin[1] = j;
				}
				if (p[j] == 4) {
					End[0] = i; End[1] = j;
				}
			}
			Board[i] = p;
		}

	}
	~Maze() {
		for (int i = 0; i < Row; i++) {
			delete[] Board[i];
		}
		delete[] Board;
	}
	void show() {
		for (int i = 0; i < Row; i++)
		{
			for (int j = 0; j < Col; j++)
			{
				cout << Board[i][j] << ' ';
			}
			cout << endl;
		}
		cout << Begin[0] << Begin[1];
		cout << End[0] << End[1];
	}
	bool IsNotBound(int t[2]) {
		return Board[t[0]][t[1]] != 1;
	}
};
class stack {
public:
	CoordinateAndDecoration* s;
	int size;
	int top;

	stack(int size) :size(size) {
		s = new CoordinateAndDecoration[size];
		top = -1;
	}
	~stack() {
		delete[] s;
	}
	void Resize() {
    int newSize = size * 2; // 将新数组的大小设置为当前大小的两倍
    CoordinateAndDecoration* newS = new CoordinateAndDecoration[newSize];
    for (int i = 0; i <= top; i++) {
        newS[i] = s[i];
    }
    delete[] s;
    s = newS;
    size = newSize;
}
	void push(CoordinateAndDecoration& tmp) {
		if (top == size - 1) {
			Resize();
		}
		if (top == -1) {
			s[++top] = tmp;
		}
		else {
			s[top].Decoration++;
			s[++top] = tmp;
		}
	}
	void pop() {
		top--;
	}
	bool IsFive() {
		return s[top].Decoration == 5;
	}
	int* topnumber() {
		return s[top].Coordinate;
	}
	CoordinateAndDecoration nextstep() {
		int t[2];//下1左2上3右4
		int dir = 1;
		if (s[top].Decoration == 1) {
			t[0] = s[top].Coordinate[0] + 1;
			t[1] = s[top].Coordinate[1];
		}
		else if (s[top].Decoration == 2) {
			t[0] = s[top].Coordinate[0];
			t[1] = s[top].Coordinate[1] - 1;
		}
		else if (s[top].Decoration == 3) {
			t[0] = s[top].Coordinate[0] - 1;
			t[1] = s[top].Coordinate[1];
		}
		else if (s[top].Decoration == 4) {
			t[0] = s[top].Coordinate[0];
			t[1] = s[top].Coordinate[1] + 1;
		}
		CoordinateAndDecoration tmp(t, dir);
		return tmp;
	}
	void show() {
		for (int i = 0; i <= top; i++) {
			cout << s[i].Coordinate[1] << ' ' << s[i].Coordinate[0] << endl;
		}
	}
};

void Search(Maze& test, stack& path) {
	bool flag = true;
	CoordinateAndDecoration tmp(test.Begin, 1);
	path.push(tmp);
	while (flag) {
		//cout << path.topnumber()[0] << " " << path.topnumber()[1] <<" " <<path.s[path.top].Decoration<< endl;
		if (path.IsFive()) {
			test.Board[path.s[path.top].Coordinate[0]][path.s[path.top].Coordinate[1]] = 1;
			path.pop();
			test.Board[path.s[path.top].Coordinate[0]][path.s[path.top].Coordinate[1]] = 0;
		}else if(test.IsNotBound(path.topnumber())) {
			tmp = path.nextstep();
			path.push(tmp);
			test.Board[path.s[path.top - 1].Coordinate[0]][path.s[path.top - 1].Coordinate[1]] = 1;
		}
		else {
			path.pop();
			test.Board[path.s[path.top].Coordinate[0]][path.s[path.top].Coordinate[1]] = 0;
		}
		//终止条件
		if (path.s[path.top].Coordinate[0] == test.End[0] && path.s[path.top].Coordinate[1] == test.End[1])flag = false;
	}
	path.show();
}
int main() {
	//创建棋盘
	int x, y; cin >> x >> y;
	Maze test(x, y);
	//创建栈
	stack path(x * y);
	Search(test, path);

}