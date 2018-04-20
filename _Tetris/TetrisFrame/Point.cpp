#include <windows.h>
#include <conio.h>
#include <ctime>
#include "Point.h"
using namespace std;

Point::Point(int x, int y) : x_(x), y_(y) // 생성자
{ 

}

Point Point::operator+(const Point &pt) // 덧셈 연산자 오버로딩
{
	return Point(x_ + pt.x_, y_ + pt.y_);
}

void Point::GotoXY(int x, int y)		// 커서 위치 이동
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos); // 라이브러리 함수
} // x, y 위치로 커서를 이동함

void Point::GotoXY(Point pos)
{
	GotoXY(pos.GetX(), pos.GetY());
}

Point Point::GetScrPosFromCurPos(const Point &pos)
{
	return Point(2 * pos.x_ + 2, (-1) * pos.y_ + 20);
}