#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Ball
{
private:
	Vector2f m_Position;	
	RectangleShape m_Shape;

	float m_Speed = 1000.0f;
	float m_DirectionX = .2f;
	float m_DirectionY = .2f;

public:
	Ball(float startX, float startY);

	FloatRect getPosition();

	float getX();

	float getY();

	void setX();

	void setY();

	RectangleShape getShape();

	float getXVelocity();

	void freeze();

	void reboundSides();

	void reboundBatOrTop();

	void unStuck();

	void reboundBottom();

	void update(Time dt);

};
