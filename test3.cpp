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

struct Field{
	uint8_t dots[20][10];
	Field(){
		this->clear();
	}
	void clear(){
		for (uint8_t i=0; i<20; i++)
			for (uint8_t j=0; j<10; j++)
				this->dots[i][j]=(uint8_t)0;	
	}
	void print(){
		for (uint8_t i=0; i<20; i++){
			for (uint8_t j=0; j<10; j++){
				std::cout<<(int)this->dots[i][j]<<' ';
			}
			std::cout<<'\n';
		}
	}
};

struct Tetramino{
	uint8_t dots[4][4];
	uint8_t i, j;
	
	Tetramino(uint8_t type, uint8_t color){
		this->i=0;
		this->j=5;
		for(uint8_t i=0; i<4; i++)
			for(uint8_t j=0; j<4; j++)
				this->dots[i][j]=tetratypes[type][i][j]*color;
	}
	
	void rotate(Field* field){//FIXME
		uint8_t res[4][4];
		for (uint8_t i=0; i<4;i++){
			for (uint8_t j=0; j<4;j++){
				res[j][3-i]=this->dots[i][j];
			}
		}
		if (this->is_invalid(res, field)){
			return;
		}
		for (uint8_t i=0; i<4;i++){
			for (uint8_t j=0; j<4;i++){
				this->dots[i][j]=res[i][j];
			}
		}
		return;
	}
	void print(){
		for(uint8_t i=0; i<4; i++){
			for(uint8_t j=0; j<4; j++){
				std::cout<<(int)this->dots[i][j]<<' ';
			}
			std::cout<<'\n';
		}
	}
	void placeto(Field* field){
		for(uint8_t i=0; i<4; i++){
			for(uint8_t j=0; j<4; j++){
				if(this->dots[i][j] && (field->dots[this->i-3+i][this->j-3+j] || this->i-3+i>19 || this->j-3+j>9)){throw -1;}
				else {field->dots[this->i-3+i][this->j-3+j]=this->dots[i][j];}
			}
		}
	}
	private:
	bool is_invalid(uint8_t res[4][4], Field* field){
		for (uint8_t i=0; i<4; i++){
			for (uint8_t j=0; j<4; j++){
				if (this->dots[i][j] && (this->i-3+i>19 || this->j-3+j >9 ||field->dots[this->i-3+i][this->j-3+j])){												
					return true;
				}
			}
		}
		return false;
	}
};
int main(){
	Field F;
	Field *f=&F;
	Tetramino T(5,3);
	Tetramino* t=&T;
	t->i=2;
	t->rotate(f);
	t->placeto(f);
	f->print();
	return EXIT_SUCCESS;
};
/*
 * Нужно еще подумать над системой функций, проверкой и тем, в какой момент она происходит.
 * Почему-то не работает rotate
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * /
