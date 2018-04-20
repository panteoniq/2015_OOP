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
			board_[i][j] = EMPTY; // ���� ȭ�鸸 -1�� ó��
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
	bool full;// �� ���ִ����� ���� ���� ����

	for (k = 0; k < 3; k++)
	{
		for (i = 0; i < 20; i++)// ���� �迭�� ���� ��(������ ��Ʈ���� ���� ȭ�� �����δ� ���� ��)
		{
			full = true;
			for (j = 0; j < 10; j++)//���� �迭�� ���� ��(��Ʈ���� ���� ȭ�� �����δ� ���� ��)
			{
				if (board_[j][i] == EMPTY) // �� �ڸ��� �ϳ��� ������ �� ���ִ� �� �ƴ�
				{
					full = false; // false�� ���� ������ ����
					break; //Ż��
				}
			}
			if (full) // Ư�� ���� �� ���ִٸ�
			{
				count++;
				for (y = i + 1; y < 20; y++)
				{
					for (x = 0; x < 10; x++)
					{
						tempX = Point::GetScrPosFromCurPos(Point(x, 0)).GetX() + reference_pos.GetX();
						tempY = Point::GetScrPosFromCurPos(Point(0, y)).GetY() + reference_pos.GetY();
						Point::GotoXY(tempX, tempY);//���� �ǿ��� �� ���� ������ �ϴϱ� ��ǥ�� �ű� ������
						cout << "��";//�����
						board_[x][y - 1] = EMPTY;
						board_[x][y - 1] = board_[x][y]; // ���� ������ �ϴ� ���� �� ���� ��������
					}
					for (x = 0; x < 10; x++) //ȭ�鿡 ǥ���ϱ�
					{
						if (board_[x][y - 1] != EMPTY) //�ش� �迭�� ����ִ��� ������� �������� ���� ȭ�鿡 ǥ��
						{
							tempX = Point::GetScrPosFromCurPos(Point(x, 0)).GetX() + reference_pos.GetX();
							tempY = Point::GetScrPosFromCurPos(Point(0, y)).GetY() + reference_pos.GetY();
							Point::GotoXY(tempX, tempY);
							SetColor(board_[x][y]);
							cout << "��";
						}
						else
						{
							tempX = Point::GetScrPosFromCurPos(Point(x, 0)).GetX() + reference_pos.GetX();
							tempY = Point::GetScrPosFromCurPos(Point(0, y)).GetY() + reference_pos.GetY();
							Point::GotoXY(tempX, tempY);
							cout << "��";
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
				if (board_[x][y] != EMPTY) //�ش� �迭�� ����ִ��� ������� �������� ���� ȭ�鿡 ǥ��
				{
					tempX = Point::GetScrPosFromCurPos(Point(x, 0)).GetX() + reference_pos.GetX();
					tempY = Point::GetScrPosFromCurPos(Point(0, y)).GetY() + reference_pos.GetY();
					Point::GotoXY(tempX, tempY);
					SetColor(board_[x][y]);
					cout << "��";
				}
				else
				{
					tempX = Point::GetScrPosFromCurPos(Point(x, 0)).GetX() + reference_pos.GetX();
					tempY = Point::GetScrPosFromCurPos(Point(0, y)).GetY() + reference_pos.GetY();
					Point::GotoXY(tempX, tempY);
					cout << "��";
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
			if (board_[x][y] != EMPTY) //�ش� �迭�� ����ִ��� ������� �������� ���� ȭ�鿡 ǥ��
			{
				tempX = Point::GetScrPosFromCurPos(Point(x, 0)).GetX() + reference_pos.GetX();
				tempY = Point::GetScrPosFromCurPos(Point(0, y)).GetY() + reference_pos.GetY();
				Point::GotoXY(tempX, tempY);
				SetColor(board_[x][y]);
				cout << "��";
			}
			else
			{
				tempX = Point::GetScrPosFromCurPos(Point(x, 0)).GetX() + reference_pos.GetX();
				tempY = Point::GetScrPosFromCurPos(Point(0, y)).GetY() + reference_pos.GetY();
				Point::GotoXY(tempX, tempY);
				cout << "��";
			}
		}
}