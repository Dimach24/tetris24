#include <SFML/Graphics.hpp>
#include <iostream>
using sf::Color;
using sf::Sprite;
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

uint8_t field[20][10];			//0 if there is nothing or color [1;8]
uint8_t tetramino[4][4];		// -||- current tetramino
uint8_t tetraminoi=0, tetraminoj=0;	//current tetramino position (left bottom corner)
constexpr uint16_t I_OFFSET=25, J_OFFSET=25;  //field offset
void rotate(){
	uint8_t res[4][4];
	for (uint8_t i=0; i<4;i++){
		for (uint8_t j=0; j<4;j++){
			if (!field[tetraminoi-i][tetraminoj-j]){return;}
			res[j][3-i]=tetramino[i][j];
		}
	}
	for (uint8_t i=0; i<4;i++){
		for (uint8_t j=0; j<4;i++){
			tetramino[i][j]=res[i][j];
		}
	}
	return;
}
void left(){
	for (uint8_t i=0; i<4;i++){
		for (uint8_t j=0; j<4;j++){
			if (tetramino[i][j] && (tetraminoj-j==0 or field[tetraminoi-i][tetraminoj-j-1])){return;}
		}
	}
	tetraminoj--;
}
void right(){
	for (uint8_t i=0; i<4;i++){
		for (uint8_t j=0; j<4;j++){
			if (tetramino[i][j] && (tetraminoj-j>=10 or field[tetraminoi-i][tetraminoj-j+1])){return;}
		}
	}
	tetraminoj++;
}
void drop(){}//TODO
void drawtetracur(){}
/*void setsprite(uint8_t color, Sprite& s){
	s.setTextureRect(sf::IntRect(color*18,0,18,18));
	return;
}*/
int main(){
	sf::RenderWindow win(sf::VideoMode(320, 480), "My First Game With SFML on C++!");
	sf::Texture blocks;
	if(!blocks.loadFromFile("./img/blocks.png"))
		return EXIT_FAILURE;
	for (uint8_t i=0; i<20; i++)
		for (uint8_t j=0; j<10; j++)
			field[i][j]=rand()%8+1;
	Sprite sprt;
	sprt.setTexture(blocks);
	
	while (win.isOpen()){
		sf::Event event;
		while (win.pollEvent(event)){
			if (event.type==sf::Event::Closed){
				win.close();
			}
			if (event.type==sf::Event::KeyPressed){
				if (event.key.code==sf::Keyboard::J){left();}
				if (event.key.code==sf::Keyboard::L){right();}
				if (event.key.code==sf::Keyboard::K){rotate();}
				if (event.key.code==sf::Keyboard::Space){drop();}
			}
		}
		
	for (uint8_t i=0; i<20;i++){
		for (uint8_t j=0; j<10;j++){
			if (field[i][j]){
				sprt.setTextureRect(sf::IntRect((field[i][j]-1)*18,0,18,18));
				sprt.setPosition(j*18+J_OFFSET,i*18 + I_OFFSET);
				win.draw(sprt);
			}
		}
	}
	/*for (uint8_t i=0; i<4;i++){
		for (uint8_t j=0; i<4;j++){
			if (tetramino[i][j]){
				sprt.setTextureRect(sf::IntRect(tetramino[i][j]*18,0,18,18));
				sprt.setPosition((tetraminoi-i)*18+6,(tetraminoj-j)*18+7);
				win.draw(sprt);
			}
		}
	}*/	
	win.display();
	win.clear(Color(223,223,223,255));
	}
	return EXIT_SUCCESS;
}
