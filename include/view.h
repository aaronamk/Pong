#ifndef VIEW_H
#define VIEW_H

#include "actor.h"
#include "paddle.h"

class View {
	protected:
		Paddle* paddle;
	public:
		View(Paddle& paddle);
		
		virtual void run(double enemy_x, double enemy_y, double ball_x, double ball_y, double spin) = 0;
		
		static const int SCREEN_WIDTH = 800;
		static const int SCREEN_HEIGHT = 600;
};

#endif
