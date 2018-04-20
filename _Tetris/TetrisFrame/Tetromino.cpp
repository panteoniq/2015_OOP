#include "Tetromino.h"
#include <iostream>
#include <windows.h>
using namespace std;

Point g_tetromino_pattern[7][4][4] =
{
	{ { Point(0, 1), Point(0, 0), Point(0, -1), Point(0, -2) }, { Point(-2, 0), Point(-1, 0), Point(0, 0), Point(1, 0) },
	{ Point(0, 1), Point(0, 0), Point(0, -1), Point(0, -2) }, { Point(-2, 0), Point(-1, 0), Point(0, 0), Point(1, 0) } },  // I
	{ { Point(0, 1), Point(0, 0), Point(0, -1), Point(-1, -1) }, { Point(-1, 0), Point(0, 0), Point(1, 0), Point(-1, 1) },
	{ Point(0, 1), Point(0, 0), Point(1, 1), Point(0, -1) }, { Point(-1, 0), Point(0, 0), Point(1, 0), Point(1, -1) } },  // J
	{ { Point(-1, 1), Point(0, 1), Point(0, 0), Point(0, -1) }, { Point(1, 1), Point(-1, 0), Point(0, 0), Point(1, 0) },
	{ Point(0, 1), Point(0, 0), Point(0, -1), Point(1, -1) }, { Point(-1, 0), Point(0, 0), Point(1, 0), Point(-1, -1) } }, // L
	{ { Point(-1, 0), Point(0, 0), Point(-1, -1), Point(0, -1) }, { Point(-1, 0), Point(0, 0), Point(-1, -1), Point(0, -1) },
	{ Point(-1, 0), Point(0, 0), Point(-1, -1), Point(0, -1) }, { Point(-1, 0), Point(0, 0), Point(-1, -1), Point(0, -1) } },  // O
	{ { Point(0, 1), Point(0, 0), Point(1, 0), Point(1, -1) }, { Point(0, 0), Point(1, 0), Point(-1, -1), Point(0, -1) },
	{ Point(0, 1), Point(0, 0), Point(1, 0), Point(1, -1) }, { Point(0, 0), Point(1, 0), Point(-1, -1), Point(0, -1) } },  // S
	{ { Point(0, 1), Point(-1, 0), Point(0, 0), Point(0, -1) }, { Point(0, 1), Point(-1, 0), Point(0, 0), Point(1, 0) },
	{ Point(0, 1), Point(0, 0), Point(1, 0), Point(0, -1) }, { Point(-1, 0), Point(0, 0), Point(1, 0), Point(0, -1) } },  // T
	{ { Point(1, 1), Point(0, 0), Point(1, 0), Point(0, -1) }, { Point(-1, 0), Point(0, 0), Point(0, -1), Point(1, -1) },
	{ Point(1, 1), Point(0, 0), Point(1, 0), Point(0, -1) }, { Point(-1, 0), Point(0, 0), Point(0, -1), Point(1, -1) } }  // Z
};

Tetromino::Tetromino(Board *board, TETROMINO_TYPE type) : board_(board), type_(type)
{
	rotate_ = rand() % 4;
}

GhostTetromino::GhostTetromino(Board *board, TETROMINO_TYPE type) : Tetromino(board, type)
{
	rotate_ = rand() % 4;
}

void Tetromino::Draw(Point reference_pos) // 그리기 함수 만들어야 함
{
	for (int i = 0; i < 4; i++)
	{
		int tempX, tempY;
		tempX = Point::GetScrPosFromCurPos(center_pos_ + g_tetromino_pattern[type_][rotate_][i]).GetX() + reference_pos.GetX();
		tempY = Point::GetScrPosFromCurPos(center_pos_ + g_tetromino_pattern[type_][rotate_][i]).GetY() + reference_pos.GetY();

		Point::GotoXY(Point(tempX, tempY));
		SetColor(type_ + 1);
		cout << "■";
		SetColor(7);
	}
}

void GhostTetromino::Draw(Point reference_pos)
{
	for (int i = 0; i < 4; i++)
	{
		int tempX, tempY;
		tempX = Point::GetScrPosFromCurPos(center_pos_ + g_tetromino_pattern[type_][rotate_][i]).GetX() + reference_pos.GetX();
		tempY = Point::GetScrPosFromCurPos(center_pos_ + g_tetromino_pattern[type_][rotate_][i]).GetY() + reference_pos.GetY();

		Point::GotoXY(Point(tempX, tempY));
		SetColor(14);
		cout << "▣";
		SetColor(7);
	}
}


void Tetromino::Erase(Point reference_pos) // 지우는 함수도 실행해야 함
{
	for (int i = 0; i < 4; i++)
	{
		int tempX, tempY;
		tempX = Point::GetScrPosFromCurPos(center_pos_ + g_tetromino_pattern[type_][rotate_][i]).GetX() + reference_pos.GetX();
		tempY = Point::GetScrPosFromCurPos(center_pos_ + g_tetromino_pattern[type_][rotate_][i]).GetY() + reference_pos.GetY();

		Point::GotoXY(Point(tempX, tempY));
		cout << "　";
	}
}

void GhostTetromino::Erase(Point reference_pos)
{
	for (int i = 0; i < 4; i++)
	{
		int tempX, tempY;
		tempX = Point::GetScrPosFromCurPos(center_pos_ + g_tetromino_pattern[type_][rotate_][i]).GetX() + reference_pos.GetX();
		tempY = Point::GetScrPosFromCurPos(center_pos_ + g_tetromino_pattern[type_][rotate_][i]).GetY() + reference_pos.GetY();

		Point::GotoXY(Point(tempX, tempY));
		cout << "　";
	}
}

void Tetromino::SetCenterPos(Point pos)
{
	center_pos_ = pos;
}

bool Tetromino::MoveDown(Point reference_pos)
{ //자리 확인하고 내려서 다시 그리기
	center_pos_.SetY(center_pos_.GetY() - 1);

	if (CheckValidPos())
	{
		center_pos_.SetY(center_pos_.GetY() + 1);
		Erase(reference_pos);
		center_pos_.SetY(center_pos_.GetY() - 1);
		if (this->CheckGhostValue())
			board_->ReDraw(reference_pos);
		Draw(reference_pos);
		return true;
	}
	else
	{
		center_pos_.SetY(center_pos_.GetY() + 1);
		return false;
	}
}

void Tetromino::MoveRight(Point reference_pos)
{
	center_pos_.SetX(center_pos_.GetX() + 1);

	if (CheckValidPos())
	{
		center_pos_.SetX(center_pos_.GetX() - 1);
		if (!(this->CheckGhostValue()))
			EraseShadowTetromino(reference_pos);
		Erase(reference_pos);
		center_pos_.SetX(center_pos_.GetX() + 1);
		if (!(this->CheckGhostValue()))
			DrawShadowTetromino(reference_pos);
		if (this->CheckGhostValue())
			board_->ReDraw(reference_pos);
		Draw(reference_pos);
	}

	else
	{
		center_pos_.SetX(center_pos_.GetX() - 1);
	}
}

void Tetromino::MoveLeft(Point reference_pos)
{
	center_pos_.SetX(center_pos_.GetX() - 1);

	if (CheckValidPos())
	{
		center_pos_.SetX(center_pos_.GetX() + 1);
		if (!(this->CheckGhostValue()))
			EraseShadowTetromino(reference_pos);
		Erase(reference_pos);
		center_pos_.SetX(center_pos_.GetX() - 1);
		if (!(this->CheckGhostValue()))
			DrawShadowTetromino(reference_pos);
		if (this->CheckGhostValue())
			board_->ReDraw(reference_pos);
		Draw(reference_pos);
	}
	else
	{
		center_pos_.SetX(center_pos_.GetX() + 1);
	}

}

void Tetromino::Rotate(Point reference_pos)
{
	rotate_++;
	if (rotate_ == 4)
		rotate_ = 0;
	if (CheckValidPos())
	{
		rotate_--;
		if (rotate_ == -1)
			rotate_ = 3;
		if (!(this->CheckGhostValue()))
			EraseShadowTetromino(reference_pos);
		Erase(reference_pos);

		rotate_++;
		if (rotate_ == 4)
			rotate_ = 0;

		if (!(this->CheckGhostValue()))
			DrawShadowTetromino(reference_pos);
		if (this->CheckGhostValue())
			board_->ReDraw(reference_pos);
		Draw(reference_pos);
	}
	else
	{
		rotate_--;
		if (rotate_ == -1)
			rotate_ = 3;
	}
}

void Tetromino::GoBottom(Point reference_pos)
{
	while (MoveDown(reference_pos))
	{
		Sleep(10); //Sleep(100);
	}
}

void Tetromino::MoveOnestepDown(Point reference_pos) //새로 구현한 함수죠~
{
	if (CheckValidPos())
		MoveDown(reference_pos);
}
// 한 칸 아래로 이동, 유효한 위치면 다시 그림. 추가적 기능

void Tetromino::DrawShadowTetromino(Point reference_pos) // 그림자 기능
{
	Point temp_pos = Point(center_pos_);
	while (CheckShadowValidPos(temp_pos))
		if (CheckShadowValidPos(temp_pos))
			temp_pos.SetY(temp_pos.GetY() - 1);
	temp_pos.SetY(temp_pos.GetY() + 1);
	int tempX, tempY;
	for (int i = 0; i < 4; i++)
	{
		tempX = Point::GetScrPosFromCurPos(temp_pos + g_tetromino_pattern[type_][rotate_][i]).GetX() + reference_pos.GetX();
		tempY = Point::GetScrPosFromCurPos(temp_pos + g_tetromino_pattern[type_][rotate_][i]).GetY() + reference_pos.GetY();
		Point::GotoXY(tempX, tempY);
		cout << "□";
	}

}

void Tetromino::EraseShadowTetromino(Point reference_pos)
{
	Point temp_pos = Point(center_pos_);
	while (CheckShadowValidPos(temp_pos))
		if (CheckShadowValidPos(temp_pos))
			temp_pos.SetY(temp_pos.GetY() - 1);
	temp_pos.SetY(temp_pos.GetY() + 1);
	int tempX, tempY;
	for (int i = 0; i < 4; i++)
	{
		tempX = Point::GetScrPosFromCurPos(temp_pos + g_tetromino_pattern[type_][rotate_][i]).GetX() + reference_pos.GetX();
		tempY = Point::GetScrPosFromCurPos(temp_pos + g_tetromino_pattern[type_][rotate_][i]).GetY() + reference_pos.GetY();
		Point::GotoXY(tempX, tempY);
		cout << "　";
	}
}

bool Tetromino::CheckValidPos(void)
{
	for (int i = 0; i < 4; i++)
	{
		Point cur_pos(center_pos_.GetX() + g_tetromino_pattern[type_][rotate_][i].GetX(), center_pos_.GetY() + g_tetromino_pattern[type_][rotate_][i].GetY());

		if (cur_pos.GetX() < 0 || cur_pos.GetX() > 9)
			return false;
		if (cur_pos.GetY() < 0)
			return false;
		if (cur_pos.GetY() <= 19 && board_->GetState(cur_pos) != EMPTY)
			return false;
	}

	return true;
}

bool GhostTetromino::CheckValidPos(void)
{
	for (int i = 0; i < 4; i++)
	{
		Point cur_pos(center_pos_.GetX() + g_tetromino_pattern[type_][rotate_][i].GetX(), center_pos_.GetY() + g_tetromino_pattern[type_][rotate_][i].GetY());

		if (cur_pos.GetX() < 0 || cur_pos.GetX() > 9)
			return false;
		if (cur_pos.GetY() < 0)
			return false;
	}

	return true;
}

bool Tetromino::CheckShadowValidPos(Point temp_pos)
{
	for (int i = 0; i < 4; i++)
	{
		Point cur_pos(temp_pos.GetX() + g_tetromino_pattern[type_][rotate_][i].GetX(), temp_pos.GetY() + g_tetromino_pattern[type_][rotate_][i].GetY());

		if (cur_pos.GetX() < 0 || cur_pos.GetX() > 9)
			return false;
		if (cur_pos.GetY() < 0)
			return false;
		if (cur_pos.GetY() <= 19 && board_->GetState(cur_pos) != EMPTY)
			return false;
	}

	return true;
}

void Tetromino::MarkCurTetrominoPos(Point reference_pos)
{
	int i;
	for (i = 0; i < 4; i++)
	{
		Point MarkPos(center_pos_.GetX() + g_tetromino_pattern[type_][rotate_][i].GetX(), center_pos_.GetY() + g_tetromino_pattern[type_][rotate_][i].GetY());
		board_->SetState(MarkPos, (type_ + 1));
	}// board_ 2차원 배열에서 테트로미노의 4개의 각 점 위치를 mark하기

}

void GhostTetromino::MarkCurTetrominoPos(Point reference_pos)
{
	int i;
	for (i = 0; i < 4; i++)
	{
		Point MarkPos(center_pos_.GetX() + g_tetromino_pattern[type_][rotate_][i].GetX(), center_pos_.GetY() + g_tetromino_pattern[type_][rotate_][i].GetY());
		board_->SetState(MarkPos, 14);
	}// board_ 2차원 배열에서 테트로미노의 4개의 각 점 위치를 mark하기
}

bool Tetromino::CheckEndCondition(void)
{
	if (board_->GetState(g_cur_tetromino_init_pos) != EMPTY) // 판에서 끝 자리에 테트로미노가 위치하고 있다면
	{
		Point::GotoXY(Pause_Pos);
		cout << "　　　　　　　　　　　　　"; //일시정지 자리 지운 다음에
		return true;//끝내야지?
	}
	return false;//아니라면 계속하고

}
