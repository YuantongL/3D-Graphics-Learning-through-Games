#pragma once
#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glaux.h>

class piece
{
public:
	piece();
	piece(int kind, float position[3], float size[3], float angle, int color, int scolor, bool appear, bool mouseon, bool mouserotate);		//构建函数
	void piece_settexture();
	void piece_CreatPictureList();
	void piece_drawself();
	void piece_turn_big();
	void piece_turn_small();

	float piece_position[3];		//位置
	float piece_size[3];
	float piece_scale;

	float piece_angle;		//自转angle
	float piece_angle2;		//公转angle
	int piece_color;
	int side_color;
	int piece_kind;		//0=方块, 1=小地图
	bool piece_appear;		//是否显示出来
	bool piece_mouseon;
	bool piece_rotateon;
	bool piece_axis;		//坐标是否画
	bool piece_rkind;	//判断是哪一种旋转，true是自转，坐标系不转
};