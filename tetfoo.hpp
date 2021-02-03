#ifndef tetfoo
#define tetfoo 1
constexpr bool DBG1=false;


struct Tetramino;


struct Field;


constexpr bool tetratypes[7][4][4]={
		{				//O
			{0,0,0,0},
			{0,0,0,0},
			{0,0,1,1},
			{0,0,1,1}
		},{				//I
			{0,0,0,1},	
			{0,0,0,1},
			{0,0,0,1},
			{0,0,0,1}
		},{				//S
			{0,0,0,0},
			{0,0,0,0},
			{0,0,1,1},
			{0,1,1,0}
		},{				//Z
			{0,0,0,0},
			{0,0,0,0},
			{0,1,1,0},
			{0,0,1,1}
		},{				//L
			{0,0,0,0},
			{0,0,1,0},
			{0,0,1,0},
			{0,0,1,1}
		},{				//J
			{0,0,0,0},
			{0,0,0,1},
			{0,0,0,1},
			{0,0,1,1}
		},{				//T
			{0,0,0,0},
			{0,0,0,0},
			{0,1,1,1},
			{0,0,1,0}
		}
	};// types of the tetramino



void tetragentest();		// Create all possible variants of 
							// tetramino (including colors) and print it


void fieldgentest();		// Create new field, fill and print it and 



bool everything_is_fine();
							// Check is current tetramino 't'
							// position on the field 'f' correct


void tetrado();
/*
 * 			do something with tetramino 't' on the field 'f'
 * 	'l' - move tetramino left	
 * 	'r' - move tetramino right		
 * 	'R' - rotate tetramino
 * 	'd' - drop
*/


void put();
							// Check possibility and put 
							// tetramino 't' to the field 'f'
#endif
