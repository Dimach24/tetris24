#include <SFML/Graphics.hpp>
#include <iostream>
using sf::RenderWindow;
using sf::VideoMode;
using sf::Event;
using sf::CircleShape;
using sf::ConvexShape;
using sf::Color;
using sf::RectangleShape;
using sf::Vector2f;
using sf::Texture;
using sf::Image;
using sf::Sprite;
int main(){
	RenderWindow w(VideoMode(600,600),"Test#1.");
	w.clear(Color(255,255,255,255));
	//sf::ContextSettings settings;

	
	CircleShape c{40.};
	{//Circle
		c.setFillColor(Color(255,0,0,255));
		c.setOutlineColor(Color(0,0,0,255));
		c.setOutlineThickness(5);
		w.draw(c);
	}
	
	RectangleShape r{Vector2f(40,120)};
	{//Rectangle
		r.setFillColor(Color(0,255,0,255));
		r.setOutlineColor(Color(0,0,255,255));
		r.setOutlineThickness(5);
		r.setPosition(80,0);
		w.draw(r);
	}
	
	Texture t;
	if(!t.loadFromFile("./img/texture1.png"))
		return EXIT_FAILURE;
	Texture i;
	if (!i.loadFromFile("./img/img1.png"))
		return EXIT_FAILURE;
	t.setSmooth(true);
	i.setSmooth(true);
	CircleShape tr{100};
	{//Triangle
		tr.setPointCount(3);
		tr.rotate(60);
		tr.setOutlineColor(Color(0,0,0,255));
		tr.setOutlineThickness(5);
		tr.move(150,150);
		tr.setTexture(&t);
		w.draw(tr);
	}
	ConvexShape Sanya;
	{//Sanya
		Sanya.setPointCount(5);
		Sanya.setPoint(4,Vector2f(213,56));
		Sanya.setPoint(0,Vector2f(98,14));
		Sanya.setPoint(2,Vector2f(512,461));
		Sanya.setPoint(1,Vector2f(386,102));
		Sanya.setPoint(3,Vector2f(21,65));
		Sanya.setFillColor(Color(220,139,255,255));
		w.draw(Sanya);
	}
	Sprite spr;
	spr.setTexture(i);
	
	spr.setPosition(250,250);
	spr.setScale(5,5);
	w.draw(spr);
	while (w.isOpen()){
		w.display();
		Event e;
		while(w.pollEvent(e)){
			if (e.type==Event::Closed){
				w.close();
			}
		}
	w.display();
	}
	return EXIT_SUCCESS;
}
