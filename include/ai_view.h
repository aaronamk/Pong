#ifndef AI_VIEW_H
#define AI_VIEW_H

#include "actor.h"
#include "paddle.h"
#include "ball.h"
#include "view.h"

class AIView : public View {
	private:
		bool check = true;

	public:
		AIView(Paddle& paddle);
		
		void run(double player_x, double player_y, double ball_x, double ball_y, double spin);
};

#endif
