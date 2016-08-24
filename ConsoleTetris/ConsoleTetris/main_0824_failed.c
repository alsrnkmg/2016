//////////////////////////////////////
//			head section			//
//////////////////////////////////////
#include <stdio.h>
#include <Windows.h>	// including <TimeAPI.h>
#pragma comment(lib,"winmm.lib")

// BASIC DEFINITIONS.
typedef unsigned long DWORD;
typedef int		BOOL;
#ifndef TRUE
#define TRUE	1
#endif
#ifndef FALSE
#define FALSE	0
#endif
#ifndef NULL
#define NULL	((void*)0)
#endif

// DEFINITIONS which are used in these codes. / in this program.
typedef struct tagKPoint{
	int x;
	int y;
}KPoint, *pKPoint;

typedef struct tagKBlock{
	BOOL	m_isOnControl;
	char	m_cType;
	KPoint	m_aBlock[4];
	KPoint	m_worldPos;
}KBlock, *pKBlock;

typedef char BOARD_CELL_TYPE;

// Keys.
#define TTET_KEY_NULL		0
#define TTET_KEY_LEFT		'a'
#define TTET_KEY_RIGHT		'd'
#define TTET_KEY_ESC		27 // ..

// Board(World)
#define BOARD_SIZE_ROW		20
#define BOARD_SIZE_COL		20

//////////////////////////////////////////
//			global variables			//	// Q1. should i declare it in main or head?
//////////////////////////////////////////

HANDLE                  g_hConsole = INVALID_HANDLE_VALUE;
BOOL                    g_bIsExitGameLoop = FALSE;

BOARD_CELL_TYPE         g_aBoard[BOARD_SIZE_ROW][BOARD_SIZE_COL]; // Working board used in current frame.
BOARD_CELL_TYPE         g_aCurBoard[BOARD_SIZE_ROW][BOARD_SIZE_COL]; // Current Board state

KBlock      g_curBlock;
float       g_fCurBlockTimer = 0.f;
float       g_fCurBlockSpeed = 1.0f; ///< unit is seconds per a block

//////////////////////////////////////////
//			function section			//
//////////////////////////////////////////
// External		-+ Windows-Console based.
void SetCursorPosition(int x, int y)
{
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(g_hConsole, coord);
}
//////////////////////////////////////////

// Draw Part	-+ Console based.
BOOL Draw(float fElapsedTimeInSecond)
{
	// Step 01. Copying back-buffer to front-buffer(facial one)
	memcpy(g_aBoard, g_aCurBoard, sizeof(g_aBoard));

	// Step 02. DrawBoard(); -- draw g_aBoard on the console Window.
	for (int y = 0; y < BOARD_SIZE_COL; ++y)
	{
		for (int x = 0; x < BOARD_SIZE_ROW; ++x)
		{
			SetCursorPosition(x, y);
			if (g_aBoard[y][x] == 0)
				printf(".");
			else if (g_aBoard[y][x] == 35)
				printf("#");
			//printf("%c", g_aBoard[y][x]);
		}
	}

	return TRUE;
}
//////////////////////////////////////////

// Data-trans between World & Object.
BOOL TransBlockOnWorld()
{
	// 그러니까, 그 좌표에 내가 있으면
	// 거기에 #을 때려박으면 되는데..

	int world_x, world_y;

	for (int i = 0; i < 4; ++i)
	{
		world_x = (g_curBlock.m_aBlock[i].x) + (g_curBlock.m_worldPos.x);
		world_y = (g_curBlock.m_aBlock[i].y) + (g_curBlock.m_worldPos.y);
		g_aCurBoard[ world_y ][ world_x ] = '#'; // 35
	}

	return FALSE;
}
// Conventional GameLoop.
// Related to Block.

BOOL Init()
{
	// c00.01 -- Getting Windows' HANDLE
	g_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// c01.01 -- Setting the boards' status to 0 (using memset)
	memset(g_aBoard, 0, sizeof(BOARD_CELL_TYPE) * BOARD_SIZE_ROW * BOARD_SIZE_COL);
	memset(g_aCurBoard, 0, sizeof(BOARD_CELL_TYPE) * BOARD_SIZE_ROW * BOARD_SIZE_COL);
	// c01.02 -- Setting current block. (for test)

	// temp.
	// #0#1		// when the origin is top-left.
	// @2		// note: @ is the aixs.
	// #3
	memset(&g_curBlock, 0, sizeof(g_curBlock));
	g_curBlock.m_aBlock[0].x = 0; g_curBlock.m_aBlock[0].y = 0;
	g_curBlock.m_aBlock[1].x = 1; g_curBlock.m_aBlock[1].y = 0;
	g_curBlock.m_aBlock[2].x = 0; g_curBlock.m_aBlock[2].y = 1;
	g_curBlock.m_aBlock[3].x = 0; g_curBlock.m_aBlock[3].y = 2;
	g_curBlock.m_cType = 'b';
	g_curBlock.m_isOnControl = TRUE;
	g_curBlock.m_worldPos.x = 2;
	g_curBlock.m_worldPos.y = 2;


	return FALSE;
}

BOOL Update(float fElapsedTimeInSecond)
{
	// Step 01. Checking Input.
	// Step 02. Checking collision by Time.
	// Step 03. Checking collision by Input.
	// Step 04. Processing basic GameLogic.

	// Calculate Time.
	g_fCurBlockTimer += fElapsedTimeInSecond;
	if (g_fCurBlockTimer >= g_fCurBlockSpeed) {
		g_fCurBlockTimer -= g_fCurBlockSpeed; // reset current block timer
		g_curBlock.m_worldPos.y += 1;
	}//if

	// Do Logic.
	TransBlockOnWorld();
	return FALSE;
}

void main()
{
	printf("Hello");
	BOOL errFlag = FALSE;

	DWORD dwCurrTime = 0L;
	DWORD dwPrevTime = 0L;
	dwCurrTime = timeGetTime();	// <TimeAPI.h>
	dwPrevTime = dwCurrTime;

	Init();

	while (!g_bIsExitGameLoop){
		DWORD dwElapsedTime = 0L;
		float fElapsedTimeInSecond = 0.f;

		{
			dwPrevTime = dwCurrTime;
			dwCurrTime = timeGetTime();
			dwElapsedTime = dwCurrTime - dwPrevTime;		// save it.
			fElapsedTimeInSecond = dwElapsedTime / 1000.f;	// dividing it with 1000 to make it 'ms'
			Sleep(10);	// On Unix, <unistd.h> -- On Windows, <windows.h>
		}

		Update(fElapsedTimeInSecond);
		Draw(fElapsedTimeInSecond);
	}
	// Drawing-test.
	//Draw();
}