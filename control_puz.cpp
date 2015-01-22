#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <GL/glut.h>
#include <GL/glaux.h>
#include <math.h>
#include "control_puz.h"
#include "piece.h"
#include "word.h"
#pragma comment(lib, "glaux")	

using namespace std;

bool control_puz_scene = true;		//控制场景切换，false = 选关, true = 拼图阶段
float menu_pos = 70.0;
int menu_blockon = 0;
bool control_puz_complete = false;		//拼图有没有完成，false=没有
bool control_puz_coordinates = false;
bool control_puz_sideshow = true;

int control_puz_onlevel = 1;		//现在是第几关-------------------------------------------------------------
int control_puz_highlevel = 5;		//最高现在达到第几关--------------------------第几关已经解锁-----------------------------

float piece1_position[3];
float piece2_position[3];
float piece3_position[3];
float piece4_position[3];
float piece5_position[3];
float piece6_position[3];
float piece7_position[3];
float piece8_position[3];
float piece9_position[3];
float piece10_position[3];
float piece11_position[3];
float piece12_position[3];

float piece_angle[12];
float piece_size[3] = { 0.0, 0.0, 0.0 };

int piece1_color[12];

piece piecelist[12] = {
	piece(0, piece1_position, piece_size, piece_angle[0], piece1_color[0], 117, false, false, false),
	piece(0, piece2_position, piece_size, piece_angle[1], piece1_color[1], 117, false, false, false),
	piece(0, piece3_position, piece_size, piece_angle[2], piece1_color[2], 117, false, false, false),
	piece(0, piece4_position, piece_size, piece_angle[3], piece1_color[3], 117, false, false, false),
	piece(0, piece5_position, piece_size, piece_angle[4], piece1_color[4], 117, false, false, false),
	piece(0, piece6_position, piece_size, piece_angle[5], piece1_color[5], 117, false, false, false),
	piece(0, piece7_position, piece_size, piece_angle[6], piece1_color[6], 117, false, false, false),
	piece(0, piece8_position, piece_size, piece_angle[7], piece1_color[7], 117, false, false, false),
	piece(0, piece9_position, piece_size, piece_angle[8], piece1_color[8], 117, false, false, false),
	piece(0, piece10_position, piece_size, piece_angle[9], piece1_color[9], 117, false, false, false),
	piece(0, piece11_position, piece_size, piece_angle[10], piece1_color[10], 117, false, false, false),
	piece(0, piece12_position, piece_size, piece_angle[11], piece1_color[11], 117, false, false, false),
};

float big_circle_position[3];

piece big_circle(1, big_circle_position, piece_size, 0.0, 0, 0, false, false, false);


//-------------------------------------word----------------------------------------------------

char *line1_cont = "Gallery";
char *line1_font = "Consolas";
float line1_pos[3] = { -15.0, 13.0, 3.0 };
int line1_size = 32;
float line1_color[4] = { 1.0, 1.0, 1.0, 1.0 };

word line1(line1_pos, true, line1_size, line1_color, line1_cont, line1_font);


//----------------------------------------buttons--------------------------------------------------------------
float control_puz_mouse_pos[3] = { 0.0, 0.0, 0.2 };
float control_puz_mouse_size[3] = { 0.7, 0.7, 0.0 };
piece control_puz_mouse(2, control_puz_mouse_pos, control_puz_mouse_size, 0.0, 123, 0, true, false, false);

float control_puz_next_pos[3] = { 25.0, 5.2, 0.1 };			//next
float control_puz_next_size[3] = { 5.0, 5.0, 0.0 };
piece control_puz_next(2, control_puz_next_pos, control_puz_next_size, 0.0, 121, 0, true, false, false);		//nextno

float control_puz_back_pos[3] = { 25.0, -0.0, 0.1 };					//返回
float control_puz_back_size[3] = { 5.0, 5.0, 0.0 };
piece control_puz_back(2, control_puz_back_pos, control_puz_back_size, 0.0, 118, 0, true, false, false);

float control_puz_refresh_pos[3] = { 25.0, -5.2, 0.1 };			//刷新
float control_puz_refresh_size[3] = { 5.0, 5.0, 0.0 };
piece control_puz_refresh(2, control_puz_refresh_pos, control_puz_refresh_size, 0.0, 119, 0, true, false, false);

float control_puz_tu_pos[3] = { -23.5, 0.0, 0.02 };			//提示
float control_puz_tu_size[3] = { 10.0, 30.0, 0.0 };
piece control_puz_tu(2, control_puz_tu_pos, control_puz_tu_size, 0.0, 122, 0, true, false, false);

float control_puz_home_pos[3] = { -24.0, 12.0, 0.1 };			//home
float control_puz_home_size[3] = { 2.0, 2.0, 0.0 };
piece control_puz_home(2, control_puz_home_pos, control_puz_home_size, 0.0, 124, 0, true, false, false);

//---------------------------------------------主界面---------------------------------------------------------
float control_puz_c1_pos[3] = { -10.5, 8.0, 0.1 };
float control_puz_c_size[3] = { 10.0, 7.5, 0.0 };

float control_puz_c2_pos[3] = { 0.0, 8.0, 0.1 };

float control_puz_c3_pos[3] = { 10.5, 8.0, 0.1 };

float control_puz_c4_pos[3] = { -10.5, 0.0, 0.1 };

float control_puz_c5_pos[3] = { 0.0, 0.0, 0.1 };

float control_puz_c6_pos[3] = { 10.5, 0.0, 0.1 };

float control_puz_c7_pos[3] = { -10.5, -8.0, 0.1 };

float control_puz_c8_pos[3] = { 0.0, -8.0, 0.1 };

float control_puz_c9_pos[3] = { 10.5, -8.0, 0.1 };

piece clist[9] =
{
	piece(2, control_puz_c1_pos, control_puz_c_size, 0.0, 125, 117, true, false, false),
	piece(2, control_puz_c2_pos, control_puz_c_size, 0.0, 126, 117, true, false, false),
	piece(2, control_puz_c3_pos, control_puz_c_size, 0.0, 127, 117, true, false, false),
	piece(2, control_puz_c4_pos, control_puz_c_size, 0.0, 128, 117, true, false, false),
	piece(2, control_puz_c5_pos, control_puz_c_size, 0.0, 129, 117, true, false, false),
	piece(2, control_puz_c6_pos, control_puz_c_size, 0.0, 130, 117, true, false, false),
	piece(2, control_puz_c7_pos, control_puz_c_size, 0.0, 131, 117, true, false, false),
	piece(2, control_puz_c8_pos, control_puz_c_size, 0.0, 132, 117, true, false, false),
	piece(2, control_puz_c9_pos, control_puz_c_size, 0.0, 133, 117, true, false, false),
};

void control_puz::control_puz_randblock()
{
	float control_puz_distance[12];
	float control_puz_min_distance = 100;
	srand((int)time(0));
	for (int i = 0; i < 12; i++)
	{
		do
		{
			control_puz_min_distance = 100;
			piecelist[i].piece_position[0] = (float)(-1600 + rand() % 3200) / 100;				//随机取位置
			piecelist[i].piece_position[1] = (float)(-900 + rand() % 1800) / 100;

			for (int j = 0; j < 12; j++)		//与每个块的距离计成数组，其中第j=i块一定是0
			{
				control_puz_distance[j] = (piecelist[i].piece_position[0] - piecelist[j].piece_position[0])*(piecelist[i].piece_position[0] - piecelist[j].piece_position[0])
					+ (piecelist[i].piece_position[1] - piecelist[j].piece_position[1])*(piecelist[i].piece_position[1] - piecelist[j].piece_position[1]);
			}

			for (int k = 0; k < 12; k++)		//让min_distance等于11个距离的最小值
			{
				if (control_puz_distance[k] < control_puz_min_distance && control_puz_distance[k] != 0)
				{
					control_puz_min_distance = control_puz_distance[k];
				}
			}
		} while (control_puz_min_distance < 32);			//如果距离的最小值大于32，可以进行下一个方块
	}

	for (int i = 0; i < 12; i++)		//产生12个随机角度
	{
		piecelist[i].piece_angle = (float)(rand() % 360);
	}
}

void control_puz::control_puz_init()
{
	control_puz_gameon = 0;
	for (int i = 0; i < 9; i++)
	{
		clist[i].piece_scale = 1.0;
		if (i < control_puz_highlevel)		//如果没到最高的关呢，就让他亮
		{
			clist[i].piece_color = i;
		}
	}
	control_puz_mouse.piece_scale = 1.0;
	control_puz_next.piece_scale = 1.0;
	control_puz_back.piece_scale = 1.0;
	control_puz_refresh.piece_scale = 1.0;
	control_puz_tu.piece_scale = 1.0;
	control_puz_home.piece_scale = 1.0;
	
	piecelist[0].piece_settexture();

	control_puz_rotate_num = 30;
	control_puz_tran_num = 30;

	control_puz_rotate_on = false;

	control_puz_randblock();
}

control_puz::control_puz()		//中间类的构建器
{

}

void control_puz::control_puz_idle()
{
	if (control_puz_scene == false)		//如果是在拼图界面	
	{
		if (control_puz_sideshow == false && control_puz_tu.piece_appear == true)
		{
			control_puz_tu.piece_scale -= 0.005;
			if (control_puz_tu.piece_scale < 0.1)
			{
				control_puz_tu.piece_appear = false;
			}
		}
		
		if (menu_pos > 0.0)
		{
			menu_pos -= 0.01 * menu_pos;
		}

		if (menu_pos < 0.05)
		{
			menu_pos = 0.0;
			for (int i = 0; i < 9; i++)
			{
				clist[i].piece_appear = false;
				clist[i].piece_scale = 1.0;
			}
			line1.word_appear = false;
			control_puz_home.piece_appear = false;
		}

		if (control_puz_complete == true)		//拼好了将他们对齐
		{
			for (int i = 0; i < 3; i++)		//横排缩进
			{
				if (piecelist[i + 1].piece_position[0] - piecelist[i].piece_position[0] > 4.0)
				{
					piecelist[i + 1].piece_position[0] -= 0.001;
				}
				if (piecelist[i + 2].piece_position[0] - piecelist[i + 1].piece_position[0] > 4.0)
				{
					piecelist[i + 2].piece_position[0] -= 0.001;
				}
				if (piecelist[i + 3].piece_position[0] - piecelist[i + 2].piece_position[0] > 4.0)
				{
					piecelist[i + 3].piece_position[0] -= 0.001;
				}
			}
			for (int i = 0; i < 4; i++)		//竖排缩进
			{
				if (piecelist[i].piece_position[1] - piecelist[i + 4].piece_position[1] > 4.0)
				{
					piecelist[i + 4].piece_position[1] += 0.001;
				}
				if (piecelist[i + 4].piece_position[1] - piecelist[i + 8].piece_position[1] > 4.0)
				{
					piecelist[i + 8].piece_position[1] += 0.001;
				}
			}

			for (int i = 0; i < 3; i++)		//横排对齐
			{
				if (piecelist[i * 4].piece_position[1] - piecelist[i * 4 + 1].piece_position[1] > 0.0)
				{
					piecelist[i * 4 + 1].piece_position[1] += 0.001;
				}
				else if (piecelist[i * 4].piece_position[1] - piecelist[i * 4 + 1].piece_position[1] < 0.0)
				{
					piecelist[i * 4 + 1].piece_position[1] -= 0.001;
				}

				if (piecelist[i * 4 + 1].piece_position[1] - piecelist[i * 4 + 2].piece_position[1] > 0.0)
				{
					piecelist[i * 4 + 2].piece_position[1] += 0.001;
				}
				else if (piecelist[i * 4 + 1].piece_position[1] - piecelist[i * 4 + 2].piece_position[1] < 0.0)
				{
					piecelist[i * 4 + 2].piece_position[1] -= 0.001;
				}

				if (piecelist[i * 4 + 2].piece_position[1] - piecelist[i * 4 + 3].piece_position[1] > 0.0)
				{
					piecelist[i * 4 + 3].piece_position[1] += 0.001;
				}
				else if (piecelist[i * 4 + 2].piece_position[1] - piecelist[i * 4 + 3].piece_position[1] < 0.0)
				{
					piecelist[i * 4 + 3].piece_position[1] -= 0.001;
				}
			}

			for (int i = 0; i < 4; i++)		//竖排对齐
			{
				if (piecelist[i].piece_position[0] - piecelist[i + 4].piece_position[0] > 0.0)
				{
					piecelist[i + 4].piece_position[0] += 0.001;
				}
				else if (piecelist[i].piece_position[0] - piecelist[i + 4].piece_position[0] < 0.0)
				{
					piecelist[i + 4].piece_position[0] -= 0.001;
				}

				if (piecelist[i + 4].piece_position[0] - piecelist[i + 8].piece_position[0] > 0.0)
				{
					piecelist[i + 8].piece_position[0] += 0.001;
				}
				else if (piecelist[i + 4].piece_position[0] - piecelist[i + 8].piece_position[0] < 0.0)
				{
					piecelist[i + 8].piece_position[0] -= 0.001;
				}
			}
		}

		if (menu_pos == 0.0)
		{
			switch (menu_blockon)
			{
			case 0:
			{
					  control_puz_next.piece_turn_small();
					  control_puz_back.piece_turn_small();
					  control_puz_refresh.piece_turn_small();
					  break;
			}
			case 1:
			{
					  control_puz_next.piece_turn_big();
					  control_puz_back.piece_turn_small();
					  control_puz_refresh.piece_turn_small();
					  break;
			}
			case 2:
			{
					  control_puz_next.piece_turn_small();
					  control_puz_back.piece_turn_big();
					  control_puz_refresh.piece_turn_small();
					  break;
			}
			case 3:
			{
					  control_puz_next.piece_turn_small();
					  control_puz_back.piece_turn_small();
					  control_puz_refresh.piece_turn_big();
					  break;
			}
			}
		}
	}
	else{		//如果是在选单界面
		if (menu_pos < 70.0)
		{
			menu_pos += -0.01 * menu_pos + 0.7;
		}

		if (menu_pos > 69.95)		//帮助归中
		{
			menu_pos = 70.0;
			for (int i = 0; i < 12; i++)
			{
				piecelist[i].piece_appear = false;
			}
			control_puz_back.piece_scale = 1.0;
		}

		if (menu_pos == 70.0)
		{
			switch (menu_blockon)
			{
			case 0:
			{
					  for (int i = 0; i < 9; i++)
					  {
						  clist[i].piece_turn_small();
					  }
					  control_puz_home.piece_turn_small();
					  break;
					  
			}
			case 1:
			{
					  clist[0].piece_turn_big();
					  for (int i = 0; i < 9; i++)
					  {
						  if (i != 0)
						  {
							  clist[i].piece_turn_small();
						  }
					  }
					  control_puz_home.piece_turn_small();
					  break;
			}
			case 2:
			{
					  clist[1].piece_turn_big();
					  for (int i = 0; i < 9; i++)
					  {
						  if (i != 1)
						  {
							  clist[i].piece_turn_small();
						  }
					  }
					  control_puz_home.piece_turn_small();
					  break;
			}
			case 3:
			{
					  clist[2].piece_turn_big();
					  for (int i = 0; i < 9; i++)
					  {
						  if (i != 2)
						  {
							  clist[i].piece_turn_small();
						  }
					  }
					  control_puz_home.piece_turn_small();
					  break;
			}
			case 4:
			{
					  clist[3].piece_turn_big();
					  for (int i = 0; i < 9; i++)
					  {
						  if (i != 3)
						  {
							  clist[i].piece_turn_small();
						  }
					  }
					  control_puz_home.piece_turn_small();
					  break;
			}
			case 5:
			{
					  clist[4].piece_turn_big();
					  for (int i = 0; i < 9; i++)
					  {
						  if (i != 4)
						  {
							  clist[i].piece_turn_small();
						  }
					  }
					  control_puz_home.piece_turn_small();
					  break;
			}
			case 6:
			{
					  clist[5].piece_turn_big();
					  for (int i = 0; i < 9; i++)
					  {
						  if (i != 5)
						  {
							  clist[i].piece_turn_small();
						  }
					  }
					  control_puz_home.piece_turn_small();
					  break;
			}
			case 7:
			{
					  clist[6].piece_turn_big();
					  for (int i = 0; i < 9; i++)
					  {
						  if (i != 6)
						  {
							  clist[i].piece_turn_small();
						  }
					  }
					  control_puz_home.piece_turn_small();
					  break;
			}
			case 8:
			{
					  clist[7].piece_turn_big();
					  for (int i = 0; i < 9; i++)
					  {
						  if (i != 7)
						  {
							  clist[i].piece_turn_small();
						  }
					  }
					  control_puz_home.piece_turn_small();
					  break;
			}
			case 9:
			{
					  clist[8].piece_turn_big();
					  for (int i = 0; i < 9; i++)
					  {
						  if (i != 8)
						  {
							  clist[i].piece_turn_small();
						  }
					  }
					  control_puz_home.piece_turn_small();
					  break;
			}
			case 10:
			{
					   control_puz_home.piece_turn_big();
					   for (int i = 0; i < 9; i++)
					   {
						   if (i != 8)
						   {
							   clist[i].piece_turn_small();
						   }
					   }
					   break;
			}
			}
		}
	}
}

void control_puz::control_puz_drawall()		//画出所有的东西
{
	glPushMatrix();

	glDisable(GL_TEXTURE_2D);
	glColor3f(1.0, 1.0, 1.0);
	control_puz_mouse.piece_drawself();

	glEnable(GL_TEXTURE_2D);

	glTranslatef(menu_pos, 0.0, 0.0);

	glPushMatrix();		//向左移画菜单界面
	
	glTranslatef(-70.0, 0.0, 0.0);
	control_puz_home.piece_drawself();
	line1.drawself();

	if (control_puz_gameon == 3)
	{
		for (int i = 0; i < 9; i++)
		{
			clist[i].piece_drawself();
		}
	}
	
	glPopMatrix();
	
	
	glPushMatrix();		//画拼图界面
	control_puz_refresh.piece_drawself();
	control_puz_next.piece_drawself();
	control_puz_back.piece_drawself();
	control_puz_tu.piece_drawself();

	for (int i = 0; i < 12; i++)
	{
		piecelist[i].piece_drawself();		//读取纹理
	}

	glDisable(GL_TEXTURE_2D);
	
	big_circle.piece_drawself();

	if (control_puz_coordinates == true && control_puz_complete == false)		//如果坐标系要显示出来的话
	{
		glColor3f(0.3, 0.3, 0.3);
		glBegin(GL_LINES);
		glVertex3f(-16.0, 0.0, -3.0);
		glVertex3f(16.0, 0.0, -3.0);
		glEnd();

		glBegin(GL_LINES);
		glVertex3f(0.0, -9.0, -3.0);
		glVertex3f(0.0, 9.0, -3.0);
		glEnd();

		glColor3f(0.2, 0.2, 0.2);
		glBegin(GL_TRIANGLE_FAN);
		int n = 50;
		for (int i = 0; i < n; ++i)
			glVertex2f(1.0 *cos(2 * 3.14159265354 / n*i), 1.0*sin(2 * 3.14159265354 / n*i));
		glEnd();
	}
	
	glEnable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();
}

void control_puz::control_puz_mouseevent()		//处理所有鼠标点击
{
	control_puz_rotate_on = false;

	if (control_puz_scene == false)		//拼图页面
	{
		if (control_puz_left_mouse_down == false)
		{
			control_puz_coordinates = false;		//不移动了就不画坐标系
			for (int i = 0; i < 12; i++)
			{
				piecelist[i].piece_axis = false;
			}
			if (abs(piecelist[control_puz_tran_num].piece_position[0]) < 1.0 && abs(piecelist[control_puz_tran_num].piece_position[1]) < 1.0)
			{
				piecelist[control_puz_tran_num].piece_position[0] = 0.0;
				piecelist[control_puz_tran_num].piece_position[1] = 0.0;
			}

			big_circle.piece_appear = false;

			//---------------------辨认拼图是否拼上------------------angle, pos------------------
			bool standard1 = true;		//先设正确，如果有一个不对了就错了
			for (int q = 0; q < 4; q++)		//判断每列是否对齐
			{
				if (piecelist[q].piece_position[1] - piecelist[q + 4].piece_position[1] < 0.0 || piecelist[q].piece_position[1] - piecelist[q + 4].piece_position[1] > 7.0)
				{
					standard1 = false;
				}
				if (piecelist[q + 4].piece_position[1] - piecelist[q + 8].piece_position[1] < 0.0 || piecelist[q + 4].piece_position[1] - piecelist[q + 8].piece_position[1] > 7.0)
				{
					standard1 = false;
				}
			}

			for (int q = 0; q < 3; q++)		//判断每行是否对齐
			{
				if (piecelist[q*4 + 1].piece_position[0] - piecelist[q*4].piece_position[0] < 0.0 || piecelist[q*4 + 1].piece_position[0] - piecelist[q*4].piece_position[0] > 7.0)
				{
					standard1 = false;
				}
				if (piecelist[q*4 + 2].piece_position[0] - piecelist[q*4 + 1].piece_position[0] < 0.0 || piecelist[q*4 + 2].piece_position[0] - piecelist[q*4 + 1].piece_position[0] > 7.0)
				{
					standard1 = false;
				}
				if (piecelist[q*4 + 3].piece_position[0] - piecelist[q*4 + 2].piece_position[0] < 0.0 || piecelist[q*4 + 3].piece_position[0] - piecelist[q*4 + 2].piece_position[0] > 7.0)
				{
					standard1 = false;
				}
			}

			int x;
			for (int i = 0; i < 12; i++)
			{
				x = (int)piecelist[i].piece_angle % 360;
				if ( (x > 20 && x < 340) || (x > -340 && x < -20))
				{
					standard1 = false;
				}
			}
			
			if (standard1 == true && control_puz_complete == false)
			{
				for (int i = 0; i < 12; i++)
				{
					piecelist[i].piece_rotateon = false;
					piecelist[i].piece_mouseon = false;
				}
				control_puz_complete = true;
				control_puz_next.piece_color = 120;		//--------------------------------------完成之后换贴图 next

				for (int i = 0; i < 12; i++)	//角度规正
				{
					piecelist[i].piece_angle = 0.0;
					piecelist[i].piece_angle2 = 0.0;
				}

				if (control_puz_onlevel == control_puz_highlevel)
				{
					control_puz_highlevel++;
				}
				for (int i = 0; i < 9; i++)			//点亮新的关
				{
					if (i < control_puz_highlevel)
					{
						clist[i].piece_color = i;
					}
				}
			}
		}
		else if (control_puz_left_mouse_down == true)
		{
			if (control_puz_posx > 22.5 && control_puz_posx < 27.5)	//三个按键
			{
				if (control_puz_posy > 2.7 && control_puz_posy < 7.7)	//下一关
				{
					control_puz_next.piece_scale = 1.05;
					if (control_puz_complete == true)		//完成了才管用
					{
						control_puz_onlevel++;
						for (int i = 0; i < 12; i++)
						{
							piecelist[i].piece_color = 9 + 12 * (control_puz_onlevel - 1) + i;
						}
						control_puz_next.piece_color = 121;
						control_puz_randblock();
						control_puz_complete = false;
					}
				}
				else if (control_puz_posy > -2.5 && control_puz_posy < 2.5)		//返回
				{
					control_puz_back.piece_scale = 1.05;
					control_puz_scene = true;
					for (int i = 0; i < 9; i++)
					{
						clist[i].piece_appear = true;
					}
					line1.word_appear = true;
					control_puz_home.piece_appear = true;
					control_puz_next.piece_color = 121;
					control_puz_complete = false;
				}
				else if (control_puz_posy > -7.7 && control_puz_posy < -2.7)		//刷新
				{
					control_puz_refresh.piece_scale = 1.05;
					control_puz_next.piece_color = 121;
					control_puz_randblock();
					control_puz_complete = false;
				}
			}
		}
	}
	else if (control_puz_scene == true)		//菜单页面
	{
		if (control_puz_left_mouse_down == true)
		{
			bool puz_zppear = false;
			if (control_puz_posy > 4.25 && control_puz_posy < 11.75)	//第一排123
			{
				if (control_puz_posx > -15.5 && control_puz_posx < -5.5)	//1
				{
					clist[0].piece_scale = 1.05;
					if (control_puz_highlevel > 0)
					{
						control_puz_scene = false;
						for (int i = 0; i < 12; i++)
						{
							piecelist[i].piece_color = 9 + i;
						}
						control_puz_randblock();
						control_puz_complete = false;
						puz_zppear = true;
						control_puz_onlevel = 1;
					}
				}
				else if (control_puz_posx > -5.0 && control_puz_posx < 5.0)		//2
				{
					clist[1].piece_scale = 1.05;
					if (control_puz_highlevel > 1)
					{
						control_puz_scene = false;
						for (int i = 0; i < 12; i++)
						{
							piecelist[i].piece_color = 21 + i;
						}
						control_puz_randblock();
						control_puz_complete = false;
						puz_zppear = true;
						control_puz_onlevel = 2;
					}
				}
				else if (control_puz_posx > 5.5 && control_puz_posx < 15.5)		//3
				{
					clist[2].piece_scale = 1.05;
					if (control_puz_highlevel > 2)
					{
						control_puz_scene = false;
						for (int i = 0; i < 12; i++)
						{
							piecelist[i].piece_color = 33 + i;
						}
						control_puz_randblock();
						control_puz_complete = false;
						puz_zppear = true;
						control_puz_onlevel = 3;
					}
				}
			}
			else if (control_puz_posy > -3.75 && control_puz_posy < 3.75)		//第二排456
			{
				if (control_puz_posx > -15.5 && control_puz_posx < -5.5)	//4
				{
					clist[3].piece_scale = 1.05;
					if (control_puz_highlevel > 3)
					{
						control_puz_scene = false;
						for (int i = 0; i < 12; i++)
						{
							piecelist[i].piece_color = 45 + i;
						}
						control_puz_randblock();
						control_puz_complete = false;
						puz_zppear = true;
						control_puz_onlevel = 4;
					}
				}
				else if (control_puz_posx > -5.0 && control_puz_posx < 5.0)		//5
				{
					clist[4].piece_scale = 1.05;
					if (control_puz_highlevel > 4)
					{
						control_puz_scene = false;
						for (int i = 0; i < 12; i++)
						{
							piecelist[i].piece_color = 57 + i;
						}
						control_puz_randblock();
						control_puz_complete = false;
						puz_zppear = true;
						control_puz_onlevel = 5;
					}

				}
				else if (control_puz_posx > 5.5 && control_puz_posx < 15.5)		//6
				{

					clist[5].piece_scale = 1.05;
					if (control_puz_highlevel > 5)
					{
						control_puz_scene = false;
						for (int i = 0; i < 12; i++)
						{
							piecelist[i].piece_color = 69 + i;
						}
						control_puz_randblock();
						control_puz_complete = false;
						puz_zppear = true;
						control_puz_onlevel = 6;
					}
				}
			}
			else if (control_puz_posy > -11.75 && control_puz_posy < -4.25)
			{
				if (control_puz_posx > -15.5 && control_puz_posx < -5.5)	//7
				{
					clist[6].piece_scale = 1.05;
					if (control_puz_highlevel > 6)
					{
						control_puz_scene = false;
						for (int i = 0; i < 12; i++)
						{
							piecelist[i].piece_color = 81 + i;
						}
						control_puz_randblock();
						control_puz_complete = false;
						puz_zppear = true;
						control_puz_onlevel = 7;
					}
				}
				else if (control_puz_posx > -5.0 && control_puz_posx < 5.0)		//8
				{
					clist[7].piece_scale = 1.05;
					if (control_puz_highlevel > 8)
					{
						control_puz_scene = false;
						for (int i = 0; i < 12; i++)
						{
							piecelist[i].piece_color = 93 + i;
						}
						control_puz_randblock();
						control_puz_complete = false;
						puz_zppear = true;
						control_puz_onlevel = 8;
					}
				}
				else if (control_puz_posx > 5.5 && control_puz_posx < 15.5)		//9
				{
					clist[8].piece_scale = 1.05;
					if (control_puz_highlevel > 9)
					{
						control_puz_scene = false;
						for (int i = 0; i < 12; i++)
						{
							piecelist[i].piece_color = 105 + i;
						}
						control_puz_randblock();
						control_puz_complete = false;
						puz_zppear = true;
						control_puz_onlevel = 9;
					}
				}
			}
			
			if (control_puz_posy > 11.0 && control_puz_posy < 13.0 && control_puz_posx > -25.0 && control_puz_posx < -23.0)		//home
			{
				control_puz_home.piece_scale = 1.05;//home
				control_puz_gameon = 0;
			}

			if (puz_zppear == true)
			{
				for (int y = 0; y < 12; y++)
				{
					piecelist[y].piece_appear = true;
				}
			}
		}
	}
}

void control_puz::control_puz_mouseevent_passive()		//处理鼠标滑动
{
	control_puz_rotate_on = false;
	control_puz_posx = control_puz_mouseposition_x * 64.0 / 1366.0 - 32.0;
	control_puz_posy = 18.0 - control_puz_mouseposition_y * 36.0 / 768.0;

	control_puz_mouse.piece_position[0] = control_puz_posx;
	control_puz_mouse.piece_position[1] = control_puz_posy;

	if (control_puz_scene == false)
	{
		if (control_puz_posx > 22.5 && control_puz_posx < 27.5)	//三个按键
		{
			if (control_puz_posy > 2.7 && control_puz_posy < 7.7)	//下一关
			{
				menu_blockon = 1;
			}
			else if (control_puz_posy > -2.5 && control_puz_posy < 2.5)		//返回
			{
				menu_blockon = 2;
			}
			else if (control_puz_posy > -7.7 && control_puz_posy < -2.7)		//刷新
			{
				menu_blockon = 3;
			}
			else{
				menu_blockon = 0;
			}
		}
		else{
			menu_blockon = 0;
		}

		if (control_puz_complete == false)
		{
			float distance;
			for (int i = 0; i < 12; i++)		//鼠标接近圆心，显示叉代表可以位移
			{
				distance = (control_puz_posx - piecelist[i].piece_position[0])*(control_puz_posx - piecelist[i].piece_position[0]) + (control_puz_posy - piecelist[i].piece_position[1])*(control_puz_posy - piecelist[i].piece_position[1]);
				if (distance <= 1.3 * 1.3)
				{
					piecelist[i].piece_mouseon = true;
				}
				else{
					piecelist[i].piece_mouseon = false;
				}
			}

			for (int i = 0; i < 12; i++)		//鼠标接近定点，显示圆圈表示可以转动
			{
				distance = (control_puz_posx - piecelist[i].piece_position[0])*(control_puz_posx - piecelist[i].piece_position[0]) + (control_puz_posy - piecelist[i].piece_position[1])*(control_puz_posy - piecelist[i].piece_position[1]);
				if (distance >= 2.0 * 2.0 && distance <= 3.0 * 3.0)
				{
					piecelist[i].piece_rotateon = true;
				}
				else{
					piecelist[i].piece_rotateon = false;
				}
			}
		}
	}
	else if (control_puz_scene == true)		//菜单页面
	{
		if (control_puz_posy > 4.25 && control_puz_posy < 11.75 && control_puz_posx > -15.5 && control_puz_posx < -5.5)	//1
		{
			menu_blockon = 1;
		}
		else if (control_puz_posy > 4.25 && control_puz_posy < 11.75 && control_puz_posx > -5.0 && control_puz_posx < 5.0)		//2
		{
			menu_blockon = 2;
		}
		else if (control_puz_posy > 4.25 && control_puz_posy < 11.75 && control_puz_posx > 5.5 && control_puz_posx < 15.5)		//3
		{
			menu_blockon = 3;
		}
		else if (control_puz_posy > -3.75 && control_puz_posy < 3.75 && control_puz_posx > -15.5 && control_puz_posx < -5.5)	//4
		{
			menu_blockon = 4;
		}
		else if (control_puz_posy > -3.75 && control_puz_posy < 3.75 && control_puz_posx > -5.0 && control_puz_posx < 5.0)		//5
		{
			menu_blockon = 5;
		}
		else if (control_puz_posy > -3.75 && control_puz_posy < 3.75 && control_puz_posx > 5.5 && control_puz_posx < 15.5)		//6
		{
			menu_blockon = 6;
		}
		else if (control_puz_posy > -11.75 && control_puz_posy < -4.25 && control_puz_posx > -15.5 && control_puz_posx < -5.5)	//7
		{
			menu_blockon = 7;
		}
		else if (control_puz_posy > -11.75 && control_puz_posy < -4.25 && control_puz_posx > -5.0 && control_puz_posx < 5.0)		//8
		{
			menu_blockon = 8;
		}
		else if (control_puz_posy > -11.75 && control_puz_posy < -4.25 && control_puz_posx > 5.5 && control_puz_posx < 15.5)		//9
		{
			menu_blockon = 9;
		}
		else if (control_puz_posy > 11.0 && control_puz_posy < 13.0 && control_puz_posx > -25.0 && control_puz_posx < -23.0)		//home
		{
			menu_blockon = 10;
		}
		else{
			menu_blockon = 0;
		}
	}

	control_puz_mouseposition_x_pre = control_puz_posx;
	control_puz_mouseposition_y_pre = control_puz_posy;
}

void control_puz::control_puz_mouseevent_motion()			//处理鼠标拖拽
{
	control_puz_posx = control_puz_mouseposition_x * 64.0 / 1366.0 - 32.0;
	control_puz_posy = 18.0 - control_puz_mouseposition_y * 36.0 / 768.0;

	control_puz_mouse.piece_position[0] = control_puz_posx;
	control_puz_mouse.piece_position[1] = control_puz_posy;

	if (control_puz_scene == false && control_puz_complete == false)
	{
		float distance;

		control_puz_coordinates = true;		//移动的时候画坐标系
	
		for (int i = 0; i < 12; i++)		//确认哪个在动
		{
			distance = (control_puz_posx - piecelist[i].piece_position[0])*(control_puz_posx - piecelist[i].piece_position[0]) + (control_puz_posy - piecelist[i].piece_position[1])*(control_puz_posy - piecelist[i].piece_position[1]);
			if (distance <= 1.8 * 1.8)
			{
				control_puz_tran_num = i;
			}
		}

		if (control_puz_left_mouse_down == true)		//左键代表要在世界坐标中变换
		{
			if (control_puz_rotate_on == false)			//如果不在转圈进行中
			{
				for (int i = 0; i < 12; i++)		//退拽位移
				{
					distance = (control_puz_posx - piecelist[i].piece_position[0])*(control_puz_posx - piecelist[i].piece_position[0]) + (control_puz_posy - piecelist[i].piece_position[1])*(control_puz_posy - piecelist[i].piece_position[1]);
					if (distance <= 1.8 * 1.8)
					{
						piecelist[i].piece_position[0] += (control_puz_posx - control_puz_mouseposition_x_pre);
						piecelist[i].piece_position[1] += (control_puz_posy - control_puz_mouseposition_y_pre);
						control_puz_tran_num = i;
						control_puz_rotate_num = 30;	//防止后面碰撞不算
						piecelist[i].piece_axis = true;
					}
				}

				for (int i = 0; i < 12; i++)		//拖拽旋转
				{
					distance = (control_puz_posx - piecelist[i].piece_position[0])*(control_puz_posx - piecelist[i].piece_position[0])
						+ (control_puz_posy - piecelist[i].piece_position[1])*(control_puz_posy - piecelist[i].piece_position[1]);
					if (distance >= 2.0 * 2.0 && distance <= 3.0 * 3.0)
					{
						control_puz_rotate_on = true;
						control_puz_rotate_num = i;		//存储第几个球在旋转
						piecelist[i].piece_rotateon = true;
						control_puz_tran_num = 30;
						piecelist[i].piece_axis = true;
					}
				}
			}
			else{		//如果正在旋转
				if (piecelist[control_puz_rotate_num].piece_position[0] == 0 && piecelist[control_puz_rotate_num].piece_position[1] == 0)
				{				//如果在原点旋转，就按着自己中心旋转
					control_puz_sideshow = false;
					float c_sq = (control_puz_mouseposition_x_pre - control_puz_posx)*(control_puz_mouseposition_x_pre - control_puz_posx) + (control_puz_mouseposition_y_pre - control_puz_posy)*(control_puz_mouseposition_y_pre - control_puz_posy);
					float a_sq = (control_puz_mouseposition_x_pre - piecelist[control_puz_rotate_num].piece_position[0])*(control_puz_mouseposition_x_pre - piecelist[control_puz_rotate_num].piece_position[0])
						+ (control_puz_mouseposition_y_pre - piecelist[control_puz_rotate_num].piece_position[1])*(control_puz_mouseposition_y_pre - piecelist[control_puz_rotate_num].piece_position[1]);
					float b_sq = (control_puz_posx - piecelist[control_puz_rotate_num].piece_position[0])*(control_puz_posx - piecelist[control_puz_rotate_num].piece_position[0])
						+ (control_puz_posy - piecelist[control_puz_rotate_num].piece_position[1])*(control_puz_posy - piecelist[control_puz_rotate_num].piece_position[1]);

					float ab = sqrt(a_sq) * sqrt(b_sq);
					float cosc = (a_sq + b_sq - c_sq) / (2 * ab);		//余弦定理

					if (cosc >= 1.0)		//防止灵敏度过高
					{
						cosc = 0.999;
					}
					
					float angle = acosf(cosc);		//角度
					angle = angle * 60.0;

					float slope_ori = (control_puz_mouseposition_y_pre - piecelist[control_puz_rotate_num].piece_position[1]) / (control_puz_mouseposition_x_pre - piecelist[control_puz_rotate_num].piece_position[0]);
					float slope_new = (control_puz_posy - piecelist[control_puz_rotate_num].piece_position[1]) / (control_puz_posx - piecelist[control_puz_rotate_num].piece_position[0]);
					if (slope_ori > slope_new)
					{
						piecelist[control_puz_rotate_num].piece_angle -= angle;
						cout << piecelist[control_puz_rotate_num].piece_angle << endl;
					}
					else{
						piecelist[control_puz_rotate_num].piece_angle += angle;
						cout << piecelist[control_puz_rotate_num].piece_angle << endl;
					}
				}
				else{		//如果不在中心，就依世界坐标旋转
					float a1 = atan2(control_puz_posy, control_puz_posx);
					float a2 = atan2(piecelist[control_puz_rotate_num].piece_position[1], piecelist[control_puz_rotate_num].piece_position[0]);

					float pfar = sqrt((control_puz_posx * control_puz_posx) + (control_puz_posy * control_puz_posy));
					float pnear = sqrt((float)(piecelist[control_puz_rotate_num].piece_position[0] * piecelist[control_puz_rotate_num].piece_position[0])
						+ (float)(piecelist[control_puz_rotate_num].piece_position[1] * piecelist[control_puz_rotate_num].piece_position[1]));

					big_circle.piece_position[0] = pnear;
					big_circle.piece_appear = true;

					piecelist[control_puz_rotate_num].piece_position[0] = (float)(control_puz_posx * pnear) / pfar;
					piecelist[control_puz_rotate_num].piece_position[1] = (float)(control_puz_posy * pnear) / pfar;

					if (abs(a1 - a2) < 0.5)
					{
						piecelist[control_puz_rotate_num].piece_angle += 57.5 * (a1 - a2);		//更新世界旋转坐标
						cout << piecelist[control_puz_rotate_num].piece_angle << endl;
					}
				}

			}

			if (control_puz_complete == false)
			{
				//判断方块是否过近，碰撞系统在complete之后不起作用
				float coll_limit = 18;		//调整碰撞距离
				for (int i = 0; i < 12; i++)
				{
					for (int j = 0; j < 12 && j != i; j++)		//方块们两两判断距离
					{
						float dis_coll = (piecelist[i].piece_position[0] - piecelist[j].piece_position[0]) * (piecelist[i].piece_position[0] - piecelist[j].piece_position[0])
							+ (piecelist[i].piece_position[1] - piecelist[j].piece_position[1]) * (piecelist[i].piece_position[1] - piecelist[j].piece_position[1]);
						if (dis_coll < coll_limit)
						{
							//移动和正在动的方块连线方向上的一段距离
							float mouse_distance = sqrt((control_puz_mouseposition_x_pre - control_puz_posx)*(control_puz_mouseposition_x_pre - control_puz_posx)
								+ (control_puz_mouseposition_y_pre - control_puz_posy)*(control_puz_mouseposition_y_pre - control_puz_posy));
							float piece_distance = sqrt((piecelist[j].piece_position[0] - piecelist[i].piece_position[0])*(piecelist[j].piece_position[0] - piecelist[i].piece_position[0])
								+ (piecelist[j].piece_position[1] - piecelist[i].piece_position[1])*(piecelist[j].piece_position[1] - piecelist[i].piece_position[1]));

							if (i != control_puz_tran_num && i != control_puz_rotate_num)	//如果不是正在拽的，就动自己
							{
								piecelist[i].piece_position[0] += (mouse_distance * (piecelist[i].piece_position[0] - piecelist[j].piece_position[0])
									/ piece_distance);		//x轴上换算的距离
								piecelist[i].piece_position[1] += (mouse_distance * (piecelist[i].piece_position[1] - piecelist[j].piece_position[1])
									/ piece_distance);		//y轴上换算的距离

								//再判断自己和其他的距离，如果近了就动另外一个
								for (int l = 0; l < 12 && l != i; l++)
								{
									float dis_coll_2 = (piecelist[i].piece_position[0] - piecelist[l].piece_position[0]) * (piecelist[i].piece_position[0] - piecelist[l].piece_position[0])
										+ (piecelist[i].piece_position[1] - piecelist[l].piece_position[1]) * (piecelist[i].piece_position[1] - piecelist[l].piece_position[1]);
									if (dis_coll_2 < coll_limit)
									{
										piecelist[l].piece_position[0] += (mouse_distance * (piecelist[l].piece_position[0] - piecelist[i].piece_position[0])
											/ piece_distance);		//x轴上换算的距离
										piecelist[l].piece_position[1] += (mouse_distance * (piecelist[l].piece_position[1] - piecelist[i].piece_position[1])
											/ piece_distance);		//y轴上换算的距离
									}
								}
							}
							else
							{		//如果是正在拽的这个，就动另外一个
								float mouse_distance = sqrt((control_puz_mouseposition_x_pre - control_puz_posx)*(control_puz_mouseposition_x_pre - control_puz_posx)
									+ (control_puz_mouseposition_y_pre - control_puz_posy)*(control_puz_mouseposition_y_pre - control_puz_posy));
								float piece_distance = sqrt((piecelist[j].piece_position[0] - piecelist[i].piece_position[0])*(piecelist[j].piece_position[0] - piecelist[i].piece_position[0])
									+ (piecelist[j].piece_position[1] - piecelist[i].piece_position[1])*(piecelist[j].piece_position[1] - piecelist[i].piece_position[1]));

								piecelist[j].piece_position[0] += (mouse_distance * (piecelist[j].piece_position[0] - piecelist[i].piece_position[0])
									/ piece_distance);		//x轴上换算的距离
								piecelist[j].piece_position[1] += (mouse_distance * (piecelist[j].piece_position[1] - piecelist[i].piece_position[1])
									/ piece_distance);		//y轴上换算的距离

								//再判断距离，如果近了就动另外一个
								for (int m = 0; m < 12 && m != j && m != i; m++)
								{
									float dis_coll_2 = (piecelist[m].piece_position[0] - piecelist[j].piece_position[0]) * (piecelist[m].piece_position[0] - piecelist[j].piece_position[0])
										+ (piecelist[m].piece_position[1] - piecelist[j].piece_position[1]) * (piecelist[m].piece_position[1] - piecelist[j].piece_position[1]);
									if (dis_coll_2 < coll_limit)
									{
										piecelist[m].piece_position[0] += (mouse_distance * (piecelist[m].piece_position[0] - piecelist[j].piece_position[0])
											/ piece_distance);		//x轴上换算的距离
										piecelist[m].piece_position[1] += (mouse_distance * (piecelist[m].piece_position[1] - piecelist[j].piece_position[1])
											/ piece_distance);		//y轴上换算的距离
									}
								}
							}
						}
					}
				}
			}
			
		}
	}
	
	control_puz_mouseposition_x_pre = control_puz_posx;
	control_puz_mouseposition_y_pre = control_puz_posy;
}

