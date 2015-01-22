#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <ctime>
#include <GL/glut.h>
#include <GL/glaux.h>
#include "control_ball.h"
#include "ball.h"
#include "faci_ball.h"
#include "word.h"
#pragma comment(lib, "glaux")
using namespace std;

int gameplay_ballstage = 1;		//是否有球被按下去了, 1=没有按， 2=第一个球被按了还没抬， 3=等待第二个球被按， 4=第二个球被按
int gameplay_balldownnum[2];			//被按下去的球是哪两个，第一个和第二个
int gameplay_balldisapp_num = 0;
bool gameplay_ball_appearlist[12] = { true, true, true, true, true, true, true, true, true, true, true, true };

int control_ball_blo_on = 0;
int arrow_onmoving = 0;		// 用于滑块可以一直动
int control_light_color = 0;		//用于记录颜色, 0 =白色

//----------------------------------  balls  -----------------------------------------------------
float x = 4.0;	//球心距离, r=1.5

float ball1_position[3] = { -1.5*x, x, 0.0 };		//球1的位置
float ball2_position[3] = { -0.5*x, x, 0.0 };		//球2的位置
float ball3_position[3] = { 0.5*x, x, 0.0 };		//球3的位置
float ball4_position[3] = { 1.5*x, x, 0.0 };		//球4的位置
float ball5_position[3] = { -1.5*x, 0.0, 0.0 };		//球5的位置
float ball6_position[3] = { -0.5*x, 0.0, 0.0 };		//球6的位置
float ball7_position[3] = { 0.5*x, 0.0, 0.0 };		//球7的位置
float ball8_position[3] = { 1.5*x, 0.0, 0.0 };		//球8的位置
float ball9_position[3] = { -1.5*x, -x, 0.0 };		//球9的位置
float ball10_position[3] = { -0.5*x, -x, 0.0 };		//球10的位置
float ball11_position[3] = { 0.5*x, -x, 0.0 };		//球11的位置
float ball12_position[3] = { 1.5*x, -x, 0.0 };		//球12的位置

int ball_rand_color[12];
float ball_r[12] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
float ball_r_big = 1.75;		//变大的半径
float ball_r_small = 1.5;

//------------------------------------------  facilities  -----------------------------------------------
int facilities1_kind = 1;
float facilities1_position[3] = { 0.0, 0.0, 0.0 };
float facilities1_size[3] = { 16.0, 9.0, 0.0 };
GLfloat facilities1_color_ambient[4] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat facilities1_color_diffuse[4] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat facilities1_color_specular[4] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat facilities1_color_shine = 5.0;

int mouse_kind = 2;
float mouse_position[3] = { 0.0, 0.0, 2.0 };
float mouse_size[3] = { 0.2, 0.0, 0.0 };
GLfloat mouse_color_ambient[4] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat mouse_color_diffuse[4] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat mouse_color_specular[4] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mouse_color_shine = 5.0;

faci_ball lightwall(facilities1_kind, facilities1_position, facilities1_size, facilities1_color_ambient, facilities1_color_diffuse, facilities1_color_specular, facilities1_color_shine, true);
faci_ball mouse(mouse_kind, mouse_position, mouse_size, mouse_color_ambient, mouse_color_diffuse, mouse_color_specular, mouse_color_shine, true);

float faci_ball_texture1_pos[3] = {14.0, 6.0, 1.0};
float faci_ball_texture1_size[3] = {2.85, 2.85, 0.0};

float faci_ball_texture2_pos[3] = { 14.0, 3.0, 1.0 };
float faci_ball_texture2_size[3] = { 2.85, 2.85, 0.0 };

float faci_ball_texture3_pos[3] = { 14.0, 0.0, 1.0 };
float faci_ball_texture3_size[3] = { 2.85, 2.85, 0.0 };

float faci_ball_texture4_pos[3] = { 14.0, -3.0, 1.0 };
float faci_ball_texture4_size[3] = { 2.85, 2.85, 0.0 };

float faci_ball_texture5_pos[3] = { 14.0, -6.0, 1.0 };
float faci_ball_texture5_size[3] = { 2.85, 2.85, 0.0 };

float faci_ball_bar_pos[3] = { -12.0, -5.0, 1.0 };
float faci_ball_bar_size[3] = { 6.0, 6.0, 0.0 };

float faci_ball_arrow1_pos[3] = { -13.75, -4.0, 1.1 };
float faci_ball_arrow1_size[3] = { 0.5, 0.5, 0.0 };

float faci_ball_arrow2_pos[3] = { -11.75, -3.8, 1.1 };
float faci_ball_arrow2_size[3] = { 0.5, 0.5, 0.0 };

float faci_ball_arrow3_pos[3] = { -9.75, -4.6, 1.1 };
float faci_ball_arrow3_size[3] = { 0.5, 0.5, 0.0 };

float faci_ball_home_pos[3] = { -14.5, 7.0, 1.0 };
float faci_ball_home_size[3] = { 1.0, 1.0, 1.0 };

faci_ball faci_ball_texture1(3, faci_ball_texture1_pos, faci_ball_texture1_size, 70, true);
faci_ball faci_ball_texture2(3, faci_ball_texture2_pos, faci_ball_texture2_size, 1, true);
faci_ball faci_ball_texture3(3, faci_ball_texture3_pos, faci_ball_texture3_size, 2, true);
faci_ball faci_ball_texture4(3, faci_ball_texture4_pos, faci_ball_texture4_size, 3, true);
faci_ball faci_ball_texture5(3, faci_ball_texture5_pos, faci_ball_texture5_size, 4, true);
faci_ball faci_ball_bar(3, faci_ball_bar_pos, faci_ball_bar_size, 5, false);
faci_ball faci_ball_arrow1(3, faci_ball_arrow1_pos, faci_ball_arrow1_size, 6, false);
faci_ball faci_ball_arrow2(3, faci_ball_arrow2_pos, faci_ball_arrow2_size, 6, false);
faci_ball faci_ball_arrow3(3, faci_ball_arrow3_pos, faci_ball_arrow3_size, 6, false);
faci_ball faci_ball_home(3, faci_ball_home_pos, faci_ball_home_size, 7, true);


//--------------------------------------------  lights  -------------------------------------------------
GLfloat light0_pos[4] = { 0.0, 0.0, 9.0, 1.0 };				//光源0，手电筒光源
GLfloat light0_ambient[4] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat light0_diffuse[4] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat light0_specular[4] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat light0_amb_ori[4] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat light0_dif_ori[4] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat light0_spec_ori[4] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat light0_cutoff = 30;		//截止角
GLfloat light0_spotdirection[3] = { 0.0, 0.0, -1.0 };

GLfloat light_change[3] = { 0.7, 0.7, 0.7 };		//暂存可变光参数

GLfloat light1_pos[4] = { 0.0, 0.0, 9.0, 0.0 };				//光源2，常光源
GLfloat light1_ambient[4] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat light1_diffuse[4] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat light1_specular[4] = { 0.1, 0.1, 0.1, 1.0 };

//------------------------------------------  news  ------------------------------------------------------
ball balllist[12] = {
	ball(ball1_position, ball_rand_color[0], ball_r[0], true),	//将所有需要用到的object在这里声明
	ball(ball2_position, ball_rand_color[1], ball_r[1], true),
	ball(ball3_position, ball_rand_color[2], ball_r[2], true),
	ball(ball4_position, ball_rand_color[3], ball_r[3], true),
	ball(ball5_position, ball_rand_color[4], ball_r[4], true),
	ball(ball6_position, ball_rand_color[5], ball_r[5], true),
	ball(ball7_position, ball_rand_color[6], ball_r[6], true),
	ball(ball8_position, ball_rand_color[7], ball_r[7], true),
	ball(ball9_position, ball_rand_color[8], ball_r[8], true),
	ball(ball10_position, ball_rand_color[9], ball_r[9], true),
	ball(ball11_position, ball_rand_color[10], ball_r[10], true),
	ball(ball12_position, ball_rand_color[11], ball_r[11], true),
};


//----------------------------------word--------------------------------------------------------------------

char *intro_cont = "LEVEL1 - Eliminate balls with same appearance";
char *intro_font = "Consolas";
float intro_pos[3] = { -7.5, 7.5, 0.0 };
int intro_size = 26;
float intro_color[4] = { 1.0, 1.0, 1.0, 1.0 };

char *intro2_cont = "Balls only different in diffuse parameters";
char *intro2_font = "Consolas";
float intro2_pos[3] = { -7.5, 6.5, 0.0 };
int intro2_size = 26;
float intro2_color[4] = { 1.0, 1.0, 1.0, 1.0 };

char *ball_info_cont = "Ball parameters";
char *ball_info_font = "Arial Rounded MT Bold";
float ball_info_pos[3] = { -15.0, 5.0, 0.0 };
int ball_info_size = 18;
float ball_info_color[4] = { 1.0, 1.0, 1.0, 1.0 };

char *ball_ambient_cont = "";
char *ball_ambient_font = "Arial Rounded MT Bold";
float ball_ambient_pos[3] = { -15.0, 4.0, 0.0 };
int ball_ambient_size = 18;
float ball_ambient_color[4] = { 1.0, 1.0, 1.0, 1.0 };

char *ball_diffuse_cont = "";
char *ball_diffuse_font = "Arial Rounded MT Bold";
float ball_diffuse_pos[3] = { -15.0, 3.0, 0.0 };
int ball_diffuse_size = 18;
float ball_diffuse_color[4] = { 1.0, 1.0, 1.0, 1.0 };

char *ball_specular_cont = "";
char *ball_specular_font = "Arial Rounded MT Bold";
float ball_specular_pos[3] = { -15.0, 2.0, 0.0 };
int ball_specular_size = 18;
float ball_specular_color[4] = { 1.0, 1.0, 1.0, 1.0 };

char *spot1_cont = "Spotlight parameters:";
char *spot1_font = "Arial Rounded MT Bold";
float spot1_pos[3] = { -15.0, -2.0, 0.0 };
int spot1_size = 18;
float spot1_color[4] = { 1.0, 1.0, 1.0, 1.0 };

char *spot2_cont = "ambient = {0.5, 0.5, 0.5, 1.0}";
char *spot2_font = "Arial Rounded MT Bold";
float spot2_pos[3] = { -15.0, -3.0, 0.0 };
int spot2_size = 18;
float spot2_color[4] = { 1.0, 1.0, 1.0, 1.0 };

char *spot3_cont = "diffuse: { 0.6, 0.6, 0.6, 1.0 }";
char *spot3_font = "Arial Rounded MT Bold";
float spot3_pos[3] = { -15.0, -4.0, 0.0 };
int spot3_size = 18;
float spot3_color[4] = { 1.0, 1.0, 1.0, 1.0 };

char *spot4_cont = "specular = { 0.2, 0.2, 0.2, 1.0 }";
char *spot4_font = "Arial Rounded MT Bold";
float spot4_pos[3] = { -15.0, -5.0, 0.0 };
int spot4_size = 18;
float spot4_color[4] = { 1.0, 1.0, 1.0, 1.0 };

word intro(intro_pos, true, intro_size, intro_color, intro_cont, intro_font);
word intro2(intro2_pos, true, intro2_size, intro2_color, intro2_cont, intro2_font);
word ball_info(ball_info_pos, true, ball_info_size, ball_info_color, ball_info_cont, ball_info_font);
word ball_ambient(ball_ambient_pos, true, ball_ambient_size, ball_ambient_color, ball_ambient_cont, ball_ambient_font);
word ball_diffuse(ball_diffuse_pos, true, ball_diffuse_size, ball_diffuse_color, ball_diffuse_cont, ball_diffuse_font);
word ball_specular(ball_specular_pos, true, ball_specular_size, ball_specular_color, ball_specular_cont, ball_specular_font);
word spot1(spot1_pos, true, spot1_size, spot1_color, spot1_cont, spot1_font);
word spot2(spot2_pos, true, spot2_size, spot2_color, spot2_cont, spot2_font);
word spot3(spot3_pos, true, spot3_size, spot3_color, spot3_cont, spot3_font);
word spot4(spot4_pos, true, spot4_size, spot4_color, spot4_cont, spot4_font);


//---------------------------------------------------------------------------------------------------------

control_ball::control_ball()		//中间类的构建器
{
	
}

void control_ball::control_ball_init()			//设定初始半径和变大变小
{
	
	control_ball_left_mouse_down = false;

	faci_ball_texture1.faci_ball_settexture();

	faci_ball_texture1.faci_ball_texture_scale = 1.0;
	faci_ball_texture2.faci_ball_texture_scale = 1.0;
	faci_ball_texture3.faci_ball_texture_scale = 1.0;
	faci_ball_texture4.faci_ball_texture_scale = 1.0;
	faci_ball_texture5.faci_ball_texture_scale = 1.0;
	faci_ball_bar.faci_ball_texture_scale = 1.0;
	faci_ball_arrow1.faci_ball_texture_scale = 1.0;
	faci_ball_arrow2.faci_ball_texture_scale = 1.0;
	faci_ball_arrow3.faci_ball_texture_scale = 1.0;
	faci_ball_home.faci_ball_texture_scale = 1.0;

	srand((int)time(0));

	for (int i = 0; i < 12; i++)
	{
		ball_rand_color[i] = rand() % 4;			//随机颜色
		balllist[i].ball_color = ball_rand_color[i];
		balllist[i].ball_click = false;

		balllist[i].ball_appear = true;
		balllist[i].ball_r = 0.0;
	}
}

void control_ball::control_ball_idle()			//球变大变小
{
	for (int i = 0; i < 12; i++)
	{
		balllist[i].ball_turnbig();
		balllist[i].ball_turnsmall();

		balllist[i].click_small();
		balllist[i].click_big();
	}

	switch (control_ball_blo_on)
	{
	case 0:{
			   faci_ball_texture1.faci_ball_turnsmall();
			   faci_ball_texture2.faci_ball_turnsmall();
			   faci_ball_texture3.faci_ball_turnsmall();
			   faci_ball_texture4.faci_ball_turnsmall();
			   faci_ball_texture5.faci_ball_turnsmall();
			   faci_ball_home.faci_ball_turnsmall();
			   break;
	}
	case 1:{
			   faci_ball_texture1.faci_ball_turnbig();
			   faci_ball_texture2.faci_ball_turnsmall();
			   faci_ball_texture3.faci_ball_turnsmall();
			   faci_ball_texture4.faci_ball_turnsmall();
			   faci_ball_texture5.faci_ball_turnsmall();
			   break;
	}
	case 2:{
			   faci_ball_texture1.faci_ball_turnsmall();
			   faci_ball_texture2.faci_ball_turnbig();
			   faci_ball_texture3.faci_ball_turnsmall();
			   faci_ball_texture4.faci_ball_turnsmall();
			   faci_ball_texture5.faci_ball_turnsmall();
			   break;
	}
	case 3:{
			   faci_ball_texture1.faci_ball_turnsmall();
			   faci_ball_texture2.faci_ball_turnsmall();
			   faci_ball_texture3.faci_ball_turnbig();
			   faci_ball_texture4.faci_ball_turnsmall();
			   faci_ball_texture5.faci_ball_turnsmall();
			   break;
	}
	case 4:{
			   faci_ball_texture1.faci_ball_turnsmall();
			   faci_ball_texture2.faci_ball_turnsmall();
			   faci_ball_texture3.faci_ball_turnsmall();
			   faci_ball_texture4.faci_ball_turnbig();
			   faci_ball_texture5.faci_ball_turnsmall();
			   break;
	}
	case 5:{
			   faci_ball_texture1.faci_ball_turnsmall();
			   faci_ball_texture2.faci_ball_turnsmall();
			   faci_ball_texture3.faci_ball_turnsmall();
			   faci_ball_texture4.faci_ball_turnsmall();
			   faci_ball_texture5.faci_ball_turnbig();
			   break;
	}
	case 6:{
			   faci_ball_home.faci_ball_turnbig();
			   break;
	}
	}
}

void control_ball::control_ball_drawall()			//画球
{
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);          //变换光照
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, &light0_cutoff);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_spotdirection);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);          //背景光照
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glEnable(GL_LIGHT1);

	//------------------------------------------------------
	for (int i = 0; i < 12; i++)
	{
		balllist[i].ball_drawself();
	}
	lightwall.faci_ball_drawself();
	mouse.faci_ball_drawself();

	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	faci_ball_texture1.faci_ball_drawself();
	faci_ball_texture2.faci_ball_drawself();
	faci_ball_texture3.faci_ball_drawself();
	faci_ball_texture4.faci_ball_drawself();
	faci_ball_texture5.faci_ball_drawself();
	faci_ball_bar.faci_ball_drawself();
	faci_ball_arrow1.faci_ball_drawself();
	faci_ball_arrow2.faci_ball_drawself();
	faci_ball_arrow3.faci_ball_drawself();
	faci_ball_home.faci_ball_drawself();
	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
	glTranslatef(0.0, 0.0, 9.0);		//让字到最前面
	
	spot1.drawself();
	spot2.drawself();
	spot3.drawself();
	spot4.drawself();

	ball_info.drawself();
	ball_ambient.drawself();
	ball_diffuse.drawself();
	ball_specular.drawself();
	
	intro.drawself();
	intro2.drawself();
	glPopMatrix();
}

void control_ball::control_ball_mouseevent()		//处理所有鼠标单击动作
{
	light0_pos[0] = control_ball_mouseposition_x * 32.0 / 1366.0 - 16.0;		//光源位置随着鼠标位置变化
	light0_pos[1] = 9.0 - control_ball_mouseposition_y * 18.0 / 768.0;
	mouse.faci_ball_position[0] = light0_pos[0];							//鼠标位置变化
	mouse.faci_ball_position[1] = light0_pos[1];

	float mp_x = light0_pos[0];
	float mp_y = light0_pos[1];

	if (control_ball_left_mouse_down == true)
	{
		//====================================鼠标点击方块=====================================
		if (light0_pos[0] > 12.5 && light0_pos[0] < 15.5 && light0_pos[1] > 4.5 && light0_pos[1] < 7.5)
		{
			for (int i = 0; i < 12; i++)
			{
				balllist[i].ball_r = 0;
			}
			for (int j = 0; j < 4; j++)
			{
				light0_ambient[j] = light0_amb_ori[j];
				light0_diffuse[j] = light0_dif_ori[j];
				light0_specular[j] = light0_spec_ori[j];
			}
			
			faci_ball_texture1.faci_ball_texture_scale = 1.1;
			faci_ball_texture1.faci_ball_color = 70;
			faci_ball_texture2.faci_ball_color = 1;
			faci_ball_texture3.faci_ball_color = 2;
			faci_ball_texture4.faci_ball_color = 3;
			faci_ball_texture5.faci_ball_color = 4;
			
			intro.word_disp = "LEVEL1 - Eliminate balls with same appearance";
			intro2.word_disp = "Balls only different in diffuse parameters";
			for (int y = 0; y < 12; y++)
			{
				balllist[y].ball_level = 1;
			}
			faci_ball_arrow1.faci_ball_position[1] = faci_ball_arrow1_pos[1];
			faci_ball_arrow2.faci_ball_position[1] = faci_ball_arrow2_pos[1];
			faci_ball_arrow3.faci_ball_position[1] = faci_ball_arrow3_pos[1];

			spot1.word_disp = "Spotlight parameters:";
			spot2.word_disp = "ambient = {0.5, 0.5, 0.5, 1.0}";
			spot3.word_disp = "diffuse: { 0.6, 0.6, 0.6, 1.0 }";
			spot4.word_disp = "specular = { 0.2, 0.2, 0.2, 1.0 }";
			faci_ball_bar.faci_ball_appear = false;
			faci_ball_arrow1.faci_ball_appear = false;
			faci_ball_arrow2.faci_ball_appear = false;
			faci_ball_arrow3.faci_ball_appear = false;
			glEnable(GL_LIGHT1);
		}
		else if (light0_pos[0] > 12.5 && light0_pos[0] < 15.5 && light0_pos[1] > 1.5 && light0_pos[1] < 4.5)
		{
			for (int i = 0; i < 12; i++)
			{
				balllist[i].ball_r = 0;
			}
			for (int j = 0; j < 4; j++)
			{
				light0_ambient[j] = light0_amb_ori[j];
				light0_diffuse[j] = light0_dif_ori[j];
				light0_specular[j] = light0_spec_ori[j];
			}
			faci_ball_arrow1.faci_ball_position[1] = faci_ball_arrow1_pos[1];
			faci_ball_arrow2.faci_ball_position[1] = faci_ball_arrow2_pos[1];
			faci_ball_arrow3.faci_ball_position[1] = faci_ball_arrow3_pos[1];

			faci_ball_texture2.faci_ball_texture_scale = 1.1;
			faci_ball_texture1.faci_ball_color = 0;
			faci_ball_texture2.faci_ball_color = 71;
			faci_ball_texture3.faci_ball_color = 2;
			faci_ball_texture4.faci_ball_color = 3;
			faci_ball_texture5.faci_ball_color = 4;
			intro.word_disp = "LEVEL2 - Now, only ambient reflection exists";
			intro2.word_disp = "Eliminate enough balls to get to next level";
			for (int y = 0; y < 12; y++)
			{
				balllist[y].ball_level = 2;
			}
			spot1.word_disp = "Spotlight parameters:";
			spot2.word_disp = "ambient = {0.5, 0.5, 0.5, 1.0}";
			spot3.word_disp = "diffuse: { 0.6, 0.6, 0.6, 1.0 }";
			spot4.word_disp = "specular = { 0.2, 0.2, 0.2, 1.0 }";
			faci_ball_bar.faci_ball_appear = false;
			faci_ball_arrow1.faci_ball_appear = false;
			faci_ball_arrow2.faci_ball_appear = false;
			faci_ball_arrow3.faci_ball_appear = false;
			glEnable(GL_LIGHT1);
		}
		else if (light0_pos[0] > 12.5 && light0_pos[0] < 15.5 && light0_pos[1] > -1.5 && light0_pos[1] < 1.5)
		{
			for (int i = 0; i < 12; i++)
			{
				balllist[i].ball_r = 0;
			}
			for (int j = 0; j < 4; j++)
			{
				light0_ambient[j] = light0_amb_ori[j];
				light0_diffuse[j] = light0_dif_ori[j];
				light0_specular[j] = light0_spec_ori[j];
			}
			faci_ball_arrow1.faci_ball_position[1] = faci_ball_arrow1_pos[1];
			faci_ball_arrow2.faci_ball_position[1] = faci_ball_arrow2_pos[1];
			faci_ball_arrow3.faci_ball_position[1] = faci_ball_arrow3_pos[1];

			faci_ball_texture3.faci_ball_texture_scale = 1.1;
			faci_ball_texture1.faci_ball_color = 0;
			faci_ball_texture2.faci_ball_color = 1;
			faci_ball_texture3.faci_ball_color = 72;
			faci_ball_texture4.faci_ball_color = 3;
			faci_ball_texture5.faci_ball_color = 4;
			intro.word_disp = "LEVEL3 - Only specular reflection in this level";
			intro2.word_disp = "Keep on!";
			for (int y = 0; y < 12; y++)
			{
				balllist[y].ball_level = 3;
			}
			spot1.word_disp = "Spotlight parameters:";
			spot2.word_disp = "ambient = {0.5, 0.5, 0.5, 1.0}";
			spot3.word_disp = "diffuse: { 0.6, 0.6, 0.6, 1.0 }";
			spot4.word_disp = "specular = { 0.2, 0.2, 0.2, 1.0 }";
			faci_ball_bar.faci_ball_appear = false;
			faci_ball_arrow1.faci_ball_appear = false;
			faci_ball_arrow2.faci_ball_appear = false;
			faci_ball_arrow3.faci_ball_appear = false;
			glEnable(GL_LIGHT1);
		}
		else if (light0_pos[0] > 12.5 && light0_pos[0] < 15.5 && light0_pos[1] > -4.5 && light0_pos[1] < -1.5)
		{
			for (int i = 0; i < 12; i++)
			{
				balllist[i].ball_r = 0;
			}
			for (int j = 0; j < 4; j++)				//还原光和滑块
			{
				light0_ambient[j] = light0_amb_ori[j];
				light0_diffuse[j] = light0_dif_ori[j];
				light0_specular[j] = light0_spec_ori[j];
			}
			faci_ball_arrow1.faci_ball_position[1] = faci_ball_arrow1_pos[1];
			faci_ball_arrow2.faci_ball_position[1] = faci_ball_arrow2_pos[1];
			faci_ball_arrow3.faci_ball_position[1] = faci_ball_arrow3_pos[1];

			faci_ball_texture4.faci_ball_texture_scale = 1.1;
			faci_ball_texture1.faci_ball_color = 0;
			faci_ball_texture2.faci_ball_color = 1;
			faci_ball_texture3.faci_ball_color = 2;
			faci_ball_texture4.faci_ball_color = 73;
			faci_ball_texture5.faci_ball_color = 4;
			intro.word_disp = "LEVEL4 - Balls are in a mix of material parameters";
			intro2.word_disp = "Distinguish their difference";
			for (int y = 0; y < 12; y++)
			{
				balllist[y].ball_level = 4;
			}
			spot1.word_disp = "Spotlight parameters:";
			spot2.word_disp = "ambient = {0.5, 0.5, 0.5, 1.0}";
			spot3.word_disp = "diffuse: { 0.6, 0.6, 0.6, 1.0 }";
			spot4.word_disp = "specular = { 0.2, 0.2, 0.2, 1.0 }";
			faci_ball_bar.faci_ball_appear = false;
			faci_ball_arrow1.faci_ball_appear = false;
			faci_ball_arrow2.faci_ball_appear = false;
			faci_ball_arrow3.faci_ball_appear = false;
			glEnable(GL_LIGHT1);
		}
		else if (light0_pos[0] > 12.5 && light0_pos[0] < 15.5 && light0_pos[1] > -7.5 && light0_pos[1] < -4.5)
		{
			for (int i = 0; i < 12; i++)
			{
				balllist[i].ball_r = 0;
			}

			faci_ball_texture5.faci_ball_texture_scale = 1.1;
			faci_ball_texture1.faci_ball_color = 0;
			faci_ball_texture2.faci_ball_color = 1;
			faci_ball_texture3.faci_ball_color = 2;
			faci_ball_texture4.faci_ball_color = 3;
			faci_ball_texture5.faci_ball_color = 74;
			intro.word_disp = "LEVEL5 - Random adjust light properties";
			intro2.word_disp = "See what's in difference";
			spot1.word_disp = "";
			spot2.word_disp = "";
			spot3.word_disp = "";
			spot4.word_disp = "";
			faci_ball_bar.faci_ball_appear = true;
			faci_ball_arrow1.faci_ball_appear = true;
			faci_ball_arrow2.faci_ball_appear = true;
			faci_ball_arrow3.faci_ball_appear = true;
			for (int y = 0; y < 12; y++)
			{
				balllist[y].ball_level = 5;
			}
			glDisable(GL_LIGHT1);
		}
		else if (light0_pos[0] > -15.0 && light0_pos[0] < -14.0 && light0_pos[1] > 6.5 && light0_pos[1] < 7.5)
		{
			faci_ball_home.faci_ball_texture_scale = 1.1;	//----------------------------------home 返回---------------------------------
			control_ball_gameon = 0;
		}
		if (balllist[0].ball_level == 5)
		{
			//------------------------------鼠标点击滑动条--------------------------------
			if (light0_pos[0] > -14.0 && light0_pos[0] < -13.5 &&
				light0_pos[1] < (faci_ball_arrow1.faci_ball_position[1] + 0.25) && light0_pos[1] > (faci_ball_arrow1.faci_ball_position[1] - 0.25))
			{
				arrow_onmoving = 1;
			}
			else if (light0_pos[0] > -12.0 && light0_pos[0] < -11.5 &&
				light0_pos[1] < (faci_ball_arrow2.faci_ball_position[1] + 0.25) && light0_pos[1] > (faci_ball_arrow2.faci_ball_position[1] - 0.25))
			{
				arrow_onmoving = 2;
			}
			else if (light0_pos[0] > -10.0 && light0_pos[0] < -9.5 &&
				light0_pos[1] < (faci_ball_arrow3.faci_ball_position[1] + 0.25) && light0_pos[1] > (faci_ball_arrow3.faci_ball_position[1] - 0.25))
			{
				arrow_onmoving = 3;
			}

			//-----------------------------------换颜色---------------------------------------------------------
			if (balllist[0].ball_level == 5)
			{
				if (light0_pos[0] > -15.0 && light0_pos[0] < -14.0 && light0_pos[1] > -8.0 && light0_pos[1] < -7.0)	//R
				{
					light0_ambient[0] = light_change[0];
					light0_ambient[1] = 0.0;
					light0_ambient[2] = 0.0;

					light0_diffuse[0] = light_change[1];
					light0_diffuse[1] = 0.0;
					light0_diffuse[2] = 0.0;

					light0_specular[0] = light_change[2];
					light0_specular[1] = 0.0;
					light0_specular[2] = 0.0;

					control_light_color = 1;
				}
				else if (light0_pos[0] > -14.0 && light0_pos[0] < -13.0 && light0_pos[1] > -8.0 && light0_pos[1] < -7.0)	//Y
				{
					light0_ambient[0] = light_change[0];
					light0_ambient[1] = light_change[0];
					light0_ambient[2] = 0.0;

					light0_diffuse[0] = light_change[1];
					light0_diffuse[1] = light_change[1];
					light0_diffuse[2] = 0.0;

					light0_specular[0] = light_change[2];
					light0_specular[1] = light_change[2];
					light0_specular[2] = 0.0;

					control_light_color = 2;
				}
				else if (light0_pos[0] > -13.0 && light0_pos[0] < -12.0 && light0_pos[1] > -8.0 && light0_pos[1] < -7.0)		//G
				{
					light0_ambient[0] = 0.0;
					light0_ambient[1] = light_change[0];
					light0_ambient[2] = 0.0;

					light0_diffuse[0] = 0.0;
					light0_diffuse[1] = light_change[1];
					light0_diffuse[2] = 0.0;

					light0_specular[0] = 0.0;
					light0_specular[1] = light_change[2];
					light0_specular[2] = 0.0;

					control_light_color = 3;
				}
				else if (light0_pos[0] > -12.0 && light0_pos[0] < -11.0 && light0_pos[1] > -8.0 && light0_pos[1] < -7.0)		//B
				{
					light0_ambient[0] = 0.0;
					light0_ambient[1] = 0.0;
					light0_ambient[2] = light_change[0];

					light0_diffuse[0] = 0.0;
					light0_diffuse[1] = 0.0;
					light0_diffuse[2] = light_change[1];

					light0_specular[0] = 0.0;
					light0_specular[1] = 0.0;
					light0_specular[2] = light_change[2];

					control_light_color = 4;
				}
				else if (light0_pos[0] > -11.0 && light0_pos[0] < -10.0 && light0_pos[1] > -8.0 && light0_pos[1] < -7.0)		//CYAN
				{
					light0_ambient[0] = 0.0;
					light0_ambient[1] = light_change[0];
					light0_ambient[2] = light_change[0];

					light0_diffuse[0] = 0.0;
					light0_diffuse[1] = light_change[1];
					light0_diffuse[2] = light_change[1];

					light0_specular[0] = 0.0;
					light0_specular[1] = light_change[2];
					light0_specular[2] = light_change[2];

					control_light_color = 5;
				}
				else if (light0_pos[0] > -10.0 && light0_pos[0] < -9.0 && light0_pos[1] > -8.0 && light0_pos[1] < -7.0)		//MAGENTA
				{
					light0_ambient[0] = light_change[0];
					light0_ambient[1] = 0.0;
					light0_ambient[2] = light_change[0];

					light0_diffuse[0] = light_change[1];
					light0_diffuse[1] = 0.0;
					light0_diffuse[2] = light_change[1];

					light0_specular[0] = light_change[2];
					light0_specular[1] = 0.0;
					light0_specular[2] = light_change[2];

					control_light_color = 6;
				}
				else if (light0_pos[0] > -15.0 && light0_pos[0] < -9.0 && light0_pos[1] > -7.0 && light0_pos[1] < -6.0)		//WHITE
				{
					light0_ambient[0] = light_change[0];
					light0_ambient[1] = light_change[0];
					light0_ambient[2] = light_change[0];

					light0_diffuse[0] = light_change[1];
					light0_diffuse[1] = light_change[1];
					light0_diffuse[2] = light_change[1];

					light0_specular[0] = light_change[2];
					light0_specular[1] = light_change[2];
					light0_specular[2] = light_change[2];

					control_light_color = 0;
				}
			}
		}
		

		//===================================================================================================
		if (gameplay_ballstage == 1)		//如果没有球被按下，就记录按得是哪个球
		{
			gameplay_balldownnum[0] = 0;
			gameplay_balldownnum[1] = 0;
			if (mp_x > -7.5 && mp_x< -4.5 && mp_y> 2.5 && mp_y < 5.5 && balllist[0].ball_appear == true)
			{
				gameplay_balldownnum[0] = 1;
				balllist[0].ball_click = true;
				gameplay_ballstage = 2;
			}
			else if (mp_x > -3.5 && mp_x< -0.5 && mp_y > 2.5 && mp_y < 5.5 && balllist[1].ball_appear == true)
			{
				gameplay_balldownnum[0] = 2;
				balllist[1].ball_click = true;
				gameplay_ballstage = 2;
			}
			else if (mp_x > 0.5 && mp_x < 3.5 && mp_y > 2.5 && mp_y < 5.5 && balllist[2].ball_appear == true)
			{
				gameplay_balldownnum[0] = 3;
				balllist[2].ball_click = true;
				gameplay_ballstage = 2;
			}
			else if (mp_x > 4.5 && mp_x < 7.5 && mp_y > 2.5 && mp_y < 5.5 && balllist[3].ball_appear == true)
			{
				gameplay_balldownnum[0] = 4;
				balllist[3].ball_click = true;
				gameplay_ballstage = 2;
			}
			else if (mp_x > -7.5 && mp_x < -4.5 && mp_y > -1.5 && mp_y < 1.5 && balllist[4].ball_appear == true)
			{
				gameplay_balldownnum[0] = 5;
				balllist[4].ball_click = true;
				gameplay_ballstage = 2;
			}
			else if (mp_x > -3.5 && mp_x < -0.5 && mp_y > -1.5 && mp_y < 1.5 && balllist[5].ball_appear == true)
			{
				gameplay_balldownnum[0] = 6;
				balllist[5].ball_click = true;
				gameplay_ballstage = 2;
			}
			else if (mp_x > 0.5 && mp_x < 3.5 && mp_y > -1.5 && mp_y < 1.5 && balllist[6].ball_appear == true)
			{
				gameplay_balldownnum[0] = 7;
				balllist[6].ball_click = true;
				gameplay_ballstage = 2;
			}
			else if (mp_x > 4.5 && mp_x < 7.5 && mp_y > -1.5 && mp_y < 1.5 && balllist[7].ball_appear == true)
			{
				gameplay_balldownnum[0] = 8;
				balllist[7].ball_click = true;
				gameplay_ballstage = 2;
			}
			else if (mp_x > -7.5 && mp_x < -4.5 && mp_y > -5.5 && mp_y < -2.5 && balllist[8].ball_appear == true)
			{
				gameplay_balldownnum[0] = 9;
				balllist[8].ball_click = true;
				gameplay_ballstage = 2;
			}
			else if (mp_x > -3.5 && mp_x < -0.5 && mp_y > -5.5 && mp_y < -2.5 && balllist[9].ball_appear == true)
			{
				gameplay_balldownnum[0] = 10;
				balllist[9].ball_click = true;
				gameplay_ballstage = 2;
			}
			else if (mp_x > 0.5 && mp_x < 3.5 && mp_y > -5.5 && mp_y < -2.5 && balllist[10].ball_appear == true)
			{
				gameplay_balldownnum[0] = 11;
				balllist[10].ball_click = true;
				gameplay_ballstage = 2;
			}
			else if (mp_x > 4.5 && mp_x < 7.5 && mp_y > -5.5 && mp_y < -2.5 && balllist[11].ball_appear == true)
			{
				gameplay_balldownnum[0] = 12;
				balllist[11].ball_click = true;
				gameplay_ballstage = 2;
			}
			else{
				ball_info.word_disp = "";
				ball_ambient.word_disp = "";
				ball_diffuse.word_disp = "";
				ball_specular.word_disp = "";
			}
		}
		else if (gameplay_ballstage == 3)		//如果已经有球按下了
		{
			if (mp_x > -7.5 && mp_x< -4.5 && mp_y> 2.5 && mp_y < 5.5 && balllist[0].ball_appear == true)
			{
				balllist[0].ball_click = true;
			}
			else if (mp_x > -3.5 && mp_x< -0.5 && mp_y > 2.5 && mp_y < 5.5 && balllist[1].ball_appear == true)
			{
				balllist[1].ball_click = true;
			}
			else if (mp_x > 0.5 && mp_x < 3.5 && mp_y > 2.5 && mp_y < 5.5 && balllist[2].ball_appear == true)
			{
				balllist[2].ball_click = true;
			}
			else if (mp_x > 4.5 && mp_x < 7.5 && mp_y > 2.5 && mp_y < 5.5 && balllist[3].ball_appear == true)
			{
				balllist[3].ball_click = true;
			}
			else if (mp_x > -7.5 && mp_x < -4.5 && mp_y > -1.5 && mp_y < 1.5 && balllist[4].ball_appear == true)
			{
				balllist[4].ball_click = true;
			}
			else if (mp_x > -3.5 && mp_x < -0.5 && mp_y > -1.5 && mp_y < 1.5 && balllist[5].ball_appear == true)
			{
				balllist[5].ball_click = true;
			}
			else if (mp_x > 0.5 && mp_x < 3.5 && mp_y > -1.5 && mp_y < 1.5 && balllist[6].ball_appear == true)
			{
				balllist[6].ball_click = true;
			}
			else if (mp_x > 4.5 && mp_x < 7.5 && mp_y > -1.5 && mp_y < 1.5 && balllist[7].ball_appear == true)
			{
				balllist[7].ball_click = true;
			}
			else if (mp_x > -7.5 && mp_x < -4.5 && mp_y > -5.5 && mp_y < -2.5 && balllist[8].ball_appear == true)
			{
				balllist[8].ball_click = true;
			}
			else if (mp_x > -3.5 && mp_x < -0.5 && mp_y > -5.5 && mp_y < -2.5 && balllist[9].ball_appear == true)
			{
				balllist[9].ball_click = true;
			}
			else if (mp_x > 0.5 && mp_x < 3.5 && mp_y > -5.5 && mp_y < -2.5 && balllist[10].ball_appear == true)
			{
				balllist[10].ball_click = true;
			}
			else if (mp_x > 4.5 && mp_x < 7.5 && mp_y > -5.5 && mp_y < -2.5 && balllist[11].ball_appear == true)
			{
				balllist[11].ball_click = true;
			}
			gameplay_ballstage = 4;
		}
	}

	//----------------------------------------------------------------------------------------------------------------------
	else if (control_ball_left_mouse_down == false){			//如果是键子被抬起来，判断是不是正确的球并熄灭
		arrow_onmoving = 0;				//释放滑块控制
		if (gameplay_ballstage == 4)
		{
			if (mp_x > -7.5 && mp_x< -4.5 && mp_y> 2.5 && mp_y < 5.5 && balllist[0].ball_appear == true && gameplay_balldownnum[0] != 1)
			{
				gameplay_balldownnum[1] = 1;
				if (ball_rand_color[gameplay_balldownnum[0] - 1] == ball_rand_color[0])
				{
					balllist[0].ball_appear = false;
					balllist[gameplay_balldownnum[0] - 1].ball_appear = false;			//将两个球都熄灭
					gameplay_ball_appearlist[0] = false;		//更新appear list
					gameplay_ball_appearlist[gameplay_balldownnum[0] - 1] = false;
				}
			}
			else if (mp_x > -3.5 && mp_x< -0.5 && mp_y > 2.5 && mp_y < 5.5 && balllist[1].ball_appear == true && gameplay_balldownnum[0] != 2)
			{
				gameplay_balldownnum[1] = 2;
				if (ball_rand_color[gameplay_balldownnum[0] - 1] == ball_rand_color[1])
				{
					balllist[1].ball_appear = false;
					balllist[gameplay_balldownnum[0] - 1].ball_appear = false;
					gameplay_ball_appearlist[1] = false;
					gameplay_ball_appearlist[gameplay_balldownnum[0] - 1] = false;
				}
			}
			else if (mp_x > 0.5 && mp_x < 3.5 && mp_y > 2.5 && mp_y < 5.5 && balllist[2].ball_appear == true && gameplay_balldownnum[0] != 3)
			{
				gameplay_balldownnum[1] = 3;
				if (ball_rand_color[gameplay_balldownnum[0] - 1] == ball_rand_color[2])
				{
					balllist[2].ball_appear = false;
					balllist[gameplay_balldownnum[0] - 1].ball_appear = false;
					gameplay_ball_appearlist[2] = false;
					gameplay_ball_appearlist[gameplay_balldownnum[0] - 1] = false;
				}
			}
			else if (mp_x > 4.5 && mp_x < 7.5 && mp_y > 2.5 && mp_y < 5.5 && balllist[3].ball_appear == true && gameplay_balldownnum[0] != 4)
			{
				gameplay_balldownnum[1] = 4;
				if (ball_rand_color[gameplay_balldownnum[0] - 1] == ball_rand_color[3])
				{
					balllist[3].ball_appear = false;
					balllist[gameplay_balldownnum[0] - 1].ball_appear = false;
					gameplay_ball_appearlist[3] = false;
					gameplay_ball_appearlist[gameplay_balldownnum[0] - 1] = false;
				}
			}
			else if (mp_x > -7.5 && mp_x < -4.5 && mp_y > -1.5 && mp_y < 1.5 && balllist[4].ball_appear == true && gameplay_balldownnum[0] != 5)
			{
				gameplay_balldownnum[1] = 5;
				if (ball_rand_color[gameplay_balldownnum[0] - 1] == ball_rand_color[4])
				{
					balllist[4].ball_appear = false;
					balllist[gameplay_balldownnum[0] - 1].ball_appear = false;
					gameplay_ball_appearlist[4] = false;
					gameplay_ball_appearlist[gameplay_balldownnum[0] - 1] = false;
				}
			}
			else if (mp_x > -3.5 && mp_x < -0.5 && mp_y > -1.5 && mp_y < 1.5 && balllist[5].ball_appear == true && gameplay_balldownnum[0] != 6)
			{
				gameplay_balldownnum[1] = 6;
				if (ball_rand_color[gameplay_balldownnum[0] - 1] == ball_rand_color[5])
				{
					balllist[5].ball_appear = false;
					balllist[gameplay_balldownnum[0] - 1].ball_appear = false;
					gameplay_ball_appearlist[5] = false;
					gameplay_ball_appearlist[gameplay_balldownnum[0] - 1] = false;
				}
			}
			else if (mp_x > 0.5 && mp_x < 3.5 && mp_y > -1.5 && mp_y < 1.5 && balllist[6].ball_appear == true && gameplay_balldownnum[0] != 7)
			{
				gameplay_balldownnum[1] = 7;
				if (ball_rand_color[gameplay_balldownnum[0] - 1] == ball_rand_color[6])
				{
					balllist[6].ball_appear = false;
					balllist[gameplay_balldownnum[0] - 1].ball_appear = false;
					gameplay_ball_appearlist[6] = false;
					gameplay_ball_appearlist[gameplay_balldownnum[0] - 1] = false;
				}
			}
			else if (mp_x > 4.5 && mp_x < 7.5 && mp_y > -1.5 && mp_y < 1.5 && balllist[7].ball_appear == true && gameplay_balldownnum[0] != 8)
			{
				gameplay_balldownnum[1] = 8;
				if (ball_rand_color[gameplay_balldownnum[0] - 1] == ball_rand_color[7])
				{
					balllist[7].ball_appear = false;
					balllist[gameplay_balldownnum[0] - 1].ball_appear = false;
					gameplay_ball_appearlist[7] = false;
					gameplay_ball_appearlist[gameplay_balldownnum[0] - 1] = false;
				}
			}
			else if (mp_x > -7.5 && mp_x < -4.5 && mp_y > -5.5 && mp_y < -2.5 && balllist[8].ball_appear == true && gameplay_balldownnum[0] != 9)
			{
				gameplay_balldownnum[1] = 9;
				if (ball_rand_color[gameplay_balldownnum[0] - 1] == ball_rand_color[8])
				{
					balllist[8].ball_appear = false;
					balllist[gameplay_balldownnum[0] - 1].ball_appear = false;
					gameplay_ball_appearlist[8] = false;
					gameplay_ball_appearlist[gameplay_balldownnum[0] - 1] = false;
				}
			}
			else if (mp_x > -3.5 && mp_x < -0.5 && mp_y > -5.5 && mp_y < -2.5 && balllist[9].ball_appear == true && gameplay_balldownnum[0] != 10)
			{
				gameplay_balldownnum[1] = 10;
				if (ball_rand_color[gameplay_balldownnum[0] - 1] == ball_rand_color[9])
				{
					balllist[9].ball_appear = false;
					balllist[gameplay_balldownnum[0] - 1].ball_appear = false;
					gameplay_ball_appearlist[9] = false;
					gameplay_ball_appearlist[gameplay_balldownnum[0] - 1] = false;
				}
			}
			else if (mp_x > 0.5 && mp_x < 3.5 && mp_y > -5.5 && mp_y < -2.5 && balllist[10].ball_appear == true && gameplay_balldownnum[0] != 11)
			{
				gameplay_balldownnum[1] = 11;
				if (ball_rand_color[gameplay_balldownnum[0] - 1] == ball_rand_color[10])
				{
					balllist[10].ball_appear = false;
					balllist[gameplay_balldownnum[0] - 1].ball_appear = false;
					gameplay_ball_appearlist[10] = false;
					gameplay_ball_appearlist[gameplay_balldownnum[0] - 1] = false;
				}
			}
			else if (mp_x > 4.5 && mp_x < 7.5 && mp_y > -5.5 && mp_y < -2.5 && balllist[11].ball_appear == true && gameplay_balldownnum[0] != 12)
			{
				gameplay_balldownnum[1] = 12;
				if (ball_rand_color[gameplay_balldownnum[0] - 1] == ball_rand_color[11])
				{
					balllist[11].ball_appear = false;
					balllist[gameplay_balldownnum[0] - 1].ball_appear = false;
					gameplay_ball_appearlist[11] = false;
					gameplay_ball_appearlist[gameplay_balldownnum[0] - 1] = false;
				}
			}		//如果没点对，就两个都变小
			
			balllist[gameplay_balldownnum[0] - 1].ball_click = false;
			balllist[gameplay_balldownnum[1] - 1].ball_click = false;
			gameplay_ballstage = 1;

			//如果有球灭了，看球数量够不够，不然就将灭的球换颜色，然后点亮
			gameplay_balldisapp_num = 0;
			for (int i = 0; i < 12; i++)
			{
				if (gameplay_ball_appearlist[i] == false)	gameplay_balldisapp_num++;		//算有几个被按下了
			}
			if (gameplay_balldisapp_num > 6)		//若果消失的比六个还多，就点让除了刚才消失的两个球之外的都亮
			{
				for (int x = 0; x < 12; x++)
				{
					if (balllist[x].ball_appear == false && gameplay_balldownnum[0] != x + 1 && gameplay_balldownnum[1] != x + 1)
					{
						balllist[x].ball_color = rand() % 4;
						balllist[x].ball_appear = true;
						gameplay_ball_appearlist[x] = true;
						ball_rand_color[x] = balllist[x].ball_color;
					}
				}
			}
		}
		else if (gameplay_ballstage == 2){
			gameplay_ballstage = 3;
		}
	}
}

void control_ball::control_ball_mouseevent_passive()
{
	light0_pos[0] = control_ball_mouseposition_x * 32.0 / 1366.0 - 16.0;		//光源位置随着鼠标位置变化
	light0_pos[1] = 9.0 - control_ball_mouseposition_y * 18.0 / 768.0;
	mouse.faci_ball_position[0] = light0_pos[0];							//鼠标位置变化
	mouse.faci_ball_position[1] = light0_pos[1];

	float mp_x = light0_pos[0];
	float mp_y = light0_pos[1];
	
	int color_num = -1;
	if (mp_x > -7.5 && mp_x< -4.5 && mp_y> 2.5 && mp_y < 5.5 && balllist[0].ball_appear == true)
	{
		color_num = balllist[0].ball_color;
	}
	else if (mp_x > -3.5 && mp_x< -0.5 && mp_y > 2.5 && mp_y < 5.5 && balllist[1].ball_appear == true)
	{
		color_num = balllist[1].ball_color;
	}
	else if (mp_x > 0.5 && mp_x < 3.5 && mp_y > 2.5 && mp_y < 5.5 && balllist[2].ball_appear == true)
	{
		color_num = balllist[2].ball_color;
	}
	else if (mp_x > 4.5 && mp_x < 7.5 && mp_y > 2.5 && mp_y < 5.5 && balllist[3].ball_appear == true)
	{
		color_num = balllist[3].ball_color;
	}
	else if (mp_x > -7.5 && mp_x < -4.5 && mp_y > -1.5 && mp_y < 1.5 && balllist[4].ball_appear == true)
	{
		color_num = balllist[4].ball_color;
	}
	else if (mp_x > -3.5 && mp_x < -0.5 && mp_y > -1.5 && mp_y < 1.5 && balllist[5].ball_appear == true)
	{
		color_num = balllist[5].ball_color;
	}
	else if (mp_x > 0.5 && mp_x < 3.5 && mp_y > -1.5 && mp_y < 1.5 && balllist[6].ball_appear == true)
	{
		color_num = balllist[6].ball_color;
	}
	else if (mp_x > 4.5 && mp_x < 7.5 && mp_y > -1.5 && mp_y < 1.5 && balllist[7].ball_appear == true)
	{
		color_num = balllist[7].ball_color;
	}
	else if (mp_x > -7.5 && mp_x < -4.5 && mp_y > -5.5 && mp_y < -2.5 && balllist[8].ball_appear == true)
	{
		color_num = balllist[8].ball_color;
	}
	else if (mp_x > -3.5 && mp_x < -0.5 && mp_y > -5.5 && mp_y < -2.5 && balllist[9].ball_appear == true)
	{
		color_num = balllist[9].ball_color;
	}
	else if (mp_x > 0.5 && mp_x < 3.5 && mp_y > -5.5 && mp_y < -2.5 && balllist[10].ball_appear == true)
	{
		color_num = balllist[10].ball_color;
	}
	else if (mp_x > 4.5 && mp_x < 7.5 && mp_y > -5.5 && mp_y < -2.5 && balllist[11].ball_appear == true)
	{
		color_num = balllist[11].ball_color;
	}

	switch (color_num){			//首先看鼠标球的颜色，再看level
	case 0:{
			   switch (balllist[0].ball_level)			//即时显示球的material
			   {
			   case 1: {
						   ball_ambient.word_disp = "ambient = { 0.0, 0.0, 0.0, 1.0 }";
						   ball_diffuse.word_disp = "diffuse = { 0.7, 0.0, 0.0, 1.0 }";
						   ball_specular.word_disp = "specular = { 0.0, 0.0, 0.0, 1.0 }";
						   break;
			   }
			   case 2: {
						   ball_ambient.word_disp = "ambient = { 0.7, 0.0, 0.0, 1.0 }";
						   ball_diffuse.word_disp = "diffuse = { 0.0, 0.0, 0.0, 1.0 }";
						   ball_specular.word_disp = "specular = { 0.0, 0.0, 0.0, 1.0 }";
						   break;
			   }
			   case 3: {
						   ball_ambient.word_disp = "ambient = { 0.1, 0.1, 0.1, 1.0 }";
						   ball_diffuse.word_disp = "diffuse = { 0.1, 0.1, 0.1, 1.0 }";
						   ball_specular.word_disp = "specular = { 0.7, 0.0, 0.0, 1.0 }";
						   break;
			   }
			   case 4: {
						   ball_ambient.word_disp = "ambient = { 0.7, 0.0, 0.0, 1.0 }";
						   ball_diffuse.word_disp = "diffuse = { 0.0, 0.0, 0.0, 1.0 }";
						   ball_specular.word_disp = "specular = { 0.0, 0.0, 0.0, 1.0 }";
						   break;
			   }
			   case 5:{
						  ball_ambient.word_disp = "ambient = { 1.0, 1.0, 1.0, 1.0 }";
						  ball_diffuse.word_disp = "diffuse = { 1.0, 0.0, 0.0, 1.0 }";
						  ball_specular.word_disp = "specular = { 0.0, 1.0, 0.0, 1.0 }";
						  break;
			   }
			   }
			   break;
	}
	case 1:{
			   switch (balllist[0].ball_level)			//即时显示球的material
			   {
			   case 1: {
						   ball_ambient.word_disp = "ambient = { 0.0, 0.0, 0.0, 1.0 }";
						   ball_diffuse.word_disp = "diffuse = { 0.0, 0.0, 0.7, 1.0 }";
						   ball_specular.word_disp = "specular = { 0.0, 0.0, 0.0, 1.0 }";
						   break;
			   }
			   case 2: {
						   ball_ambient.word_disp = "ambient = { 0.0, 0.0, 0.7, 1.0 }";
						   ball_diffuse.word_disp = "diffuse = { 0.0, 0.0, 0.0, 1.0 }";
						   ball_specular.word_disp = "specular = { 0.0, 0.0, 0.0, 1.0 }";
						   break;
			   }
			   case 3: {
						   ball_ambient.word_disp = "ambient = { 0.1, 0.1, 0.1, 1.0 }";
						   ball_diffuse.word_disp = "diffuse = { 0.1, 0.1, 0.1, 1.0 }";
						   ball_specular.word_disp = "specular = { 0.0, 0.0, 0.7, 1.0 }";
						   break;
			   }
			   case 4: {
						   ball_ambient.word_disp = "ambient = { 0.0, 0.0, 0.0, 1.0 }";
						   ball_diffuse.word_disp = "diffuse = { 0.7, 0.0, 0.0, 1.0 }";
						   ball_specular.word_disp = "specular = { 0.0, 0.0, 0.0, 1.0 }";
						   break;
			   }
			   case 5:{
						  ball_ambient.word_disp = "ambient = { 0.0, 0.0, 0.0, 1.0 }";
						  ball_diffuse.word_disp = "diffuse = { 1.0, 1.0, 1.0, 1.0 }";
						  ball_specular.word_disp = "specular = { 1.0, 0.0, 0.0, 1.0 }";
						  break;
			   }
			   }
			   break;
	}
	case 2:{
			   switch (balllist[0].ball_level)			//即时显示球的material
			   {
			   case 1: {
						   ball_ambient.word_disp = "ambient = { 0.0, 0.0, 0.0, 1.0 }";
						   ball_diffuse.word_disp = "diffuse = { 0.0, 0.7, 0.0, 1.0 }";
						   ball_specular.word_disp = "specular = { 0.0, 0.0, 0.0, 1.0 }";
						   break;
			   }
			   case 2: {
						   ball_ambient.word_disp = "ambient = { 0.0, 0.7, 0.0, 1.0 }";
						   ball_diffuse.word_disp = "diffuse = { 0.0, 0.0, 0.0, 1.0 }";
						   ball_specular.word_disp = "specular = { 0.0, 0.0, 0.0, 1.0 }";
						   break;
			   }
			   case 3: {
						   ball_ambient.word_disp = "ambient = { 0.1, 0.1, 0.1, 1.0 }";
						   ball_diffuse.word_disp = "diffuse = { 0.1, 0.1, 0.1, 1.0 }";
						   ball_specular.word_disp = "specular = { 0.0, 0.7, 0.0, 1.0 }";
						   break;
			   }
			   case 4: {
						   ball_ambient.word_disp = "ambient = { 0.0, 0.0, 0.0, 1.0 }";
						   ball_diffuse.word_disp = "diffuse = { 0.0, 0.0, 0.0, 1.0 }";
						   ball_specular.word_disp = "specular = { 0.7, 0.0, 0.0, 1.0 }";
						   break;
			   }
			   case 5:{
						  ball_ambient.word_disp = "ambient = { 0.0, 1.0, 0.0, 1.0 }";
						  ball_diffuse.word_disp = "diffuse = { 1.0, 1.0, 1.0, 1.0 }";
						  ball_specular.word_disp = "specular = { 1.0, 1.0, 1.0, 1.0 }";
						  break;
			   }
			   }
			   break;
	}
	case 3:{
			   switch (balllist[0].ball_level)			//即时显示球的material
			   {
			   case 1: {
						   ball_ambient.word_disp = "ambient = { 0.0, 0.0, 0.0, 1.0 }";
						   ball_diffuse.word_disp = "diffuse = { 0.7, 0.0, 0.7, 1.0 }";
						   ball_specular.word_disp = "specular = { 0.0, 0.0, 0.0, 1.0 }";
						   break;
			   }
			   case 2: {
						   ball_ambient.word_disp = "ambient = { 0.7, 0.0, 0.7, 1.0 }";
						   ball_diffuse.word_disp = "diffuse = { 0.0, 0.0, 0.0, 1.0 }";
						   ball_specular.word_disp = "specular = { 0.0, 0.0, 0.0, 1.0 }";
						   break;
			   }
			   case 3: {
						   ball_ambient.word_disp = "ambient = { 0.1, 0.1, 0.1, 1.0 }";
						   ball_diffuse.word_disp = "diffuse = { 0.1, 0.1, 0.1, 1.0 }";
						   ball_specular.word_disp = "specular = { 0.7, 0.0, 0.7, 1.0 }";
						   break;
			   }
			   case 4: {
						   ball_ambient.word_disp = "ambient = { 0.9, 0.0, 0.0, 1.0 }";
						   ball_diffuse.word_disp = "diffuse = { 0.9, 0.0, 0.0, 1.0 }";
						   ball_specular.word_disp = "specular = { 0.9, 0.0, 0.0, 1.0 }";
						   break;
			   }
			   case 5:{
						  ball_ambient.word_disp = "ambient = { 0.0, 0.0, 1.0, 1.0 }";
						  ball_diffuse.word_disp = "diffuse = { 0.0, 1.0, 0.0, 1.0 }";
						  ball_specular.word_disp = "specular = { 1.0, 0.0, 0.0, 1.0 }";
						  break;
			   }
			   }
			   break;
	}
	}
	
if (light0_pos[0] > 12.5 && light0_pos[0] < 15.5 && light0_pos[1] > 4.5 && light0_pos[1] < 7.5)
	{
		control_ball_blo_on = 1;
	}
	else if (light0_pos[0] > 12.5 && light0_pos[0] < 15.5 && light0_pos[1] > 1.5 && light0_pos[1] < 4.5)
	{
		control_ball_blo_on = 2;
	}
	else if (light0_pos[0] > 12.5 && light0_pos[0] < 15.5 && light0_pos[1] > -1.5 && light0_pos[1] < 1.5)
	{
		control_ball_blo_on = 3;
	}
	else if (light0_pos[0] > 12.5 && light0_pos[0] < 15.5 && light0_pos[1] > -4.5 && light0_pos[1] < -1.5)
	{
		control_ball_blo_on = 4;
	}
	else if (light0_pos[0] > 12.5 && light0_pos[0] < 15.5 && light0_pos[1] > -7.5 && light0_pos[1] < -4.5)
	{
		control_ball_blo_on = 5;
	}
	else if (light0_pos[0] > -15.0 && light0_pos[0] < -14.0 && light0_pos[1] > 6.5 && light0_pos[1] < 7.5)
	{
		control_ball_blo_on = 6;
	}
	else{
		control_ball_blo_on = 0;
	}
}

void control_ball::control_ball_mouseevent_motion()
{
	light0_pos[0] = control_ball_mouseposition_x * 32.0 / 1366.0 - 16.0;		//光源位置随着鼠标位置变化
	light0_pos[1] = 9.0 - control_ball_mouseposition_y * 18.0 / 768.0;
	mouse.faci_ball_position[0] = light0_pos[0];							//鼠标位置变化
	mouse.faci_ball_position[1] = light0_pos[1];

	if (balllist[0].ball_level == 5)
	{
		//根据滑块的位置算该调的光度
		switch (arrow_onmoving){
		case 1:
		{
				  if (light0_pos[1] > -5.0 && light0_pos[1] < -3.0)
				  {
					  faci_ball_arrow1.faci_ball_position[1] = light0_pos[1];
					  light_change[0] = 0.5 * faci_ball_arrow1.faci_ball_position[1] + 2.5;
				  }
				  break;
		}
		case 2:
		{
				  if (light0_pos[1] > -5.0 && light0_pos[1] < -3.0)
				  {
					  faci_ball_arrow2.faci_ball_position[1] = light0_pos[1];
					  light_change[1] = 0.5 * faci_ball_arrow2.faci_ball_position[1] + 2.5;
				  }
				  break;
		}
		case 3:
		{
				  if (light0_pos[1] > -5.0 && light0_pos[1] < -3.0)
				  {
					  faci_ball_arrow3.faci_ball_position[1] = light0_pos[1];
					  light_change[2] = 0.5 * faci_ball_arrow3.faci_ball_position[1] + 2.5;
				  }
				  break;
		}
		}

		//根据当前颜色，调节光度
		switch (control_light_color){
		case 1:
		{
				  light0_ambient[0] = light_change[0];
				  light0_diffuse[0] = light_change[1];
				  light0_specular[0] = light_change[2];
				  break;
		}
		case 2:
		{
				  light0_ambient[0] = light_change[0];
				  light0_ambient[1] = light_change[0];

				  light0_diffuse[0] = light_change[1];
				  light0_diffuse[1] = light_change[1];

				  light0_specular[0] = light_change[2];
				  light0_specular[1] = light_change[2];
				  break;
		}
		case 3:
		{
				  light0_ambient[1] = light_change[0];
				  light0_diffuse[1] = light_change[1];
				  light0_specular[1] = light_change[2];
				  break;
		}
		case 4:
		{
				  light0_ambient[2] = light_change[0];
				  light0_diffuse[2] = light_change[1];
				  light0_specular[2] = light_change[2];
				  break;
		}
		case 5:
		{
				  light0_ambient[1] = light_change[0];
				  light0_ambient[2] = light_change[0];
				  light0_diffuse[1] = light_change[1];
				  light0_diffuse[2] = light_change[1];
				  light0_specular[1] = light_change[2];
				  light0_specular[2] = light_change[2];
				  break;
		}
		case 6:
		{
				  light0_ambient[0] = light_change[0];
				  light0_ambient[2] = light_change[0];

				  light0_diffuse[0] = light_change[1];
				  light0_diffuse[2] = light_change[1];

				  light0_specular[0] = light_change[2];
				  light0_specular[2] = light_change[2];
				  break;
		}
		case 0:
		{
				  light0_ambient[0] = light_change[0];
				  light0_ambient[1] = light_change[0];
				  light0_ambient[2] = light_change[0];

				  light0_diffuse[0] = light_change[1];
				  light0_diffuse[1] = light_change[1];
				  light0_diffuse[2] = light_change[1];

				  light0_specular[0] = light_change[2];
				  light0_specular[1] = light_change[2];
				  light0_specular[2] = light_change[2];
				  break;
		}
		}
	}
}