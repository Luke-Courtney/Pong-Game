#include "Box.h"

// This the constructor and it is called when we create an object
Box::Box(float startX, float startY)
{
	m_Position.x = startX;
	m_Position.y = startY;

	m_Shape.setSize(sf::Vector2f(50, 50));
	m_Shape.setPosition(m_Position);

	m_Shape.setFillColor(Color::Cyan);
}

FloatRect Box::getPosition()
{
	return m_Shape.getGlobalBounds();
}

float Box::getX()
{
	return m_Position.x;
}

float Box::getY()
{
	return m_Position.y;
}

void Box::remove()
{
	m_Shape.setSize(sf::Vector2f(0, 0));
}

RectangleShape Box::getShape()
{
	return m_Shape;
}

void Box::collide()
{
	//shouldDraw = true;
}


