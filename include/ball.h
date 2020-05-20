#ifndef BALL_H
#define BALL_H

#include "actor.h"

class Ball : public Actor {
	private:
		double spin = 0;
	
	public:
	Ball(void);
       	
		double get_spin(void);
       	
		void bounce_up(void);
		
		void bounce_down(void);
		
		void bounce_right(double speed);
		
		void bounce_left(double speed);
		
		void reset(void);
		
		static const int RADIUS = 5;
};

#endif
