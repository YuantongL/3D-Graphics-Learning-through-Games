#pragma once
#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glaux.h>

class facilities
{
public:
	facilities();
	facilities(int kind, int color, float position[3], float size[3], bool appear);
	void drawself();
	void settexture();
	void turn_big();
	void turn_small();

	int UI_faci_kind;		//����,1=Ļ
	int UI_faci_color;
	float UI_faci_position[3];		//λ��
	float UI_faci_size[3];		//��С
	float UI_faci_scale = 1.0;
	bool UI_faci_appear;
	bool UI_faci_mouseon = false;
};

