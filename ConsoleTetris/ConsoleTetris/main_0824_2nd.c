// LAST UPDATE : 2016-08-25-04:49 AM
// [TASK #1 : collision checker] [Ln : 262]
// [TASK #2 : in RENEW TEST] [Ln : 301]
// and -- so -- on ...

#include <stdio.h>
#include <conio.h>
#include <memory.h>
#include <stdlib.h>

#define BOARD_SIZE_ROW	20
#define BOARD_SIZE_COL	10
int board_face[BOARD_SIZE_ROW][BOARD_SIZE_COL];
int board_back[BOARD_SIZE_ROW][BOARD_SIZE_COL];
int board_coll[BOARD_SIZE_ROW][BOARD_SIZE_COL];

typedef int BOOL;
#define TRUE	1
#define FALSE	0

#define IN

typedef struct tagKPoint{
	int x;
	int y;
}KPoint, *pKPoint;

typedef struct tagKBlock{
	KPoint member[4];
	int world_pos_x;
	int world_pos_y;
	BOOL on_control;
	char type;
	int rotation_status;
}KBlock, *pKBlock;

BOOL esc_signal = FALSE;
KPoint offset_table[ 9 ] ={
	{ 0, 0 },		// O

	{ -1, -1 },		// NW
	{ 0, -1 },		// N
	{ +1, -1 },		// NE

	{ +1, 0},		// E

	{ +1, +1 },		// SE
	{ 0, +1},		// S
	{ -1, +1},		// SW

	{ -1, 0 }		// W
};

#define OFFSET_O	0

#define OFFSET_NW	1
#define OFFSET_N	2
#define OFFSET_NE	3

#define OFFSET_E	4

#define OFFSET_SE	5
#define OFFSET_S	6
#define OFFSET_SW	7

#define OFFSET_W	8

void test_draw()
{
	// 01 // wait for signal
	//_getch();

	// 02 // clear the screen
	system("cls");

	// 03 // copy "back-board" to "face-board"
	memcpy((int*)board_face, (int*)board_back, sizeof(int) * BOARD_SIZE_ROW * BOARD_SIZE_COL);

	// temp // show msg
	printf("wsad = move\r\n");
	printf("e = (test)release/gain control\r\n");
	printf("z = (test)do_nothing(proceed routine)\r\n");
	printf("ESC = quit\r\n");

	// 04 // draw "face-board" on the screen.
	for (int y = 0; y < BOARD_SIZE_ROW; ++y)
	{
		for (int x = 0; x < BOARD_SIZE_COL; ++x)
		{
			if (board_face[y][x] == 0)
				printf(". ");
			else if (board_face[y][x] = 1)
				printf("# ");
		}
		printf("\r\n");
	}
}

// name it : put
void test_current_block_to_world(KBlock* curr)
{
	// fn // updating current position data on "back-board"
	int curr_board_x, curr_board_y;

	for (int i = 0; i < 4; ++i)
	{
		curr_board_x = (curr->member[i].x) + (curr->world_pos_x);
		curr_board_y = (curr->member[i].y) + (curr->world_pos_y);
		board_back[curr_board_y][curr_board_x] = 1;
	}
}

// name it : rip (as ripping)
void test_previous_block_to_world(KBlock* prev)
{
	// fn // whenever block moves, previous-data on "back-board" needs to be updated to '0'
	int prev_board_x, prev_board_y;
	
	for (int i = 0; i < 4; ++i)
	{
		prev_board_x = (prev->member[i].x) + (prev->world_pos_x);
		prev_board_y = (prev->member[i].y) + (prev->world_pos_y);
		board_back[prev_board_y][prev_board_x] = 0;
	}
}

void test_rotate( KBlock* target_block )
{
	// fn // rotate the target-block with pre-defined coordinates, effects on local-coord.
	if ( target_block->type == 'a' )
		;
	else if ( target_block->type == 'b' )
	{
		target_block->rotation_status = (target_block->rotation_status + 1) % 4; // using mod-op. so it will be 0 to 3.

		if (target_block->rotation_status == 0)
		{
			/// @desc	member[ index 0 ] is always the axis.
			//			the others follow clock-wise-index, start from NW.
			//			additionaly, definition of these local coordinate's origin is top-left.

			target_block->member[0] = offset_table[OFFSET_O];	// #1#2
			target_block->member[1] = offset_table[OFFSET_N];	// @0
			target_block->member[2] = offset_table[OFFSET_NE];	// #3
			target_block->member[3] = offset_table[OFFSET_S];	// @ is always origin.

			//target_block->member[0].x = 0; target_block->member[0].y = 0;
			//target_block->member[1].x = 0; target_block->member[1].y = -1;	// #1#2
			//target_block->member[2].x = 1; target_block->member[2].y = -1;	// @0 -- @ : the axis.
			//target_block->member[3].x = 0; target_block->member[3].y = 1;		// #3

			//target_block->member
			//target_block->member[0].x = 0; target_block->member[0].y = 0;	// #0#1
			//target_block->member[1].x = 1; target_block->member[1].y = 0;	// @2  -- @ : the axis.
			//target_block->member[2].x = 0; target_block->member[2].y = 1;	// #3
			//target_block->member[3].x = 0; target_block->member[3].y = 2;	// note : when the origin is top-left.
		}
		else if (target_block->rotation_status == 1)
		{
			//target_block->member[0] = offset_table[OFFSET_O];	// doesnot need to be modified.
			target_block->member[1] = offset_table[OFFSET_W];
			target_block->member[2] = offset_table[OFFSET_E];	// #1@0#2
			target_block->member[3] = offset_table[OFFSET_SE];	//     #3
		}
		else if (target_block->rotation_status == 2)
		{
			target_block->member[0] = offset_table[OFFSET_O];	//   #1
			target_block->member[1] = offset_table[OFFSET_N];	//   @0
			target_block->member[2] = offset_table[OFFSET_S];	// #3#2
			target_block->member[3] = offset_table[OFFSET_SW];
		}
		else if (target_block->rotation_status == 3)
		{
			target_block->member[0] = offset_table[OFFSET_O];	// #1
			target_block->member[1] = offset_table[OFFSET_NW];	// #3@0#2
			target_block->member[2] = offset_table[OFFSET_E];
			target_block->member[3] = offset_table[OFFSET_W];
		}
		else
			; // error
	}
}

char test_key_input_check()
{
	char ch = -1;

	while (1)
	{
		ch = _getch();
		if (ch == 'a')
			break;
		else if (ch == 'd')
			break;
		else if (ch == 's')
			break;
		else if (ch == 'q')
			break;
		else if (ch == 27)	// 0033, 0x1b
			break;
		else if (ch == 'z')
			break;
		else if (ch == 'w')
			break;
		else if (ch == 'e')
			break;
	}

	return ch;
}

void test_regular_update(IN KBlock* curr_block)
{
	// 01 // make prev-one
	KBlock prev_block;
	KBlock coll_check_block;
	memcpy((KBlock*)&prev_block, (KBlock*)curr_block, sizeof(KBlock));
	memcpy((KBlock*)&coll_check_block, (KBlock*)curr_block, sizeof(KBlock));

	char input = 0;
	BOOL can_locate = FALSE;
	int coll_checker_x, coll_checker_y;

	// -- test -- //
	// 02 // updating-current-block by key-input;signal or automatically;time.
	//		// --00 - create next one
	//		// --01 - move(+y)
	//		// --02 - move(-x)
	//		// --03 - move(+x)
	//		// --04 - rotate
	{
		input = test_key_input_check();

		if (coll_check_block.on_control)
		{
			if (input == 'z')
				; // do nothing for test.
			else if (input == 'a')
				coll_check_block.world_pos_x -= 1;//curr_block->world_pos_x -= 1;
			else if (input == 'd')
				coll_check_block.world_pos_x += 1;//curr_block->world_pos_x += 1;
			else if (input == 's')
				coll_check_block.world_pos_y += 1;//curr_block->world_pos_y += 1;
			else if (input == 'w')
				coll_check_block.world_pos_y -= 1;//curr_block->world_pos_y += 1;
			else if (input == 'q')
				test_rotate(&coll_check_block);//test_rotate( curr_block );
		}
		if (input == 'e')
			//coll_check_block.on_control = FALSE;
			coll_check_block.on_control = 1 - coll_check_block.on_control;
		else if (input == 27)
			esc_signal = TRUE;//exit(0);

		//curr_block->world_pos_y += 1;	// --01
		//curr_block->world_pos_x -= 1;	// --02
		//curr_block->world_pos_x += 1;	// --03
		//test_rotate(curr_block);		// --04
	}

	// 03 // collision checking.
	// [TASK #1 : collision checker ] - needs to be double-check this code is right or not.
	{
		for (int i = 0; i < 4; i++)
		{
			coll_checker_x = coll_check_block.member[i].x + coll_check_block.world_pos_x;
			coll_checker_y = coll_check_block.member[i].y + coll_check_block.world_pos_y;
			// 03-01, checking it is on valid position (in the array area)
			if (   coll_checker_x >= 0 && coll_checker_x < BOARD_SIZE_COL
				&& coll_checker_y >= 0 && coll_checker_y < BOARD_SIZE_ROW)
			{
				// 03-01-01, if it is, checking there is empty or not.
				if (board_coll[coll_checker_y][coll_checker_x] != 0)
				{
					can_locate = FALSE;
					break;
				}
				// 03-01-02, when passes all these -if- the block can locate.
				can_locate = TRUE;
			}
			// 03-02, the block's world position is not on the board.
			else
			{
				can_locate = FALSE;
				break;
			}
		}
	}

	// 04 // regular update. base on BOOL can_locate.
	if (can_locate)
	{
		memcpy((KBlock*)curr_block, (KBlock*)&coll_check_block, sizeof(KBlock));
		//test_previous_block_to_world(curr_block->on_control, &prev_block);
		test_previous_block_to_world(&prev_block);
		test_current_block_to_world(curr_block);
	}
	else
	{
		memcpy((int*)&board_coll, (int*)&board_back, sizeof(int)*BOARD_SIZE_ROW*BOARD_SIZE_COL);
		// TEST RENEW -- [TASK #2 : in RENEW TEST]
		// specifically, this RENEW action does not defend on that block can be located or not.
		// so it needs to be considered the other way as well.
		curr_block->world_pos_x = 5;
		curr_block->world_pos_y = 5;
		test_current_block_to_world(curr_block);
	}
}

void main()
{
	KBlock test_block;
	memset((int*)board_back, 0, sizeof(int)*BOARD_SIZE_ROW*BOARD_SIZE_COL);
	{
		for (int x = 0; x < BOARD_SIZE_COL; ++x)
			board_back[ BOARD_SIZE_ROW-1 ][x] = 1;
		board_back[ BOARD_SIZE_ROW-1 ][ 5 ] = 0;
	}
	memset((int*)board_face, 0, sizeof(int)*BOARD_SIZE_ROW*BOARD_SIZE_COL);
	memset((int*)board_coll, 0, sizeof(int)*BOARD_SIZE_ROW*BOARD_SIZE_COL); // init the boards.
	memcpy((int*)&board_coll, (int*)&board_back, sizeof(int)*BOARD_SIZE_ROW*BOARD_SIZE_COL);
	memset((pKBlock)&test_block, 0, sizeof(KBlock));
	{
		test_block.member[0] = offset_table[OFFSET_O];	// #1#2
		test_block.member[1] = offset_table[OFFSET_N];	// @0
		test_block.member[2] = offset_table[OFFSET_NE];	// #3
		test_block.member[3] = offset_table[OFFSET_S];	// @ is always origin.

		//DEP / these are subtitute in the way of "Test 02".
			//test_block.member[0].x = 0; test_block.member[0].y = 0;
			//test_block.member[1].x = 0; test_block.member[1].y = 1;
			//test_block.member[2].x = 1; test_block.member[2].y = 0;
			//test_block.member[3].x = 1; test_block.member[3].y = 1;

		test_block.world_pos_x = 5;
		test_block.world_pos_y = 5;
		test_block.on_control = TRUE;
		test_block.type = 'b';
		test_block.rotation_status = 0;
	} // init the block.

	while ( esc_signal != TRUE )
	{
		test_draw();
		test_regular_update(&test_block);
	}
	printf("Good bye then\t\t");
}


/* OLD CODES */
/* EXCEPTED 2016-08-25-04:27-AM from test_regular_update()*/
/* NOTE : seems not needed.*/
//if (collide_y)
//{
//	coll_check_block.on_control = FALSE;
//	reach_bottom = TRUE;
//}
//// 04 // game logic
//// when the block reaches at the bottom of board, stop and create new one. / by automatical process
//
//// "board_coll" which is the board to check the collisions, is needed to be updated.
//if (reach_bottom)
//{
//	memcpy((int*)&board_coll, (int*)&board_back, sizeof(int)*BOARD_SIZE_ROW*BOARD_SIZE_COL);
//	memcpy((int*)&board_back, (int*)&board_coll, sizeof(int)*BOARD_SIZE_ROW*BOARD_SIZE_COL);
//	//memcpy((int*)&board_back, (int*)&board_coll, sizeof(int)*BOARD_SIZE_ROW*BOARD_SIZE_COL);
//	//reach_bottom = FALSE;
//	coll_check_block.world_pos_x = 5;
//	coll_check_block.world_pos_y = 5;
//	coll_check_block.on_control = TRUE;
//}
/* EXCEPTED 2016-08-25-03:43-AM */
//void test_previous_block_to_world(BOOL curr_on_control, KBlock* prev)
//{
//	// fn // when the current block is on_contorl, it is keep-moving-thing.
//	// so that means, previous-data on "back-board" needs to be updated to '0'
//	int prev_board_x, prev_board_y;
//
//	// CONDITION // check whether  'src' is on_control or not.
//	if (curr_on_control)
//	{
//		for (int i = 0; i < 4; ++i)
//		{
//			prev_board_x = (prev->member[i].x) + (prev->world_pos_x);
//			prev_board_y = (prev->member[i].y) + (prev->world_pos_y);
//			// -- TRUE -- // do <fn>
//			board_back[prev_board_y][prev_board_x] = 0;
//		}
//	}
//	else
//		;	// if it is not, <fn> does nothing.
//}

/* EXCEPTED 2016-08-25-02:12-AM FROM main() */
//// 01 - should be ' . ' to all
//test_draw();
//
//// 02 - should be (5,5) (5,6) (6,5) (6,6) are ' # '
//// .y += 1 , so (5,6) (5,7) (6,6) (6,7) are '#'
////DEP / made it regular routine.
////DEP / test_block_to_world(&test_block);
////test_current_block_to_world(&test_block);
//test_regular_update(&test_block);
//test_draw();
//
//// 03 - move block downward,
////		manipulates only world_pos_y, results should be .. (5,6) (5,7) (6,6) (6,7) are '#'
//
////DEP / made it regular routine.
////KBlock test_prev_block = test_block;	// should be regular routine.
////test_block.world_pos_y += 1;
//
////DEP / test_block_to_world(&test_block);
////test_previous_block_to_world( test_block.on_control, &test_prev_block);
////test_current_block_to_world( &test_block );
//
//test_regular_update(&test_block);
//test_draw();

/* EXCEPTED 2016-08-25-02:03-AM FROM main() */
/* Test 01 */ // find out how struct's subtitution works.
//struct test_s_a{
//	int x;
//	int y;
//} b;
//struct test_s_a a[2]= { 100, 100 };
//b = a[0];

//printf("b.x = %i\tb.y = %i\r\n", b.x, b.y);
//printf("a[0].x = %i\ta[0].y = %i\r\n", a[0].x, a[0].y);
//printf("a[1].x = %i\ta[1].y = %i\r\n", a[1].x, a[1].y);

/* Test 02 */ // find out that using "Test 01" in practice, with predefined-offset-table.
//KBlock st_test_block;
//memset((KBlock*)&st_test_block, 0, sizeof(KBlock));
//{
//	st_test_block.member[0] = offset_table[OFFSET_O];
//	st_test_block.member[1] = offset_table[OFFSET_N];
//	st_test_block.member[2] = offset_table[OFFSET_NE];
//	st_test_block.member[3] = offset_table[OFFSET_S];

//	st_test_block.world_pos_x = 5;
//	st_test_block.world_pos_y = 5;
//	st_test_block.on_control = TRUE;
//	st_test_block.type = 'b';
//	st_test_block.rotation_status = 0;
//}
//printf("-- show : st_test_block.member --\r\n");
//for (int i = 0;i<4;++i)
//	printf("  [%i].x = %i\t[%i].y = %i\r\n", i, st_test_block.member[i].x, i, st_test_block.member[i].y);

//test_regular_update(&st_test_block);
//test_draw();

/* End of Test */
// exit(0);

/* EXCEPTED 2016-08-25-02:03-AM */
//void test_block_to_world(pKBlock src)
//{
//	// 01 // make a copy.
//	pKBlock saved_src;
//	saved_src = (pKBlock)malloc(sizeof(KBlock));
//	memcpy((pKBlock)saved_src, src, sizeof(KBlock));
//
//	KBlock saved_org;
//	memcpy((pKBlock)&saved_org, src, sizeof(KBlock));
//
//	//int board_x, board_y;
//	int src_board_x, src_board_y;
//	int cpy_board_x, cpy_board_y;
//
//	// 02 // check whether 'src' is on_control or not.
//	if (saved_src->on_control == TRUE)
//	{
//		for (int i = 0; i < 4; ++i)
//		{
//			cpy_board_x = (saved_src->member[i].x) + (src->world_pos_x);
//			cpy_board_y = (saved_src->member[i].y) + (src->world_pos_y);
//			// 02-01 // if it is on_control, it is keep-moving.
//					 // so that means, previous position-data on "back-board" needs to be updated to '0'
//			board_back[cpy_board_y][cpy_board_x] = 0;
//		}
//	}
//
//	// 03 // regular routine, updating current position-data on "back-board" to '1'.
//	for (int j = 0; j < 4; ++j)
//	{
//		src_board_x = (src->member[j].x) + (src->world_pos_x);
//		src_board_y = (src->member[j].y) + (src->world_pos_y);
//		board_back[src_board_y][src_board_x] = 1;
//	}
//
//	free(saved_src);
//
//	//if (src->on_control == TRUE)
//	//{
//	//	for (int i = 0; i < 4; ++i)
//	//	{
//	//		board_x = (src->member[i].x) + (src->world_pos_x);
//	//		board_y = (src->member[i].y) + (src->world_pos_y);
//	//		board_face[board_y][board_x] = 1;
//	//	}
//	//}
//}