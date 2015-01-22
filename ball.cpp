#include "ball.h"
using namespace std;
#pragma comment(lib, "glaux")
//------------------------------------------------------------------------------------
GLfloat color1_ambient[][5] = { { 0.0, 0.0, 0.0, 1.0 }, { 0.7, 0.0, 0.0, 1.0 }, { 0.1, 0.1, 0.1, 1.0 }, { 0.7, 0.0, 0.0, 1.0 }, { 1.0, 1.0, 1.0, 1.0 } };				//第一种颜色
GLfloat color1_diffuse[][5] = { { 0.7, 0.0, 0.0, 1.0 }, { 0.0, 0.0, 0.0, 1.0 }, { 0.1, 0.1, 0.1, 1.0 }, { 0.0, 0.0, 0.0, 1.0 }, { 1.0, 0.0, 0.0, 1.0 } };
GLfloat color1_specular[][5] = { { 0.0, 0.0, 0.0, 1.0 }, { 0.0, 0.0, 0.0, 1.0 }, { 0.7, 0.0, 0.0, 1.0 }, { 0.0, 0.0, 0.0, 1.0 }, { 0.0, 1.0, 0.0, 1.0 } };
GLfloat color1_shine[] = { 10.0, 10.0, 20.0, 20.0 ,10.0 };

GLfloat color2_ambient[][5] = { { 0.0, 0.0, 0.0, 1.0 }, { 0.0, 0.0, 0.7, 1.0 }, { 0.1, 0.1, 0.1, 1.0 }, { 0.0, 0.0, 0.0, 1.0 }, { 0.0, 0.0, 0.0, 1.0 } };				//第二中颜色
GLfloat color2_diffuse[][5] = { { 0.0, 0.0, 0.7, 1.0 }, { 0.0, 0.0, 0.0, 1.0 }, { 0.1, 0.1, 0.1, 1.0 }, { 0.7, 0.0, 0.0, 1.0 }, { 1.0, 1.0, 1.0, 1.0 } };
GLfloat color2_specular[][5] = { { 0.0, 0.0, 0.0, 1.0 }, { 0.0, 0.0, 0.0, 1.0 }, { 0.0, 0.0, 0.7, 1.0 }, { 0.0, 0.0, 0.0, 1.0 }, { 1.0, 0.0, 0.0, 1.0 } };
GLfloat color2_shine[] = { 10.0, 10.0, 20.0, 20.0, 10.0 };

GLfloat color3_ambient[][5] = { { 0.0, 0.0, 0.0, 1.0 }, { 0.0, 0.7, 0.0, 1.0 }, { 0.1, 0.1, 0.1, 1.0 }, { 0.0, 0.0, 0.0, 1.0 }, { 0.0, 1.0, 0.0, 1.0 } };				//第三种颜色
GLfloat color3_diffuse[][5] = { { 0.0, 0.7, 0.0, 1.0 }, { 0.0, 0.0, 0.0, 1.0 }, { 0.1, 0.1, 0.1, 1.0 }, { 0.0, 0.0, 0.0, 1.0 }, { 1.0, 1.0, 1.0, 1.0 } };
GLfloat color3_specular[][5] = { { 0.0, 0.0, 0.0, 1.0 }, { 0.0, 0.0, 0.0, 1.0 }, { 0.0, 0.7, 0.0, 1.0 }, { 0.7, 0.0, 0.0, 1.0 }, { 1.0, 1.0, 1.0, 1.0 } };
GLfloat color3_shine[] = { 10.0, 10.0, 20.0, 20.0, 10.0 };

GLfloat color4_ambient[][5] = { { 0.0, 0.0, 0.0, 1.0 }, { 0.7, 0.0, 0.7, 1.0 }, { 0.1, 0.1, 0.1, 1.0 }, { 0.9, 0.0, 0.0, 1.0 }, { 0.0, 0.0, 1.0, 1.0 } };				//第四种颜色
GLfloat color4_diffuse[][5] = { { 0.7, 0.0, 0.7, 1.0 }, { 0.0, 0.0, 0.0, 1.0 }, { 0.1, 0.1, 0.1, 1.0 }, { 0.9, 0.0, 0.0, 1.0 }, { 0.0, 1.0, 0.0, 1.0 } };
GLfloat color4_specular[][5] = { { 0.0, 0.0, 0.0, 1.0 }, { 0.0, 0.0, 0.0, 1.0 }, { 0.7, 0.0, 0.7, 1.0 }, { 0.9, 0.0, 0.0, 1.0 }, { 1.0, 0.0, 0.0, 1.0 } };
GLfloat color4_shine[] = { 10.0, 10.0, 20.0, 20.0, 10.0 };


//----------------------------------------------------------------------------------------------

ball::ball(float position[3], int color, float radius, bool appear)
{
	for (int i = 0; i <= 2; i++)
	{
		ball_position[i] = position[i];		//一定要loop才可以传进去,传入位置
	}
	ball_color = color;
	ball_appear = appear;
	ball_r = radius;
	ball_level = 1;
}

void ball::ball_drawself()
{
	if (ball_r > 0.1)		//如果显示就画
	{
		if (endlessmode == false)
		{
			glPushMatrix();
			glTranslatef(ball_position[0], ball_position[1], ball_position[2]);
			if (ball_color == 0)				//看是什么颜色的球就画什么颜色的
			{
				glMaterialfv(GL_FRONT, GL_AMBIENT, color1_ambient[ball_level - 1]);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, color1_diffuse[ball_level - 1]);
				glMaterialfv(GL_FRONT, GL_SPECULAR, color1_specular[ball_level - 1]);
				glMaterialf(GL_FRONT, GL_SHININESS, color1_shine[ball_level - 1]);
			}
			else if (ball_color == 1)
			{
				glMaterialfv(GL_FRONT, GL_AMBIENT, color2_ambient[ball_level - 1]);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, color2_diffuse[ball_level - 1]);
				glMaterialfv(GL_FRONT, GL_SPECULAR, color2_specular[ball_level - 1]);
				glMaterialf(GL_FRONT, GL_SHININESS, color2_shine[ball_level - 1]);
			}
			else if (ball_color == 2)
			{
				glMaterialfv(GL_FRONT, GL_AMBIENT, color3_ambient[ball_level - 1]);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, color3_diffuse[ball_level - 1]);
				glMaterialfv(GL_FRONT, GL_SPECULAR, color3_specular[ball_level - 1]);
				glMaterialf(GL_FRONT, GL_SHININESS, color3_shine[ball_level - 1]);
			}
			else if (ball_color == 3)
			{
				glMaterialfv(GL_FRONT, GL_AMBIENT, color4_ambient[ball_level - 1]);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, color4_diffuse[ball_level - 1]);
				glMaterialfv(GL_FRONT, GL_SPECULAR, color4_specular[ball_level - 1]);
				glMaterialf(GL_FRONT, GL_SHININESS, color4_shine[ball_level - 1]);
			}
			glutSolidSphere(ball_r, 80, 80);
			glPopMatrix();
		}
		else if (endlessmode == true)
		{
			glPushMatrix();
			glTranslatef(ball_position[0], ball_position[1], ball_position[2]);
			if (ball_color == 0)				//看是什么颜色的球就画什么颜色的
			{
				glMaterialfv(GL_FRONT, GL_AMBIENT, endless_color_ambient[0]);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, endless_color_diffuse[0]);
				glMaterialfv(GL_FRONT, GL_SPECULAR, endless_color_specular[0]);
				glMaterialf(GL_FRONT, GL_SHININESS, endless_color_shine[0]);
			}
			else if (ball_color == 1)
			{
				glMaterialfv(GL_FRONT, GL_AMBIENT, endless_color_ambient[1]);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, endless_color_diffuse[1]);
				glMaterialfv(GL_FRONT, GL_SPECULAR, endless_color_specular[1]);
				glMaterialf(GL_FRONT, GL_SHININESS, endless_color_shine[1]);
			}
			else if (ball_color == 2)
			{
				glMaterialfv(GL_FRONT, GL_AMBIENT, endless_color_ambient[2]);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, endless_color_diffuse[2]);
				glMaterialfv(GL_FRONT, GL_SPECULAR, endless_color_specular[2]);
				glMaterialf(GL_FRONT, GL_SHININESS, endless_color_shine[2]);
			}
			else if (ball_color == 3)
			{
				glMaterialfv(GL_FRONT, GL_AMBIENT, endless_color_ambient[3]);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, endless_color_diffuse[3]);
				glMaterialfv(GL_FRONT, GL_SPECULAR, endless_color_specular[3]);
				glMaterialf(GL_FRONT, GL_SHININESS, endless_color_shine[3]);
			}
			glutSolidSphere(ball_r, 80, 80);
			glPopMatrix();
		}
		
	}
}


void ball::ball_turnsmall()
{
	if (ball_appear == false && ball_r > 0.0)
	{
		ball_r -= ball_r*0.1;
	}
}

void ball::ball_turnbig()
{
	if (ball_appear == true && ball_r < 1.5)
	{
		ball_r += -0.1*ball_r + 0.15;
	}
}

void ball::click_small()
{
	if (ball_appear == true && ball_click == false && ball_r > 1.5)
	{
		ball_r -= 0.2*ball_r - 0.3;
	}
}

void ball::click_big()
{
	if (ball_appear == true && ball_click == true && ball_r < 1.75)
	{
		ball_r += -0.2*ball_r + 0.35;
	}
}