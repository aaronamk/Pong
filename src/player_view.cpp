#include <SFML/Graphics.hpp>

#include "view.h"
#include "player_view.h"

#include "actor.h"
#include "paddle.h"
#include "ball.h"

PlayerView::PlayerView(Paddle& paddle)
	: View(paddle) {
	
	// create main window
	Game.create(sf::VideoMode(View::SCREEN_WIDTH, View::SCREEN_HEIGHT, 32), "Pong!", sf::Style::Titlebar | sf::Style::Close);
	Game.setFramerateLimit(120);
	Game.setKeyRepeatEnabled(false);
	
	player_paddle.setSize(sf::Vector2f(Paddle::WIDTH, Paddle::HEIGHT));
	draw_list.push_back(&player_paddle);
	
	ai_paddle.setSize(sf::Vector2f(Paddle::WIDTH, Paddle::HEIGHT));
	draw_list.push_back(&ai_paddle);
	
	ball.setRadius(Ball::RADIUS);
	draw_list.push_back(&ball);
	
	ball_line.setSize(sf::Vector2f(Ball::RADIUS * 2, 2));
	ball_line.setOrigin(Ball::RADIUS, 1);
	ball_line.setFillColor(sf::Color::Black);
}

void PlayerView::run(double ai_x, double ai_y, double ball_x, double ball_y, double spin) {
	player_paddle.setPosition(paddle->get_x(), paddle->get_y());
	
	ai_paddle.setPosition(ai_x, ai_y);
	
	ball.setPosition(ball_x, ball_y);
	
	ball_line.setPosition(ball_x + Ball::RADIUS, ball_y + Ball::RADIUS);
	ball_line.rotate(spin);
	
	for (int i = 0; i < draw_list.size(); i++) {
		draw_list[i]->setFillColor(sf::Color::White);
		Game.draw(*draw_list[i]);
	}
	Game.draw(ball_line);
	
	// display
	Game.display();
}

void PlayerView::key_pressed(sf::Event event) {
	if (event.key.code == sf::Keyboard::Up) {
		paddle->move_up();
	}
	
	if (event.key.code == sf::Keyboard::Down) {
		paddle->move_down();
	}
}

void PlayerView::key_released(sf::Event event) {
	if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down) {
		paddle->stop();
	}
}
