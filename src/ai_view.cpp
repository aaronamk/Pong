#include "view.h"
#include "ai_view.h"

#include "actor.h"
#include "paddle.h"
#include "ball.h"

AIView::AIView(Paddle& paddle) : View(paddle) {}

void AIView::run(double player_x, double player_y, double ball_x, double ball_y, double spin) {
	if (check && paddle->get_y() > ball_y) {
		check = false;
		paddle->move_up();
	}
		
	if (!check && paddle->get_y() < ball_y) {
		check = true;
		paddle->move_down();	
	}
}
