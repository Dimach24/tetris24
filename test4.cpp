#include <SFML/Graphics.hpp>
#include <iostream>
bool tetratypes[7][4][4]=
	{
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
	};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Tetramino{
	uint8_t i,j;
	uint8_t dot[4][4];
	char type;
	Tetramino(uint8_t type, uint8_t color){
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
};


void tetragentest();
void fieldgentest();

int main(){
	srand(24);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	return EXIT_SUCCESS;
}
void fieldgentest(){
	Field F;
	for (uint8_t i=0; i<20; i++){
			for (uint8_t j=0; j<10; j++){
				F.dot[i][j]=rand()%9;
			}
	}
	F.print();
}
void tetragentest(){
	for (uint8_t type=0; type<7; type++){
		for (uint8_t color=1; color<9; color++){
			Tetramino T(type, color);
			T.print();
		}
	}
	
}
