// cpp001-2016-08-03-19:28
#include <iostream>
#include <conio.h>
//struct KPoint {
//	int x;
//	int y;
//};//KPoint
//
//struct KBlock {
//	KPoint  m_aBlockPosition[MAX_BLOCK_SIZE];
//	int     m_iNumBlock;
//


// ��ǥ��ȯ�� ���忡�� �ϴ� ���� ���� �� ����.
//	void DrawBlockOnBoard(/*const KBlock* this_,*/ int xBoard_, int yBoard_) {
//		for (int iBlock = 0; iBlock < this->m_iNumBlock; ++iBlock) {
//			// transform local coordinate to global coordinate
//			const int xGlobal = this->m_aBlockPosition[iBlock].x + xBoard_;
//			const int yGlobal = this->m_aBlockPosition[iBlock].y + yBoard_;
//			// draw a block on the board
//			if (yGlobal >= 0 && yGlobal < BOARD_SIZE_ROW
//				&& xGlobal >= 0 && yGlobal < BOARD_SIZE_COL) {
//				g_aBoard[yGlobal][xGlobal] = '#';
//			}//if
//		}//for
//	}//DrawBlockOnBoard()
//};//struct KBlock

#define MAX_BLOCK_SIZE 4
#define TEST_LOG_ON 1

enum BUnitColor {
	//EMPTY = -1,
	EMPTY = 0,
	DEFAULT, // 1
	RED,
	GREEN,
	BLUE}; // ..

struct BlockUnit{
	int x;
	int y;
	BUnitColor color;
};

//BlockQuad // parental o.
//NOTE : �����ڰ� ��ȣ���� �ȿ� ������ �ܺ��Լ� (��� �̿��� �Լ�) ������ ������ �Ұ����غ��δ�. �׸��� �ǵ��� �̰��� �´�.
class BlockQuad{
private:	// protected? // ����ڶ� ������ �ʿ䰡 ���� ������ ���̴�.
	int m_iNumBlock;
protected:
	BlockUnit m_aBlockPosition[MAX_BLOCK_SIZE];
	int m_iBlockRotation;

	BlockQuad() : m_iNumBlock(MAX_BLOCK_SIZE), m_iBlockRotation(0){
		if (TEST_LOG_ON) printf("PARENT - DEF. CONSTRUCTOR called\r\n");
	}
	BlockQuad(bool bMsg) : m_iNumBlock(MAX_BLOCK_SIZE), m_iBlockRotation(0){
		if (TEST_LOG_ON) printf("PARENT - OVL. MSG CONSTRUCTOR called\r\n");
		if (bMsg){
			if (TEST_LOG_ON) printf("PARENT - Set m_iNumBlock to '%i(MAX_BLOCKSIZE)'\r\n", MAX_BLOCK_SIZE);
		}//if
	}

	void SetUnit(int in_index, int in_x, int in_y){
		m_aBlockPosition[in_index].x = in_x;
		m_aBlockPosition[in_index].y = in_y;
		//return true;	//succed
	}
	void SetUnit(int in_index, int in_x, int in_y, BUnitColor in_color){
		m_aBlockPosition[in_index].x = in_x;
		m_aBlockPosition[in_index].y = in_y;
		m_aBlockPosition[in_index].color = in_color;
		//m_aBlockPosition[in_index].color = (int)in_color;	//typecasting�� �̿��� . . .
	}//overloaded SetUnit with Unit's Color.
	void SetQuad_Color(BUnitColor in_color){
		for (int i = 0; i < MAX_BLOCK_SIZE; i++)
			m_aBlockPosition[i].color = in_color;
	}
public:
	~BlockQuad(){
		if (TEST_LOG_ON) printf("PARENT - DEF. DESTROYER called\r\n");
	}

	virtual void SetRotation(){}	// ���� ȸ���Լ��� �����ϴ� �ͺ��� �̰��� �´�... �̸��� �����غ� �ʿ�� �ִ�..
};

//BlockType_A // .. A - - - -
class BlockType_A : public BlockQuad{
private:
	const int m_ciBlockLimiter;
public:
	BlockType_A(bool bMsg) : m_ciBlockLimiter(2), BlockQuad(bMsg){	// ��ӹ��� �ڽ�Ŭ������ �θ��� ����� �����ڸ� ȣ���ϴ� ���.
		if (TEST_LOG_ON) printf("CHILD - OVL. MSG CONSTRUCTOR called\r\n");
	}
	BlockType_A() : m_ciBlockLimiter(2){
		if (TEST_LOG_ON) printf("CHILD - DEF. CONSTRUCTOR called\r\n");
	}
	~BlockType_A(){
		if (TEST_LOG_ON) printf("CHILD - DEF. DESTROYER called\r\n");
	}

	virtual void SetRotation(){
		m_iBlockRotation = (m_iBlockRotation + 1) % m_ciBlockLimiter;

		if (m_iBlockRotation == 0){
			SetUnit(0, 0, 0);	// ��3
			SetUnit(1, 0, 1);	// ��2
			SetUnit(2, 0, 2);	// ��1
			SetUnit(3, 0, 3);	// ��0
		}
		else if (m_iBlockRotation == 1){
			SetUnit(0, 0, 0);	//
			SetUnit(1, 1, 0);	//
			SetUnit(2, 2, 0);	// 0 1 2 3
			SetUnit(3, 3, 0);	// �١ڡڡ�
		}
		else
			exit(1); // error, m_iBlockRotation should be form 0 to 1.

		if (TEST_LOG_ON){
			printf("\tcurrent iBlockRotation = %i\r\n", m_iBlockRotation);
			printf("\tcurrent this block members' local coordinates are ..\r\n");
			for (int i = 0; i < MAX_BLOCK_SIZE; i++)
				printf("\tINDEX: %i\tX : %i\tY : %i\r\n", i, m_aBlockPosition[i].x, m_aBlockPosition[i].y);
		}
	}

	void ShowMe()
	{
		printf("ShowMe Test -- accessible? -- %i\r\n", m_iBlockRotation);
	}
};
//BlockType_B // .. B - - - o
//BlockType_C // .. C o - - -
//...to G (to 7th)

void main()
{
	BlockQuad* pTest;
	
	char TestBlock = 0;
	char input = 0;

	std::cout << "Select Block-Type" << std::endl
		<< "  Type A : a, A" << std::endl
		<< "  Type B : b, B" << std::endl
		<< "  Type C : c, C" << std::endl
		<< "  Type D : d, D" << std::endl
		<< "  Type E : e, E" << std::endl
		<< "  Type F : f, F" << std::endl
		<< "  Type G : g, G" << std::endl
		<< "  _quit_ : ESC" << std::endl;
		//<< "  command> " << std::endl;

	while (1){
		std::cout << "   command> ";
		std::cin >> TestBlock;
		if (TestBlock == 'a' || TestBlock == 'A'){
			pTest = new BlockType_A(true);
			break;
		}
		//else if (TestBlock == 'b' || TestBlock == 'B'){
		//	pTest = new BlockType_B(true);
		//	break;
		//}
		else
		{
			std::cout << "   ! warning (wrong Block-Type)" << std::endl;
			continue;
		}
	}

	std::cout << "�ϳ������ �����ϴ�." << std::endl << "�׽�Ʈ ��� : 'a'�� ȸ��, 's'�� �ߴ� �� ����" << std::endl;
	while (1)
	{
		if (_kbhit())
		{
			input = _getch();

			if (input == 'a')
				pTest->SetRotation();
			else if (input == 's')
				break;
			else
				continue;
		}
	}
	//BlockType_A TestOff(false);
	//return;

	delete(pTest);
}