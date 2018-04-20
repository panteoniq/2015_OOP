#include "Tetris.h"
#include "Controller.h"
#include "Tetromino.h"
//#include "GhostTetromino.h"
#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <iomanip>
using namespace std;


Tetris::Tetris(Point reference_pos, int key_esc, int key_right, int key_left, int key_rotate, int key_down, int key_space) : reference_pos_(reference_pos) 
{
	running_ = true;
	cur_tetromino_ = NULL;
	next_tetromino_ = NULL;
	start_time_ = clock();
	falling_speed_ = 0.8;

	SetCursorInvisible();

	controller_.SetController(key_esc, key_right, key_left, key_rotate, key_down, key_space); 
	DrawBoard();
	GenerateNextTetromino(); // ���� ��Ʈ�ι̳� �����
	GetCurTetrominoFromNext(); // �װ� ���� ��Ʈ�ι̳�� �ű� ������
	GenerateNextTetromino(); // ���� ��Ʈ�ι̳� ���� ����
	cur_tetromino_->Draw(reference_pos_); 
	cur_tetromino_->DrawShadowTetromino(reference_pos);
	next_tetromino_->Draw(reference_pos_);
	score_.Print(reference_pos_);
	Point::GotoXY(Pause_Pos);
	cout << "�Ͻ� ����...(pause) : OFF  ";
}

int Tetris::pause_count_ = 0; //static ���� �ʱ�ȭ

void Tetris::DrawBoard(void) // �� �׸��� �Ϸ�!!!!!!!!!!!!!!!!!!!!!!!!! ������ 2�� �׸�
{
	int i;
	Point::GotoXY(reference_pos_);
	cout << "�ˢˢˢˢˢˢˢˢˢˢˢˢˢˢˢˢˢˢ�";
	for (i = 0; i < 6; i++)
	{
		Point::GotoXY(reference_pos_ + Point(0, i + 1));
		cout << "��                    ��            ��";
	}
	Point::GotoXY(reference_pos_ + Point(0, 7));
	cout << "��                    �ˢˢˢˢˢˢˢ�";
	for (i = 0; i < 3; i++)
	{
		Point::GotoXY(reference_pos_ + Point(0, 8 + i));
		cout << "��                    ��            ��";
	}
	Point::GotoXY(reference_pos_ + Point(0, 11));
	cout << "��                    �ˢˢˢˢˢˢˢ�";
	Point::GotoXY(reference_pos_ + Point(0, 12));
	cout << "��                    ��            ��";
	Point::GotoXY(reference_pos_ + Point(0, 13));
	if (reference_pos_.GetX()==0)
		cout << "��                    �� d  ������  ��";
	else
		cout << "��                    �� �� ������  ��";

	Point::GotoXY(reference_pos_ + Point(0, 14));
	cout << "��                    ��            ��";
	Point::GotoXY(reference_pos_ + Point(0, 15));
	if (reference_pos_.GetX() == 0)
		cout << "��                    �� a  ����    ��";
	else
		cout << "��                    �� �� ����    ��";
	Point::GotoXY(reference_pos_ + Point(0, 16));
	cout << "��                    ��            ��";
	Point::GotoXY(reference_pos_ + Point(0, 17));
	if (reference_pos_.GetX() == 0)
		cout << "��                    �� w  ����    ��";
	else
		cout << "��                    �� �� ����    ��";
	Point::GotoXY(reference_pos_ + Point(0, 18));
	cout << "��                    ��            ��";
	Point::GotoXY(reference_pos_ + Point(0, 19));
	if (reference_pos_.GetX() == 0)
		cout << "��                    �� g  ����    ��";
	else
		cout << "��                    �� Space ���� ��";
	Point::GotoXY(reference_pos_ + Point(0, 20));
	cout << "��                    ��            ��";
	Point::GotoXY(reference_pos_ + Point(0, 21));
	cout << "�ˢˢˢˢˢˢˢˢˢˢˢˢˢˢˢˢˢˢ�";


}

int Tetris::Run(void) //1
{
	while (running_)
	{
		RunStep();
	}
	return score_.ReturnScore();
}

void Tetris::RunStep(void) //2
{
	if (kbhit())
	{
		pause_count_ = 0;
		int key = Controller::GetKey(); //3-1
		KeyHandler(key);
	}
	else
	{
		NormalStep(); //3-2
	}
}

bool Tetris::KeyHandler(int key) //3-1
{
	if (key == controller_.Getkey_esc())
	{
		running_ = false;
		return true;
	}
	else if (key == controller_.Getkey_right())
	{
		cur_tetromino_->MoveRight(reference_pos_);
		return true;
	}
	else if (key == controller_.Getkey_left())
	{
		cur_tetromino_->MoveLeft(reference_pos_);
		return true;
	}
	else if (key == controller_.Getkey_rotate())
	{
		cur_tetromino_->Rotate(reference_pos_);
		return true;
	}
	else if (key == controller_.Getkey_down()) 
	{
		cur_tetromino_->MoveDown(reference_pos_);
		start_time_ = clock();
		return true;
	}
	else if (key == controller_.Getkey_space())
	{
		cur_tetromino_->GoBottom(reference_pos_);
		cur_tetromino_->EraseShadowTetromino(reference_pos_);
		PrepareNextStep();
		return true;
	}
	else if (key == 80 || key == 112)
	{
		if (pause_count_ == 0)
		{
			pause = false;
			while (pause != true)
			{
				Sleep(1);
				Point::GotoXY(Pause_Pos);
				cout << "�Ͻ� ����...(pause) : ON  ";
				key = getch();
				if (key == 80 || key == 112)
				{
					pause = true;
					Point::GotoXY(Pause_Pos);
					cout << "�Ͻ� ����...(pause) : OFF";
				}
			}
			pause_count_++;
		}
		else
			pause_count_ = 0;
	}

	return false;
}

void Tetris::NormalStep(void) //3-2
{

	if (GetDiffTime() >= falling_speed_)
	{
		if (cur_tetromino_->MoveDown(reference_pos_))
		{
			start_time_ = clock();
		}
		else
		{	// ������ ��������. ��ó��
			PrepareNextStep();
		}
	}
}

void Tetris::PrepareNextStep(void)
{
	cur_tetromino_->MarkCurTetrominoPos(reference_pos_);
	//���� �ٽ� �׷��ִ� �Լ�
	score_.Erase(reference_pos_); // �ϴ� ���ھ �����ְ�(�� �� ��������ϱ�)
	int EraseLineCount = board_.CheckLineFull(reference_pos_);
	if (EraseLineCount > 0) //���� �� �������ٸ�
		score_.UpdateScore(reference_pos_, EraseLineCount); //���ھ� �ٽ� ǥ��
	board_.ReDraw(reference_pos_);
	Level = score_.CurLevel();
	falling_speed_ = 0.8 - (Level*0.1);

	if (cur_tetromino_->CheckEndCondition())
	{
		running_ = false;
		Point::GotoXY(reference_pos_ + Point(10, 10));
		cout << "The game is over !!!";
		getch();
	}
	else
	{
		next_tetromino_->Tetromino::Erase(reference_pos_);
		GetCurTetrominoFromNext();
		GenerateNextTetromino();
		cur_tetromino_->Draw(reference_pos_);
		if (!cur_tetromino_->CheckGhostValue())
			cur_tetromino_->DrawShadowTetromino(reference_pos_);
		next_tetromino_->Draw(reference_pos_);
	}
	start_time_ = clock();
}

void Tetris::GenerateNextTetromino(void)
{
	TETROMINO_TYPE tetromino_type = (TETROMINO_TYPE)(rand() % TETROMINO_TYPE_COUNT);
	if (rand() % 10 == 0)           // GhostTetromino
	{
		next_tetromino_ = new GhostTetromino(&board_, tetromino_type);
		next_tetromino_->SetCenterPos(g_next_tetromino_init_pos);
		next_tetromino_->SetGhostValue();
	}
	else
	{
		next_tetromino_ = new Tetromino(&board_, tetromino_type);
		next_tetromino_->SetCenterPos(g_next_tetromino_init_pos); 
		next_tetromino_->ReSetGhostValue();
	}
}

void Tetris::GetCurTetrominoFromNext(void)
{
	int x, y;
	x = g_cur_tetromino_init_pos.GetX();
	y = g_cur_tetromino_init_pos.GetY();

	Point cur_point(x, y);
	// cur_tetromino_�� ���� NULL�� �ƴ϶�� delete
	if (cur_tetromino_ != NULL)
		delete cur_tetromino_;
	// next_tetromino_�� ��Ʈ�ι̳븦 cur_tetromino_�� ������
	cur_tetromino_ = next_tetromino_;
	// cur_tetromino_�� ���� ��ġ setting
	cur_tetromino_->SetCenterPos(cur_point);
	//g_next_tetromino_init_pos ���� ��ȯ�ؼ� �ڸ��̵���Ų �Ŀ� empty�� �ٲٸ� �� �� ���⵵ �ϰ�(��Ʈ�ι̳� ���� ��ó��)
}

double Tetris::GetDiffTime(void)
{
	clock_t CurTime;
	CurTime = clock();	//time(&CurTime);
	return ((double)(CurTime - start_time_) / CLOCKS_PER_SEC);
}

// Utility
void Tetris::SetCursorInvisible(void)	// ȭ�� Ŀ���� �� ���̰� ��
{
	CONSOLE_CURSOR_INFO ci = { 10, FALSE };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
}