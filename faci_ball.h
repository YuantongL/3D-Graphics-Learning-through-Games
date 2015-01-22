#pragma once
#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glaux.h>


class faci_ball
{
public:
	faci_ball();
	faci_ball(int kind, float position[3], float size[3], GLfloat color_ambient[4], GLfloat color_diffuse[4],
		GLfloat color_specular[4], GLfloat color_shine, bool appear);
	faci_ball(int kind, float position[3], float size[3], int color, bool appear);			//用于题图的重载

	void faci_ball_settexture();
	void faci_ball_turnbig();
	void faci_ball_emerge();
	void faci_ball_turnsmall();

	void faci_ball_drawself();

	int faci_ball_kind;		//哪种,1=幕, 2=mouse, 3=贴图
	int faci_ball_color;    //贴图编号
	float faci_ball_position[3];		//位置
	float faci_ball_size[3];		//大小
	float faci_ball_texture_scale;
	GLfloat faci_ball_color_ambient[4];
	GLfloat faci_ball_color_diffuse[4];
	GLfloat faci_ball_color_specular[4];
	GLfloat faci_ball_color_shine;

	bool faci_ball_appear;		//是否显示出来
};

