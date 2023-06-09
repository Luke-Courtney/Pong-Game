// Pong.cpp : Defines the entry point for the console application.
//

#include "Bat.h"
#include "Ball.h"
#include "Box.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <math.h>


int main()
{
	// Create a video mode object
	VideoMode vm(1650, 1050);

	// Create and open a window for the game

	RenderWindow window(vm, "Pong", Style::Fullscreen);


	int score = 0;
	int lives = 3;

	// Create a bat
	Bat bat(1650 / 2, 1050 - 20);

	//Creating boxes using array
	int targetX = 100;
	Box boxes[] = {Box(targetX, 100),Box(targetX * 2, 100),Box(targetX * 3,100),Box(targetX * 4,100),Box(targetX * 5,100),Box(targetX * 6,100),Box(targetX * 7, 100),Box(targetX * 8, 100),Box(targetX * 9,100),Box(targetX * 10,100),Box(targetX * 11,100),Box(targetX * 12,100),Box(targetX * 13,100),Box(targetX * 14,100),Box(targetX * 15,100),
				   Box(targetX, 200),Box(targetX * 2, 200),Box(targetX * 3,200),Box(targetX * 4,200),Box(targetX * 5,200),Box(targetX * 6,200),Box(targetX * 7, 200),Box(targetX * 8, 200),Box(targetX * 9,200),Box(targetX * 10,200),Box(targetX * 11,200),Box(targetX * 12,200),Box(targetX * 13,200),Box(targetX * 14,200),Box(targetX * 15,200),
				   Box(targetX, 300),Box(targetX * 2, 300),Box(targetX * 3,300),Box(targetX * 4,300),Box(targetX * 5,300),Box(targetX * 6,300),Box(targetX * 7, 300),Box(targetX * 8, 300),Box(targetX * 9,300),Box(targetX * 10,300),Box(targetX * 11,300),Box(targetX * 12,300),Box(targetX * 13,300),Box(targetX * 14,300),Box(targetX * 15,300) };
	int targetNum = 45;//Number of Boxes

	// We will add a ball in the next chapter
	Ball ball(1650 / 2, 0);

	// Create a Text object called HUD
	Text hud;

	// A cool retro-style font
	Font font;
	font.loadFromFile("fonts/DS-DIGI.TTF");

	// Set the font to our retro-style
	hud.setFont(font);

	// Make it nice and big
	hud.setCharacterSize(75);

	// Choose a color
	hud.setFillColor(Color::White);

	hud.setPosition(20, 20);

	// Here is our clock for timing everything
	Clock clock;

	while (window.isOpen())
	{
		/*
		Handle the player input
		*********************************************************************
		*********************************************************************
		*********************************************************************
		*/

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				// Quit the game when the window is closed
				window.close();

		}

		// Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Handle the pressing and releasing of the arrow keys
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			bat.moveLeft();
		}
		else
		{
			bat.stopLeft();
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			bat.moveRight();
		}
		else
		{
			bat.stopRight();
		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			ball.unStuck();
		}

		/*
		Update the bat, the ball and the HUD
		*********************************************************************
		*********************************************************************
		*********************************************************************
		*/
		// Update the delta time
		Time dt = clock.restart();
		bat.update(dt);
		ball.update(dt);
		// Update the HUD text
		std::stringstream ss;

		//Checking for max score
		if (score > 44)
		{
			ss << "Score:" << score << "    Lives:" << lives << "       All boxes destroyed -  You Win!";
			for (int i = 0; i < 9999; i++)
			{
				ball.setX();
				ball.setY();
			}
		}
		else if (lives < 1)
		{
			ss << "Score:" << score << "    Lives:" << lives << "       Out of lives -  You Lose!";
			for(int i = 0; i<9999; i++)
			{
				ball.setX();
				ball.setY();
			}
		}
		else {
			ss << "Score:" << score << "    Lives:" << lives;
		}
		
		hud.setString(ss.str());


		// Handle ball hitting the bottom
		if (ball.getPosition().top > window.getSize().y)
		{
			// reverse the ball direction
			ball.reboundBottom();
			// Remove a life
			lives--;
		}

		// Handle ball hitting top
		if (ball.getPosition().top < 0)
		{
			ball.reboundBatOrTop();

		}

		// Handle ball hitting sides
		if (ball.getPosition().left < 0 ||
			ball.getPosition().left + 10 > window.getSize().x)
		{
			ball.reboundSides();
		}

		// Has the ball hit the bat?
		if (ball.getPosition().intersects(bat.getPosition()))
		{
			// Hit detected so reverse the ball and score a point
			ball.reboundBatOrTop();
		}


		//Hitting box

		for (int i = 0; i < targetNum; i++)
		{

			if (ball.getPosition().intersects(boxes[i].getPosition()))
			{

				//Finds midpoint of boxes
				float boxMidX = boxes[i].getX() + 25;
				float boxMidY = boxes[i].getY() + 25;

				float XDistance;
				float YDistance;

				//Finds difference between ballX and Y and box mid X and Y
				if (ball.getX() > boxMidX)
				{
					XDistance = boxMidX - ball.getX();
				}
				else
				{
					XDistance = ball.getX() - boxMidX;
				}

				if (ball.getY() > boxMidY)
				{
					YDistance = boxMidY - ball.getY();
				}
				else
				{
					YDistance = ball.getY() - boxMidY;
				}

				//Seeing if YDistance or XDistance is bigger.
				//Lower number means less distance from midpoint.
				//If the ball bounces off the side, YDistance will be smaller, as it can only go as low as the top or bottom of the shape on a top or bottom hit
				//Vice Versa for XDistance
				if (XDistance == YDistance)
				{
					//Ball bounced of corner
					ball.reboundBatOrTop();
					ball.reboundSides();

				}else if(XDistance > YDistance)
				{
					//Ball bounced off top or bottom
					ball.reboundBatOrTop();
				}
				else
				{
					//Ball bounced off side
					ball.reboundSides();
				}

				//remove box
				boxes[i].remove();

				// Add a point to the players score
				score++;

			}


			//Draw the bat, the ball and the HUD
			window.clear();
			window.draw(hud);
			window.draw(bat.getShape());
			window.draw(ball.getShape());
			for (int i = 0; i < targetNum; i++) //Using targetNum value to set loop length as sizeOf(boxes) causes an error
			{
				window.draw(boxes[i].getShape());//Drawing objects from Boxes array
			}
			window.display();
		}
	}
	return 0;
}

