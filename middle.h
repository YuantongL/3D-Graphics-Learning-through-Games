#pragma once

class middle
{
public:
	middle();

	void drawall();
	void mouseevent();
	void mouseevent_passive();
	void mouseevent_motion();
	void init();
	void middle_idle();
	void keyboardevent(unsigned char a);
	void specialevent(GLint a);

	bool left_mouse_down;
	bool right_mouse_down;

	GLfloat mouseposition_x;
	GLfloat mouseposition_y;
	GLfloat mouseposition_x_pre;
	GLfloat mouseposition_y_pre;

	float posx;		//鼠标在世界坐标位置
	float posy;

	int gameon;   //0=UI, 1=BALLS, 2=Puzzle
	int gamereallyon;
};

