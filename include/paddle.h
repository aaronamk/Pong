#ifndef PADDLE_H
#define PADDLE_H

#include "actor.h"

class Paddle : public Actor {
	public:
		Paddle(double x, double y);
		
		void move_up(void);
		
		void move_down(void);
		
		void stop(void);
		
		void reset(void);
		
		void run(void);
		
		static const int WIDTH = 7;
		
		static const int HEIGHT = 70;
};

#endif
