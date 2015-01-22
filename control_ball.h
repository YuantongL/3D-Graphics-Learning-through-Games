#pragma once
#include "ball.h"
#include "facilities.h"

class control_ball
{
public:
	control_ball();

	void control_ball_drawall();		//把所有东西都画出来
	void control_ball_mouseevent();	//用来处理鼠标事件
	void control_ball_idle();
	void control_ball_init();
	void control_ball_mouseevent_passive();
	void control_ball_mouseevent_motion();

	int control_ball_gameon;

	bool control_ball_left_mouse_down;
	GLint control_ball_mouseposition_x;
	GLint control_ball_mouseposition_y;
};

