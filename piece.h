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
	piece(int kind, float position[3], float size[3], float angle, int color, int scolor, bool appear, bool mouseon, bool mouserotate);		//��������
	void piece_settexture();
	void piece_CreatPictureList();
	void piece_drawself();
	void piece_turn_big();
	void piece_turn_small();

	float piece_position[3];		//λ��
	float piece_size[3];
	float piece_scale;

	float piece_angle;		//��תangle
	float piece_angle2;		//��תangle
	int piece_color;
	int side_color;
	int piece_kind;		//0=����, 1=С��ͼ
	bool piece_appear;		//�Ƿ���ʾ����
	bool piece_mouseon;
	bool piece_rotateon;
	bool piece_axis;		//�����Ƿ�
	bool piece_rkind;	//�ж�����һ����ת��true����ת������ϵ��ת
};