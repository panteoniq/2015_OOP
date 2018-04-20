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
	GenerateNextTetromino(); // 다음 테트로미노 만들고
	GetCurTetrominoFromNext(); // 그걸 현재 테트로미노로 옮긴 다음에
	GenerateNextTetromino(); // 다음 테트로미노 새로 생성
	cur_tetromino_->Draw(reference_pos_); 
	cur_tetromino_->DrawShadowTetromino(reference_pos);
	next_tetromino_->Draw(reference_pos_);
	score_.Print(reference_pos_);
	Point::GotoXY(Pause_Pos);
	cout << "일시 정지...(pause) : OFF  ";
}

int Tetris::pause_count_ = 0; //static 변수 초기화

void Tetris::DrawBoard(void) // 판 그리기 완료!!!!!!!!!!!!!!!!!!!!!!!!! 과정의 2번 항목
{
	int i;
	Point::GotoXY(reference_pos_);
	cout << "▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦";
	for (i = 0; i < 6; i++)
	{
		Point::GotoXY(reference_pos_ + Point(0, i + 1));
		cout << "▦                    ▦            ▦";
	}
	Point::GotoXY(reference_pos_ + Point(0, 7));
	cout << "▦                    ▦▦▦▦▦▦▦▦";
	for (i = 0; i < 3; i++)
	{
		Point::GotoXY(reference_pos_ + Point(0, 8 + i));
		cout << "▦                    ▦            ▦";
	}
	Point::GotoXY(reference_pos_ + Point(0, 11));
	cout << "▦                    ▦▦▦▦▦▦▦▦";
	Point::GotoXY(reference_pos_ + Point(0, 12));
	cout << "▦                    ▦            ▦";
	Point::GotoXY(reference_pos_ + Point(0, 13));
	if (reference_pos_.GetX()==0)
		cout << "▦                    ▦ d  오른쪽  ▦";
	else
		cout << "▦                    ▦ → 오른쪽  ▦";

	Point::GotoXY(reference_pos_ + Point(0, 14));
	cout << "▦                    ▦            ▦";
	Point::GotoXY(reference_pos_ + Point(0, 15));
	if (reference_pos_.GetX() == 0)
		cout << "▦                    ▦ a  왼쪽    ▦";
	else
		cout << "▦                    ▦ ← 왼쪽    ▦";
	Point::GotoXY(reference_pos_ + Point(0, 16));
	cout << "▦                    ▦            ▦";
	Point::GotoXY(reference_pos_ + Point(0, 17));
	if (reference_pos_.GetX() == 0)
		cout << "▦                    ▦ w  변경    ▦";
	else
		cout << "▦                    ▦ ↑ 변경    ▦";
	Point::GotoXY(reference_pos_ + Point(0, 18));
	cout << "▦                    ▦            ▦";
	Point::GotoXY(reference_pos_ + Point(0, 19));
	if (reference_pos_.GetX() == 0)
		cout << "▦                    ▦ g  낙하    ▦";
	else
		cout << "▦                    ▦ Space 낙하 ▦";
	Point::GotoXY(reference_pos_ + Point(0, 20));
	cout << "▦                    ▦            ▦";
	Point::GotoXY(reference_pos_ + Point(0, 21));
	cout << "▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦";


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
				cout << "일시 정지...(pause) : ON  ";
				key = getch();
				if (key == 80 || key == 112)
				{
					pause = true;
					Point::GotoXY(Pause_Pos);
					cout << "일시 정지...(pause) : OFF";
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
		{	// 끝까지 내려왔음. 후처리
			PrepareNextStep();
		}
	}
}

void Tetris::PrepareNextStep(void)
{
	cur_tetromino_->MarkCurTetrominoPos(reference_pos_);
	//새로 다시 그려주는 함수
	score_.Erase(reference_pos_); // 일단 스코어를 지워주고(한 번 출력했으니까)
	int EraseLineCount = board_.CheckLineFull(reference_pos_);
	if (EraseLineCount > 0) //만약 또 지워졌다면
		score_.UpdateScore(reference_pos_, EraseLineCount); //스코어 다시 표시
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
	// cur_tetromino_의 값이 NULL이 아니라면 delete
	if (cur_tetromino_ != NULL)
		delete cur_tetromino_;
	// next_tetromino_의 테트로미노를 cur_tetromino_로 가져옴
	cur_tetromino_ = next_tetromino_;
	// cur_tetromino_의 시작 위치 setting
	cur_tetromino_->SetCenterPos(cur_point);
	//g_next_tetromino_init_pos 갖고 변환해서 자리이동시킨 후에 empty로 바꾸면 될 거 같기도 하고(테트로미노 찍을 때처럼)
}

double Tetris::GetDiffTime(void)
{
	clock_t CurTime;
	CurTime = clock();	//time(&CurTime);
	return ((double)(CurTime - start_time_) / CLOCKS_PER_SEC);
}

// Utility
void Tetris::SetCursorInvisible(void)	// 화면 커서를 안 보이게 함
{
	CONSOLE_CURSOR_INFO ci = { 10, FALSE };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
}