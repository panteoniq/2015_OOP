#include <iostream>
#include <iomanip>
using namespace std;
#include "Score.h"

Score::Score()
{
    score_ = 0;
	level_ = 1;
    score_pos_ = Point(28, 9);
	level_pos_ = Point(26, 8);
	plus_pos_ = Point(28, 10);
}

void Score::Print(Point reference_pos)
{
    Point::GotoXY(reference_pos + score_pos_);
    cout << "    ";
    Point::GotoXY(reference_pos + score_pos_);
    cout << setw(5) << score_;
	Point::GotoXY(reference_pos + level_pos_);
	cout << "레　벨 : " << level_;
}

void Score::UpdateScore(Point reference_pos, int increment)
{
	switch (increment) //increment=지워진 줄 수
	{
	case 1: //한 줄 사라지면
		score_ += 10;
		Point::GotoXY(reference_pos + plus_pos_);
		cout << "+10!";
		break;
	case 2: //두 줄 사라지면
		score_ += 40;
		Point::GotoXY(reference_pos + plus_pos_);
		cout << "+40!";
		break;
	case 3: // 세 줄 사라지면
		score_ += 90;
		Point::GotoXY(reference_pos + plus_pos_);
		cout << "+90!";
		break;
	case 4: //네 줄 사라지면
		score_ += 160;
		Point::GotoXY(reference_pos + plus_pos_);
		cout << "+160!";
		break;
	}
    
    Print(reference_pos);
}

void Score::Erase(Point reference_pos)
{
	Point::GotoXY(reference_pos + plus_pos_);
	cout << "      ";
}

int Score::CurLevel(void)
{
	level_ = 1 + (score_ / 500);
	return level_;
}