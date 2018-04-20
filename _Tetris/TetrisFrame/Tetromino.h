#ifndef JHHWANG_TETROMINO_H
#define JHHWANG_TETROMINO_H
#include "Point.h"
#include "Board.h"

#define TETROMINO_TYPE_COUNT 7
#define ROTATE_COUNT 4
//const Point g_next_tetromino_init_pos_2p(29, 3);
const Point g_next_tetromino_init_pos(13, 17); //������ 13, 17�̾���
const Point g_cur_tetromino_init_pos(4, 18); // ������ 4, 20�̾���
const Point Pause_Pos(10, 23);

enum TETROMINO_TYPE { TETROMINO_I, TETROMINO_J, TETROMINO_L, TETROMINO_O, TETROMINO_S, TETROMINO_T, TETROMINO_Z };

class Tetromino
{
public:
	Tetromino(Board *board, TETROMINO_TYPE type);
	virtual void Draw(Point reference_pos);			        // ���� ȭ�� �߽� ��ġ�� �������� �׸���
	virtual void Erase(Point reference_pos);		        // ���� ȭ�� �߽� ��ġ�� �������� �����
	bool MoveDown(Point reference_pos);		        // �� ĭ ��������, ��ȿ�� ��ġ�� �ٽ� �׸�
	void MoveRight(Point reference_pos);	        // �� ĭ ���������� �̵�, ��ȿ�� ��ġ�� �ٽ� �׸�
	void MoveLeft(Point reference_pos);		        // �� ĭ �������� �̵�, ��ȿ�� ��ġ�� �ٽ� �׸�
	void Rotate(Point reference_pos);		        // ȸ��, ��ȿ�� ��ġ�� �ٽ� �׸�
	void GoBottom(Point reference_pos);		        // ���ϴ����� �̵�, ��ȿ�� ����� MoveDown() ����
	void MoveOnestepDown(Point reference_pos);		// �� ĭ �Ʒ��� �̵�, ��ȿ�� ��ġ�� �ٽ� �׸�. �߰��� ���
	virtual void MarkCurTetrominoPos(Point reference_pos);	// �� �������� �� �Ŀ� board_�� ��ü�� ���� �� setting
	bool CheckEndCondition(void);					// ���� ���� �˻�, y�� �������� 20�̻�(���� ��)�̸� ����(return true)
	void SetCenterPos(Point pos);					// �߽� ��ġ ����
	void DrawShadowTetromino(Point reference_pos); // �׸��� ���
	void EraseShadowTetromino(Point reference_pos); // �׸��� ���
	bool CheckShadowValidPos(Point temp_pos);
	void SetGhostValue(void) { ghost_value = true; }
	void ReSetGhostValue(void) { ghost_value = false; }
	bool CheckGhostValue(void){ return ghost_value; }

protected:
	virtual bool CheckValidPos(void);	        // ���� ��Ʈ�ι̳� ��ġ�� ��ȿ���� �˻�, ���� ����� �ʰ� �ٸ� ��Ʈ�ι̳밡 �׿����� ����

protected:
	Point center_pos_;			        // ���� �߽� ��ġ (���� �迭 ����)
	TETROMINO_TYPE type_;               // ��Ʈ�ι̳� Ÿ��
	int rotate_;				        // ���� ȸ�� ��ġ
	Board *board_;			            // Board ��ü ������ �˱� ���� Board ��ü�� ����    
	bool ghost_value;
};

class GhostTetromino : public Tetromino
{
public:
	GhostTetromino(Board *board, TETROMINO_TYPE type);
	virtual void Draw(Point reference_pos);			        // ���� ȭ�� �߽� ��ġ�� �������� �׸���
	virtual void Erase(Point reference_pos);				 // ���� ȭ�� �߽� ��ġ�� �������� �����
	virtual void MarkCurTetrominoPos(Point reference_pos);	// �� �������� �� �Ŀ� board_�� ��ü�� ���� �� setting
protected:
	virtual bool CheckValidPos(void);	        // ���� ��Ʈ�ι̳� ��ġ�� ��ȿ���� �˻�, ���� ����� �ʰ� �ٸ� ��Ʈ�ι̳밡 �׿����� ����
};
#endif