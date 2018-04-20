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
	srand(time(NULL));		// ���� �߻��� �ʱ�ȭ
	int input;

	cout << ">>>>>>>> Testris <<<<<<<<" << endl;
	cout << ">> 1�ο�, 2�ο� ���� : ";
	cin >> input;

	system("cls");
	PlaySound("CarolinaSummer.wav", NULL, SND_ASYNC | SND_LOOP);
	if (input == 1)         // 1�ο� 
	{
		Tetris tetris(Point(0, 0), KEY_ESC, 'd', 'a', 'w', 's', 'g');
		int finalscore=tetris.Run();
		system("cls");
		PlaySound(0, 0, 0);
		ofstream fout;
		fout.open("Result.txt", ios_base::out | ios_base::app);
		char resultname[20] = "NULL";
		Point::GotoXY(20, 10);
		cout << "���� ������ " << finalscore << "���Դϴ�!" ;
		Point::GotoXY(20, 11);
		cout << "����� �̸��� �Է��Ͻʽÿ� : ";
		cin >> resultname;
		fout << setw(20) << right << resultname << setw(10) << right << finalscore << "Points" << endl;
		fout << endl;
		fout.close();
	}
	else                    // 2�ο�
    {
		system("mode con:cols=90 lines=30");
		char p1name[20] = "NULL"; //1p�� �̸�
		char p2name[20] = "NULL"; //2p�� �̸�
		int p1score; //1p�� ����
		int p2score; //2p�� ����
		Tetris tetris1(Point(0, 0), KEY_ESC, 'd', 'a', 'w', 's','g');
		Tetris tetris2(Point(38, 0), KEY_ESC, KEY_RIGHT,KEY_LEFT,KEY_UP,KEY_DOWN,KEY_SPACE);

		while (tetris1.IsRunning() || tetris2.IsRunning()) 
        {
			bool key1 = false;
			bool key2 = false;

			if (kbhit())    // Ű �Է��� �ִٸ� 
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
		p1score = tetris1.ReturnScore(); //���� ���޹���
		p2score = tetris2.ReturnScore();
		system("cls;"); //ȭ���� �� �����
		PlaySound(0, 0, 0);
		Point::GotoXY(20, 10);
		cout << "1p�� ���� ������ " << p1score << "���Դϴ�!";
		Point::GotoXY(20, 11);
		cout << "2p�� ���� ������ " << p2score << "���Դϴ�!";
		Point::GotoXY(20, 12);
		cout << "1p�� ����� �̸��� �Է��� �ּ��� : ";
		cin >> p1name;
		Point::GotoXY(20, 13);
		cout << "2p�� ����� �̸��� �Է��� �ּ��� : ";
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