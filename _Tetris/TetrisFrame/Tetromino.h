#ifndef JHHWANG_TETROMINO_H
#define JHHWANG_TETROMINO_H
#include "Point.h"
#include "Board.h"

#define TETROMINO_TYPE_COUNT 7
#define ROTATE_COUNT 4
//const Point g_next_tetromino_init_pos_2p(29, 3);
const Point g_next_tetromino_init_pos(13, 17); //원래는 13, 17이었음
const Point g_cur_tetromino_init_pos(4, 18); // 원래는 4, 20이었음
const Point Pause_Pos(10, 23);

enum TETROMINO_TYPE { TETROMINO_I, TETROMINO_J, TETROMINO_L, TETROMINO_O, TETROMINO_S, TETROMINO_T, TETROMINO_Z };

class Tetromino
{
public:
	Tetromino(Board *board, TETROMINO_TYPE type);
	virtual void Draw(Point reference_pos);			        // 현재 화면 중심 위치를 기준으로 그리기
	virtual void Erase(Point reference_pos);		        // 현재 화면 중심 위치를 기준으로 지우기
	bool MoveDown(Point reference_pos);		        // 한 칸 내려오기, 유효한 위치면 다시 그림
	void MoveRight(Point reference_pos);	        // 한 칸 오른쪽으로 이동, 유효한 위치면 다시 그림
	void MoveLeft(Point reference_pos);		        // 한 칸 왼쪽으로 이동, 유효한 위치면 다시 그림
	void Rotate(Point reference_pos);		        // 회전, 유효한 위치면 다시 그림
	void GoBottom(Point reference_pos);		        // 최하단으로 이동, 유효할 때까기 MoveDown() 실행
	void MoveOnestepDown(Point reference_pos);		// 한 칸 아래로 이동, 유효한 위치면 다시 그림. 추가적 기능
	virtual void MarkCurTetrominoPos(Point reference_pos);	// 다 내려오고 난 후에 board_의 객체에 대한 값 setting
	bool CheckEndCondition(void);					// 종료 조건 검사, y축 기준으로 20이상(가득 참)이면 종료(return true)
	void SetCenterPos(Point pos);					// 중심 위치 설정
	void DrawShadowTetromino(Point reference_pos); // 그림자 기능
	void EraseShadowTetromino(Point reference_pos); // 그림자 기능
	bool CheckShadowValidPos(Point temp_pos);
	void SetGhostValue(void) { ghost_value = true; }
	void ReSetGhostValue(void) { ghost_value = false; }
	bool CheckGhostValue(void){ return ghost_value; }

protected:
	virtual bool CheckValidPos(void);	        // 현재 테트로미노 위치가 유효한지 검사, 판을 벗어나지 않고 다른 테트로미노가 쌓여있지 않음

protected:
	Point center_pos_;			        // 현재 중심 위치 (내부 배열 기준)
	TETROMINO_TYPE type_;               // 테트로미노 타입
	int rotate_;				        // 현재 회전 위치
	Board *board_;			            // Board 객체 정보를 알기 위해 Board 객체와 연결    
	bool ghost_value;
};

class GhostTetromino : public Tetromino
{
public:
	GhostTetromino(Board *board, TETROMINO_TYPE type);
	virtual void Draw(Point reference_pos);			        // 현재 화면 중심 위치를 기준으로 그리기
	virtual void Erase(Point reference_pos);				 // 현재 화면 중심 위치를 기준으로 지우기
	virtual void MarkCurTetrominoPos(Point reference_pos);	// 다 내려오고 난 후에 board_의 객체에 대한 값 setting
protected:
	virtual bool CheckValidPos(void);	        // 현재 테트로미노 위치가 유효한지 검사, 판을 벗어나지 않고 다른 테트로미노가 쌓여있지 않음
};
#endif