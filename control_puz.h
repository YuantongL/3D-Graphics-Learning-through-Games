#pragma once
#include "piece.h"
#include "facilities.h"

class control_puz
{
public:
	control_puz();

	void control_puz_drawall();		//把所有东西都画出来
	void control_puz_mouseevent();	//用来处理鼠标事件
	void control_puz_mouseevent_passive();
	void control_puz_mouseevent_motion();
	void control_puz_init();
	void control_puz_idle();
	void control_puz_randblock();

	bool control_puz_left_mouse_down;
	bool control_puz_right_mouse_down;
	bool control_puz_rotate_on;
	int control_puz_rotate_num;		//第几个球正在旋转
	int control_puz_tran_num;		//第几个球正在拖拽
	GLfloat control_puz_mouseposition_x;
	GLfloat control_puz_mouseposition_y;
	GLfloat control_puz_mouseposition_x_pre;
	GLfloat control_puz_mouseposition_y_pre;

	float control_puz_posx;
	float control_puz_posy;

	int control_puz_gameon;
};

