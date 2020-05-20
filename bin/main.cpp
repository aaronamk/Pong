#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <ctime>

#include "actor.h"
#include "paddle.h"
#include "ball.h"
#include "view.h"
#include "player_view.h"
#include "ai_view.h"

bool running = false;

sf::Font arial;

// create actor list
std::vector<Actor*> actor_list;

Paddle left_paddle(50, View::SCREEN_HEIGHT / 2);
Paddle right_paddle(View::SCREEN_WIDTH - 50, View::SCREEN_HEIGHT / 2);

int left_score = 0;
int right_score = 0;
sf::Text text;
sf::Text winner;

sf::SoundBuffer hit;
sf::Sound hit_sound;

Ball ball;
PlayerView player_view(left_paddle);
AIView ai_view(right_paddle);

//setup
void init() {
	//load font
	arial.loadFromFile("../include/arial.ttf");
	text.setFont(arial);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(30);
	
	winner.setFont(arial);
	winner.setCharacterSize(50);
	winner.setPosition(200, 0);
	
	//load audio
	hit.loadFromFile("../include/arrow_x.wav");
	hit_sound.setBuffer(hit);
	
	actor_list.push_back(&left_paddle);
	actor_list.push_back(&right_paddle);
	actor_list.push_back(&ball);
}

//when someone scores
void next_round() {
	for (int i = 0; i < actor_list.size(); i++)
		actor_list[i]->reset();
}

//new game
void restart() {
	winner.setString("");
	left_score = right_score = 0;
	next_round();
	running = false;
}

int main() {
	init();
	// start main loop
	while (player_view.Game.isOpen()) {
		//float time = clock.restart().asSeconds();
		
		// process events
		sf::Event event;
		
		while (player_view.Game.pollEvent(event)) {
			// Exit
			if (event.type == sf::Event::Closed)
				player_view.Game.close();
			
			if (event.type == sf::Event::LostFocus) {
				running = false;
			}

			if (event.type == sf::Event::GainedFocus) {
				running = true;
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape)
					running = !running;
				else
					player_view.key_pressed(event);
			}
			if (event.type == sf::Event::KeyReleased) {
				player_view.key_released(event);
			}
		}
		if (running) {
			for (int i = 0; i < actor_list.size(); i++)
				actor_list[i]->run();
			
			if (ball.get_x() + 2 * Ball::RADIUS < 0) {
				right_score++;
				next_round();
			}
			
			if (ball.get_x() > View::SCREEN_WIDTH) {
				left_score++;
				next_round();
			}
			
			//check for ball bounces
			if (ball.get_y() + 2 * Ball::RADIUS > View::SCREEN_HEIGHT) {
				ball.bounce_up();
			}
			if (ball.get_y() < 0) {
				ball.bounce_down();
			}
			
			if (std::abs(ball.get_x() - left_paddle.get_x() - Paddle::WIDTH) < 2
			&& ball.get_y() < left_paddle.get_y() + Paddle::HEIGHT
			&& ball.get_y() + (2 * Ball::RADIUS) > left_paddle.get_y()) {
				ball.bounce_right(left_paddle.get_y_speed());
				hit_sound.play();
			}
			if (std::abs(ball.get_x() + (Ball::RADIUS * 2) - right_paddle.get_x()) < 2
			&& ball.get_y() < right_paddle.get_y() + Paddle::HEIGHT
			&& ball.get_y() + (2 * Ball::RADIUS) > right_paddle.get_y()) {
				ball.bounce_left(right_paddle.get_y_speed());
				hit_sound.play();
			}
				
		}
		
		//check for win
		if (left_score == 11) {
			winner.setFillColor(sf::Color::Green);
			winner.setString("YOU WIN");
		}
		if (right_score == 11) {
			winner.setFillColor(sf::Color::Red);
			winner.setString("YOU LOSE");
		}
		
		// clear screen and fill with black
		player_view.Game.clear(sf::Color::Black);
		
		//draw score
		text.setString(std::to_string(left_score) + " : " + std::to_string(right_score));
		
		player_view.Game.draw(text);
		player_view.Game.draw(winner);
		
		//run views
		player_view.run(right_paddle.get_x(), right_paddle.get_y(), ball.get_x(), ball.get_y(), ball.get_spin());
		ai_view.run(left_paddle.get_x(), left_paddle.get_y(), ball.get_x(), ball.get_y(), ball.get_spin());
		
		//wait to show who won, then restart
		if (left_score == 11 || right_score == 11) {
			sf::sleep(sf::milliseconds(3000));
			restart();
		}
	}
	
	// Done.
	return 0;
}
