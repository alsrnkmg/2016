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
private:	// protected? // 상속자라도 접근할 필요가 없는 변수일 것이다.
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
	BlockType_A() : BlockQuad(2){// 상속받은 자식클래스가 부모의 명시적 생성자를 호출하는 방법.
		if (TEST_LOG_ON) printf("CHILD - DEF. without (bMsg) CONSTRUCTOR called\r\n");}
	BlockType_A(bool bMsg) : BlockQuad(bMsg, 2){
		if (TEST_LOG_ON) printf("CHILD - EXP. OVL. with (bMsg) CONSTRUCTOR called\r\n");}
	~BlockType_A(){
		if (TEST_LOG_ON) printf("CHILD - DEF. DESTROYER called\r\n");}

	virtual void SetRotation(bool bMsg){
		m_iBlockRotation = (m_iBlockRotation + 1) % m_ciBlockLimiter;

		if (m_iBlockRotation == 0){
			m_aBlockPosition[0].x = 0; m_aBlockPosition[0].y = 0;	// ★3
			m_aBlockPosition[1].x = 0; m_aBlockPosition[1].y = 1;	// ★2
			m_aBlockPosition[2].x = 0; m_aBlockPosition[2].y = 2;	// ★1
			m_aBlockPosition[3].x = 0; m_aBlockPosition[3].y = 3;	// ☆0
		}
		else if (m_iBlockRotation == 1){
			m_aBlockPosition[0].x = 0; m_aBlockPosition[0].y = 0;	// 
			m_aBlockPosition[1].x = 1; m_aBlockPosition[1].y = 0;	// 
			m_aBlockPosition[2].x = 2; m_aBlockPosition[2].y = 0;	// 0 1 2 3
			m_aBlockPosition[3].x = 3; m_aBlockPosition[3].y = 0;	// ☆★★★
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
//NOTE : 생성자가 보호범위 안에 있으면 외부함수 (상속 이외의 함수) 에서는 생성이 불가능해보인다. 그리고 의도상 이것이 맞다.
class BlockQuad{
private:	// protected? // 상속자라도 접근할 필요가 없는 변수일 것이다.
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

	virtual void SetRotation(){}	// 기존 회전함수를 응용하는 것보단 이것이 맞다... 이름도 점검해볼 필요는 있다..
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
	//m_aBlockPosition[in_index].color = (int)in_color;	//typecasting을 이용한 . . .
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
	BlockType_A(bool bMsg) : BlockQuad(bMsg, 2){	// 상속받은 자식클래스가 부모의 명시적 생성자를 호출하는 방법.
		if (TEST_LOG_ON) printf("CHILD - EXP. OVL. with (bMsg) CONSTRUCTOR called\r\n");
	}
	~BlockType_A(){
		if (TEST_LOG_ON) printf("CHILD - DEF. DESTROYER called\r\n");
	}

	virtual void SetRotation(){
		m_iBlockRotation = (m_iBlockRotation + 1) % m_ciBlockLimiter;

		if (m_iBlockRotation == 0){
			SetUnit(0, 0, 0);	// ★3
			SetUnit(1, 0, 1);	// ★2
			SetUnit(2, 0, 2);	// ★1
			SetUnit(3, 0, 3);	// ☆0
		}
		else if (m_iBlockRotation == 1){
			SetUnit(0, 0, 0);	//
			SetUnit(1, 1, 0);	//
			SetUnit(2, 2, 0);	// 0 1 2 3
			SetUnit(3, 3, 0);	// ☆★★★
		}
		else
			exit(1); // error, m_iBlockRotation should be from 0 to 1.
	}//SetRotation
	virtual void SetRotation(bool bMsg){
		m_iBlockRotation = (m_iBlockRotation + 1) % m_ciBlockLimiter;

		if (m_iBlockRotation == 0){
			SetUnit(0, 0, 0);	// ★3
			SetUnit(1, 0, 1);	// ★2
			SetUnit(2, 0, 2);	// ★1
			SetUnit(3, 0, 3);	// ☆0
		}
		else if (m_iBlockRotation == 1){
			SetUnit(0, 0, 0);	//
			SetUnit(1, 1, 0);	//
			SetUnit(2, 2, 0);	// 0 1 2 3
			SetUnit(3, 3, 0);	// ☆★★★
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

	//pTest->ShowMe();	// 부모의 함수가 아닌, 재 정의된 자식의 ShowMe()를 불러온다 -- 어떻게?
						// 그러나, 생성자에서 초기화되었어야 하는 m_ciBlockLimiter을 가져오지는 못한다.
						// 당연한 이야기이고, 해서도 안될 짓..

	pTest->Show();		// ... 인 줄 알았는데, 기본생성자를 호출하는 new의 특성상 ciBlockLimiter를 2로 초기화 시키는 것을 목격..
						// 부모에게는 없는 멤버를 참조하는 것은 가능해서는 안되는 것 아닌가?
						// '허가' 되지 않은 영역. 참조, http://www.soen.kr/lecture/ccpp/cpp3/30-1-1.htm

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

	... ㅜㅜ ...
*/

/* 기존 코드에서 쓰던..



*/

// 좌표변환은 월드에서 하는 것이 맞을 것 같다.
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