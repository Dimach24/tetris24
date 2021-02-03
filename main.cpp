#include "tetfoo.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>


constexpr uint16_t xoffset = 25;
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


int main(){
	srand(65);
	Field F;
	Tetramino current(0,0), next(0,0);
	
	sf::Texture blocks;
	if(!blocks.loadFromFile("./img/blocks.png"))
		return EXIT_FAILURE;
	sprite.setTexture(blocks);
	window.create(sf::VideoMode(320,480), "Tetris24");
	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
				if (event.type==sf::Event::Closed){
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
