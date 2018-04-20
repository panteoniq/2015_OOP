#ifndef JHHWANG_SCORE_H
#define JHHWANG_SCORE_H

#include "Point.h"

class Score
{
public:
	Score();    // score_ 값을 0으로 초기화
	void UpdateScore(Point reference_pos, int increment);   // Increment 만큼 점수를 더해 줌
	void Print(Point reference_pos);                        // 점수 출력 위치에 점수 출력
	void Erase(Point reference_pos);//화면상에 표시된 추가점을 지워주는 함수
	int CurLevel(void); //현재 스코어에 비교해서 그에 합당한 레벨을 출력
	int ReturnScore(void) { return score_; } //게임이 끝난 후 최종 스코어를 반환하는 함수;

private :
    int score_;
	int level_;
    Point score_pos_;
	Point level_pos_;
	Point plus_pos_;
};

#endif