#pragma once
#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glaux.h>

class ball
{
public:
	ball();
	ball(float position[3], int color, float radius, bool appear);		//���캯��
	void ball_drawself();
	void ball_turnsmall();
	void ball_turnbig();

	void click_small();
	void click_big();

	float ball_position[3];		//λ��

	int ball_color;
	int ball_level;
	float ball_r;
	bool ball_appear;		//�Ƿ���ʾ����
	bool ball_click;

	//endless ģʽ�µ�������ɫ����set======4color * 4parameters
	GLfloat endless_color_ambient[4][4];
	GLfloat endless_color_diffuse[4][4];
	GLfloat endless_color_specular[4][4];
	GLfloat endless_color_shine[4];

	bool endlessmode;

};