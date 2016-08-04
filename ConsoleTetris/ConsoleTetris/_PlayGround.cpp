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
//NOTE : 생성자가 보호범위 안에 있으면 외부함수 (상속 이외의 함수) 에서는 생성이 불가능해보인다. 그리고 의도상 이것이 맞다.
class BlockQuad{
private:	// protected? // 상속자라도 접근할 필요가 없는 변수일 것이다.
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
		//m_aBlockPosition[in_index].color = (int)in_color;	//typecasting을 이용한 . . .
	}//overloaded SetUnit with Unit's Color.
	void SetQuad_Color(BUnitColor in_color){
		for (int i = 0; i < MAX_BLOCK_SIZE; i++)
			m_aBlockPosition[i].color = in_color;
	}
public:
	~BlockQuad(){
		if (TEST_LOG_ON) printf("PARENT - DEF. DESTROYER called\r\n");
	}

	virtual void SetRotation(){}	// 기존 회전함수를 응용하는 것보단 이것이 맞다... 이름도 점검해볼 필요는 있다..
};

//BlockType_A // .. A - - - -
class BlockType_A : public BlockQuad{
private:
	const int m_ciBlockLimiter;
public:
	BlockType_A(bool bMsg) : m_ciBlockLimiter(2), BlockQuad(bMsg){	// 상속받은 자식클래스가 부모의 명시적 생성자를 호출하는 방법.
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

	std::cout << "하나무라로 떠납니다." << std::endl << "테스트 모드 : 'a'는 회전, 's'는 중단 후 종료" << std::endl;
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