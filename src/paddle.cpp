#include <cstdlib>
#include "actor.h"
#include "paddle.h"
#include "view.h"

Paddle::Paddle(double x, double y)
	: Actor(x, y, WIDTH, HEIGHT) {}

void Paddle::move_up(void) {
	y_speed = -0.50;
}

void Paddle::move_down(void) {
	y_speed = 0.50;
}

void Paddle::stop(void) {
	y_speed = 0;
}

void Paddle::reset(void) {
	y = View::SCREEN_HEIGHT / 2;
}

void Paddle::run(void) {
	y += y_speed;
	
	if (std::abs(y_speed) < 2) {
		if (y_speed < 0)
			y_speed -= .02;
		if (y_speed > 0)
			y_speed += .02;
	}
	
	if (y < 0) {
		y = 0;
		stop();
	}
	
	if (y + height > View::SCREEN_HEIGHT) {
		y = View::SCREEN_HEIGHT - height;
		stop();
	}
}
