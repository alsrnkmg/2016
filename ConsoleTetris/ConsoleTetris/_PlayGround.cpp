// cpp002-2016-08-04-09:30 IN
#include "stdafx.h"

#define MAX_BLOCK_SIZE 4
#define TEST_LOG_ON 1

enum BUnitColor {
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
	BUnitColor color;
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
		if (TEST_LOG_ON) printf("PARENT - EXP. OVL. without (bMsg) CONSTRUCTOR called\r\n");
	}
	BlockQuad(bool bMsg, int in_limiter) :
		m_iNumBlock(MAX_BLOCK_SIZE),
		m_iBlockRotation(0),
		m_ciBlockLimiter(in_limiter){
		if (TEST_LOG_ON) printf("PARENT - EXP. OVL. with (bMsg) CONSTRUCTOR called\r\n");
		if (bMsg) printf("PARENT - Set m_iNumBlock to '%i(MAX_BLOCKSIZE)'\r\n", MAX_BLOCK_SIZE);
	}

	void SetQuad_Color(BUnitColor in_color){
		for (int i = 0; i < MAX_BLOCK_SIZE; i++)
			m_aBlockPosition[i].color = in_color;
	}
public:
	~BlockQuad(){
		if (TEST_LOG_ON) printf("PARENT - DEF. DESTROYER called\r\n");
	}

	virtual void SetRotation(bool bMsg){}

	virtual void Show(){}
	virtual void Display(){}
};

class BlockType_A : public BlockQuad{
public:
	BlockType_A() : BlockQuad(2){// ��ӹ��� �ڽ�Ŭ������ �θ��� ����� �����ڸ� ȣ���ϴ� ���.
		if (TEST_LOG_ON) printf("CHILD - DEF. without (bMsg) CONSTRUCTOR called\r\n");}
	BlockType_A(bool bMsg) : BlockQuad(bMsg, 2){
		if (TEST_LOG_ON) printf("CHILD - EXP. OVL. with (bMsg) CONSTRUCTOR called\r\n");}
	~BlockType_A(){
		if (TEST_LOG_ON) printf("CHILD - DEF. DESTROYER called\r\n");}

	virtual void SetRotation(bool bMsg){
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

		if (bMsg){
			printf("\tcurrent iBlockRotation = %i\r\n", m_iBlockRotation);
			printf("\tcurrent this block members' local coordinates are ..\r\n");
			for (int i = 0; i < MAX_BLOCK_SIZE; i++)
				printf("\tINDEX: %i\tX : %i\tY : %i\r\n", i, m_aBlockPosition[i].x, m_aBlockPosition[i].y);
		}
	}//SetRotation

	void Show(){
		printf("\t< ShowThis >\r\n");
		printf("\tCONSTANT ciBlockLimiter = %i\r\n", m_ciBlockLimiter);
		printf("\tcurrent iBlockRotation  = %i\r\n", m_iBlockRotation);
		printf("\tcurrent this block members' local coordinates are ..\r\n");
		for (int i = 0; i < MAX_BLOCK_SIZE; i++)
			printf("\tINDEX: %i\tX : %i\tY : %i\r\n", i, m_aBlockPosition[i].x, m_aBlockPosition[i].y);
	}
	void Display(){

	}
};

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
			//pTest = new BlockType_A(true);//!!new(1)
			pTest = new BlockType_A();//!!new(1)
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

	std::cout << "Testing (SetRotation)" << std::endl
			<< "   a key : Proceed" << std::endl
			<< "   s key : Stop and Quit" << std::endl;
	while (1)
	{
		if (_kbhit())
		{
			input = _getch();

			if (input == 'a')
				pTest->SetRotation(true);
			else if (input == 's')
				break;
			else
				continue;
		}
	}
	//BlockType_A TestOff(false);
	//return;

	delete(pTest);//!!delete(1)
}

/*

//BlockQuad - parental o.
//NOTE : �����ڰ� ��ȣ���� �ȿ� ������ �ܺ��Լ� (��� �̿��� �Լ�) ������ ������ �Ұ����غ��δ�. �׸��� �ǵ��� �̰��� �´�.
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
		if (TEST_LOG_ON) printf("PARENT - EXP. OVL. without (bMsg) CONSTRUCTOR called\r\n");
	}
	BlockQuad(bool bMsg, int in_limiter) :
		m_iNumBlock(MAX_BLOCK_SIZE),
		m_iBlockRotation(0),
		m_ciBlockLimiter(in_limiter){
		if (TEST_LOG_ON) printf("PARENT - EXP. OVL. with (bMsg) CONSTRUCTOR called\r\n");
		if (bMsg){
			printf("PARENT - Set m_iNumBlock to '%i(MAX_BLOCKSIZE)'\r\n", MAX_BLOCK_SIZE);
		}//if
	}

	void SetUnit(int in_index, int in_x, int in_y);
	void SetUnit(int in_index, int in_x, int in_y, BUnitColor in_color);
	void SetQuad_Color(BUnitColor in_color);
public:
	~BlockQuad(){
		if (TEST_LOG_ON) printf("PARENT - DEF. DESTROYER called\r\n");
	}

	virtual void SetRotation(){}	// ���� ȸ���Լ��� �����ϴ� �ͺ��� �̰��� �´�... �̸��� �����غ� �ʿ�� �ִ�..
	virtual void SetRotation(bool bMsg){}

	virtual void Show(){}
	virtual void Display(){}
};

void BlockQuad::SetUnit(int in_index, int in_x, int in_y){
	m_aBlockPosition[in_index].x = in_x;
	m_aBlockPosition[in_index].y = in_y;
}//SetUnit
void BlockQuad::SetUnit(int in_index, int in_x, int in_y, BUnitColor in_color){
	m_aBlockPosition[in_index].x = in_x;
	m_aBlockPosition[in_index].y = in_y;
	m_aBlockPosition[in_index].color = in_color;
	//m_aBlockPosition[in_index].color = (int)in_color;	//typecasting�� �̿��� . . .
}//overloaded SetUnit with Unit's Color.
void BlockQuad::SetQuad_Color(BUnitColor in_color){
	for (int i = 0; i < MAX_BLOCK_SIZE; i++)
		m_aBlockPosition[i].color = in_color;
}

//BlockType_A // .. A - - - -
class BlockType_A : public BlockQuad{
public:
	BlockType_A() : BlockQuad(2){
		//SetRotation();
		if (TEST_LOG_ON) printf("CHILD - DEF. without (bMsg) CONSTRUCTOR called\r\n");
	}
	BlockType_A(bool bMsg) : BlockQuad(bMsg, 2){	// ��ӹ��� �ڽ�Ŭ������ �θ��� ����� �����ڸ� ȣ���ϴ� ���.
		if (TEST_LOG_ON) printf("CHILD - EXP. OVL. with (bMsg) CONSTRUCTOR called\r\n");
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
			exit(1); // error, m_iBlockRotation should be from 0 to 1.
	}//SetRotation
	virtual void SetRotation(bool bMsg){
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

		if (bMsg){
			printf("\tcurrent iBlockRotation = %i\r\n", m_iBlockRotation);
			printf("\tcurrent this block members' local coordinates are ..\r\n");
			for (int i = 0; i < MAX_BLOCK_SIZE; i++)
				printf("\tINDEX: %i\tX : %i\tY : %i\r\n", i, m_aBlockPosition[i].x, m_aBlockPosition[i].y);
		}
	}//overloaded-SetRotation with message.

	void Show(){
		printf("\t< ShowThis >\r\n");
		printf("\tCONSTANT ciBlockLimiter = %i\r\n", m_ciBlockLimiter);
		printf("\tcurrent iBlockRotation  = %i\r\n", m_iBlockRotation);
		printf("\tcurrent this block members' local coordinates are ..\r\n");
		for (int i = 0; i < MAX_BLOCK_SIZE; i++)
			printf("\tINDEX: %i\tX : %i\tY : %i\r\n", i, m_aBlockPosition[i].x, m_aBlockPosition[i].y);
	}
	void Display(){

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
			pTest = new BlockType_A(true);//!!new(1)
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

	//pTest->ShowMe();	// �θ��� �Լ��� �ƴ�, �� ���ǵ� �ڽ��� ShowMe()�� �ҷ��´� -- ���?
						// �׷���, �����ڿ��� �ʱ�ȭ�Ǿ���� �ϴ� m_ciBlockLimiter�� ���������� ���Ѵ�.
						// �翬�� �̾߱��̰�, �ؼ��� �ȵ� ��..

	pTest->Show();		// ... �� �� �˾Ҵµ�, �⺻�����ڸ� ȣ���ϴ� new�� Ư���� ciBlockLimiter�� 2�� �ʱ�ȭ ��Ű�� ���� ���..
						// �θ𿡰Դ� ���� ����� �����ϴ� ���� �����ؼ��� �ȵǴ� �� �ƴѰ�?
						// '�㰡' ���� ���� ����. ����, http://www.soen.kr/lecture/ccpp/cpp3/30-1-1.htm

	std::cout << "Testing (SetRotation)" << std::endl
		<< "   a key : Proceed" << std::endl
		<< "   s key : Stop and Quit" << std::endl;
	while (1)
	{
		if (_kbhit())
		{
			input = _getch();

			if (input == 'a')
				pTest->SetRotation(true);
			else if (input == 's')
				break;
			else
				continue;
		}
	}
	//BlockType_A TestOff(false);
	//return;

	delete(pTest);//!!delete(1)
}
*/
/* 
	void (BlockQuad::*pFunc2)(void);
	pFunc2 = (void(BlockType_A::*)(void))(pTest->SetRotation);
	
	void (BlockType_A::*pFunc)(void) = &BlockType_A::SetRotation;
	//pFunc = (void(*)(void))(pTest->SetRotation);

	//void(*pFunc2)(void) = pTest->SetRotation;
	//void(*pFunc2)(void) = &SetRotation();
	//cannot convert form 'overloaded-function' to 'void (__cdecl *)(void)'

	... �̤� ...
*/

/* ���� �ڵ忡�� ����..



*/

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