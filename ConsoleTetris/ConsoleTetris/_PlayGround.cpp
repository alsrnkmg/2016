// cpp003-2016-08-04-19:30 IN
//////////////////////////////////////////////////////////////////
// *. block generator, FILE I/O�� �̿��Ͽ� ...
// ���� �ϳ���ž �������� ������ ������..
// fwrite�� �̿��� �������� ���Ͽ� ����� ��,
// ���� Ŀ���� [���� ��ġ]�� �̵� �� �ڿ� �׸�
// fread�� �о���� ����̾���.
//
// ��Ʈ������ ��쿡�� �о���̴� ���̰� -������- �� �� �ִ�.
// ����-Ÿ���� �������� ����� ���� ������ ��ġ�� ũ�� �ǹ̵� ������,
// ��忡 �� ���̸� �ְ� [100] �̸�, 100�� ���� ����ϰ�,
// �������� ��Ͻ������� ����� ������ �޸𸮸� �Ҵ��ϸ� �� ���̴�.
//
// *. C++�� ���� �������� ������ ���ص��� �Բ�
// *. �⺻���� Game ����Ŭ�� ���� ���ص��� ������ ���̰�.. (����۸� ������)
// *. ���������� Draw�� ���� �͵� �߻������� �ۿ� �𸣴� �� ���� ��������.
//////////////////////////////////////////////////////////////////
#include "stdafx.h"

#define MAX_BLOCK_SIZE 4

#define BOARD_SIZE_ROW      20
#define BOARD_SIZE_COL      20

#define BOARD_BACK 0
#define BOARD_FACE 1

HANDLE                  g_hConsole = INVALID_HANDLE_VALUE;
void SetCursorPosition(int x, int y) {
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(g_hConsole, coord);
}

enum EKeys {
	KEY_NULL = 0,
	KEY_LEFT = 'a',
	KEY_RIGHT = 'd',
	KEY_ROTATE = 'w',	// added
	KEY_ESC = 27,
};//enum EKeys

enum EBUnitColor {
	//EMPTY = -1,
	EMPTY = 0,
	DEFAULT, // 1
	RED,
	GREEN,
	BLUE
}; // ..
struct BlockUnit{
	int x;
	int y;
	EBUnitColor color;
};

class BlockQuad{
private:	// protected? // ����ڶ� ������ �ʿ䰡 ���� ������ ���̴�.
	int m_iNumBlock;
protected:
	BlockUnit m_aBlockPosition[MAX_BLOCK_SIZE];
	int m_iBlockRotation;
	const int m_ciBlockLimiter;

	BlockQuad(int in_limiter) :
		m_iNumBlock(MAX_BLOCK_SIZE),
		m_iBlockRotation(0),
		m_ciBlockLimiter(in_limiter){
	}
public:
	BlockQuad() :
		m_iNumBlock(MAX_BLOCK_SIZE),
		m_iBlockRotation(0),
		m_ciBlockLimiter(0){
		for (int i = 0; i < m_iNumBlock; ++i){
			m_aBlockPosition[i].x = 0;
			m_aBlockPosition[i].y = 0;
			m_aBlockPosition[i].color = EMPTY;
		}
	}
	virtual ~BlockQuad(){}

	virtual void SetRotation(){}
	virtual void Show(){}

	// common setter & getters
	void SetUnit(int in_index, int in_x, int in_y){
		m_aBlockPosition[in_index].x = in_x;
		m_aBlockPosition[in_index].y = in_y;
	}
	void SetQuad_Color(EBUnitColor in_color){
		for (int i = 0; i < MAX_BLOCK_SIZE; i++)
			m_aBlockPosition[i].color = in_color;
	}
	const BlockQuad* GetQuad(){
		return this;
	}
	const BlockUnit* GetUnit(int in_index){
		return &(this->m_aBlockPosition[in_index]);
	}
};

class BlockType_A : public BlockQuad{
public:
	BlockType_A() : BlockQuad(2){
		Init_temp();
	}
	virtual ~BlockType_A(){}								// -- NOTE 1 -- �����ı���

	void Init_temp(){
		m_aBlockPosition[0].x = 0; m_aBlockPosition[0].y = 0; m_aBlockPosition[0].color = DEFAULT;
		m_aBlockPosition[1].x = 0; m_aBlockPosition[1].y = 1; m_aBlockPosition[1].color = DEFAULT;
		m_aBlockPosition[2].x = 0; m_aBlockPosition[2].y = 2; m_aBlockPosition[2].color = DEFAULT;
		m_aBlockPosition[3].x = 0; m_aBlockPosition[3].y = 3; m_aBlockPosition[3].color = DEFAULT;
	}
	virtual void SetRotation(){
		m_iBlockRotation = (m_iBlockRotation + 1) % m_ciBlockLimiter;

		if (m_iBlockRotation == 0){
			m_aBlockPosition[0].x = 0; m_aBlockPosition[0].y = 0;	// ��3
			m_aBlockPosition[1].x = 0; m_aBlockPosition[1].y = 1;	// ��2
			m_aBlockPosition[2].x = 0; m_aBlockPosition[2].y = 2;	// ��1
			m_aBlockPosition[3].x = 0; m_aBlockPosition[3].y = 3;	// ��0
		}
		else if (m_iBlockRotation == 1){
			m_aBlockPosition[0].x = 0; m_aBlockPosition[0].y = 0;	// 
			m_aBlockPosition[1].x = 1; m_aBlockPosition[1].y = 0;	// 
			m_aBlockPosition[2].x = 2; m_aBlockPosition[2].y = 0;	// 0 1 2 3
			m_aBlockPosition[3].x = 3; m_aBlockPosition[3].y = 0;	// �١ڡڡ�
		}
		else
			exit(1); // error, m_iBlockRotation should be from 0 to 1.
	}//SetRotation
	virtual void Show(){
		printf("\t< ShowThis >\r\n");
		printf("\tCONSTANT ciBlockLimiter = %i\r\n", m_ciBlockLimiter);
		printf("\tcurrent iBlockRotation  = %i\r\n", m_iBlockRotation);
		printf("\tcurrent this block members' local coordinates are ..\r\n");
		for (int i = 0; i < MAX_BLOCK_SIZE; i++)
			printf("\tINDEX: %i\tX : %i\tY : %i\r\n", i, m_aBlockPosition[i].x, m_aBlockPosition[i].y);
	}//SHow .. for test.
};//BlockType_A

class BlockType_B : public BlockQuad{
public:
	BlockType_B() : BlockQuad(4){
		Init_temp();
	}
	virtual ~BlockType_B(){}

	void Init_temp(){
		m_aBlockPosition[0].x = 0; m_aBlockPosition[0].y = 0; m_aBlockPosition[0].color = DEFAULT;	//
		m_aBlockPosition[1].x = 1; m_aBlockPosition[1].y = 0; m_aBlockPosition[1].color = DEFAULT;	// ��3
		m_aBlockPosition[2].x = 0; m_aBlockPosition[2].y = 1; m_aBlockPosition[2].color = DEFAULT;	// ��2
		m_aBlockPosition[3].x = 0; m_aBlockPosition[3].y = 2; m_aBlockPosition[3].color = DEFAULT;	// ��0��1
	}
	virtual void SetRotation(){
		m_iBlockRotation = (m_iBlockRotation + 1) % m_ciBlockLimiter;

		if (m_iBlockRotation == 0){
			m_aBlockPosition[0].x = 0; m_aBlockPosition[0].y = 0;	//
			m_aBlockPosition[1].x = 1; m_aBlockPosition[1].y = 0;	// ��3
			m_aBlockPosition[2].x = 0; m_aBlockPosition[2].y = 1;	// ��2
			m_aBlockPosition[3].x = 0; m_aBlockPosition[3].y = 2;	// ��0��1
		}
		else if (m_iBlockRotation == 1){
			m_aBlockPosition[0].x = 0; m_aBlockPosition[0].y = 0;	//
			m_aBlockPosition[1].x = 1; m_aBlockPosition[1].y = 0;	//
			m_aBlockPosition[2].x = 2; m_aBlockPosition[2].y = 0;	// �� �� ��3
			m_aBlockPosition[3].x = 2; m_aBlockPosition[3].y = 1;	// ��0��1��2
		}
		else if (m_iBlockRotation == 2){
			m_aBlockPosition[0].x = 1; m_aBlockPosition[0].y = 0;	//
			m_aBlockPosition[1].x = 1; m_aBlockPosition[1].y = 1;	// ��2��3
			m_aBlockPosition[2].x = 0; m_aBlockPosition[2].y = 2;	// �� ��1
			m_aBlockPosition[3].x = 1; m_aBlockPosition[3].y = 2;	// �� ��0
		}
		else if (m_iBlockRotation == 3){
			m_aBlockPosition[0].x = 0; m_aBlockPosition[0].y = 0;	//
			m_aBlockPosition[1].x = 0; m_aBlockPosition[1].y = 1;	// 
			m_aBlockPosition[2].x = 1; m_aBlockPosition[2].y = 1;	// ��1��2��3
			m_aBlockPosition[3].x = 2; m_aBlockPosition[3].y = 1;	// ��0
		}
		else{
			printf("%i", m_iBlockRotation);
			printf("��Ҵ� �̳�");
			exit(1);
		}
	}
	virtual void Show(){
		printf("\t< ShowThis >\r\n");
		printf("\tCONSTANT ciBlockLimiter = %i\r\n", m_ciBlockLimiter);
		printf("\tcurrent iBlockRotation  = %i\r\n", m_iBlockRotation);
		printf("\tcurrent this block members' local coordinates are ..\r\n");
		for (int i = 0; i < MAX_BLOCK_SIZE; i++)
			printf("\tINDEX: %i\tX : %i\tY : %i\r\n", i, m_aBlockPosition[i].x, m_aBlockPosition[i].y);
	}//Show .. for test.
};//BlockType_B

// C .. G

class TetrisBoard{
private:
	EBUnitColor aBoard[BOARD_SIZE_ROW][BOARD_SIZE_COL];
protected:
public:
	TetrisBoard(){
		::memset(this, 0, sizeof(TetrisBoard));
	}
	~TetrisBoard(){}

	void SetBoard(int in_x, int in_y, EBUnitColor in_color){
		aBoard[in_y][in_x] = in_color;
	}

	void ClearBoard(){ ::memset(this, 0, sizeof(TetrisBoard)); }

	void Show(){
		printf("     < ShowThis >\r\n");
		printf("     current status of 'aBoard' is ..\r\n");
		for (int y = 0; y < BOARD_SIZE_ROW; ++y){
			for (int x = 0; x < BOARD_SIZE_COL; ++x){
				if (aBoard[y][x] == EMPTY)
					printf(" .");
				else
					printf(" #");
			}// for-x
			printf("\r\n");
		}//for-y

	}//Show .. for test.
};

class TetrisGame{
private:
	BlockQuad* pcCurrentBlock;
	TetrisBoard cWorld[2];
	int iCurrentBlockPos_x;
	int iCurrentBlockPos_y;
protected:
public:
	TetrisGame(){
		pcCurrentBlock = nullptr;
	}
	~TetrisGame(){ DeleteBlock(); }

	// getter
	const int GetCurrentBlockPos_x(){ return iCurrentBlockPos_x; }
	const int GetCurrentBlockPos_y(){ return iCurrentBlockPos_y; }

	void Init(){
		CreateBlock('b');
		iCurrentBlockPos_x = 9;
		iCurrentBlockPos_y = 9;
	}
	void CreateBlock(char in_type){
		if (in_type == 'a')
			pcCurrentBlock = new BlockType_A();
		else if (in_type == 'b')
			pcCurrentBlock = new BlockType_B();
	}
	
	void DeleteBlock(){ delete pcCurrentBlock; }

	void UpdateCurrentBlock(){
		if(pcCurrentBlock)
			pcCurrentBlock->SetRotation();
	}
	void Local_to_Global(int xBoard_, int yBoard_){
	//void TransLocalBlockToGlobalWorld(int xBoard_, int yBoard_){
		const BlockUnit* pcaLocalUnit[MAX_BLOCK_SIZE] = { nullptr, nullptr, nullptr, nullptr };

		cWorld[BOARD_BACK].ClearBoard();

		if (pcCurrentBlock){
			for (int iBlock = 0; iBlock < MAX_BLOCK_SIZE; ++iBlock){
				pcaLocalUnit[iBlock] = pcCurrentBlock->GetUnit(iBlock);
				//test //cGlobalQuad.SetUnit(iBlock, pcaLocalUnit[iBlock]->x + xBoard_, pcaLocalUnit[iBlock]->y);
				const int xGlobal = pcaLocalUnit[iBlock]->x + xBoard_;
				const int yGlobal = pcaLocalUnit[iBlock]->y + yBoard_;

				if (yGlobal >= 0 && yGlobal < BOARD_SIZE_ROW
					&& xGlobal >= 0 && xGlobal < BOARD_SIZE_COL){
					cWorld[BOARD_BACK].SetBoard(xGlobal, yGlobal, DEFAULT);
				}
			}
		}
		else
			; // error, there is no block to excute this function.
	}


	void Show(){
		cWorld[BOARD_BACK].Show();
	}
};

void main()
{
	TetrisGame test;
	char input = 0;

	g_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	test.Show();
	
	_getch();
	system("cls");
	test.Init();

	test.Local_to_Global(test.GetCurrentBlockPos_x(), test.GetCurrentBlockPos_y());
	SetCursorPosition(0, 0);
	test.Show();

	//_kbhit()
	while (1)
	{
		if (_kbhit())
		{
			system("cls");
			input = _getch();

			if (input == 'q')
				test.UpdateCurrentBlock();
			else if (input == 's')
				break;
			else
				;

			test.Local_to_Global(test.GetCurrentBlockPos_x(), test.GetCurrentBlockPos_y());
			SetCursorPosition(0, 0);
			test.Show();
		}
	}
}
