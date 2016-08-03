#include <iostream>

//struct KPoint {
//	int x;
//	int y;
//};//KPoint
//
//struct KBlock {
//	KPoint  m_aBlockPosition[MAX_BLOCK_SIZE];
//	int     m_iNumBlock;
//
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

enum BUnitColor { EMPTY = -1, DEFAULT, RED, GREEN, BLUE}; // ..
struct BlockUnit{
	int x;
	int y;
	BUnitColor color;
};

class BlockQuad{
private:	// protected?
	BlockUnit m_aBlockPosition[MAX_BLOCK_SIZE];
	int m_iNumBlock;
};

//BlockQuad // parental o.
//BlockType_A // .. A - - - -
//BlockType_B // .. B - - - o
//BlockType_C // .. C o - - -

void main()
{
	std::cout << "하나무라로 떠납니다." << std::endl;

	return;
}