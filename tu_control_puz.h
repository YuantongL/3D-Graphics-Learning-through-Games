#pragma once
#include "piece.h"
#include "facilities.h"

class tu_control_puz
{
public:
	tu_control_puz();

	void tu_control_puz_drawall();		//把所有东西都画出来
	void tu_control_puz_mouseevent();	//用来处理鼠标事件
	void tu_control_puz_mouseevent_passive();
	void tu_control_puz_mouseevent_motion();
	void tu_control_puz_init();
	void tu_control_puz_idle();
	void tu_control_puz_randblock();

	bool tu_control_puz_left_mouse_down;
	bool tu_control_puz_right_mouse_down;
	bool tu_control_puz_rotate_on;
	int tu_control_puz_rotate_num;		//第几个球正在旋转
	int tu_control_puz_tran_num;		//第几个球正在拖拽
	GLfloat tu_control_puz_mouseposition_x;
	GLfloat tu_control_puz_mouseposition_y;
	GLfloat tu_control_puz_mouseposition_x_pre;
	GLfloat tu_control_puz_mouseposition_y_pre;

	float tu_control_puz_posx;
	float tu_control_puz_posy;

	int tu_control_puz_gameon;
};

