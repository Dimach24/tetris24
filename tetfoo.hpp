#include <iostream>
#ifndef tetfoo
#define tetfoo 1
constexpr bool DBG1=false;

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

typedef unsigned char uint8_t;

struct Tetramino{
	uint8_t i,j;
	uint8_t dot[4][4];
	char type;
	Tetramino(uint8_t type, uint8_t color){
		this->reset(type, color);
	}
	void reset(uint8_t type, uint8_t color){
		switch(type){
			case 0:
				this->type='O';
				break;
			case 1:
				this->type='I';
				break;
			case 2:
				this->type='S';
				break;
			case 3:
				this->type='Z';
				break;
			case 4:
				this->type='L';
				break;
			case 5:
				this->type='J';
				break;
			case 6:
				this->type='T';
				break;
			default:
				throw "Incorrect type";
		}
		for (uint8_t i=0; i<4; i++)
			for (uint8_t j=0; j<4; j++)
				this->dot[i][j]=tetratypes[type][i][j]? color:0;
		this->i=0;
		this->j=0;
	}
	void print(){
		std::cout<<"Tetramino '"<<type<<"' at "<<(int)this->i<<", "<<(int)this->j<<" printing:\n";
		for (uint8_t i=0; i<4; i++){
			for (uint8_t j=0; j<4; j++){
				if (this->dot[i][j]!=8){
					std::cout<<"\033["<<(int)(40+this->dot[i][j])<<"m   ";
				} else {
					std::cout<<"\033[40m * ";
				}
				//std::cout<<(int)this->dot[i][j];
			}
			std::cout<<"\033[m\n";
		}
		std::cout<<"\033[34;41;1m     END    \033[m\n";				
	}
	void rotate(){
		uint8_t res[4][4];
		for (uint8_t i=0; i<4;i++){
			for (uint8_t j=0; j<4;j++){
				res[j][3-i]=this->dot[i][j];
			}
		}
		for (uint8_t i=0; i<4;i++){
			for (uint8_t j=0; j<4;j++){
				this->dot[i][j]=res[i][j];
			}
		}
	}
};

struct Field{
	uint8_t dot[20][10];
	Field(){
		this->clear();
	}
	void clear(){
		for (uint8_t i=0;i<20;i++)
			for (uint8_t j=0;j<10;j++)
			this->dot[i][j]=0;
	}
	void print(){
		std::cout<<"Field printing:\n";
		for (uint8_t i=0; i<20; i++){
			for (uint8_t j=0; j<10; j++){
				if (this->dot[i][j]!=8){
					std::cout<<"\033["<<(int)(40+this->dot[i][j])<<"m   ";
				} else {
					std::cout<<"\033[40m * ";
				}
				//std::cout<<(int)this->dot[i][j];
			}
			std::cout<<"\033[m\n";
		}
		std::cout<<"\033[34;41;1m     END    \033[m\n";				
	}
	uint16_t update(){
		uint16_t result;
		for (uint8_t i=0; i<20; i++){
			bool is_full=true;
			for (uint8_t j=0; j<10; j++){
				if (!this->dot[i][j]){
					is_full=false;
					break;
				}
			}
			if (is_full){
				result++;
				for (uint8_t j=0; j<10; j++){
					this->dot[i][j]=0;
				}
				
			}
		}
		this->drop();
		return result;
	}
	void drop(){
		bool its_correct=false;
		while (!its_correct){
			bool firstline=true;
			its_correct=true;
			for (uint8_t i=1; i<20; i++){;
				bool line_is_empty=true;
				for (uint8_t j=0; j<10; j++){
					if (this->dot[i][j]){
						line_is_empty=false;
						break;
					}
				}
				if (line_is_empty && !firstline){
					its_correct=false;
					for (uint8_t j=0; j<10; j++){
						this->dot[i][j]=this->dot[i-1][j];
						this->dot[i-1][j]=0;
					}
					break;
				}
				firstline=firstline&&line_is_empty;
			}
		}
	}
};





void tetragentest();		// Create all possible variants of 
							// tetramino (including colors) and print it


void fieldgentest();		// Create new field, fill and print it and 


bool everything_is_fine(Tetramino* t, Field* f);
							// Check is current tetramino 't'
							// position on the field 'f' correct


void tetrado(uint8_t cmd, Tetramino* t, Field* f);
/*
 * 			do something with tetramino 't' on the field 'f'
 * 	'l' - move tetramino left	
 * 	'r' - move tetramino right		
 * 	'R' - rotate tetramino
 * 	'd' - drop
*/

bool movedown(Tetramino* t, Field* f);



void put(Tetramino* t, Field* f);
							// Check possibility and put 
							// tetramino 't' to the field 'f'
#endif
