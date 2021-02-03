#include "tetfoo.hpp"
#include <iostream>

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
};

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
			for (uint8_t rotations=0; rotations<4; rotations++){
				T.rotate();
				T.print();
			}
		}
	}
	
}

bool everything_is_fine(Tetramino* t, Field* f){
		if (DBG1){return true;}
		uint8_t globali, globalj;
		for (uint8_t i=0; i<4;i++){
			for (uint8_t j=0; j<4;j++){
				globali=t->i+i;
				globalj=t->j+j;
				if (t->dot[i][j] && (globali>=20 || globalj>=10)){	//outside the field
					return false;
				}
				if (t->dot[i][j] && f->dot[globali][globalj]){		//intersection with field
					return false;
				}
			}
		}
		return true;	//No intersections, tetramino in the field
}
void tetrado(uint8_t cmd, Tetramino* t, Field* f){
	/*
	 * 	do something
	 * 	'l' - move tetramino left	
	 * 	'r' - move tetramino right		
	 * 	'R' - rotate tetramino
	 * 	'd' - drop
	*/
	Tetramino R=*t;
	Tetramino* r=&R;
	switch(cmd){					//cmd manager
		case 'l':
			R.j--;		//moving R left
			break;
		case 'r':
			R.j++;		//moving R right
			break;
		case 'R':
			R.rotate();	//Hmmm... And yet it turns
			break;
		case 'd':
			while (everything_is_fine(r,f)){	//moving it down
				R.i++;							//and down
			}
			R.i--;								//one jump and...
			break;
		default:
			throw "Incorrect command";
	}
	if (everything_is_fine(r,f)){	//OK, that's fine
		*t=R;
		return;
	} else {						//OK, that's not fine
		return;
	}
}
void put(Tetramino* t, Field* f){	
	uint8_t globali, globalj;
		for (uint8_t i=0; i<4;i++){
			for (uint8_t j=0; j<4;j++){
				globali=t->i+i;
				globalj=t->j+j;
				if (t->dot[i][j] && (globali>=20 || globalj>=10)){	//outside the field
					throw "Sorry, master, but i can't place this tetramino here";;
				}
				if (t->dot[i][j] && f->dot[globali][globalj]){		//intersection with field
					throw "Sorry, master, but i can't place this tetramino here";
				}
				if (t->dot[i][j]){				//only if [i][j] exists
					f->dot[globali][globalj]=t->dot[i][j];
				}
			}
		}
}

