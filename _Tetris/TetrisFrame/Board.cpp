#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include "Board.h"
using namespace std;

void SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

Board::Board()
{
	int i, j;

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 20; j++)
			board_[i][j] = EMPTY; // 게임 화면만 -1로 처리
	}
}

int Board::GetState(Point pos)
{
	return board_[pos.GetX()][pos.GetY()];
}

void Board::SetState(Point pos, int state)
{
	board_[pos.GetX()][pos.GetY()] = state;
}

int Board::CheckLineFull(Point reference_pos)
{
	srand(time(NULL));
	int count = 0, i, j, k;
	int x, y;
	int tempX, tempY;
	bool full;// 다 차있는지에 대한 정보 제공

	for (k = 0; k < 3; k++)
	{
		for (i = 0; i < 20; i++)// 보드 배열의 가로 행(하지만 테트리스 보드 화면 상으로는 세로 줄)
		{
			full = true;
			for (j = 0; j < 10; j++)//보드 배열의 세로 열(테트리스 보드 화면 상으로는 가로 줄)
			{
				if (board_[j][i] == EMPTY) // 빈 자리가 하나라도 있으면 꽉 차있는 게 아님
				{
					full = false; // false로 값을 변경한 다음
					break; //탈출
				}
			}
			if (full) // 특정 행이 꽉 차있다면
			{
				count++;
				for (y = i + 1; y < 20; y++)
				{
					for (x = 0; x < 10; x++)
					{
						tempX = Point::GetScrPosFromCurPos(Point(x, 0)).GetX() + reference_pos.GetX();
						tempY = Point::GetScrPosFromCurPos(Point(0, y)).GetY() + reference_pos.GetY();
						Point::GotoXY(tempX, tempY);//이제 판에서 그 줄을 지워야 하니까 좌표를 옮긴 다음에
						cout << "　";//지우기
						board_[x][y - 1] = EMPTY;
						board_[x][y - 1] = board_[x][y]; // 지금 내려야 하는 줄의 윗 줄을 복사했지
					}
					for (x = 0; x < 10; x++) //화면에 표시하기
					{
						if (board_[x][y - 1] != EMPTY) //해당 배열이 비어있는지 비어있지 않은지에 따라 화면에 표시
						{
							tempX = Point::GetScrPosFromCurPos(Point(x, 0)).GetX() + reference_pos.GetX();
							tempY = Point::GetScrPosFromCurPos(Point(0, y)).GetY() + reference_pos.GetY();
							Point::GotoXY(tempX, tempY);
							SetColor(board_[x][y]);
							cout << "■";
						}
						else
						{
							tempX = Point::GetScrPosFromCurPos(Point(x, 0)).GetX() + reference_pos.GetX();
							tempY = Point::GetScrPosFromCurPos(Point(0, y)).GetY() + reference_pos.GetY();
							Point::GotoXY(tempX, tempY);
							cout << "　";
						}
					}
				}
			}
		}
	}
	if (count != 0)
	{
		for (y = 0; y < 20; y++)
			for (x = 0; x < 10; x++)
			{
				if (board_[x][y] != EMPTY) //해당 배열이 비어있는지 비어있지 않은지에 따라 화면에 표시
				{
					tempX = Point::GetScrPosFromCurPos(Point(x, 0)).GetX() + reference_pos.GetX();
					tempY = Point::GetScrPosFromCurPos(Point(0, y)).GetY() + reference_pos.GetY();
					Point::GotoXY(tempX, tempY);
					SetColor(board_[x][y]);
					cout << "■";
				}
				else
				{
					tempX = Point::GetScrPosFromCurPos(Point(x, 0)).GetX() + reference_pos.GetX();
					tempY = Point::GetScrPosFromCurPos(Point(0, y)).GetY() + reference_pos.GetY();
					Point::GotoXY(tempX, tempY);
					cout << "　";
				}

			}
	}
	SetColor(7);
	return count;
}

void Board::ReDraw(Point reference_pos)
{
	int x, y;
	int tempX, tempY;
	for (y = 0; y < 20; y++)
		for (x = 0; x < 10; x++)
		{
			if (board_[x][y] != EMPTY) //해당 배열이 비어있는지 비어있지 않은지에 따라 화면에 표시
			{
				tempX = Point::GetScrPosFromCurPos(Point(x, 0)).GetX() + reference_pos.GetX();
				tempY = Point::GetScrPosFromCurPos(Point(0, y)).GetY() + reference_pos.GetY();
				Point::GotoXY(tempX, tempY);
				SetColor(board_[x][y]);
				cout << "■";
			}
			else
			{
				tempX = Point::GetScrPosFromCurPos(Point(x, 0)).GetX() + reference_pos.GetX();
				tempY = Point::GetScrPosFromCurPos(Point(0, y)).GetY() + reference_pos.GetY();
				Point::GotoXY(tempX, tempY);
				cout << "　";
			}
		}
}