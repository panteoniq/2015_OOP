#ifndef JHHWANG_SCORE_H
#define JHHWANG_SCORE_H

#include "Point.h"

class Score
{
public:
	Score();    // score_ ���� 0���� �ʱ�ȭ
	void UpdateScore(Point reference_pos, int increment);   // Increment ��ŭ ������ ���� ��
	void Print(Point reference_pos);                        // ���� ��� ��ġ�� ���� ���
	void Erase(Point reference_pos);//ȭ��� ǥ�õ� �߰����� �����ִ� �Լ�
	int CurLevel(void); //���� ���ھ ���ؼ� �׿� �մ��� ������ ���
	int ReturnScore(void) { return score_; } //������ ���� �� ���� ���ھ ��ȯ�ϴ� �Լ�;

private :
    int score_;
	int level_;
    Point score_pos_;
	Point level_pos_;
	Point plus_pos_;
};

#endif