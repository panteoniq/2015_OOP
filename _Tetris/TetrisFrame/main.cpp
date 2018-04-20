#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <fstream>
#include <iomanip>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm")
using namespace std;
#include "Tetris.h"

int main()
{
	srand(time(NULL));		// 난수 발생기 초기화
	int input;

	cout << ">>>>>>>> Testris <<<<<<<<" << endl;
	cout << ">> 1인용, 2인용 선택 : ";
	cin >> input;

	system("cls");
	PlaySound("CarolinaSummer.wav", NULL, SND_ASYNC | SND_LOOP);
	if (input == 1)         // 1인용 
	{
		Tetris tetris(Point(0, 0), KEY_ESC, 'd', 'a', 'w', 's', 'g');
		int finalscore=tetris.Run();
		system("cls");
		PlaySound(0, 0, 0);
		ofstream fout;
		fout.open("Result.txt", ios_base::out | ios_base::app);
		char resultname[20] = "NULL";
		Point::GotoXY(20, 10);
		cout << "최종 점수는 " << finalscore << "점입니다!" ;
		Point::GotoXY(20, 11);
		cout << "저장될 이름을 입력하십시오 : ";
		cin >> resultname;
		fout << setw(20) << right << resultname << setw(10) << right << finalscore << "Points" << endl;
		fout << endl;
		fout.close();
	}
	else                    // 2인용
    {
		system("mode con:cols=90 lines=30");
		char p1name[20] = "NULL"; //1p의 이름
		char p2name[20] = "NULL"; //2p의 이름
		int p1score; //1p의 점수
		int p2score; //2p의 점수
		Tetris tetris1(Point(0, 0), KEY_ESC, 'd', 'a', 'w', 's','g');
		Tetris tetris2(Point(38, 0), KEY_ESC, KEY_RIGHT,KEY_LEFT,KEY_UP,KEY_DOWN,KEY_SPACE);

		while (tetris1.IsRunning() || tetris2.IsRunning()) 
        {
			bool key1 = false;
			bool key2 = false;

			if (kbhit())    // 키 입력이 있다면 
            {
				int key = Controller::GetKey();					
				if (tetris1.IsRunning())
					key1 = tetris1.KeyHandler(key);
				if (tetris2.IsRunning() && !key1)
					key2 = tetris2.KeyHandler(key);				
			}

			if (tetris1.IsRunning() && !key1)
				tetris1.NormalStep();
			if (tetris2.IsRunning() && !key2)
				tetris2.NormalStep();
		}
		p1score = tetris1.ReturnScore(); //점수 전달받음
		p2score = tetris2.ReturnScore();
		system("cls;"); //화면을 다 지우고
		PlaySound(0, 0, 0);
		Point::GotoXY(20, 10);
		cout << "1p의 최종 점수는 " << p1score << "점입니다!";
		Point::GotoXY(20, 11);
		cout << "2p의 최종 점수는 " << p2score << "점입니다!";
		Point::GotoXY(20, 12);
		cout << "1p로 저장될 이름을 입력해 주세요 : ";
		cin >> p1name;
		Point::GotoXY(20, 13);
		cout << "2p로 저장될 이름을 입력해 주세요 : ";
		cin >> p2name;
		ofstream fout;
		fout.open("Result2player.txt", ios_base::out | ios_base::app);
		fout << setw(20) << right << p1name << setw(10) << right << p1score << "Points";
		fout << setw(20) << right << p2name << setw(10) << right << p2score << "Points" << endl;
		fout << endl;
		fout.close();
	}

    return 0;
}

/*
int main()
{
	srand(time(NULL));
	Tetris tetris;
	tetris.Run();

    return 0;
}
*/