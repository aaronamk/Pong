#include "actor.h"
#include "ball.h"
#include "view.h"

Ball::Ball()
	: Actor(View::SCREEN_WIDTH / 2 - RADIUS, View::SCREEN_HEIGHT / 2 - RADIUS, RADIUS, RADIUS) {
	x_speed = -1.5;
	y_speed = 1.8;
}

double Ball::get_spin(void) {
	return spin;
}

void Ball::bounce_up(void) {
	y_speed *= -1;
	x_speed += spin / 10;
	spin /= 2;
}

void Ball::bounce_down(void) {
	y_speed *= -1;
	x_speed -= spin / 10;
	spin /= 2;
}

void Ball::bounce_right(double speed) {
	x_speed *= -1;
	y_speed -= spin / 10;
	spin /= 2;
	spin -= speed * 3;
}

void Ball::bounce_left(double speed) {
	x_speed *= -1;
	y_speed -= spin / 10;
	spin /= 2;
	spin += speed * 3;
}

void Ball::reset(void) {
	x = View::SCREEN_WIDTH / 2 - RADIUS;
	y = View::SCREEN_HEIGHT / 2 - RADIUS;
	x_speed = -1.5;
	y_speed = 2;
	spin = 0;
}
