#ifndef PLAYER_VIEW_H
#define PLAYER_VIEW_H

#include <vector>
#include <SFML/Graphics.hpp>

#include "view.h"

#include "actor.h"
#include "paddle.h"

class PlayerView : public View {
	private:
		std::vector<sf::Shape*> draw_list;
		sf::RectangleShape player_paddle, ai_paddle, ball_line;
		sf::CircleShape ball;

	public:
		PlayerView(Paddle& paddle);
		
		sf::RenderWindow Game;
		
		void run(double ai_x, double ai_y, double ball_x, double ball_y, double spin);
		
		void key_pressed(sf::Event event);
		
		void key_released(sf::Event event);
};

#endif
