#include "view.h"

#include "actor.h"
#include "paddle.h"

View::View(Paddle& paddle) {
	this->paddle = &paddle;
}
