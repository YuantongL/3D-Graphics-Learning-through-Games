#pragma once
#include "ball.h"
#include "facilities.h"

class endless_control_ball
{
public:
	endless_control_ball();

	void endless_control_ball_drawall();		//�����ж�����������
	void endless_control_ball_mouseevent();	//������������¼�
	void endless_control_ball_idle();
	void endless_control_ball_init();
	void endless_control_ball_mouseevent_passive();
	void endless_control_ball_mouseevent_motion();

	void endless_control_ball_randballcolor();

	int endless_control_ball_gameon;

	bool endless_control_ball_left_mouse_down;
	GLint endless_control_ball_mouseposition_x;
	GLint endless_control_ball_mouseposition_y;
};

