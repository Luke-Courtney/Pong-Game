#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Box
{
private:
	Vector2f m_Position;
	RectangleShape m_Shape;

	float m_Speed = 1000.0f;
	float m_DirectionX = .2f;
	float m_DirectionY = .2f;

	

public:
	bool shouldDraw = true;


	Box(float startX, float startY);

	FloatRect getPosition();

	RectangleShape getShape();

	void collide();

	float getX();

	float getY();

	void remove();

	//Other method bits go here
};
