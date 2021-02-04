#include "tetfoo.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>


constexpr uint16_t xoffset = 15;
constexpr uint16_t yoffset = 25;

sf::Sprite sprite;
sf::RenderWindow window;

void drawfield(Field* f){
	for(uint8_t i=0; i<20; i++){
		for(uint8_t j=0; j<10; j++){
			uint8_t c = f->dot[i][j];
			if (c){
				sprite.setTextureRect(sf::IntRect(18*(c-1),0,18,18));
				sprite.setPosition(xoffset+j*18,yoffset+i*18);
				window.draw(sprite);
			}
		}
	}
}

void drawtetra(Tetramino* t){
	for(uint8_t i=0; i<4; i++){
		for(uint8_t j=0; j<4; j++){
			uint8_t c = t->dot[i][j];
			uint8_t gi=t->i+i;
			uint8_t gj=t->j+j;
			if (c){
				sprite.setTextureRect(sf::IntRect(18*(c-1),0,18,18));
				sprite.setPosition(xoffset+gj*18,yoffset+gi*18);
				window.draw(sprite);
			}
		}
	}
}

uint8_t lowerdot(Tetramino* t){
	uint8_t res = 0;
	for(uint8_t i=0; i<4; i++){
		for(uint8_t j=0; j<4; j++){
			if (t->dot[i][j]){
				res=i;
			}
		}
	}
	return res;
}

bool game_tick(Field* f, Tetramino* c, Tetramino* n){
	if (movedown(c,f)){
		if (lowerdot(c)+c->i==3){
			return true;
		}
		*c=*n;
		c->j=3;
		n->reset(rand()%7, rand()%8+1);
		n->j = 12;
		f->update();
	}
	return false;
}



int main(){
	srand(time(0));
	Field F;
	Tetramino current(rand()%7, rand()%8+1), next(rand()%7, rand()%8+1);
	next.j=12;
	sf::Texture blocks;
	if(!blocks.loadFromFile("./img/blocks.png"))
		return EXIT_FAILURE;
	sprite.setTexture(blocks);
	window.create(sf::VideoMode(320,400), "Tetris24");
	uint64_t past, now;
	past=now=clock() / CLOCKS_PER_SEC;
	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
				if (event.type==sf::Event::Closed){
					window.close();
				}
				if (event.type==sf::Event::KeyPressed){
					if(event.key.code==sf::Keyboard::J){
						tetrado('l', &current, &F);
					}
					if(event.key.code==sf::Keyboard::K){
						tetrado('R', &current, &F);
					}
					if(event.key.code==sf::Keyboard::L){
						tetrado('r', &current, &F);
					}
					if(event.key.code==sf::Keyboard::Space){
						tetrado('d', &current, &F);
					}
				}
				
			}
		now=clock() / CLOCKS_PER_SEC;
		if (now>past){
			//std::cout<<"Clock!"<<now<<"\n";
			past=now;
			if (game_tick(&F,&current,&next)){
				window.close();
			}
		}
		window.clear(sf::Color(217,217,217,255));
		drawfield(&F);
		drawtetra(&next);
		drawtetra(&current);
		window.display();
	}
	
	return EXIT_SUCCESS;
}
