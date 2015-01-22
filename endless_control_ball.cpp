#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <ctime>
#include <GL/glut.h>
#include <GL/glaux.h>
#include "endless_control_ball.h"
#include "ball.h"
#include "faci_ball.h"
#include "word.h"
#pragma comment(lib, "glaux")
using namespace std;

int endless_gameplay_ballstage = 1;		//是否有球被按下去了, 1=没有按， 2=第一个球被按了还没抬， 3=等待第二个球被按， 4=第二个球被按
int endless_gameplay_balldownnum[2];			//被按下去的球是哪两个，第一个和第二个
int endless_gameplay_balldisapp_num = 0;
bool endless_gameplay_ball_appearlist[12] = { true, true, true, true, true, true, true, true, true, true, true, true };

int endless_gameplay_wallstage = 0;		//记录墙的移动，0=原位，6=消了六对球

float endless_gameplay_rand_updown[4][9];
float endless_gameplay_light_updown[6][3];

int endless_gameplay_eliballnum = 0;
bool endless_gameplay_scene = false; //fasle = game, true = select
int endless_gameplay_blockon;		//现在鼠标在哪个方块上

int endless_control_ball_gamelevel = 1;//=================调关----------------------------------------------------------------
int endless_control_ball_toplevel = 30;	//记录现在最高的level

//----------------------------------  balls  -----------------------------------------------------
float endless_x = 4.0;	//球心距离, r=1.5

float endless_ball1_position[3] = { -1.5*endless_x, endless_x, 0.0 };		//球1的位置
float endless_ball2_position[3] = { -0.5*endless_x, endless_x, 0.0 };		//球2的位置
float endless_ball3_position[3] = { 0.5*endless_x, endless_x, 0.0 };		//球3的位置
float endless_ball4_position[3] = { 1.5*endless_x, endless_x, 0.0 };		//球4的位置
float endless_ball5_position[3] = { -1.5*endless_x, 0.0, 0.0 };		//球5的位置
float endless_ball6_position[3] = { -0.5*endless_x, 0.0, 0.0 };		//球6的位置
float endless_ball7_position[3] = { 0.5*endless_x, 0.0, 0.0 };		//球7的位置
float endless_ball8_position[3] = { 1.5*endless_x, 0.0, 0.0 };		//球8的位置
float endless_ball9_position[3] = { -1.5*endless_x, -endless_x, 0.0 };		//球9的位置
float endless_ball10_position[3] = { -0.5*endless_x, -endless_x, 0.0 };		//球10的位置
float endless_ball11_position[3] = { 0.5*endless_x, -endless_x, 0.0 };		//球11的位置
float endless_ball12_position[3] = { 1.5*endless_x, -endless_x, 0.0 };		//球12的位置

int endless_ball_rand_color[12];
float endless_ball_r[12] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
float endless_ball_r_big = 1.75;		//变大的半径
float endless_ball_r_small = 1.5;

//------------------------------------------  facilities  -----------------------------------------------
int endless_facilities1_kind = 1;
float endless_facilities1_position[3] = { 0.0, 0.0, 0.0 };
float endless_facilities1_size[3] = { 16.0, 9.0, 0.0 };
GLfloat endless_facilities1_color_ambient[4] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat endless_facilities1_color_diffuse[4] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat endless_facilities1_color_specular[4] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat endless_facilities1_color_shine = 5.0;

float endless_mouse_position[3] = { 0.0, 0.0, 2.0 };
float endless_mouse_size[3] = { 0.2, 0.0, 0.0 };
GLfloat endless_mouse_color_ambient[4] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat endless_mouse_color_diffuse[4] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat endless_mouse_color_specular[4] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat endless_mouse_color_shine = 5.0;

faci_ball endless_lightwall(endless_facilities1_kind, endless_facilities1_position, endless_facilities1_size, endless_facilities1_color_ambient, endless_facilities1_color_diffuse, endless_facilities1_color_specular, endless_facilities1_color_shine, true);
faci_ball endless_mouse(2, endless_mouse_position, endless_mouse_size, endless_mouse_color_ambient, endless_mouse_color_diffuse, endless_mouse_color_specular, endless_mouse_color_shine, true);

//--------------------------------------------关卡贴图--------------------------------------------------

float G1_pos[3] = { -7.5, 6.0, 1.0 };
float G_size[3] = { 2.4, 2.4, 0.0 };

float G2_pos[3] = { -4.5, 6.0, 1.0 };
float G3_pos[3] = { -1.5, 6.0, 1.0 };
float G4_pos[3] = { 1.5, 6.0, 1.0 };
float G5_pos[3] = { 4.5, 6.0, 1.0 };
float G6_pos[3] = { 7.5, 6.0, 1.0 };
float G7_pos[3] = { -7.5, 3.0, 1.0 };
float G8_pos[3] = { -4.5, 3.0, 1.0 };
float G9_pos[3] = { -1.5, 3.0, 1.0 };
float G10_pos[3] = { 1.5, 3.0, 1.0 };
float G11_pos[3] = { 4.5, 3.0, 1.0 };
float G12_pos[3] = { 7.5, 3.0, 1.0 };
float G13_pos[3] = { -7.5, 0.0, 1.0 };
float G14_pos[3] = { -4.5, 0.0, 1.0 };
float G15_pos[3] = { -1.5, 0.0, 1.0 };
float G16_pos[3] = { 1.5, 0.0, 1.0 };
float G17_pos[3] = { 4.5, 0.0, 1.0 };
float G18_pos[3] = { 7.5, 0.0, 1.0 };
float G19_pos[3] = { -7.6, -3.0, 1.0 };
float G20_pos[3] = { -4.5, -3.0, 1.0 }; 
float G21_pos[3] = { -1.5, -3.0, 1.0 };
float G22_pos[3] = { 1.5, -3.0, 1.0 };
float G23_pos[3] = { 4.5, -3.0, 1.0 };
float G24_pos[3] = { 7.5, -3.0, 1.0 };
float G25_pos[3] = { -7.5, -6.0, 1.0 };
float G26_pos[3] = { -4.5, -6.0, 1.0 };
float G27_pos[3] = { -1.5, -6.0, 1.0 };
float G28_pos[3] = { 1.5, -6.0, 1.0 };
float G29_pos[3] = { 4.5, -6.0, 1.0 };
float G30_pos[3] = { 7.5, -6.0, 1.0 };

float endless_pos[3] = { 10.5, -6, 1.0 };

faci_ball Glist[31] = {
	faci_ball(3, G1_pos, G_size, 8, false),
	faci_ball(3, G2_pos, G_size, 9, false),
	faci_ball(3, G3_pos, G_size, 10, false),
	faci_ball(3, G4_pos, G_size, 11, false),
	faci_ball(3, G5_pos, G_size, 12, false),
	faci_ball(3, G6_pos, G_size, 13, false),
	faci_ball(3, G7_pos, G_size, 14, false),
	faci_ball(3, G8_pos, G_size, 15, false),
	faci_ball(3, G9_pos, G_size, 16, false),
	faci_ball(3, G10_pos, G_size, 17, false),
	faci_ball(3, G11_pos, G_size, 18, false),
	faci_ball(3, G12_pos, G_size, 19, false),
	faci_ball(3, G13_pos, G_size, 20, false),
	faci_ball(3, G14_pos, G_size, 21, false),
	faci_ball(3, G15_pos, G_size, 22, false),
	faci_ball(3, G16_pos, G_size, 23, false),
	faci_ball(3, G17_pos, G_size, 24, false),
	faci_ball(3, G18_pos, G_size, 25, false),
	faci_ball(3, G19_pos, G_size, 26, false),
	faci_ball(3, G20_pos, G_size, 27, false),
	faci_ball(3, G21_pos, G_size, 28, false),
	faci_ball(3, G22_pos, G_size, 29, false),
	faci_ball(3, G23_pos, G_size, 30, false),
	faci_ball(3, G24_pos, G_size, 31, false),
	faci_ball(3, G25_pos, G_size, 32, false),
	faci_ball(3, G26_pos, G_size, 33, false),
	faci_ball(3, G27_pos, G_size, 34, false),
	faci_ball(3, G28_pos, G_size, 35, false),
	faci_ball(3, G29_pos, G_size, 36, false),
	faci_ball(3, G30_pos, G_size, 37, false),
	faci_ball(3, endless_pos, G_size, 38, false)
};

float Gscore_pos[3] = { 14.0, 1.5, 1.0 };
float Gcontrol_size[3] = { 2.85, 2.85, 0.0 };

float Gcontrol_pos[3] = { 14.0, -1.5, 1.0 };

float endless_home_pos[3] = { -14.5, 7.0, 1.0 };
float endless_home_size[3] = { 1.0, 1.0, 1.0 };

float endless_wallpaper_pos[3] = { 0.0, 0.0, 0.0 };
float endless_wallpaper_size[3] = { 32.0, 18.0, 0.0 };

faci_ball Gscore(3, Gscore_pos, Gcontrol_size, 8, true);
faci_ball Gcontrol(3, Gcontrol_pos, Gcontrol_size, 69, true);
faci_ball endless_home(3, endless_home_pos, endless_home_size, 7, true);
faci_ball endless_wallpaper(3, endless_wallpaper_pos, endless_wallpaper_size, 39, true);

//--------------------------------------------  lights  -------------------------------------------------
GLfloat endless_light0_pos[4] = { 0.0, 0.0, 9.0, 1.0 };				//光源0，手电筒光源
GLfloat endless_light0_ambient[4] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat endless_light0_diffuse[4] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat endless_light0_specular[4] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat endless_light0_amb_ori[4] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat endless_light0_dif_ori[4] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat endless_light0_spec_ori[4] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat endless_light0_cutoff = 30;		//截止角
GLfloat endless_light0_spotdirection[3] = { 0.0, 0.0, -1.0 };

GLfloat endless_light1_pos[4] = { 0.0, 0.0, 9.0, 0.0 };				//光源2，常光源
GLfloat endless_light1_ambient[4] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat endless_light1_diffuse[4] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat endless_light1_specular[4] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat endless_light1_amb_ori[4] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat endless_light1_dif_ori[4] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat endless_light1_spec_ori[4] = { 0.1, 0.1, 0.1, 1.0 };

//------------------------------------------  news  ------------------------------------------------------
ball endless_balllist[12] = {
	ball(endless_ball1_position, endless_ball_rand_color[0], endless_ball_r[0], true),	//将所有需要用到的object在这里声明
	ball(endless_ball2_position, endless_ball_rand_color[1], endless_ball_r[1], true),
	ball(endless_ball3_position, endless_ball_rand_color[2], endless_ball_r[2], true),
	ball(endless_ball4_position, endless_ball_rand_color[3], endless_ball_r[3], true),
	ball(endless_ball5_position, endless_ball_rand_color[4], endless_ball_r[4], true),
	ball(endless_ball6_position, endless_ball_rand_color[5], endless_ball_r[5], true),
	ball(endless_ball7_position, endless_ball_rand_color[6], endless_ball_r[6], true),
	ball(endless_ball8_position, endless_ball_rand_color[7], endless_ball_r[7], true),
	ball(endless_ball9_position, endless_ball_rand_color[8], endless_ball_r[8], true),
	ball(endless_ball10_position, endless_ball_rand_color[9], endless_ball_r[9], true),
	ball(endless_ball11_position, endless_ball_rand_color[10], endless_ball_r[10], true),
	ball(endless_ball12_position, endless_ball_rand_color[11], endless_ball_r[11], true),
};


//----------------------------------word--------------------------------------------------------------------



//---------------------------------------------------------------------------------------------------------



endless_control_ball::endless_control_ball()		//中间类的构建器
{

}

void endless_control_ball::endless_control_ball_randballcolor()		//用来产生随机球的material
{
	for (int i = 0; i < 12; i++)		//先全部归零
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				endless_balllist[i].endless_color_ambient[j][i] = 0.0;
				endless_balllist[i].endless_color_diffuse[j][i] = 0.0;
				endless_balllist[i].endless_color_specular[j][i] = 0.0;
			}
		}
		
	}

	for (int i = 0; i < 3; i++)
	{
		endless_light0_ambient[i] = endless_light0_amb_ori[i];
		endless_light0_diffuse[i] = endless_light0_dif_ori[i];
		endless_light0_specular[i] = endless_light0_spec_ori[i];
		endless_light1_ambient[i] = endless_light1_amb_ori[i];
		endless_light1_diffuse[i] = endless_light1_dif_ori[i];
		endless_light1_specular[i] = endless_light1_spec_ori[i];
	}

	//---------------------------------随机出四种颜色-------------------------------------------------
	//srand((int)time(0));

	if (endless_control_ball_gamelevel <= 5)//-------------------------------------------level5--------------------------------------
	{
		float color[4][3];

		for (int j = 0; j < 4; j++)		//三原色
		{
			for (int i = 0; i < 3; i++)		//四个颜色
			{
				color[j][i] = (float)(rand() % 80) / 100;
			}
		}

		for (int c = 0; c < 4; c++)
		{
			for (int i = 0; i < 12; i++)
			{
				endless_balllist[i].endless_color_diffuse[c][0] = color[c][0];
				endless_balllist[i].endless_color_diffuse[c][1] = color[c][1];
				endless_balllist[i].endless_color_diffuse[c][2] = color[c][2];

				endless_balllist[i].endless_color_ambient[c][0] = color[c][0];
				endless_balllist[i].endless_color_ambient[c][1] = color[c][1];
				endless_balllist[i].endless_color_ambient[c][2] = color[c][2];

				endless_balllist[i].endless_color_specular[c][0] = color[c][0];
				endless_balllist[i].endless_color_specular[c][1] = color[c][1];
				endless_balllist[i].endless_color_specular[c][2] = color[c][2];
			}
		}
		
	}
	else if (endless_control_ball_gamelevel > 5 && endless_control_ball_gamelevel <= 10)//---------------------level10--------------------
	{
		float color[4][3];

		for (int i = 0; i < 3; i++)		//三原色
		{
			for (int j = 0; j < 4; j++)		//四个颜色
			{
				color[j][i] = (float)(rand() % 80) / 100;
			}
		}

		for (int c = 0; c < 4; c++)
		{
			for (int i = 0; i < 12; i++)
			{
				endless_balllist[i].endless_color_diffuse[c][0] = color[c][0];
				endless_balllist[i].endless_color_diffuse[c][1] = color[c][1];
				endless_balllist[i].endless_color_diffuse[c][2] = color[c][2];
				
				endless_balllist[i].endless_color_ambient[c][0] = color[c][2];
				endless_balllist[i].endless_color_ambient[c][1] = color[c][0];
				endless_balllist[i].endless_color_ambient[c][2] = color[c][1];

				endless_balllist[i].endless_color_specular[c][0] = color[c][1];
				endless_balllist[i].endless_color_specular[c][1] = color[c][2];
				endless_balllist[i].endless_color_specular[c][2] = color[c][0];
			}
		}
	}
	else if (endless_control_ball_gamelevel > 10 && endless_control_ball_gamelevel <= 20)//---------------------------level 10-20------------
	{
		float color[3];
		float material[4][3];

		for (int i = 0; i < 3; i++)		//三原色
		{
			color[i] = (float)(rand() % 100) / 100;
			
		}
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				material[j][i] = float(rand() % 100) / 100;		//随机比重,4种颜色，3个维度
			}
		}		

		float sum = color[0] + color[1] + color[2];

		for (int c = 0; c < 4; c++)
		{
			for (int i = 0; i < 12; i++)
			{
				endless_balllist[i].endless_color_ambient[c][0] = material[c][0] * ((float) color[0] / sum);		//r
				endless_balllist[i].endless_color_ambient[c][1] = material[c][0] * ((float) color[1] / sum);		//g
				endless_balllist[i].endless_color_ambient[c][2] = material[c][0] * ((float) color[2] / sum);		//b

				endless_balllist[i].endless_color_diffuse[c][0] = material[c][1] * ((float) color[0] / sum);
				endless_balllist[i].endless_color_diffuse[c][1] = material[c][1] * ((float) color[1] / sum);
				endless_balllist[i].endless_color_diffuse[c][2] = material[c][1] * ((float) color[2] / sum);

				endless_balllist[i].endless_color_specular[c][0] = material[c][2] * ((float) color[0] / sum);
				endless_balllist[i].endless_color_specular[c][1] = material[c][2] * ((float) color[1] / sum);
				endless_balllist[i].endless_color_specular[c][2] = material[c][2] * ((float) color[2] / sum);
			}
		}
	}
	else if (endless_control_ball_gamelevel > 20)	//光变，球也变-----------------------------------level 20+---------------
	{
		float color[3][3];
		for (int c = 0; c < 4; c++)
		{
			
			for (int i = 0; i < 3; i++)		//三原色
			{
				for (int j = 0; j < 3; j++)		//三个material
				{
					color[j][i] = (float)(rand() % 80) / 100;
				}
			}

			for (int i = 0; i < 3; i++)
			{
				for (int x = 0; x < 12; x++)
				{
					endless_balllist[x].endless_color_diffuse[c][i] = color[0][i];
					endless_balllist[x].endless_color_ambient[c][i] = color[1][i];
					endless_balllist[x].endless_color_specular[c][i] = color[2][i];
				}
			}
		}
	}
	else if (endless_control_ball_gamelevel > 30)
	{
		float color[3][3];
		for (int c = 0; c < 4; c++)
		{

			for (int i = 0; i < 3; i++)		//三原色
			{
				for (int j = 0; j < 3; j++)		//三个material
				{
					color[j][i] = (float)(rand() % 80) / 100;
				}
			}

			for (int i = 0; i < 3; i++)
			{
				for (int x = 0; x < 12; x++)
				{
					endless_balllist[x].endless_color_diffuse[c][i] = color[0][i];
					endless_balllist[x].endless_color_ambient[c][i] = color[1][i];
					endless_balllist[x].endless_color_specular[c][i] = color[2][i];
				}
			}
		}
		for (int p = 0; p < 3; p++)
		{
			endless_light0_ambient[p] = (float)(rand() % 80) / 100;
			endless_light0_diffuse[p] = (float)(rand() % 80) / 100;
			endless_light0_specular[p] = (float)(rand() % 80) / 100;
			endless_light1_ambient[p] = (float)(rand() % 80) / 100;
			endless_light1_diffuse[p] = (float)(rand() % 80) / 100;
			endless_light1_specular[p] = (float)(rand() % 80) / 100;
		}
	}
}

void endless_control_ball::endless_control_ball_init()			//设定初始半径和变大变小
{
	Gcontrol.faci_ball_settexture();
	Gcontrol.faci_ball_texture_scale = 1.0;
	Gscore.faci_ball_texture_scale = 1.0;
	endless_wallpaper.faci_ball_texture_scale = 1.0;
	for (int i = 0; i < 31; i++)
	{
		Glist[i].faci_ball_texture_scale = 1.0;
		Glist[i].faci_ball_appear = false;	//防止打开选关页面退出游戏再进游戏之后字帖出现的状况
	}

	Gcontrol.faci_ball_appear = true;
	endless_gameplay_scene = false;

	endless_home.faci_ball_texture_scale = 1.0;

	endless_control_ball_left_mouse_down = false;

	endless_balllist[2].ball_position[2] = 0.0; //不知道为何会自动变成1
	
	srand((int)time(0));

	for (int i = 0; i < 12; i++)
	{
		endless_ball_rand_color[i] = rand() % 4;			//随机颜色
		endless_balllist[i].ball_color = endless_ball_rand_color[i];
		endless_balllist[i].ball_click = false;

		endless_balllist[i].ball_appear = true;
		endless_balllist[i].ball_r = 0.0;
		endless_balllist[i].endlessmode = true;

		endless_balllist[i].endless_color_shine[0] = 1.0;
		endless_balllist[i].endless_color_shine[1] = 1.0;
		endless_balllist[i].endless_color_shine[2] = 1.0;
		endless_balllist[i].endless_color_shine[3] = 1.0;

		endless_control_ball_randballcolor();
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			endless_gameplay_rand_updown[i][j] = (float)(rand() % 2) * 2.0 - 1.0;
		}
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			endless_gameplay_light_updown[i][j] = (float)(rand() % 2) * 2.0 - 1.0;
		}
	}
}

void endless_control_ball::endless_control_ball_idle()			//球变大变小
{
	for (int i = 0; i < 12; i++)
	{
		endless_balllist[i].ball_turnbig();
		endless_balllist[i].ball_turnsmall();

		endless_balllist[i].click_small();
		endless_balllist[i].click_big();
	}

	if (endless_gameplay_scene == false)		//如果是在游戏中，只有两个键子
	{
		Gcontrol.faci_ball_emerge();
		Gscore.faci_ball_emerge();

		switch (endless_gameplay_wallstage)		//墙移动
		{
		case 0:
		{
				  if (endless_lightwall.faci_ball_position[0] > 0.0)	//如果大于0.0就要往回缩
				  {
					  endless_lightwall.faci_ball_position[0] -= 0.1 * endless_lightwall.faci_ball_position[0];
				  }
				  else if (endless_lightwall.faci_ball_position[0] < 0.0)
				  {
					  endless_wallpaper.faci_ball_position[0] += -0.02 * endless_lightwall.faci_ball_position[0] + 0.1;
					  endless_lightwall.faci_ball_position[0] += -0.02 * endless_lightwall.faci_ball_position[0] + 0.1;
					  
					  if (endless_lightwall.faci_ball_position[0] > -0.1)
					  {
						  
						  endless_wallpaper.faci_ball_color = rand() % 30 + 39;
						  cout << endless_wallpaper.faci_ball_color << endl;
					  }
				  }
				  break;
		}
		case 1:		//如果是第一页
		{
				  if (endless_lightwall.faci_ball_position[0] < 5.0)
				  {
					  endless_lightwall.faci_ball_position[0] += -0.1 * endless_lightwall.faci_ball_position[0] + 0.5;
				  }
				  if (endless_lightwall.faci_ball_position[0] > 0.3)
				  {
					  endless_wallpaper.faci_ball_position[0] = 0.0;
				  }
				  break;
		}
		case 2:
		{
				  if (endless_lightwall.faci_ball_position[0] < 10.0)
				  {
					  endless_lightwall.faci_ball_position[0] += -0.1 * endless_lightwall.faci_ball_position[0] + 1.0;
				  }
				  if (endless_lightwall.faci_ball_position[0] > 0.3)
				  {
					  endless_wallpaper.faci_ball_position[0] = 0.0;
				  }
				  break;
		}
		case 3:
		{
				  if (endless_lightwall.faci_ball_position[0] < 15.0)
				  {
					  endless_lightwall.faci_ball_position[0] += -0.1 * endless_lightwall.faci_ball_position[0] + 1.5;
				  }
				  break;
		}
		case 4:
		{
				  if (endless_lightwall.faci_ball_position[0] < 20.0)
				  {
					  endless_lightwall.faci_ball_position[0] += -0.1 * endless_lightwall.faci_ball_position[0] + 2.0;
				  }
				  break;
		}
		case 5:
		{
				  if (endless_lightwall.faci_ball_position[0] < 25.0)
				  {
					  endless_lightwall.faci_ball_position[0] += -0.1 * endless_lightwall.faci_ball_position[0] + 2.5;
				  }
				  break;
		}
		case 6:
		{
				  
				  endless_lightwall.faci_ball_position[0] += -0.01 * endless_lightwall.faci_ball_position[0] + 1.75;

				  if (endless_lightwall.faci_ball_position[0] >= 35.0)
				  {
					  endless_lightwall.faci_ball_position[0] = -32.0;
					  endless_gameplay_wallstage = 0;

					  endless_control_ball_gamelevel++;		//升高一关
					  for (int i = 0; i < 12; i++)			//将球收回
					  {
						  endless_balllist[i].ball_r = 0.0;
						  endless_ball_rand_color[i] = rand() % 4;			//随机颜色
						  endless_balllist[i].ball_color = endless_ball_rand_color[i];
						  endless_balllist[i].ball_appear = true;
						  endless_gameplay_ball_appearlist[i] = true;
					  }
					  endless_control_ball_randballcolor();		//重新分配颜色
					  endless_gameplay_eliballnum = 0;		//重新开始记正确对数

					  if (endless_control_ball_gamelevel <= 30)
					  {
						  Gscore.faci_ball_color = endless_control_ball_gamelevel + 7;
					  }
					  else if (endless_control_ball_gamelevel > 30)
					  {
						  Gscore.faci_ball_color = 38;
					  }

					  if (endless_control_ball_gamelevel > endless_control_ball_toplevel)
					  {
						  endless_control_ball_toplevel++;
					  }
				  }
				  break;
		}
		}

		
		switch (endless_gameplay_blockon)	//键子大小变化
		{
		case -1:
		{
				   Gcontrol.faci_ball_turnbig();
				   endless_home.faci_ball_turnsmall();
				   break;
		}
		case -2:
		{
				   Gcontrol.faci_ball_turnsmall();
				   endless_home.faci_ball_turnbig();
				   break;
		}
		default:
		{
				   Gcontrol.faci_ball_turnsmall();
				   endless_home.faci_ball_turnsmall();
		}
		}
	}
	else if (endless_gameplay_scene == true)		//如果是在菜单，有30个选关
	{
		if (endless_gameplay_wallstage == 0)
		{
			if (endless_lightwall.faci_ball_position[0] > 0.0)	//如果大于0.0就要往回缩
			{
				endless_lightwall.faci_ball_position[0] -= 0.1 * endless_lightwall.faci_ball_position[0];
			}
		}
		
		for (int i = 0; i < 31; i++)
		{
			Glist[i].faci_ball_emerge();
		}
		
		switch (endless_gameplay_blockon)
		{
		case 1:
		{
				  Glist[0].faci_ball_turnbig();
				  endless_home.faci_ball_turnsmall();
				  for (int i = 0; i < 31; i++)
				  {
					  if (i != 0)
					  {
						  Glist[i].faci_ball_turnsmall();
					  }
				  }
				  break;
		}
		case 2:
		{
				  Glist[1].faci_ball_turnbig();
				  endless_home.faci_ball_turnsmall();
				  for (int i = 0; i < 31; i++)
				  {
					  if (i != 1)
					  {
						  Glist[i].faci_ball_turnsmall();
					  }
				  }
				  break;
		}
		case 3:
		{
				  Glist[2].faci_ball_turnbig();
				  endless_home.faci_ball_turnsmall();
				  for (int i = 0; i < 31; i++)
				  {
					  if (i != 2)
					  {
						  Glist[i].faci_ball_turnsmall();
					  }
				  }
				  break;
		}
		case 4:
		{
				  Glist[3].faci_ball_turnbig();
				  endless_home.faci_ball_turnsmall();
				  for (int i = 0; i < 31; i++)
				  {
					  if (i != 3)
					  {
						  Glist[i].faci_ball_turnsmall();
					  }
				  }
				  break;
		}
		case 5:
		{
				  Glist[4].faci_ball_turnbig();
				  endless_home.faci_ball_turnsmall();
				  for (int i = 0; i < 31; i++)
				  {
					  if (i != 4)
					  {
						  Glist[i].faci_ball_turnsmall();
					  }
				  }
				  break;
		}
		case 6:
		{
				  Glist[5].faci_ball_turnbig();
				  endless_home.faci_ball_turnsmall();
				  for (int i = 0; i < 31; i++)
				  {
					  if (i != 5)
					  {
						  Glist[i].faci_ball_turnsmall();
					  }
				  }
				  break;
		}
		case 7:
		{
				  Glist[6].faci_ball_turnbig();
				  endless_home.faci_ball_turnsmall();
				  for (int i = 0; i < 31; i++)
				  {
					  if (i != 6)
					  {
						  Glist[i].faci_ball_turnsmall();
					  }
				  }
				  break;
		}
		case 8:
		{
				  Glist[7].faci_ball_turnbig();
				  endless_home.faci_ball_turnsmall();
				  for (int i = 0; i < 31; i++)
				  {
					  if (i != 7)
					  {
						  Glist[i].faci_ball_turnsmall();
					  }
				  }
				  break;
		}
		case 9:
		{
				  Glist[8].faci_ball_turnbig();
				  endless_home.faci_ball_turnsmall();
				  for (int i = 0; i < 31; i++)
				  {
					  if (i != 8)
					  {
						  Glist[i].faci_ball_turnsmall();
					  }
				  }
				  break;
		}
		case 10:
		{
				  Glist[9].faci_ball_turnbig();
				  endless_home.faci_ball_turnsmall();
				  for (int i = 0; i < 31; i++)
				  {
					  if (i != 9)
					  {
						  Glist[i].faci_ball_turnsmall();
					  }
				  }
				  break;
		}
		case 11:
		{
				  Glist[10].faci_ball_turnbig();
				  endless_home.faci_ball_turnsmall();
				  for (int i = 0; i < 31; i++)
				  {
					  if (i != 10)
					  {
						  Glist[i].faci_ball_turnsmall();
					  }
				  }
				  break;
		}
		case 12:
		{
				  Glist[11].faci_ball_turnbig();
				  endless_home.faci_ball_turnsmall();
				  for (int i = 0; i < 31; i++)
				  {
					  if (i != 11)
					  {
						  Glist[i].faci_ball_turnsmall();
					  }
				  }
				  break;
		}
		case 13:
		{
				  Glist[12].faci_ball_turnbig();
				  endless_home.faci_ball_turnsmall();
				  for (int i = 0; i < 31; i++)
				  {
					  if (i != 12)
					  {
						  Glist[i].faci_ball_turnsmall();
					  }
				  }
				  break;
		}
		case 14:
		{
				  Glist[13].faci_ball_turnbig();
				  endless_home.faci_ball_turnsmall();
				  for (int i = 0; i < 31; i++)
				  {
					  if (i != 13)
					  {
						  Glist[i].faci_ball_turnsmall();
					  }
				  }
				  break;
		}
		case 15:
		{
				  Glist[14].faci_ball_turnbig();
				  endless_home.faci_ball_turnsmall();
				  for (int i = 0; i < 31; i++)
				  {
					  if (i != 14)
					  {
						  Glist[i].faci_ball_turnsmall();
					  }
				  }
				  break;
		}
		case 16:
		{
				  Glist[15].faci_ball_turnbig();
				  endless_home.faci_ball_turnsmall();
				  for (int i = 0; i < 31; i++)
				  {
					  if (i != 15)
					  {
						  Glist[i].faci_ball_turnsmall();
					  }
				  }
				  break;
		}
		case 17:
		{
				  Glist[16].faci_ball_turnbig();
				  endless_home.faci_ball_turnsmall();
				  for (int i = 0; i < 31; i++)
				  {
					  if (i != 16)
					  {
						  Glist[i].faci_ball_turnsmall();
					  }
				  }
				  break;
		}
		case 18:
		{
				  Glist[17].faci_ball_turnbig();
				  endless_home.faci_ball_turnsmall();
				  for (int i = 0; i < 31; i++)
				  {
					  if (i != 17)
					  {
						  Glist[i].faci_ball_turnsmall();
					  }
				  }
				  break;
		}
		case 19:
		{
				  Glist[18].faci_ball_turnbig();
				  endless_home.faci_ball_turnsmall();
				  for (int i = 0; i < 31; i++)
				  {
					  if (i != 18)
					  {
						  Glist[i].faci_ball_turnsmall();
					  }
				  }
				  break;
		}
		case 20:
		{
				  Glist[19].faci_ball_turnbig();
				  endless_home.faci_ball_turnsmall();
				  for (int i = 0; i < 31; i++)
				  {
					  if (i != 19)
					  {
						  Glist[i].faci_ball_turnsmall();
					  }
				  }
				  break;
		}
		case 21:
		{
				  Glist[20].faci_ball_turnbig();
				  endless_home.faci_ball_turnsmall();
				  for (int i = 0; i < 31; i++)
				  {
					  if (i != 20)
					  {
						  Glist[i].faci_ball_turnsmall();
					  }
				  }
				  break;
		}
		case 22:
		{
				  Glist[21].faci_ball_turnbig();
				  endless_home.faci_ball_turnsmall();
				  for (int i = 0; i < 31; i++)
				  {
					  if (i != 21)
					  {
						  Glist[i].faci_ball_turnsmall();
					  }
				  }
				  break;
		}
		case 23:
		{
				  Glist[22].faci_ball_turnbig();
				  endless_home.faci_ball_turnsmall();
				  for (int i = 0; i < 31; i++)
				  {
					  if (i != 22)
					  {
						  Glist[i].faci_ball_turnsmall();
					  }
				  }
				  break;
		}
		case 24:
		{
				  Glist[23].faci_ball_turnbig();
				  endless_home.faci_ball_turnsmall();
				  for (int i = 0; i < 31; i++)
				  {
					  if (i != 23)
					  {
						  Glist[i].faci_ball_turnsmall();
					  }
				  }
				  break;
		}
		case 25:
		{
				  Glist[24].faci_ball_turnbig();
				  endless_home.faci_ball_turnsmall();
				  for (int i = 0; i < 31; i++)
				  {
					  if (i != 24)
					  {
						  Glist[i].faci_ball_turnsmall();
					  }
				  }
				  break;
		}
		case 26:
		{
				  Glist[25].faci_ball_turnbig();
				  endless_home.faci_ball_turnsmall();
				  for (int i = 0; i < 31; i++)
				  {
					  if (i != 25)
					  {
						  Glist[i].faci_ball_turnsmall();
					  }
				  }
				  break;
		}
		case 27:
		{
				  Glist[26].faci_ball_turnbig();
				  endless_home.faci_ball_turnsmall();
				  for (int i = 0; i < 31; i++)
				  {
					  if (i != 26)
					  {
						  Glist[i].faci_ball_turnsmall();
					  }
				  }
				  break;
		}
		case 28:
		{
				  Glist[27].faci_ball_turnbig();
				  endless_home.faci_ball_turnsmall();
				  for (int i = 0; i < 31; i++)
				  {
					  if (i != 27)
					  {
						  Glist[i].faci_ball_turnsmall();
					  }
				  }
				  break;
		}
		case 29:
		{
				  Glist[28].faci_ball_turnbig();
				  endless_home.faci_ball_turnsmall();
				  for (int i = 0; i < 31; i++)
				  {
					  if (i != 28)
					  {
						  Glist[i].faci_ball_turnsmall();
					  }
				  }
				  break;
		}
		case 30:
		{
				  Glist[29].faci_ball_turnbig();
				  endless_home.faci_ball_turnsmall();
				  for (int i = 0; i < 31; i++)
				  {
					  if (i != 29)
					  {
						  Glist[i].faci_ball_turnsmall();
					  }
				  }
				  break;
		}
		case 31:
		{
				   Glist[30].faci_ball_turnbig();
				   endless_home.faci_ball_turnsmall();
				   for (int i = 0; i < 31; i++)
				   {
					   if (i != 30)
					   {
						   Glist[i].faci_ball_turnsmall();
					   }
				   }
				   break;
		}
		case -2:
		{
				   endless_home.faci_ball_turnbig();
				   for (int i = 0; i < 31; i++)
				   {
					   Glist[i].faci_ball_turnsmall();
				   }
				   break;
		}
		default:
		{
				   for (int i = 0; i < 31; i++)
				   {
					   Glist[i].faci_ball_turnsmall();
				   }
				   endless_home.faci_ball_turnsmall();
		}
		}
	}
}

void endless_control_ball::endless_control_ball_drawall()			//画球
{
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, endless_light0_pos);          //变换光照
	glLightfv(GL_LIGHT0, GL_AMBIENT, endless_light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, endless_light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, endless_light0_specular);
	glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, &endless_light0_cutoff);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, endless_light0_spotdirection);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_POSITION, endless_light1_pos);          //背景光照
	glLightfv(GL_LIGHT1, GL_AMBIENT, endless_light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, endless_light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, endless_light1_specular);
	glEnable(GL_LIGHT1);

	//------------------------------------------------------
	for (int i = 0; i < 12; i++)
	{
		endless_balllist[i].ball_drawself();
	}
	endless_lightwall.faci_ball_drawself();
	endless_mouse.faci_ball_drawself();

	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	endless_wallpaper.faci_ball_drawself();
	for (int i = 0; i < 31; i++)
	{
		Glist[i].faci_ball_drawself();
	}
	Gscore.faci_ball_drawself();
	Gcontrol.faci_ball_drawself();
	endless_home.faci_ball_drawself();
	glDisable(GL_TEXTURE_2D);
}

void endless_control_ball::endless_control_ball_mouseevent()		//处理所有鼠标单击动作
{
	endless_light0_pos[0] = endless_control_ball_mouseposition_x * 32.0 / 1366.0 - 16.0;		//光源位置随着鼠标位置变化
	endless_light0_pos[1] = 9.0 - endless_control_ball_mouseposition_y * 18.0 / 768.0;
	endless_mouse.faci_ball_position[0] = endless_light0_pos[0];							//鼠标位置变化
	endless_mouse.faci_ball_position[1] = endless_light0_pos[1];

	float mp_x = endless_light0_pos[0];
	float mp_y = endless_light0_pos[1];

	if (endless_control_ball_left_mouse_down == true)
	{
		
		//===================================================================================================
		if (endless_gameplay_ballstage == 1)		//如果没有球被按下，就记录按得是哪个球
		{
			endless_gameplay_balldownnum[0] = 0;
			endless_gameplay_balldownnum[1] = 0;
			if (mp_x > -7.5 && mp_x< -4.5 && mp_y> 2.5 && mp_y < 5.5 && endless_balllist[0].ball_appear == true)
			{
				endless_gameplay_balldownnum[0] = 1;
				endless_balllist[0].ball_click = true;
				endless_gameplay_ballstage = 2;
			}
			else if (mp_x > -3.5 && mp_x< -0.5 && mp_y > 2.5 && mp_y < 5.5 && endless_balllist[1].ball_appear == true)
			{
				endless_gameplay_balldownnum[0] = 2;
				endless_balllist[1].ball_click = true;
				endless_gameplay_ballstage = 2;
			}
			else if (mp_x > 0.5 && mp_x < 3.5 && mp_y > 2.5 && mp_y < 5.5 && endless_balllist[2].ball_appear == true)
			{
				endless_gameplay_balldownnum[0] = 3;
				endless_balllist[2].ball_click = true;
				endless_gameplay_ballstage = 2;
			}
			else if (mp_x > 4.5 && mp_x < 7.5 && mp_y > 2.5 && mp_y < 5.5 && endless_balllist[3].ball_appear == true)
			{
				endless_gameplay_balldownnum[0] = 4;
				endless_balllist[3].ball_click = true;
				endless_gameplay_ballstage = 2;
			}
			else if (mp_x > -7.5 && mp_x < -4.5 && mp_y > -1.5 && mp_y < 1.5 && endless_balllist[4].ball_appear == true)
			{
				endless_gameplay_balldownnum[0] = 5;
				endless_balllist[4].ball_click = true;
				endless_gameplay_ballstage = 2;
			}
			else if (mp_x > -3.5 && mp_x < -0.5 && mp_y > -1.5 && mp_y < 1.5 && endless_balllist[5].ball_appear == true)
			{
				endless_gameplay_balldownnum[0] = 6;
				endless_balllist[5].ball_click = true;
				endless_gameplay_ballstage = 2;
			}
			else if (mp_x > 0.5 && mp_x < 3.5 && mp_y > -1.5 && mp_y < 1.5 && endless_balllist[6].ball_appear == true)
			{
				endless_gameplay_balldownnum[0] = 7;
				endless_balllist[6].ball_click = true;
				endless_gameplay_ballstage = 2;
			}
			else if (mp_x > 4.5 && mp_x < 7.5 && mp_y > -1.5 && mp_y < 1.5 && endless_balllist[7].ball_appear == true)
			{
				endless_gameplay_balldownnum[0] = 8;
				endless_balllist[7].ball_click = true;
				endless_gameplay_ballstage = 2;

				srand((int)time(0));
			}
			else if (mp_x > -7.5 && mp_x < -4.5 && mp_y > -5.5 && mp_y < -2.5 && endless_balllist[8].ball_appear == true)
			{
				endless_gameplay_balldownnum[0] = 9;
				endless_balllist[8].ball_click = true;
				endless_gameplay_ballstage = 2;
			}
			else if (mp_x > -3.5 && mp_x < -0.5 && mp_y > -5.5 && mp_y < -2.5 && endless_balllist[9].ball_appear == true)
			{
				endless_gameplay_balldownnum[0] = 10;
				endless_balllist[9].ball_click = true;
				endless_gameplay_ballstage = 2;
			}
			else if (mp_x > 0.5 && mp_x < 3.5 && mp_y > -5.5 && mp_y < -2.5 && endless_balllist[10].ball_appear == true)
			{
				endless_gameplay_balldownnum[0] = 11;
				endless_balllist[10].ball_click = true;
				endless_gameplay_ballstage = 2;
			}
			else if (mp_x > 4.5 && mp_x < 7.5 && mp_y > -5.5 && mp_y < -2.5 && endless_balllist[11].ball_appear == true)
			{
				endless_gameplay_balldownnum[0] = 12;
				endless_balllist[11].ball_click = true;
				endless_gameplay_ballstage = 2;
			}
		}
		else if (endless_gameplay_ballstage == 3)		//如果已经有球按下了
		{
			if (mp_x > -7.5 && mp_x< -4.5 && mp_y> 2.5 && mp_y < 5.5 && endless_balllist[0].ball_appear == true)
			{
				endless_balllist[0].ball_click = true;
			}
			else if (mp_x > -3.5 && mp_x< -0.5 && mp_y > 2.5 && mp_y < 5.5 && endless_balllist[1].ball_appear == true)
			{
				endless_balllist[1].ball_click = true;
			}
			else if (mp_x > 0.5 && mp_x < 3.5 && mp_y > 2.5 && mp_y < 5.5 && endless_balllist[2].ball_appear == true)
			{
				endless_balllist[2].ball_click = true;
			}
			else if (mp_x > 4.5 && mp_x < 7.5 && mp_y > 2.5 && mp_y < 5.5 && endless_balllist[3].ball_appear == true)
			{
				endless_balllist[3].ball_click = true;
			}
			else if (mp_x > -7.5 && mp_x < -4.5 && mp_y > -1.5 && mp_y < 1.5 && endless_balllist[4].ball_appear == true)
			{
				endless_balllist[4].ball_click = true;
			}
			else if (mp_x > -3.5 && mp_x < -0.5 && mp_y > -1.5 && mp_y < 1.5 && endless_balllist[5].ball_appear == true)
			{
				endless_balllist[5].ball_click = true;
			}
			else if (mp_x > 0.5 && mp_x < 3.5 && mp_y > -1.5 && mp_y < 1.5 && endless_balllist[6].ball_appear == true)
			{
				endless_balllist[6].ball_click = true;
			}
			else if (mp_x > 4.5 && mp_x < 7.5 && mp_y > -1.5 && mp_y < 1.5 && endless_balllist[7].ball_appear == true)
			{
				endless_balllist[7].ball_click = true;
			}
			else if (mp_x > -7.5 && mp_x < -4.5 && mp_y > -5.5 && mp_y < -2.5 && endless_balllist[8].ball_appear == true)
			{
				endless_balllist[8].ball_click = true;
			}
			else if (mp_x > -3.5 && mp_x < -0.5 && mp_y > -5.5 && mp_y < -2.5 && endless_balllist[9].ball_appear == true)
			{
				endless_balllist[9].ball_click = true;
			}
			else if (mp_x > 0.5 && mp_x < 3.5 && mp_y > -5.5 && mp_y < -2.5 && endless_balllist[10].ball_appear == true)
			{
				endless_balllist[10].ball_click = true;
			}
			else if (mp_x > 4.5 && mp_x < 7.5 && mp_y > -5.5 && mp_y < -2.5 && endless_balllist[11].ball_appear == true)
			{
				endless_balllist[11].ball_click = true;
			}
			endless_gameplay_ballstage = 4;
		}

		//-----------------------处理按键效果----------------------------
		if (endless_gameplay_scene == false)		//如果在游戏之中
		{
			if (endless_light0_pos[0] > 12.5 && endless_light0_pos[0] < 15.5 && endless_light0_pos[1] > -3.0 && endless_light0_pos[1] < 0.15)
			{
				Gcontrol.faci_ball_texture_scale = 1.1;
				Gcontrol.faci_ball_appear = false;
				Gscore.faci_ball_appear = false;
				endless_gameplay_scene = true;		//在当前关的数字上,退到选关菜单
				endless_gameplay_wallstage = 0;
				for (int p = 0; p < endless_control_ball_toplevel && p < 31; p++)
				{
					Glist[p].faci_ball_appear = true;
					Glist[p].faci_ball_texture_scale = 0.0;
				}
				
				for (int p = 0; p <12; p++)
				{
					endless_balllist[p].ball_appear = false;
				}
				endless_lightwall.faci_ball_color_ambient[0] = 0.1;		//将屏幕置回原色
				endless_lightwall.faci_ball_color_diffuse[0] = 0.1;
				endless_lightwall.faci_ball_color_specular[0] = 0.1;
				endless_gameplay_wallstage = 0;
			}
			else if (endless_light0_pos[0] > -15.0 && endless_light0_pos[0] < -14.0 && endless_light0_pos[1] > 6.5 && endless_light0_pos[1] < 7.5)
			{
						//home键返回主菜单--------------------------------------------------
				endless_control_ball_gameon = 0;
				endless_lightwall.faci_ball_color_ambient[0] = 0.1;		//将屏幕置回原色
				endless_lightwall.faci_ball_color_diffuse[0] = 0.1;
				endless_lightwall.faci_ball_color_specular[0] = 0.1;
				endless_gameplay_wallstage = 0;
			}
		}
		else if (endless_gameplay_scene == true)		//如果在选关画面中
		{
			bool refresh_level = false;
			if (endless_light0_pos[0] > -8.5 && endless_light0_pos[0] < -6.5 && endless_light0_pos[1] > 5.0 && endless_light0_pos[1] < 7.0 && endless_control_ball_toplevel >= 1)
			{
				endless_control_ball_gamelevel = 1;
				endless_gameplay_scene = true;
				refresh_level = true;
			}
			else if (endless_light0_pos[0] > -5.5 && endless_light0_pos[0] < -3.5 && endless_light0_pos[1] > 5.0 && endless_light0_pos[1] < 7.0 && endless_control_ball_toplevel >= 2)
			{
				endless_control_ball_gamelevel = 2;
				endless_gameplay_scene = true;
				refresh_level = true;
			}
			else if (endless_light0_pos[0] > -2.5 && endless_light0_pos[0] < -0.5 && endless_light0_pos[1] > 5.0 && endless_light0_pos[1] < 7.0 && endless_control_ball_toplevel >= 3)
			{
				endless_control_ball_gamelevel = 3;
				endless_gameplay_scene = true;
				refresh_level = true;
			}
			else if (endless_light0_pos[0] > 0.5 && endless_light0_pos[0] < 2.5 && endless_light0_pos[1] > 5.0 && endless_light0_pos[1] < 7.0 && endless_control_ball_toplevel >= 4)
			{
				endless_control_ball_gamelevel = 4;
				endless_gameplay_scene = true;
				refresh_level = true;
			}
			else if (endless_light0_pos[0] > 3.5 && endless_light0_pos[0] < 5.5 && endless_light0_pos[1] > 5.0 && endless_light0_pos[1] < 7.0 && endless_control_ball_toplevel >= 5)
			{
				endless_control_ball_gamelevel = 5;
				endless_gameplay_scene = true;
				refresh_level = true;
			}
			else if (endless_light0_pos[0] > 6.5 && endless_light0_pos[0] < 8.5 && endless_light0_pos[1] > 5.0 && endless_light0_pos[1] < 7.0 && endless_control_ball_toplevel >= 6)
			{
				endless_control_ball_gamelevel = 6;
				endless_gameplay_scene = true;
				refresh_level = true;
			}
			//-------------------------第二排
			else if (endless_light0_pos[0] > -8.5 && endless_light0_pos[0] < -6.5 && endless_light0_pos[1] > 2.0 && endless_light0_pos[1] < 4.0 && endless_control_ball_toplevel >= 7)
			{
				endless_control_ball_gamelevel = 7;
				endless_gameplay_scene = true;
				refresh_level = true;
			}
			else if (endless_light0_pos[0] > -5.5 && endless_light0_pos[0] < -3.5 && endless_light0_pos[1] > 2.0 && endless_light0_pos[1] < 4.0 && endless_control_ball_toplevel >= 8)
			{
				endless_control_ball_gamelevel = 8;
				endless_gameplay_scene = true;
				refresh_level = true;
			}
			else if (endless_light0_pos[0] > -2.5 && endless_light0_pos[0] < -0.5 && endless_light0_pos[1] > 2.0 && endless_light0_pos[1] < 4.0 && endless_control_ball_toplevel >= 9)
			{
				endless_control_ball_gamelevel = 9;
				endless_gameplay_scene = true;
				refresh_level = true;
			}
			else if (endless_light0_pos[0] > 0.5 && endless_light0_pos[0] < 2.5 && endless_light0_pos[1] > 2.0 && endless_light0_pos[1] < 4.0 && endless_control_ball_toplevel >= 10)
			{
				endless_control_ball_gamelevel = 10;
				endless_gameplay_scene = true;
				refresh_level = true;
			}
			else if (endless_light0_pos[0] > 3.5 && endless_light0_pos[0] < 5.5 && endless_light0_pos[1] > 2.0 && endless_light0_pos[1] < 4.0 && endless_control_ball_toplevel >= 11)
			{
				endless_control_ball_gamelevel = 11;
				endless_gameplay_scene = true;
				refresh_level = true;
			}
			else if (endless_light0_pos[0] > 6.5 && endless_light0_pos[0] < 8.5 && endless_light0_pos[1] > 2.0 && endless_light0_pos[1] < 4.0 && endless_control_ball_toplevel >= 12)
			{
				endless_control_ball_gamelevel = 12;
				endless_gameplay_scene = true;
				refresh_level = true;
			}
			//-------------------------------第三排
			else if (endless_light0_pos[0] > -8.5 && endless_light0_pos[0] < -6.5 && endless_light0_pos[1] > -1.0 && endless_light0_pos[1] < 1.0 && endless_control_ball_toplevel >= 13)
			{
				endless_control_ball_gamelevel = 13;
				endless_gameplay_scene = true;
				refresh_level = true;
			}
			else if (endless_light0_pos[0] > -5.5 && endless_light0_pos[0] < -3.5 && endless_light0_pos[1] > -1.0 && endless_light0_pos[1] < 1.0 && endless_control_ball_toplevel >= 14)
			{
				endless_control_ball_gamelevel = 14;
				endless_gameplay_scene = true;
				refresh_level = true;
			}
			else if (endless_light0_pos[0] > -2.5 && endless_light0_pos[0] < -0.5 && endless_light0_pos[1] > -1.0 && endless_light0_pos[1] < 1.0 && endless_control_ball_toplevel >= 15)
			{
				endless_control_ball_gamelevel = 15;
				endless_gameplay_scene = true;
				refresh_level = true;
			}
			else if (endless_light0_pos[0] > 0.5 && endless_light0_pos[0] < 2.5 && endless_light0_pos[1] > -1.0 && endless_light0_pos[1] < 1.0 && endless_control_ball_toplevel >= 16)
			{
				endless_control_ball_gamelevel = 16;
				endless_gameplay_scene = true;
				refresh_level = true;
			}
			else if (endless_light0_pos[0] > 3.5 && endless_light0_pos[0] < 5.5 && endless_light0_pos[1] > -1.0 && endless_light0_pos[1] < 1.0 && endless_control_ball_toplevel >= 17)
			{
				endless_control_ball_gamelevel = 17;
				endless_gameplay_scene = true;
				refresh_level = true;
			}
			else if (endless_light0_pos[0] > 6.5 && endless_light0_pos[0] < 8.5 && endless_light0_pos[1] > -1.0 && endless_light0_pos[1] < 1.0 && endless_control_ball_toplevel >= 18)
			{
				endless_control_ball_gamelevel = 18;
				endless_gameplay_scene = true;
				refresh_level = true;
			}
			//----------------------------第四排
			else if (endless_light0_pos[0] > -8.5 && endless_light0_pos[0] < -6.5 && endless_light0_pos[1] > -4.0 && endless_light0_pos[1] < -2.0 && endless_control_ball_toplevel >= 19)
			{
				endless_control_ball_gamelevel = 19;
				endless_gameplay_scene = true;
				refresh_level = true;
			}
			else if (endless_light0_pos[0] > -5.5 && endless_light0_pos[0] < -3.5 && endless_light0_pos[1] > -4.0 && endless_light0_pos[1] < -2.0 && endless_control_ball_toplevel >= 20)
			{
				endless_control_ball_gamelevel = 20;
				endless_gameplay_scene = true;
				refresh_level = true;
			}
			else if (endless_light0_pos[0] > -2.5 && endless_light0_pos[0] < -0.5 && endless_light0_pos[1] > -4.0 && endless_light0_pos[1] < -2.0 && endless_control_ball_toplevel >= 21)
			{
				endless_control_ball_gamelevel = 21;
				endless_gameplay_scene = true;
				refresh_level = true;
			}
			else if (endless_light0_pos[0] > 0.5 && endless_light0_pos[0] < 2.5 && endless_light0_pos[1] > -4.0 && endless_light0_pos[1] < -2.0 && endless_control_ball_toplevel >= 22)
			{
				endless_control_ball_gamelevel = 22;
				endless_gameplay_scene = true;
				refresh_level = true;
			}
			else if (endless_light0_pos[0] > 3.5 && endless_light0_pos[0] < 5.5 && endless_light0_pos[1] > -4.0 && endless_light0_pos[1] < -2.0 && endless_control_ball_toplevel >= 23)
			{
				endless_control_ball_gamelevel = 23;
				endless_gameplay_scene = true;
				refresh_level = true;
			}
			else if (endless_light0_pos[0] > 6.5 && endless_light0_pos[0] < 8.5 && endless_light0_pos[1] > -4.0 && endless_light0_pos[1] < -2.0 && endless_control_ball_toplevel >= 24)
			{
				endless_control_ball_gamelevel = 24;
				endless_gameplay_scene = true;
				refresh_level = true;
			}
			//--------------------------------------第五排
			else if (endless_light0_pos[0] > -8.5 && endless_light0_pos[0] < -6.5 && endless_light0_pos[1] > -7.0 && endless_light0_pos[1] < -5.0 && endless_control_ball_toplevel >= 25)
			{
				endless_control_ball_gamelevel = 25;
				endless_gameplay_scene = true;
				refresh_level = true;
			}
			else if (endless_light0_pos[0] > -5.5 && endless_light0_pos[0] < -3.5 && endless_light0_pos[1] > -7.0 && endless_light0_pos[1] < -5.0 && endless_control_ball_toplevel >= 26)
			{
				endless_control_ball_gamelevel = 26;
				endless_gameplay_scene = true;
				refresh_level = true;
			}
			else if (endless_light0_pos[0] > -2.5 && endless_light0_pos[0] < -0.5 && endless_light0_pos[1] > -7.0 && endless_light0_pos[1] < -5.0 && endless_control_ball_toplevel >= 27)
			{
				endless_control_ball_gamelevel = 27;
				endless_gameplay_scene = true;
				refresh_level = true;
			}
			else if (endless_light0_pos[0] > 0.5 && endless_light0_pos[0] < 2.5 && endless_light0_pos[1] > -7.0 && endless_light0_pos[1] < -5.0 && endless_control_ball_toplevel >= 28)
			{
				endless_control_ball_gamelevel = 28;
				endless_gameplay_scene = true;
				refresh_level = true;
			}
			else if (endless_light0_pos[0] > 3.5 && endless_light0_pos[0] < 5.5 && endless_light0_pos[1] > -7.0 && endless_light0_pos[1] < -5.0 && endless_control_ball_toplevel >= 29)
			{
				endless_control_ball_gamelevel = 29;
				endless_gameplay_scene = true;
				refresh_level = true;
			}
			else if (endless_light0_pos[0] > 6.5 && endless_light0_pos[0] < 8.5 && endless_light0_pos[1] > -7.0 && endless_light0_pos[1] < -5.0 && endless_control_ball_toplevel >= 30)
			{
				endless_control_ball_gamelevel = 30;
				endless_gameplay_scene = true;
				refresh_level = true;
			}
			else if (endless_light0_pos[0] > 9.5 && endless_light0_pos[0] < 11.5 && endless_light0_pos[1] > -7.0 && endless_light0_pos[1] < -5.0 && endless_control_ball_toplevel >= 30)
			{
				endless_control_ball_gamelevel = endless_control_ball_toplevel;
				endless_gameplay_scene = true;
				refresh_level = true;
			}
			else if (endless_light0_pos[0] > -15.0 && endless_light0_pos[0] < -14.0 && endless_light0_pos[1] > 6.5 && endless_light0_pos[1] < 7.5)
			{
				//home键返回主菜单--------------------------------------------------
				endless_control_ball_gameon = 0;
			}

			if (refresh_level == true)
			{
				for (int u = 0; u < 12; u++)
				{
					endless_balllist[u].ball_r = 0.0;
					endless_ball_rand_color[u] = rand() % 4;			//随机颜色
					endless_balllist[u].ball_color = endless_ball_rand_color[u];
					endless_balllist[u].ball_appear = true;
					endless_gameplay_ball_appearlist[u] = true;
				}
				Gcontrol.faci_ball_texture_scale = 0.0;
				Gscore.faci_ball_texture_scale = 0.0;
				Gcontrol.faci_ball_appear = true;
				Gscore.faci_ball_appear = true;
				for (int p = 0; p < 31; p++)
				{
					Glist[p].faci_ball_appear = false;
				}
				endless_gameplay_scene = false;
				endless_control_ball_randballcolor();		//重新分配颜色
				endless_gameplay_eliballnum = 0;		//重新开始记正确对数
				if (endless_control_ball_gamelevel <= 30)
				{
					Gscore.faci_ball_color = endless_control_ball_gamelevel + 7;
				}
				else if (endless_control_ball_gamelevel > 30)
				{
					Gscore.faci_ball_color = 38;
				}
				
			}
		}


	}
	//----------------------------------------------------------------------------------------------------------------------
	else if (endless_control_ball_left_mouse_down == false){			//如果是键子被抬起来，判断是不是正确的球并熄灭
		if (endless_gameplay_ballstage == 4)
		{
			if (mp_x > -7.5 && mp_x< -4.5 && mp_y> 2.5 && mp_y < 5.5 && endless_balllist[0].ball_appear == true && endless_gameplay_balldownnum[0] != 1)
			{
				endless_gameplay_balldownnum[1] = 1;
				if (endless_ball_rand_color[endless_gameplay_balldownnum[0] - 1] == endless_ball_rand_color[0])
				{
					endless_balllist[0].ball_appear = false;
					endless_balllist[endless_gameplay_balldownnum[0] - 1].ball_appear = false;			//将两个球都熄灭
					endless_gameplay_ball_appearlist[0] = false;		//更新appear list
					endless_gameplay_ball_appearlist[endless_gameplay_balldownnum[0] - 1] = false;
					endless_gameplay_eliballnum++;

					endless_lightwall.faci_ball_color_ambient[0] = 0.1;		//将屏幕置回原色
					endless_lightwall.faci_ball_color_diffuse[0] = 0.1;
					endless_lightwall.faci_ball_color_specular[0] = 0.1;

					endless_gameplay_wallstage++;
				}
				else{
					endless_gameplay_eliballnum = 0;
					endless_lightwall.faci_ball_color_ambient[0] = 0.4;		//将屏幕置红
					endless_lightwall.faci_ball_color_diffuse[0] = 0.4;
					endless_lightwall.faci_ball_color_specular[0] = 0.2;

					endless_gameplay_wallstage = 0;
				}
			}
			else if (mp_x > -3.5 && mp_x< -0.5 && mp_y > 2.5 && mp_y < 5.5 && endless_balllist[1].ball_appear == true && endless_gameplay_balldownnum[0] != 2)
			{
				endless_gameplay_balldownnum[1] = 2;
				if (endless_ball_rand_color[endless_gameplay_balldownnum[0] - 1] == endless_ball_rand_color[1])
				{
					endless_balllist[1].ball_appear = false;
					endless_balllist[endless_gameplay_balldownnum[0] - 1].ball_appear = false;
					endless_gameplay_ball_appearlist[1] = false;
					endless_gameplay_ball_appearlist[endless_gameplay_balldownnum[0] - 1] = false;
					endless_gameplay_eliballnum++;

					endless_lightwall.faci_ball_color_ambient[0] = 0.1;		//将屏幕置回原色
					endless_lightwall.faci_ball_color_diffuse[0] = 0.1;
					endless_lightwall.faci_ball_color_specular[0] = 0.1;

					endless_gameplay_wallstage++;
				}
				else{
					endless_gameplay_eliballnum = 0;
					endless_lightwall.faci_ball_color_ambient[0] = 0.4;		//将屏幕置红
					endless_lightwall.faci_ball_color_diffuse[0] = 0.4;
					endless_lightwall.faci_ball_color_specular[0] = 0.2;

					endless_gameplay_wallstage = 0;
				}
			}
			else if (mp_x > 0.5 && mp_x < 3.5 && mp_y > 2.5 && mp_y < 5.5 && endless_balllist[2].ball_appear == true && endless_gameplay_balldownnum[0] != 3)
			{
				endless_gameplay_balldownnum[1] = 3;
				if (endless_ball_rand_color[endless_gameplay_balldownnum[0] - 1] == endless_ball_rand_color[2])
				{
					endless_balllist[2].ball_appear = false;
					endless_balllist[endless_gameplay_balldownnum[0] - 1].ball_appear = false;
					endless_gameplay_ball_appearlist[2] = false;
					endless_gameplay_ball_appearlist[endless_gameplay_balldownnum[0] - 1] = false;
					endless_gameplay_eliballnum++;

					endless_lightwall.faci_ball_color_ambient[0] = 0.1;		//将屏幕置回原色
					endless_lightwall.faci_ball_color_diffuse[0] = 0.1;
					endless_lightwall.faci_ball_color_specular[0] = 0.1;

					endless_gameplay_wallstage++;
				}
				else{
					endless_gameplay_eliballnum = 0;
					endless_lightwall.faci_ball_color_ambient[0] = 0.4;		//将屏幕置红
					endless_lightwall.faci_ball_color_diffuse[0] = 0.4;
					endless_lightwall.faci_ball_color_specular[0] = 0.2;

					endless_gameplay_wallstage = 0;
				}
			}
			else if (mp_x > 4.5 && mp_x < 7.5 && mp_y > 2.5 && mp_y < 5.5 && endless_balllist[3].ball_appear == true && endless_gameplay_balldownnum[0] != 4)
			{
				endless_gameplay_balldownnum[1] = 4;
				if (endless_ball_rand_color[endless_gameplay_balldownnum[0] - 1] == endless_ball_rand_color[3])
				{
					endless_balllist[3].ball_appear = false;
					endless_balllist[endless_gameplay_balldownnum[0] - 1].ball_appear = false;
					endless_gameplay_ball_appearlist[3] = false;
					endless_gameplay_ball_appearlist[endless_gameplay_balldownnum[0] - 1] = false;
					endless_gameplay_eliballnum++;

					endless_lightwall.faci_ball_color_ambient[0] = 0.1;		//将屏幕置回原色
					endless_lightwall.faci_ball_color_diffuse[0] = 0.1;
					endless_lightwall.faci_ball_color_specular[0] = 0.1;

					endless_gameplay_wallstage++;
				}
				else{
					endless_gameplay_eliballnum = 0;
					endless_lightwall.faci_ball_color_ambient[0] = 0.4;		//将屏幕置红
					endless_lightwall.faci_ball_color_diffuse[0] = 0.4;
					endless_lightwall.faci_ball_color_specular[0] = 0.2;

					endless_gameplay_wallstage = 0;
				}
			}
			else if (mp_x > -7.5 && mp_x < -4.5 && mp_y > -1.5 && mp_y < 1.5 && endless_balllist[4].ball_appear == true && endless_gameplay_balldownnum[0] != 5)
			{
				endless_gameplay_balldownnum[1] = 5;
				if (endless_ball_rand_color[endless_gameplay_balldownnum[0] - 1] == endless_ball_rand_color[4])
				{
					endless_balllist[4].ball_appear = false;
					endless_balllist[endless_gameplay_balldownnum[0] - 1].ball_appear = false;
					endless_gameplay_ball_appearlist[4] = false;
					endless_gameplay_ball_appearlist[endless_gameplay_balldownnum[0] - 1] = false;
					endless_gameplay_eliballnum++;

					endless_lightwall.faci_ball_color_ambient[0] = 0.1;		//将屏幕置回原色
					endless_lightwall.faci_ball_color_diffuse[0] = 0.1;
					endless_lightwall.faci_ball_color_specular[0] = 0.1;

					endless_gameplay_wallstage++;
				}
				else{
					endless_gameplay_eliballnum = 0;
					endless_lightwall.faci_ball_color_ambient[0] = 0.4;		//将屏幕置红
					endless_lightwall.faci_ball_color_diffuse[0] = 0.4;
					endless_lightwall.faci_ball_color_specular[0] = 0.2;

					endless_gameplay_wallstage = 0;
				}
			}
			else if (mp_x > -3.5 && mp_x < -0.5 && mp_y > -1.5 && mp_y < 1.5 && endless_balllist[5].ball_appear == true && endless_gameplay_balldownnum[0] != 6)
			{
				endless_gameplay_balldownnum[1] = 6;
				if (endless_ball_rand_color[endless_gameplay_balldownnum[0] - 1] == endless_ball_rand_color[5])
				{
					endless_balllist[5].ball_appear = false;
					endless_balllist[endless_gameplay_balldownnum[0] - 1].ball_appear = false;
					endless_gameplay_ball_appearlist[5] = false;
					endless_gameplay_ball_appearlist[endless_gameplay_balldownnum[0] - 1] = false;
					endless_gameplay_eliballnum++;

					endless_lightwall.faci_ball_color_ambient[0] = 0.1;		//将屏幕置回原色
					endless_lightwall.faci_ball_color_diffuse[0] = 0.1;
					endless_lightwall.faci_ball_color_specular[0] = 0.1;

					endless_gameplay_wallstage++;
				}
				else{
					endless_gameplay_eliballnum = 0;
					endless_lightwall.faci_ball_color_ambient[0] = 0.4;		//将屏幕置红
					endless_lightwall.faci_ball_color_diffuse[0] = 0.4;
					endless_lightwall.faci_ball_color_specular[0] = 0.2;

					endless_gameplay_wallstage = 0;
				}
			}
			else if (mp_x > 0.5 && mp_x < 3.5 && mp_y > -1.5 && mp_y < 1.5 && endless_balllist[6].ball_appear == true && endless_gameplay_balldownnum[0] != 7)
			{
				endless_gameplay_balldownnum[1] = 7;
				if (endless_ball_rand_color[endless_gameplay_balldownnum[0] - 1] == endless_ball_rand_color[6])
				{
					endless_balllist[6].ball_appear = false;
					endless_balllist[endless_gameplay_balldownnum[0] - 1].ball_appear = false;
					endless_gameplay_ball_appearlist[6] = false;
					endless_gameplay_ball_appearlist[endless_gameplay_balldownnum[0] - 1] = false;
					endless_gameplay_eliballnum++;

					endless_lightwall.faci_ball_color_ambient[0] = 0.1;		//将屏幕置回原色
					endless_lightwall.faci_ball_color_diffuse[0] = 0.1;
					endless_lightwall.faci_ball_color_specular[0] = 0.1;

					endless_gameplay_wallstage++;
				}
				else{
					endless_gameplay_eliballnum = 0;
					endless_lightwall.faci_ball_color_ambient[0] = 0.4;		//将屏幕置红
					endless_lightwall.faci_ball_color_diffuse[0] = 0.4;
					endless_lightwall.faci_ball_color_specular[0] = 0.2;

					endless_gameplay_wallstage = 0;
				}
			}
			else if (mp_x > 4.5 && mp_x < 7.5 && mp_y > -1.5 && mp_y < 1.5 && endless_balllist[7].ball_appear == true && endless_gameplay_balldownnum[0] != 8)
			{
				endless_gameplay_balldownnum[1] = 8;
				if (endless_ball_rand_color[endless_gameplay_balldownnum[0] - 1] == endless_ball_rand_color[7])
				{
					endless_balllist[7].ball_appear = false;
					endless_balllist[endless_gameplay_balldownnum[0] - 1].ball_appear = false;
					endless_gameplay_ball_appearlist[7] = false;
					endless_gameplay_ball_appearlist[endless_gameplay_balldownnum[0] - 1] = false;
					endless_gameplay_eliballnum++;

					endless_lightwall.faci_ball_color_ambient[0] = 0.1;		//将屏幕置回原色
					endless_lightwall.faci_ball_color_diffuse[0] = 0.1;
					endless_lightwall.faci_ball_color_specular[0] = 0.1;

					endless_gameplay_wallstage++;
				}
				else{
					endless_gameplay_eliballnum = 0;
					endless_lightwall.faci_ball_color_ambient[0] = 0.4;		//将屏幕置红
					endless_lightwall.faci_ball_color_diffuse[0] = 0.4;
					endless_lightwall.faci_ball_color_specular[0] = 0.2;

					endless_gameplay_wallstage = 0;
				}
			}
			else if (mp_x > -7.5 && mp_x < -4.5 && mp_y > -5.5 && mp_y < -2.5 && endless_balllist[8].ball_appear == true && endless_gameplay_balldownnum[0] != 9)
			{
				endless_gameplay_balldownnum[1] = 9;
				if (endless_ball_rand_color[endless_gameplay_balldownnum[0] - 1] == endless_ball_rand_color[8])
				{
					endless_balllist[8].ball_appear = false;
					endless_balllist[endless_gameplay_balldownnum[0] - 1].ball_appear = false;
					endless_gameplay_ball_appearlist[8] = false;
					endless_gameplay_ball_appearlist[endless_gameplay_balldownnum[0] - 1] = false;
					endless_gameplay_eliballnum++;

					endless_lightwall.faci_ball_color_ambient[0] = 0.1;		//将屏幕置回原色
					endless_lightwall.faci_ball_color_diffuse[0] = 0.1;
					endless_lightwall.faci_ball_color_specular[0] = 0.1;

					endless_gameplay_wallstage++;
				}
				else{
					endless_gameplay_eliballnum = 0;
					endless_lightwall.faci_ball_color_ambient[0] = 0.4;		//将屏幕置红
					endless_lightwall.faci_ball_color_diffuse[0] = 0.4;
					endless_lightwall.faci_ball_color_specular[0] = 0.2;

					endless_gameplay_wallstage = 0;
				}
			}
			else if (mp_x > -3.5 && mp_x < -0.5 && mp_y > -5.5 && mp_y < -2.5 && endless_balllist[9].ball_appear == true && endless_gameplay_balldownnum[0] != 10)
			{
				endless_gameplay_balldownnum[1] = 10;
				if (endless_ball_rand_color[endless_gameplay_balldownnum[0] - 1] == endless_ball_rand_color[9])
				{
					endless_balllist[9].ball_appear = false;
					endless_balllist[endless_gameplay_balldownnum[0] - 1].ball_appear = false;
					endless_gameplay_ball_appearlist[9] = false;
					endless_gameplay_ball_appearlist[endless_gameplay_balldownnum[0] - 1] = false;
					endless_gameplay_eliballnum++;

					endless_lightwall.faci_ball_color_ambient[0] = 0.1;		//将屏幕置回原色
					endless_lightwall.faci_ball_color_diffuse[0] = 0.1;
					endless_lightwall.faci_ball_color_specular[0] = 0.1;

					endless_gameplay_wallstage++;
				}
				else{
					endless_gameplay_eliballnum = 0;
					endless_lightwall.faci_ball_color_ambient[0] = 0.4;		//将屏幕置红
					endless_lightwall.faci_ball_color_diffuse[0] = 0.4;
					endless_lightwall.faci_ball_color_specular[0] = 0.2;

					endless_gameplay_wallstage = 0;
				}
			}
			else if (mp_x > 0.5 && mp_x < 3.5 && mp_y > -5.5 && mp_y < -2.5 && endless_balllist[10].ball_appear == true && endless_gameplay_balldownnum[0] != 11)
			{
				endless_gameplay_balldownnum[1] = 11;
				if (endless_ball_rand_color[endless_gameplay_balldownnum[0] - 1] == endless_ball_rand_color[10])
				{
					endless_balllist[10].ball_appear = false;
					endless_balllist[endless_gameplay_balldownnum[0] - 1].ball_appear = false;
					endless_gameplay_ball_appearlist[10] = false;
					endless_gameplay_ball_appearlist[endless_gameplay_balldownnum[0] - 1] = false;
					endless_gameplay_eliballnum++;

					endless_lightwall.faci_ball_color_ambient[0] = 0.1;		//将屏幕置回原色
					endless_lightwall.faci_ball_color_diffuse[0] = 0.1;
					endless_lightwall.faci_ball_color_specular[0] = 0.1;

					endless_gameplay_wallstage++;
				}
				else{
					endless_gameplay_eliballnum = 0;
					endless_lightwall.faci_ball_color_ambient[0] = 0.4;		//将屏幕置红
					endless_lightwall.faci_ball_color_diffuse[0] = 0.4;
					endless_lightwall.faci_ball_color_specular[0] = 0.2;

					endless_gameplay_wallstage = 0;
				}
			}
			else if (mp_x > 4.5 && mp_x < 7.5 && mp_y > -5.5 && mp_y < -2.5 && endless_balllist[11].ball_appear == true && endless_gameplay_balldownnum[0] != 12)
			{
				endless_gameplay_balldownnum[1] = 12;
				if (endless_ball_rand_color[endless_gameplay_balldownnum[0] - 1] == endless_ball_rand_color[11])
				{
					endless_balllist[11].ball_appear = false;
					endless_balllist[endless_gameplay_balldownnum[0] - 1].ball_appear = false;
					endless_gameplay_ball_appearlist[11] = false;
					endless_gameplay_ball_appearlist[endless_gameplay_balldownnum[0] - 1] = false;
					endless_gameplay_eliballnum++;

					endless_lightwall.faci_ball_color_ambient[0] = 0.1;		//将屏幕置回原色
					endless_lightwall.faci_ball_color_diffuse[0] = 0.1;
					endless_lightwall.faci_ball_color_specular[0] = 0.1;

					endless_gameplay_wallstage++;
				}
				else{
					endless_gameplay_eliballnum = 0;
					endless_lightwall.faci_ball_color_ambient[0] = 0.4;		//将屏幕置红
					endless_lightwall.faci_ball_color_diffuse[0] = 0.4;
					endless_lightwall.faci_ball_color_specular[0] = 0.2;

					endless_gameplay_wallstage = 0;

				}
			}		//如果没点对，就两个都变小

			endless_balllist[endless_gameplay_balldownnum[0] - 1].ball_click = false;
			endless_balllist[endless_gameplay_balldownnum[1] - 1].ball_click = false;
			endless_gameplay_ballstage = 1;
			
			if (endless_gameplay_eliballnum >= 6)	//如果已经连续灭了六组球
			{
				
			}
			else{
				//如果有球灭了，看球数量够不够，不然就将灭的球换颜色，然后点亮
				endless_gameplay_balldisapp_num = 0;
				for (int i = 0; i < 12; i++)
				{
					if (endless_gameplay_ball_appearlist[i] == false)	endless_gameplay_balldisapp_num++;		//算有几个被按下了
				}
				if (endless_gameplay_balldisapp_num > 6)		//若果消失的比六个还多，就点让除了刚才消失的两个球之外的都亮
				{
					for (int x = 0; x < 12; x++)
					{
						if (endless_balllist[x].ball_appear == false && endless_gameplay_balldownnum[0] != x + 1 && endless_gameplay_balldownnum[1] != x + 1)
						{
							endless_balllist[x].ball_color = rand() % 4;
							endless_balllist[x].ball_appear = true;
							endless_gameplay_ball_appearlist[x] = true;
							endless_ball_rand_color[x] = endless_balllist[x].ball_color;
						}
					}
				}
			}
		}
		else if (endless_gameplay_ballstage == 2){
			endless_gameplay_ballstage = 3;
		}
	}
}

void endless_control_ball::endless_control_ball_mouseevent_passive()
{
	endless_light0_pos[0] = endless_control_ball_mouseposition_x * 32.0 / 1366.0 - 16.0;		//光源位置随着鼠标位置变化
	endless_light0_pos[1] = 9.0 - endless_control_ball_mouseposition_y * 18.0 / 768.0;
	endless_mouse.faci_ball_position[0] = endless_light0_pos[0];							//鼠标位置变化
	endless_mouse.faci_ball_position[1] = endless_light0_pos[1];

	if (endless_control_ball_gamelevel > 20 && endless_control_ball_gamelevel <= 30)
	{
		for (int c = 0; c < 4; c++)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 12; j++)		//变换ambient颜色
				{
					endless_balllist[j].endless_color_ambient[c][i] += endless_gameplay_rand_updown[c][i * 3] * (0.0035*endless_control_ball_gamelevel - 0.065);
				}
				if (endless_balllist[0].endless_color_ambient[c][i] >= 0.6 || endless_balllist[0].endless_color_ambient[c][i] <= 0.0)
				{
					endless_gameplay_rand_updown[c][i*3] = -endless_gameplay_rand_updown[c][i*3];
				}

				for (int j = 0; j < 12; j++)		//变换diffuse颜色
				{
					endless_balllist[j].endless_color_diffuse[c][i] += endless_gameplay_rand_updown[c][i * 3 + 1] * (0.0035*endless_control_ball_gamelevel - 0.065);
				}
				if (endless_balllist[0].endless_color_diffuse[c][i] >= 0.6 || endless_balllist[0].endless_color_diffuse[c][i] <= 0.0)
				{
					endless_gameplay_rand_updown[c][i*3+1] = -endless_gameplay_rand_updown[c][i*3+1];
				}

				for (int j = 0; j < 12; j++)		//变换specular颜色
				{
					endless_balllist[j].endless_color_specular[c][i] += endless_gameplay_rand_updown[c][i * 3 + 2] * (0.0035*endless_control_ball_gamelevel - 0.065);
				}
				if (endless_balllist[0].endless_color_specular[c][i] >= 0.6 || endless_balllist[0].endless_color_specular[c][i] <= 0.0)
				{
					endless_gameplay_rand_updown[c][i*3+2] = -endless_gameplay_rand_updown[c][i*3+2];
				}
			}
		}
		
	}
	else if (endless_control_ball_gamelevel > 30)
	{
		for (int c = 0; c < 4; c++)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 12; j++)		//变换ambient颜色
				{
					endless_balllist[j].endless_color_ambient[c][i] += endless_gameplay_rand_updown[c][i * 3] * (0.0035*endless_control_ball_gamelevel - 0.1);
				}
				if (endless_balllist[0].endless_color_ambient[c][i] >= 0.6 || endless_balllist[0].endless_color_ambient[c][i] <= 0.0)
				{
					endless_gameplay_rand_updown[c][i * 3] = -endless_gameplay_rand_updown[c][i * 3];
				}

				for (int j = 0; j < 12; j++)		//变换diffuse颜色
				{
					endless_balllist[j].endless_color_diffuse[c][i] += endless_gameplay_rand_updown[c][i * 3 + 1] * (0.0035*endless_control_ball_gamelevel - 0.1);
				}
				if (endless_balllist[0].endless_color_diffuse[c][i] >= 0.6 || endless_balllist[0].endless_color_diffuse[c][i] <= 0.0)
				{
					endless_gameplay_rand_updown[c][i * 3 + 1] = -endless_gameplay_rand_updown[c][i * 3 + 1];
				}

				for (int j = 0; j < 12; j++)		//变换specular颜色
				{
					endless_balllist[j].endless_color_specular[c][i] += endless_gameplay_rand_updown[c][i * 3 + 2] * (0.0035*endless_control_ball_gamelevel - 0.1);
				}
				if (endless_balllist[0].endless_color_specular[c][i] >= 0.6 || endless_balllist[0].endless_color_specular[c][i] <= 0.0)
				{
					endless_gameplay_rand_updown[c][i * 3 + 2] = -endless_gameplay_rand_updown[c][i * 3 + 2];
				}
			}
		}

		for (int i = 0; i < 3; i++)
		{
			endless_light0_ambient[i] += 0.01 * endless_gameplay_light_updown[0][i];
			if (endless_light0_ambient[i] >= 0.6 || endless_light0_ambient[i] <= 0.0)
			{
				endless_gameplay_light_updown[0][i] = -endless_gameplay_light_updown[0][i];
			}

			endless_light0_diffuse[i] += 0.01 * endless_gameplay_light_updown[1][i];
			if (endless_light0_diffuse[i] >= 0.6 || endless_light0_diffuse[i] <= 0.0)
			{
				endless_gameplay_light_updown[1][i] = -endless_gameplay_light_updown[1][i];
			}

			endless_light0_specular[i] += 0.01 * endless_gameplay_light_updown[2][i];
			if (endless_light0_specular[i] >= 0.6 || endless_light0_specular[i] <= 0.0)
			{
				endless_gameplay_light_updown[2][i] = -endless_gameplay_light_updown[2][i];
			}

			endless_light1_ambient[i] += 0.01 * endless_gameplay_light_updown[3][i];
			if (endless_light1_ambient[i] >= 0.2 || endless_light1_ambient[i] <= 0.0)
			{
				endless_gameplay_light_updown[3][i] = -endless_gameplay_light_updown[3][i];
			}

			endless_light1_diffuse[i] += 0.01 * endless_gameplay_light_updown[4][i];
			if (endless_light1_diffuse[i] >= 0.2 || endless_light1_diffuse[i] <= 0.0)
			{
				endless_gameplay_light_updown[4][i] = -endless_gameplay_light_updown[4][i];
			}

			endless_light1_specular[i] += 0.01 * endless_gameplay_light_updown[5][i];
			if (endless_light1_specular[i] >= 0.2 || endless_light1_specular[i] <= 0.0)
			{
				endless_gameplay_light_updown[5][i] = -endless_gameplay_light_updown[5][i];
			}

		}
	}

	//------------------------------处理方框变大变小------------------------------------------------
	if (endless_gameplay_scene == false)		//如果在游戏之中
	{
		if (endless_light0_pos[0] > 12.5 && endless_light0_pos[0] < 15.5 && endless_light0_pos[1] > -3.0 && endless_light0_pos[1] < 0.15)
		{
			endless_gameplay_blockon = -1;		//在当前关的数字上,退到选关菜单
		}
		else if (endless_light0_pos[0] > -15.0 && endless_light0_pos[0] < -14.0 && endless_light0_pos[1] > 6.5 && endless_light0_pos[1] < 7.5)
		{
			endless_gameplay_blockon = -2;		//home键
		}
		else{
			endless_gameplay_blockon = 0;		//什么都没有
		}
	}
	else if (endless_gameplay_scene == true)		//如果在选关画面中
	{
		if (endless_light0_pos[0] > -8.5 && endless_light0_pos[0] < -6.5 && endless_light0_pos[1] > 5.0 && endless_light0_pos[1] < 7.0 && endless_control_ball_toplevel >= 1)
		{
			endless_gameplay_blockon = 1;
		}
		else if (endless_light0_pos[0] > -5.5 && endless_light0_pos[0] < -3.5 && endless_light0_pos[1] > 5.0 && endless_light0_pos[1] < 7.0 && endless_control_ball_toplevel >= 2)
		{
			endless_gameplay_blockon = 2;
		}
		else if (endless_light0_pos[0] > -2.5 && endless_light0_pos[0] < -0.5 && endless_light0_pos[1] > 5.0 && endless_light0_pos[1] < 7.0 && endless_control_ball_toplevel >= 3)
		{
			endless_gameplay_blockon = 3;
		}
		else if (endless_light0_pos[0] > 0.5 && endless_light0_pos[0] < 2.5 && endless_light0_pos[1] > 5.0 && endless_light0_pos[1] < 7.0 && endless_control_ball_toplevel >= 4)
		{
			endless_gameplay_blockon = 4;
		}
		else if (endless_light0_pos[0] > 3.5 && endless_light0_pos[0] < 5.5 && endless_light0_pos[1] > 5.0 && endless_light0_pos[1] < 7.0 && endless_control_ball_toplevel >= 5)
		{
			endless_gameplay_blockon = 5;
		}
		else if (endless_light0_pos[0] > 6.5 && endless_light0_pos[0] < 8.5 && endless_light0_pos[1] > 5.0 && endless_light0_pos[1] < 7.0 && endless_control_ball_toplevel >= 6)
		{
			endless_gameplay_blockon = 6;
		}
		//-------------------------第二排
		else if (endless_light0_pos[0] > -8.5 && endless_light0_pos[0] < -6.5 && endless_light0_pos[1] > 2.0 && endless_light0_pos[1] < 4.0 && endless_control_ball_toplevel >= 7)
		{
			endless_gameplay_blockon = 7;
		}
		else if (endless_light0_pos[0] > -5.5 && endless_light0_pos[0] < -3.5 && endless_light0_pos[1] > 2.0 && endless_light0_pos[1] < 4.0 && endless_control_ball_toplevel >= 8)
		{
			endless_gameplay_blockon = 8;
		}
		else if (endless_light0_pos[0] > -2.5 && endless_light0_pos[0] < -0.5 && endless_light0_pos[1] > 2.0 && endless_light0_pos[1] < 4.0 && endless_control_ball_toplevel >= 9)
		{
			endless_gameplay_blockon = 9;
		}
		else if (endless_light0_pos[0] > 0.5 && endless_light0_pos[0] < 2.5 && endless_light0_pos[1] > 2.0 && endless_light0_pos[1] < 4.0 && endless_control_ball_toplevel >= 10)
		{
			endless_gameplay_blockon = 10;
		}
		else if (endless_light0_pos[0] > 3.5 && endless_light0_pos[0] < 5.5 && endless_light0_pos[1] > 2.0 && endless_light0_pos[1] < 4.0 && endless_control_ball_toplevel >= 11)
		{
			endless_gameplay_blockon = 11;
		}
		else if (endless_light0_pos[0] > 6.5 && endless_light0_pos[0] < 8.5 && endless_light0_pos[1] > 2.0 && endless_light0_pos[1] < 4.0 && endless_control_ball_toplevel >= 12)
		{
			endless_gameplay_blockon = 12;
		}
		//-------------------------------第三排
		else if (endless_light0_pos[0] > -8.5 && endless_light0_pos[0] < -6.5 && endless_light0_pos[1] > -1.0 && endless_light0_pos[1] < 1.0 && endless_control_ball_toplevel >= 13)
		{
			endless_gameplay_blockon = 13;
		}
		else if (endless_light0_pos[0] > -5.5 && endless_light0_pos[0] < -3.5 && endless_light0_pos[1] > -1.0 && endless_light0_pos[1] < 1.0 && endless_control_ball_toplevel >= 14)
		{
			endless_gameplay_blockon = 14;
		}
		else if (endless_light0_pos[0] > -2.5 && endless_light0_pos[0] < -0.5 && endless_light0_pos[1] > -1.0 && endless_light0_pos[1] < 1.0 && endless_control_ball_toplevel >= 15)
		{
			endless_gameplay_blockon = 15;
		}
		else if (endless_light0_pos[0] > 0.5 && endless_light0_pos[0] < 2.5 && endless_light0_pos[1] > -1.0 && endless_light0_pos[1] < 1.0 && endless_control_ball_toplevel >= 16)
		{
			endless_gameplay_blockon = 16;
		}
		else if (endless_light0_pos[0] > 3.5 && endless_light0_pos[0] < 5.5 && endless_light0_pos[1] > -1.0 && endless_light0_pos[1] < 1.0 && endless_control_ball_toplevel >= 17)
		{
			endless_gameplay_blockon = 17;
		}
		else if (endless_light0_pos[0] > 6.5 && endless_light0_pos[0] < 8.5 && endless_light0_pos[1] > -1.0 && endless_light0_pos[1] < 1.0 && endless_control_ball_toplevel >= 18)
		{
			endless_gameplay_blockon = 18;
		}
		//----------------------------第四排
		else if (endless_light0_pos[0] > -8.5 && endless_light0_pos[0] < -6.5 && endless_light0_pos[1] > -4.0 && endless_light0_pos[1] < -2.0 && endless_control_ball_toplevel >= 19)
		{
			endless_gameplay_blockon = 19;
		}
		else if (endless_light0_pos[0] > -5.5 && endless_light0_pos[0] < -3.5 && endless_light0_pos[1] > -4.0 && endless_light0_pos[1] < -2.0 && endless_control_ball_toplevel >= 20)
		{
			endless_gameplay_blockon = 20;
		}
		else if (endless_light0_pos[0] > -2.5 && endless_light0_pos[0] < -0.5 && endless_light0_pos[1] > -4.0 && endless_light0_pos[1] < -2.0 && endless_control_ball_toplevel >= 21)
		{
			endless_gameplay_blockon = 21;
		}
		else if (endless_light0_pos[0] > 0.5 && endless_light0_pos[0] < 2.5 && endless_light0_pos[1] > -4.0 && endless_light0_pos[1] < -2.0 && endless_control_ball_toplevel >= 22)
		{
			endless_gameplay_blockon = 22;
		}
		else if (endless_light0_pos[0] > 3.5 && endless_light0_pos[0] < 5.5 && endless_light0_pos[1] > -4.0 && endless_light0_pos[1] < -2.0 && endless_control_ball_toplevel >= 23)
		{
			endless_gameplay_blockon = 23;
		}
		else if (endless_light0_pos[0] > 6.5 && endless_light0_pos[0] < 8.5 && endless_light0_pos[1] > -4.0 && endless_light0_pos[1] < -2.0 && endless_control_ball_toplevel >= 24)
		{
			endless_gameplay_blockon = 24;
		}
		//--------------------------------------第五排
		else if (endless_light0_pos[0] > -8.5 && endless_light0_pos[0] < -6.5 && endless_light0_pos[1] > -7.0 && endless_light0_pos[1] < -5.0 && endless_control_ball_toplevel >= 25)
		{
			endless_gameplay_blockon = 25;
		}
		else if (endless_light0_pos[0] > -5.5 && endless_light0_pos[0] < -3.5 && endless_light0_pos[1] > -7.0 && endless_light0_pos[1] < -5.0 && endless_control_ball_toplevel >= 26)
		{
			endless_gameplay_blockon = 26;
		}
		else if (endless_light0_pos[0] > -2.5 && endless_light0_pos[0] < -0.5 && endless_light0_pos[1] > -7.0 && endless_light0_pos[1] < -5.0 && endless_control_ball_toplevel >= 27)
		{
			endless_gameplay_blockon = 27;
		}
		else if (endless_light0_pos[0] > 0.5 && endless_light0_pos[0] < 2.5 && endless_light0_pos[1] > -7.0 && endless_light0_pos[1] < -5.0 && endless_control_ball_toplevel >= 28)
		{
			endless_gameplay_blockon = 28;
		}
		else if (endless_light0_pos[0] > 3.5 && endless_light0_pos[0] < 5.5 && endless_light0_pos[1] > -7.0 && endless_light0_pos[1] < -5.0 && endless_control_ball_toplevel >= 29)
		{
			endless_gameplay_blockon = 29;
		}
		else if (endless_light0_pos[0] > 6.5 && endless_light0_pos[0] < 8.5 && endless_light0_pos[1] > -7.0 && endless_light0_pos[1] < -5.0 && endless_control_ball_toplevel >= 30)
		{
			endless_gameplay_blockon = 30;
		}
		else if (endless_light0_pos[0] > 9.5 && endless_light0_pos[0] < 11.5 && endless_light0_pos[1] > -7.0 && endless_light0_pos[1] < -5.0 && endless_control_ball_toplevel >= 31)
		{
			endless_gameplay_blockon = 31;
		}
		else if (endless_light0_pos[0] > -15.0 && endless_light0_pos[0] < -14.0 && endless_light0_pos[1] > 6.5 && endless_light0_pos[1] < 7.5)
		{
			endless_gameplay_blockon = -2;		//home键
		}
		else{
			endless_gameplay_blockon = 0;
		}
	}
}

void endless_control_ball::endless_control_ball_mouseevent_motion()
{
	endless_light0_pos[0] = endless_control_ball_mouseposition_x * 32.0 / 1366.0 - 16.0;		//光源位置随着鼠标位置变化
	endless_light0_pos[1] = 9.0 - endless_control_ball_mouseposition_y * 18.0 / 768.0;
	endless_mouse.faci_ball_position[0] = endless_light0_pos[0];							//鼠标位置变化
	endless_mouse.faci_ball_position[1] = endless_light0_pos[1];
}