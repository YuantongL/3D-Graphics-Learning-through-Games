#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <GL/glut.h>
#include <GL/glaux.h>
#include <math.h>
#include "tu_control_puz.h"
#include "piece.h"
#include "word.h"
#pragma comment(lib, "glaux")	

using namespace std;

bool tu_control_puz_complete = false;		//拼图有没有完成，false=没有
bool tu_control_puz_coordinates = false;
int tu_control_puz_stage = 1;

int tu_menu_blockon;

float tu_piece_position[3];

float tu_piece_l1[12][3] = { { -4.5, 4.5, 0.0 }, { -12.0, -5.0, 0.0 }, { 4.5, 4.5, 0.0 }, { 9.0, 4.5, 0.0 }, { 4.5, 9.0, 0.0 }, { -0.5, 0.0, 0.0 },
{ 4.5, 0.0, 0.0 }, { 9.0, 0.0, 0.0 }, { -4.5, -4.5, 0.0 }, { 0.0, -4.5, 0.0 }, { 4.5, -4.5, 0.0 }, { 15.4, -6.0, 0.0 } };

float tu_piece_l2[12][3] = { { 0.0, 2.5, 0.0 }, { 4.5, 2.5, 0.0 }, { 9.0, 2.5, 0.0 }, { 13.5, 2.5, 0.0 }, { 0.0, -2.5, 0.0 }, { 4.5, -2.5, 0.0 },
{ 9.0, -2.5, 0.0 }, { 13.5, -2.5, 0.0 }, { -8.0, 0.5, 0.0 }, { 4.5, -7.0, 0.0 }, { 9.0, -7.0, 0.0 }, { -14.0, -7.0, 0.0 } };

float tu_piece_l3[12][3] = { { 7.0, 12.0, 0.0 }, { 11.5, 12.0, 0.0 }, { 16.0, 12.0, 0.0 }, { 20.5, 12.0, 0.0 }, { 7.0, 7.5, 0.0 }, { 11.5, 7.5, 0.0 },
{ 16.0, 7.5, 0.0 }, { 20.5, 7.5, 0.0 }, { 0.0, 0.0, 0.0 }, { 11.5, 3.0, 0.0 }, { 16.0, 3.0, 0.0 }, { 20.5, 3.0, 0.0 } };

float tu_piece_angle[12];
float tu_piece_size[3] = { 0.0, 0.0, 0.0 };

int tu_piece_color[12];

//--------------------------12块拼图-----------------------------------------
piece tu_piecelist[12] = {
	piece(0, tu_piece_l1[0], tu_piece_size, tu_piece_angle[0], tu_piece_color[0], 191, true, false, false),
	piece(0, tu_piece_l1[1], tu_piece_size, tu_piece_angle[1], tu_piece_color[1], 191, true, false, false),
	piece(0, tu_piece_l1[2], tu_piece_size, tu_piece_angle[2], tu_piece_color[2], 191, true, false, false),
	piece(0, tu_piece_l1[3], tu_piece_size, tu_piece_angle[3], tu_piece_color[3], 191, true, false, false),
	piece(0, tu_piece_l1[4], tu_piece_size, tu_piece_angle[4], tu_piece_color[4], 191, true, false, false),
	piece(0, tu_piece_l1[5], tu_piece_size, tu_piece_angle[5], tu_piece_color[5], 191, true, false, false),
	piece(0, tu_piece_l1[6], tu_piece_size, tu_piece_angle[6], tu_piece_color[6], 191, true, false, false),
	piece(0, tu_piece_l1[7], tu_piece_size, tu_piece_angle[7], tu_piece_color[7], 191, true, false, false),
	piece(0, tu_piece_l1[8], tu_piece_size, tu_piece_angle[8], tu_piece_color[8], 191, true, false, false),
	piece(0, tu_piece_l1[9], tu_piece_size, tu_piece_angle[9], tu_piece_color[9], 191, true, false, false),
	piece(0, tu_piece_l1[10], tu_piece_size, tu_piece_angle[10], tu_piece_color[10], 191, true, false, false),
	piece(0, tu_piece_l1[11], tu_piece_size, tu_piece_angle[11], tu_piece_color[11], 191, true, false, false),
};

float tu_big_circle_position[3];

piece tu_big_circle(1, tu_big_circle_position, tu_piece_size, 0.0, 0, 0, false, false, false);


//-------------------------------------word----------------------------------------------------

char *tu_line1_cont = "Gallery";
char *tu_line1_font = "Consolas";
float tu_line1_pos[3] = { -15.0, 13.0, 3.0 };
int tu_line1_size = 32;
float tu_line1_color[4] = { 1.0, 1.0, 1.0, 1.0 };

word tu_line1(tu_line1_pos, true, tu_line1_size, tu_line1_color, tu_line1_cont, tu_line1_font);


//----------------------------------------buttons--------------------------------------------------------------
float tu_control_puz_mouse_pos[3] = { 0.0, 0.0, 0.2 };			//mouse
float tu_control_puz_mouse_size[3] = { 0.7, 0.7, 0.0 };
piece tu_control_puz_mouse(2, tu_control_puz_mouse_pos, tu_control_puz_mouse_size, 0.0, 123, 0, true, false, false);

float tu_control_puz_stage1_pos[3] = { 25.0, 10.4, 0.1 };		//stage1
float tu_control_puz_stage_size[3] = { 5.0, 5.0, 0.0 };
piece tu_control_puz_stage1(2, tu_control_puz_stage1_pos, tu_control_puz_stage_size, 0.0, 192, 0, true, false, false);

float tu_control_puz_stage2_pos[3] = { 25.0, 5.2, 0.1 };		//stage2
piece tu_control_puz_stage2(2, tu_control_puz_stage2_pos, tu_control_puz_stage_size, 0.0, 187, 0, true, false, false);

float tu_control_puz_stage3_pos[3] = { 25.0, -0.0, 0.1 };			//stage3
piece tu_control_puz_stage3(2, tu_control_puz_stage3_pos, tu_control_puz_stage_size, 0.0, 188, 0, true, false, false);

float tu_control_puz_stage4_pos[3] = { 25.0, -5.2, 0.1 };		//stage4
piece tu_control_puz_stage4(2, tu_control_puz_stage4_pos, tu_control_puz_stage_size, 0.0, 189, 0, true, false, false);

float tu_control_puz_stage5_pos[3] = { 25.0, -10.4, 0.1 };		//重置
piece tu_control_puz_stage5(2, tu_control_puz_stage5_pos, tu_control_puz_stage_size, 0.0, 190, 0, true, false, false);

float tu_control_puz_tu_pos[3] = { -22.5, -2.0, 0.02 };			//提示
float tu_control_puz_tu_size[3] = { 11.5, 23.0, 0.0 };
piece tu_control_puz_tu(2, tu_control_puz_tu_pos, tu_control_puz_tu_size, 0.0, 197, 0, true, false, false);

float tu_control_puz_home_pos[3] = { -24.0, 12.0, 0.1 };			//home
float tu_control_puz_home_size[3] = { 2.0, 2.0, 0.0 };
piece tu_control_puz_home(2, tu_control_puz_home_pos, tu_control_puz_home_size, 0.0, 124, 0, true, false, false);

//------------------------------------------------------------------------------------------------
void tu_control_puz::tu_control_puz_randblock()
{
	if (tu_control_puz_stage == 4)
	{
		float tu_control_puz_distance[12];
		float tu_control_puz_min_distance = 100;
		srand((int)time(0));
		for (int i = 0; i < 12; i++)
		{
			do
			{
				tu_control_puz_min_distance = 100;
				tu_piecelist[i].piece_position[0] = (float)(-1600 + rand() % 3200) / 100;				//随机取位置
				tu_piecelist[i].piece_position[1] = (float)(-900 + rand() % 1800) / 100;

				for (int j = 0; j < 12; j++)		//与每个块的距离计成数组，其中第j=i块一定是0
				{
					tu_control_puz_distance[j] = (tu_piecelist[i].piece_position[0] - tu_piecelist[j].piece_position[0])*(tu_piecelist[i].piece_position[0] - tu_piecelist[j].piece_position[0])
						+ (tu_piecelist[i].piece_position[1] - tu_piecelist[j].piece_position[1])*(tu_piecelist[i].piece_position[1] - tu_piecelist[j].piece_position[1]);
				}

				for (int k = 0; k < 12; k++)		//让min_distance等于11个距离的最小值
				{
					if (tu_control_puz_distance[k] < tu_control_puz_min_distance && tu_control_puz_distance[k] != 0)
					{
						tu_control_puz_min_distance = tu_control_puz_distance[k];
					}
				}
			} while (tu_control_puz_min_distance < 32);			//如果距离的最小值大于32，可以进行下一个方块
		}

		for (int i = 0; i < 12; i++)		//产生12个随机角度
		{
			tu_piecelist[i].piece_angle = (float)(rand() % 360);
		}
	}

	for (int i = 0; i < 12; i++)
	{
		tu_piecelist[i].piece_color = 138 + 12 * (tu_control_puz_stage - 1) + i;
	}
}

void tu_control_puz::tu_control_puz_init()
{
	tu_control_puz_mouse.piece_scale = 1.0;
	tu_control_puz_stage1.piece_scale = 1.0;
	tu_control_puz_stage2.piece_scale = 1.0;
	tu_control_puz_stage3.piece_scale = 1.0;
	tu_control_puz_stage4.piece_scale = 1.0;
	tu_control_puz_stage5.piece_scale = 1.0;
	tu_control_puz_tu.piece_scale = 1.0;
	tu_control_puz_home.piece_scale = 1.0;

	tu_piecelist[0].piece_settexture();

	tu_control_puz_rotate_num = 30;
	tu_control_puz_tran_num = 30;

	tu_control_puz_rotate_on = false;
}

tu_control_puz::tu_control_puz()		//中间类的构建器
{

}

void tu_control_puz::tu_control_puz_idle()
{
	if (tu_control_puz_complete == true)		//拼好了将他们对齐
	{
		for (int i = 0; i < 3; i++)		//横排缩进
		{
			if (tu_piecelist[i + 1].piece_position[0] - tu_piecelist[i].piece_position[0] > 4.0)
			{
				tu_piecelist[i + 1].piece_position[0] -= 0.001;
			}
			if (tu_piecelist[i + 2].piece_position[0] - tu_piecelist[i + 1].piece_position[0] > 4.0)
			{
				tu_piecelist[i + 2].piece_position[0] -= 0.001;
			}
			if (tu_piecelist[i + 3].piece_position[0] - tu_piecelist[i + 2].piece_position[0] > 4.0)
			{
				tu_piecelist[i + 3].piece_position[0] -= 0.001;
			}
		}
		for (int i = 0; i < 4; i++)		//竖排缩进
		{
			if (tu_piecelist[i].piece_position[1] - tu_piecelist[i + 4].piece_position[1] > 4.0)
			{
				tu_piecelist[i + 4].piece_position[1] += 0.001;
			}
			if (tu_piecelist[i + 4].piece_position[1] - tu_piecelist[i + 8].piece_position[1] > 4.0)
			{
				tu_piecelist[i + 8].piece_position[1] += 0.001;
			}
		}

		for (int i = 0; i < 3; i++)		//横排对齐
		{
			if (tu_piecelist[i * 4].piece_position[1] - tu_piecelist[i * 4 + 1].piece_position[1] > 0.0)
			{
				tu_piecelist[i * 4 + 1].piece_position[1] += 0.001;
			}
			else if (tu_piecelist[i * 4].piece_position[1] - tu_piecelist[i * 4 + 1].piece_position[1] < 0.0)
			{
				tu_piecelist[i * 4 + 1].piece_position[1] -= 0.001;
			}

			if (tu_piecelist[i * 4 + 1].piece_position[1] - tu_piecelist[i * 4 + 2].piece_position[1] > 0.0)
			{
				tu_piecelist[i * 4 + 2].piece_position[1] += 0.001;
			}
			else if (tu_piecelist[i * 4 + 1].piece_position[1] - tu_piecelist[i * 4 + 2].piece_position[1] < 0.0)
			{
				tu_piecelist[i * 4 + 2].piece_position[1] -= 0.001;
			}

			if (tu_piecelist[i * 4 + 2].piece_position[1] - tu_piecelist[i * 4 + 3].piece_position[1] > 0.0)
			{
				tu_piecelist[i * 4 + 3].piece_position[1] += 0.001;
			}
			else if (tu_piecelist[i * 4 + 2].piece_position[1] - tu_piecelist[i * 4 + 3].piece_position[1] < 0.0)
			{
				tu_piecelist[i * 4 + 3].piece_position[1] -= 0.001;
			}
		}

		for (int i = 0; i < 4; i++)		//竖排对齐
		{
			if (tu_piecelist[i].piece_position[0] - tu_piecelist[i + 4].piece_position[0] > 0.0)
			{
				tu_piecelist[i + 4].piece_position[0] += 0.001;
			}
			else if (tu_piecelist[i].piece_position[0] - tu_piecelist[i + 4].piece_position[0] < 0.0)
			{
				tu_piecelist[i + 4].piece_position[0] -= 0.001;
			}

			if (tu_piecelist[i + 4].piece_position[0] - tu_piecelist[i + 8].piece_position[0] > 0.0)
			{
				tu_piecelist[i + 8].piece_position[0] += 0.001;
			}
			else if (tu_piecelist[i + 4].piece_position[0] - tu_piecelist[i + 8].piece_position[0] < 0.0)
			{
				tu_piecelist[i + 8].piece_position[0] -= 0.001;
			}
		}
	}

	switch (tu_menu_blockon)
	{
	case 0:
	{
			  tu_control_puz_stage1.piece_turn_small();
			  tu_control_puz_stage2.piece_turn_small();
			  tu_control_puz_stage3.piece_turn_small();
			  tu_control_puz_stage4.piece_turn_small();
			  tu_control_puz_stage5.piece_turn_small();
			  tu_control_puz_home.piece_turn_small();
			  break;
	}
	case 1:
	{
			  tu_control_puz_stage1.piece_turn_big();
			  tu_control_puz_stage2.piece_turn_small();
			  tu_control_puz_stage3.piece_turn_small();
			  tu_control_puz_stage4.piece_turn_small();
			  tu_control_puz_stage5.piece_turn_small();
			  tu_control_puz_home.piece_turn_small();
			  break;
	}
	case 2:
	{
			  tu_control_puz_stage1.piece_turn_small();
			  tu_control_puz_stage2.piece_turn_big();
			  tu_control_puz_stage3.piece_turn_small();
			  tu_control_puz_stage4.piece_turn_small();
			  tu_control_puz_stage5.piece_turn_small();
			  tu_control_puz_home.piece_turn_small();
			  break;
	}
	case 3:
	{
			  tu_control_puz_stage1.piece_turn_small();
			  tu_control_puz_stage2.piece_turn_small();
			  tu_control_puz_stage3.piece_turn_big();
			  tu_control_puz_stage4.piece_turn_small();
			  tu_control_puz_stage5.piece_turn_small();
			  tu_control_puz_home.piece_turn_small();
			  break;
	}
	case 4:
	{
			  tu_control_puz_stage1.piece_turn_small();
			  tu_control_puz_stage2.piece_turn_small();
			  tu_control_puz_stage3.piece_turn_small();
			  tu_control_puz_stage4.piece_turn_big();
			  tu_control_puz_stage5.piece_turn_small();
			  tu_control_puz_home.piece_turn_small();
			  break;
	}
	case 5:
	{
			  tu_control_puz_stage1.piece_turn_small();
			  tu_control_puz_stage2.piece_turn_small();
			  tu_control_puz_stage3.piece_turn_small();
			  tu_control_puz_stage4.piece_turn_small();
			  tu_control_puz_stage5.piece_turn_big();
			  tu_control_puz_home.piece_turn_small();
			  break;
	}
	case 6:
	{
			  tu_control_puz_stage1.piece_turn_small();
			  tu_control_puz_stage2.piece_turn_small();
			  tu_control_puz_stage3.piece_turn_small();
			  tu_control_puz_stage4.piece_turn_small();
			  tu_control_puz_stage5.piece_turn_small();
			  tu_control_puz_home.piece_turn_big();
			  break;
	}
	}
}

void tu_control_puz::tu_control_puz_drawall()		//画出所有的东西
{
	glPushMatrix();

	glColor3f(1.0, 1.0, 1.0);
	tu_control_puz_mouse.piece_drawself();

	glEnable(GL_TEXTURE_2D);

	tu_control_puz_stage1.piece_drawself();
	tu_control_puz_stage2.piece_drawself();
	tu_control_puz_stage3.piece_drawself();
	tu_control_puz_stage4.piece_drawself();
	tu_control_puz_stage5.piece_drawself();
	tu_control_puz_tu.piece_drawself();
	tu_control_puz_home.piece_drawself();

	for (int i = 0; i < 12; i++)
	{
		tu_piecelist[i].piece_drawself();	
	}

	glDisable(GL_TEXTURE_2D);

	tu_big_circle.piece_drawself();

	if (tu_control_puz_coordinates == true && tu_control_puz_complete == false)		//如果坐标系要显示出来的话
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
		
		if (tu_control_puz_stage > 3)
		{
			glColor3f(0.2, 0.2, 0.2);
			glBegin(GL_TRIANGLE_FAN);
			int n = 50;
			for (int i = 0; i < n; ++i)
				glVertex2f(1.0 *cos(2 * 3.14159265354 / n*i), 1.0*sin(2 * 3.14159265354 / n*i));
			glEnd();
		}
	}

	glPopMatrix();
}

void tu_control_puz::tu_control_puz_mouseevent()		//处理所有鼠标点击
{
	tu_control_puz_rotate_on = false;

	if (tu_control_puz_left_mouse_down == false)
	{
		tu_control_puz_coordinates = false;		//不移动了就不画坐标系
		for (int i = 0; i < 12; i++)
		{
			tu_piecelist[i].piece_axis = false;
		}

		if (abs(tu_piecelist[tu_control_puz_tran_num].piece_position[0]) < 1.0 && abs(tu_piecelist[tu_control_puz_tran_num].piece_position[1]) < 1.0 && tu_control_puz_stage > 1)
		{
			tu_piecelist[tu_control_puz_tran_num].piece_position[0] = 0.0;
			tu_piecelist[tu_control_puz_tran_num].piece_position[1] = 0.0;
		}

		tu_big_circle.piece_appear = false;

		//---------------------辨认拼图是否拼上------------------angle, pos------------------
		bool standard1 = true;		//先设正确，如果有一个不对了就错了
		for (int q = 0; q < 4; q++)		//判断每列是否对齐
		{
			if (tu_piecelist[q].piece_position[1] - tu_piecelist[q + 4].piece_position[1] < 0.0 || tu_piecelist[q].piece_position[1] - tu_piecelist[q + 4].piece_position[1] > 7.0)
			{
				standard1 = false;
			}
			if (tu_piecelist[q + 4].piece_position[1] - tu_piecelist[q + 8].piece_position[1] < 0.0 || tu_piecelist[q + 4].piece_position[1] - tu_piecelist[q + 8].piece_position[1] > 7.0)
			{
				standard1 = false;
			}
		}

		for (int q = 0; q < 3; q++)		//判断每行是否对齐
		{
			if (tu_piecelist[q * 4 + 1].piece_position[0] - tu_piecelist[q * 4].piece_position[0] < 0.0 || tu_piecelist[q * 4 + 1].piece_position[0] - tu_piecelist[q * 4].piece_position[0] > 7.0)
			{
				standard1 = false;
			}
			if (tu_piecelist[q * 4 + 2].piece_position[0] - tu_piecelist[q * 4 + 1].piece_position[0] < 0.0 || tu_piecelist[q * 4 + 2].piece_position[0] - tu_piecelist[q * 4 + 1].piece_position[0] > 7.0)
			{
				standard1 = false;
			}
			if (tu_piecelist[q * 4 + 3].piece_position[0] - tu_piecelist[q * 4 + 2].piece_position[0] < 0.0 || tu_piecelist[q * 4 + 3].piece_position[0] - tu_piecelist[q * 4 + 2].piece_position[0] > 7.0)
			{
				standard1 = false;
			}
		}

		int x;
		for (int i = 0; i < 12; i++)
		{
			x = (int)tu_piecelist[i].piece_angle % 360;
			if ((x > 20 && x < 340) || (x > -340 && x < -20))
			{
				standard1 = false;
			}
		}

		if (standard1 == true && tu_control_puz_complete == false)
		{
			tu_control_puz_stage5.piece_color = 196;
			for (int i = 0; i < 12; i++)
			{
				tu_piecelist[i].piece_rotateon = false;
				tu_piecelist[i].piece_mouseon = false;
			}
			tu_control_puz_complete = true;
			for (int i = 0; i < 12; i++)	//角度规正
			{
				tu_piecelist[i].piece_angle = 0.0;
				tu_piecelist[i].piece_angle2 = 0.0;
			}
		}
	}
	else if (tu_control_puz_left_mouse_down == true)
	{
		if (tu_control_puz_posx > 22.5 && tu_control_puz_posx < 27.5)
		{
			if (tu_control_puz_posy > 7.9 && tu_control_puz_posy < 12.9)	//stage1
			{
				tu_control_puz_stage1.piece_scale = 1.05;
				tu_control_puz_stage1.piece_color = 192;
				tu_control_puz_stage2.piece_color = 187;
				tu_control_puz_stage3.piece_color = 188;
				tu_control_puz_stage4.piece_color = 189;

				for (int j = 0; j < 12; j++)	//重置位置
				{
					tu_piecelist[j].piece_position[0] = tu_piece_l1[j][0];
					tu_piecelist[j].piece_position[1] = tu_piece_l1[j][1];
					tu_piecelist[j].piece_angle = 0.0;
				}
				tu_piecelist[8].piece_angle = 0;
				tu_piecelist[11].piece_angle = 0;

				tu_control_puz_stage5.piece_color = 190;
				tu_control_puz_tu.piece_color = 197;
				tu_control_puz_complete = false;
				tu_control_puz_stage = 1;
				tu_control_puz_randblock();
			}
			else if (tu_control_puz_posy > 2.7 && tu_control_puz_posy < 7.7)	//stage2
			{
				tu_control_puz_stage2.piece_scale = 1.05;
				tu_control_puz_stage1.piece_color = 186;
				tu_control_puz_stage2.piece_color = 193;
				tu_control_puz_stage3.piece_color = 188;
				tu_control_puz_stage4.piece_color = 189;

				for (int j = 0; j < 12; j++)	//重置位置
				{
					tu_piecelist[j].piece_position[0] = tu_piece_l2[j][0];
					tu_piecelist[j].piece_position[1] = tu_piece_l2[j][1];
					tu_piecelist[j].piece_angle = 0.0;
				}
				tu_piecelist[8].piece_angle = -70;
				tu_piecelist[11].piece_angle = -130;

				tu_control_puz_stage5.piece_color = 190;
				tu_control_puz_tu.piece_color = 198;
				tu_control_puz_complete = false;
				tu_control_puz_stage = 2;
				tu_control_puz_randblock();
			}
			else if (tu_control_puz_posy > -2.5 && tu_control_puz_posy < 2.5)		//stage3
			{
				tu_control_puz_stage3.piece_scale = 1.05;
				tu_control_puz_stage1.piece_color = 186;
				tu_control_puz_stage2.piece_color = 187;
				tu_control_puz_stage3.piece_color = 194;
				tu_control_puz_stage4.piece_color = 189;

				for (int j = 0; j < 12; j++)	//重置位置
				{
					tu_piecelist[j].piece_position[0] = tu_piece_l3[j][0];
					tu_piecelist[j].piece_position[1] = tu_piece_l3[j][1];
					tu_piecelist[j].piece_angle = 0.0;
				}
				tu_piecelist[8].piece_angle = 139;
				tu_piecelist[11].piece_angle = 0;

				tu_control_puz_stage5.piece_color = 190;
				tu_control_puz_tu.piece_color = 199;
				tu_control_puz_complete = false;
				tu_control_puz_stage = 3;
				tu_control_puz_randblock();
			}
			else if (tu_control_puz_posy > -7.7 && tu_control_puz_posy < -2.7)		//stage4
			{
				tu_control_puz_stage4.piece_scale = 1.05;
				tu_control_puz_stage1.piece_color = 186;
				tu_control_puz_stage2.piece_color = 187;
				tu_control_puz_stage3.piece_color = 188;
				tu_control_puz_stage4.piece_color = 195;
				tu_control_puz_complete = false;
				tu_control_puz_stage5.piece_color = 190;
				tu_control_puz_tu.piece_color = 200;
				tu_control_puz_stage = 4;
				tu_control_puz_randblock();
			}
			else if (tu_control_puz_posy > -12.9 && tu_control_puz_posy < 7.9)	//重置
			{
				tu_control_puz_stage5.piece_scale = 1.05;
				tu_control_puz_complete = false;
				tu_control_puz_stage5.piece_color = 190;
				if (tu_control_puz_stage == 1)
				{
					for (int j = 0; j < 12; j++)	//重置位置
					{
						tu_piecelist[j].piece_position[0] = tu_piece_l1[j][0];
						tu_piecelist[j].piece_position[1] = tu_piece_l1[j][1];
						tu_piecelist[j].piece_angle = 0.0;
					}
				}
				else if (tu_control_puz_stage == 2)
				{
					for (int j = 0; j < 12; j++)	//重置位置
					{
						tu_piecelist[j].piece_position[0] = tu_piece_l2[j][0];
						tu_piecelist[j].piece_position[1] = tu_piece_l2[j][1];
						tu_piecelist[j].piece_angle = 0.0;
					}
					tu_piecelist[8].piece_angle = -70;
					tu_piecelist[11].piece_angle = -130;
				}
				else if (tu_control_puz_stage == 3)
				{
					for (int j = 0; j < 12; j++)	//重置位置
					{
						tu_piecelist[j].piece_position[0] = tu_piece_l3[j][0];
						tu_piecelist[j].piece_position[1] = tu_piece_l3[j][1];
						tu_piecelist[j].piece_angle = 0.0;
					}
					tu_piecelist[8].piece_angle = 139;
				}
				else if (tu_control_puz_stage == 4)
				{
					tu_control_puz_randblock();
				}
			}
		}

		if (tu_control_puz_posy > 11.0 && tu_control_puz_posy < 13.0 && tu_control_puz_posx > -25.0 && tu_control_puz_posx < -23.0)
		{
			tu_control_puz_complete = false;
			tu_control_puz_gameon = 0;		//返回主界面
		}
	}
}

void tu_control_puz::tu_control_puz_mouseevent_passive()		//处理鼠标滑动
{
	tu_control_puz_rotate_on = false;
	tu_control_puz_posx = tu_control_puz_mouseposition_x * 64.0 / 1366.0 - 32.0;
	tu_control_puz_posy = 18.0 - tu_control_puz_mouseposition_y * 36.0 / 768.0;

	tu_control_puz_mouse.piece_position[0] = tu_control_puz_posx;
	tu_control_puz_mouse.piece_position[1] = tu_control_puz_posy;

	if (tu_control_puz_posx > 22.5 && tu_control_puz_posx < 27.5 && tu_control_puz_posy > 7.9 && tu_control_puz_posy < 12.9)	//stage1
	{
		tu_menu_blockon = 1;
	}
	else if (tu_control_puz_posx > 22.5 && tu_control_puz_posx < 27.5 && tu_control_puz_posy > 2.7 && tu_control_puz_posy < 7.7)	//stage2
	{
		tu_menu_blockon = 2;
	}
	else if (tu_control_puz_posx > 22.5 && tu_control_puz_posx < 27.5 && tu_control_puz_posy > -2.5 && tu_control_puz_posy < 2.5)		//stage3
	{
		tu_menu_blockon = 3;
	}
	else if (tu_control_puz_posx > 22.5 && tu_control_puz_posx < 27.5 && tu_control_puz_posy > -7.7 && tu_control_puz_posy < -2.7)		//stage4
	{
		tu_menu_blockon = 4;
	}
	else if (tu_control_puz_posx > 22.5 && tu_control_puz_posx < 27.5 && tu_control_puz_posy > -12.9 && tu_control_puz_posy < -7.9)	//重置
	{
		tu_menu_blockon = 5;
	}
	else if (tu_control_puz_posy > 11.0 && tu_control_puz_posy < 13.0 && tu_control_puz_posx > -25.0 && tu_control_puz_posx < -23.0)	//home
	{
		tu_menu_blockon = 6;
	}
	else{
		tu_menu_blockon = 0;
	}

	if (tu_control_puz_complete == false)
	{
		float distance;
		for (int i = 0; i < 12; i++)		//鼠标接近圆心，显示叉代表可以位移
		{
			distance = (tu_control_puz_posx - tu_piecelist[i].piece_position[0])*(tu_control_puz_posx - tu_piecelist[i].piece_position[0]) + (tu_control_puz_posy - tu_piecelist[i].piece_position[1])*(tu_control_puz_posy - tu_piecelist[i].piece_position[1]);
			if (distance <= 1.3 * 1.3)
			{
				tu_piecelist[i].piece_mouseon = true;
			}
			else{
				tu_piecelist[i].piece_mouseon = false;
			}
		}

		if (tu_control_puz_stage > 1)
		{
			for (int i = 0; i < 12; i++)		//鼠标接近定点，显示圆圈表示可以转动或拉伸
			{
				distance = (tu_control_puz_posx - tu_piecelist[i].piece_position[0])*(tu_control_puz_posx - tu_piecelist[i].piece_position[0]) + (tu_control_puz_posy - tu_piecelist[i].piece_position[1])*(tu_control_puz_posy - tu_piecelist[i].piece_position[1]);
				if (distance >= 2.0 * 2.0 && distance <= 3.0 * 3.0)
				{
					tu_piecelist[i].piece_rotateon = true;
				}
				else{
					tu_piecelist[i].piece_rotateon = false;
				}
			}
		}
		
	}

	tu_control_puz_mouseposition_x_pre = tu_control_puz_posx;
	tu_control_puz_mouseposition_y_pre = tu_control_puz_posy;
}

void tu_control_puz::tu_control_puz_mouseevent_motion()			//处理鼠标拖拽
{
	tu_control_puz_posx = tu_control_puz_mouseposition_x * 64.0 / 1366.0 - 32.0;
	tu_control_puz_posy = 18.0 - tu_control_puz_mouseposition_y * 36.0 / 768.0;

	tu_control_puz_mouse.piece_position[0] = tu_control_puz_posx;
	tu_control_puz_mouse.piece_position[1] = tu_control_puz_posy;

	if (tu_control_puz_complete == false)
	{
		float distance;

		tu_control_puz_coordinates = true;		//移动的时候画坐标系

		for (int i = 0; i < 12; i++)		//确认哪个在动
		{
			distance = (tu_control_puz_posx - tu_piecelist[i].piece_position[0])*(tu_control_puz_posx - tu_piecelist[i].piece_position[0])
				+ (tu_control_puz_posy - tu_piecelist[i].piece_position[1])*(tu_control_puz_posy - tu_piecelist[i].piece_position[1]);
			if (distance <= 1.8 * 1.8)
			{
				tu_control_puz_tran_num = i;
			}
		}

		if (tu_control_puz_left_mouse_down == true)
		{
			if (tu_control_puz_rotate_on == false)			//如果不在转圈进行中
			{
				for (int i = 0; i < 12; i++)		//退拽位移
				{
					distance = (tu_control_puz_posx - tu_piecelist[i].piece_position[0])*(tu_control_puz_posx - tu_piecelist[i].piece_position[0]) 
						+ (tu_control_puz_posy - tu_piecelist[i].piece_position[1])*(tu_control_puz_posy - tu_piecelist[i].piece_position[1]);
					if (distance <= 1.8 * 1.8)
					{
						tu_piecelist[i].piece_position[0] += (tu_control_puz_posx - tu_control_puz_mouseposition_x_pre);
						tu_piecelist[i].piece_position[1] += (tu_control_puz_posy - tu_control_puz_mouseposition_y_pre);
						tu_control_puz_tran_num = i;
						tu_control_puz_rotate_num = 30;	//防止后面碰撞不算
						tu_piecelist[i].piece_axis = true;
					}
				}

				if (tu_control_puz_stage > 1)		//如果不是第一stage就标记旋转
				{
					for (int i = 0; i < 12; i++)		//拖拽旋转
					{
						distance = (tu_control_puz_posx - tu_piecelist[i].piece_position[0])*(tu_control_puz_posx - tu_piecelist[i].piece_position[0])
							+ (tu_control_puz_posy - tu_piecelist[i].piece_position[1])*(tu_control_puz_posy - tu_piecelist[i].piece_position[1]);
						if (distance >= 2.0 * 2.0 && distance <= 3.0 * 3.0)
						{
							tu_control_puz_rotate_on = true;
							tu_control_puz_rotate_num = i;		//存储第几个球在旋转
							tu_piecelist[i].piece_rotateon = true;
							tu_control_puz_tran_num = 30;
							tu_piecelist[i].piece_axis = true;
						}
					}
				}
			}
			else{
				if (tu_piecelist[tu_control_puz_rotate_num].piece_position[0] == 0 && tu_piecelist[tu_control_puz_rotate_num].piece_position[1] == 0)
				{				//如果在原点旋转，就按着自己中心旋转
					float c_sq = (tu_control_puz_mouseposition_x_pre - tu_control_puz_posx)*(tu_control_puz_mouseposition_x_pre - tu_control_puz_posx)
						+ (tu_control_puz_mouseposition_y_pre - tu_control_puz_posy)*(tu_control_puz_mouseposition_y_pre - tu_control_puz_posy);
					float a_sq = (tu_control_puz_mouseposition_x_pre - tu_piecelist[tu_control_puz_rotate_num].piece_position[0])*(tu_control_puz_mouseposition_x_pre - tu_piecelist[tu_control_puz_rotate_num].piece_position[0])
						+ (tu_control_puz_mouseposition_y_pre - tu_piecelist[tu_control_puz_rotate_num].piece_position[1])*(tu_control_puz_mouseposition_y_pre - tu_piecelist[tu_control_puz_rotate_num].piece_position[1]);
					float b_sq = (tu_control_puz_posx - tu_piecelist[tu_control_puz_rotate_num].piece_position[0])*(tu_control_puz_posx - tu_piecelist[tu_control_puz_rotate_num].piece_position[0])
						+ (tu_control_puz_posy - tu_piecelist[tu_control_puz_rotate_num].piece_position[1])*(tu_control_puz_posy - tu_piecelist[tu_control_puz_rotate_num].piece_position[1]);

					float ab = sqrt(a_sq) * sqrt(b_sq);
					float cosc = (a_sq + b_sq - c_sq) / (2 * ab);		//余弦定理

					if (cosc >= 1.0)		//防止灵敏度过高
					{
						cosc = 0.999;
					}

					float angle = acosf(cosc);		//角度
					angle = angle * 60.0;

					float slope_ori = (tu_control_puz_mouseposition_y_pre - tu_piecelist[tu_control_puz_rotate_num].piece_position[1]) / (tu_control_puz_mouseposition_x_pre - tu_piecelist[tu_control_puz_rotate_num].piece_position[0]);
					float slope_new = (tu_control_puz_posy - tu_piecelist[tu_control_puz_rotate_num].piece_position[1]) / (tu_control_puz_posx - tu_piecelist[tu_control_puz_rotate_num].piece_position[0]);
					if (slope_ori > slope_new)
					{
						tu_piecelist[tu_control_puz_rotate_num].piece_angle -= angle;
						cout << tu_piecelist[tu_control_puz_rotate_num].piece_angle << endl;
					}
					else{
						tu_piecelist[tu_control_puz_rotate_num].piece_angle += angle;
						cout << tu_piecelist[tu_control_puz_rotate_num].piece_angle << endl;
					}
				}
				else{		//如果不在中心，就依世界坐标旋转
					float a1 = atan2(tu_control_puz_posy, tu_control_puz_posx);
					float a2 = atan2(tu_piecelist[tu_control_puz_rotate_num].piece_position[1], tu_piecelist[tu_control_puz_rotate_num].piece_position[0]);

					float pfar = sqrt((tu_control_puz_posx * tu_control_puz_posx) + (tu_control_puz_posy * tu_control_puz_posy));
					float pnear = sqrt((float)(tu_piecelist[tu_control_puz_rotate_num].piece_position[0] * tu_piecelist[tu_control_puz_rotate_num].piece_position[0])
						+ (float)(tu_piecelist[tu_control_puz_rotate_num].piece_position[1] * tu_piecelist[tu_control_puz_rotate_num].piece_position[1]));

					tu_big_circle.piece_position[0] = pnear;
					tu_big_circle.piece_appear = true;

					tu_piecelist[tu_control_puz_rotate_num].piece_position[0] = (float)(tu_control_puz_posx * pnear) / pfar;
					tu_piecelist[tu_control_puz_rotate_num].piece_position[1] = (float)(tu_control_puz_posy * pnear) / pfar;

					if (abs(a1 - a2) < 0.5)
					{
						tu_piecelist[tu_control_puz_rotate_num].piece_angle += 57.5 * (a1 - a2);		//更新世界旋转坐标
						cout << tu_piecelist[tu_control_puz_rotate_num].piece_angle << endl;
					}
				}
			}

			if (tu_control_puz_complete == false)	//只有在第四关的时候开启碰撞
			{
				//判断方块是否过近，碰撞系统在complete之后不起作用
				float coll_limit = 18;		//调整碰撞距离
				for (int i = 0; i < 12; i++)
				{
					for (int j = 0; j < 12 && j != i; j++)		//方块们两两判断距离
					{
						float dis_coll = (tu_piecelist[i].piece_position[0] - tu_piecelist[j].piece_position[0]) * (tu_piecelist[i].piece_position[0] - tu_piecelist[j].piece_position[0])
							+ (tu_piecelist[i].piece_position[1] - tu_piecelist[j].piece_position[1]) * (tu_piecelist[i].piece_position[1] - tu_piecelist[j].piece_position[1]);
						if (dis_coll < coll_limit)
						{
							//移动和正在动的方块连线方向上的一段距离
							float mouse_distance = sqrt((tu_control_puz_mouseposition_x_pre - tu_control_puz_posx)*(tu_control_puz_mouseposition_x_pre - tu_control_puz_posx)
								+ (tu_control_puz_mouseposition_y_pre - tu_control_puz_posy)*(tu_control_puz_mouseposition_y_pre - tu_control_puz_posy));
							float piece_distance = sqrt((tu_piecelist[j].piece_position[0] - tu_piecelist[i].piece_position[0])*(tu_piecelist[j].piece_position[0] - tu_piecelist[i].piece_position[0])
								+ (tu_piecelist[j].piece_position[1] - tu_piecelist[i].piece_position[1])*(tu_piecelist[j].piece_position[1] - tu_piecelist[i].piece_position[1]));

							if (i != tu_control_puz_tran_num && i != tu_control_puz_rotate_num)	//如果不是正在拽的，就动自己
							{
								tu_piecelist[i].piece_position[0] += (mouse_distance * (tu_piecelist[i].piece_position[0] - tu_piecelist[j].piece_position[0])
									/ piece_distance);		//x轴上换算的距离
								tu_piecelist[i].piece_position[1] += (mouse_distance * (tu_piecelist[i].piece_position[1] - tu_piecelist[j].piece_position[1])
									/ piece_distance);		//y轴上换算的距离

								//再判断自己和其他的距离，如果近了就动另外一个
								for (int l = 0; l < 12 && l != i; l++)
								{
									float dis_coll_2 = (tu_piecelist[i].piece_position[0] - tu_piecelist[l].piece_position[0]) * (tu_piecelist[i].piece_position[0] - tu_piecelist[l].piece_position[0])
										+ (tu_piecelist[i].piece_position[1] - tu_piecelist[l].piece_position[1]) * (tu_piecelist[i].piece_position[1] - tu_piecelist[l].piece_position[1]);
									if (dis_coll_2 < coll_limit)
									{
										tu_piecelist[l].piece_position[0] += (mouse_distance * (tu_piecelist[l].piece_position[0] - tu_piecelist[i].piece_position[0])
											/ piece_distance);		//x轴上换算的距离
										tu_piecelist[l].piece_position[1] += (mouse_distance * (tu_piecelist[l].piece_position[1] - tu_piecelist[i].piece_position[1])
											/ piece_distance);		//y轴上换算的距离
									}
								}
							}
							else
							{		//如果是正在拽的这个，就动另外一个
								float mouse_distance = sqrt((tu_control_puz_mouseposition_x_pre - tu_control_puz_posx)*(tu_control_puz_mouseposition_x_pre - tu_control_puz_posx)
									+ (tu_control_puz_mouseposition_y_pre - tu_control_puz_posy)*(tu_control_puz_mouseposition_y_pre - tu_control_puz_posy));
								float piece_distance = sqrt((tu_piecelist[j].piece_position[0] - tu_piecelist[i].piece_position[0])*(tu_piecelist[j].piece_position[0] - tu_piecelist[i].piece_position[0])
									+ (tu_piecelist[j].piece_position[1] - tu_piecelist[i].piece_position[1])*(tu_piecelist[j].piece_position[1] - tu_piecelist[i].piece_position[1]));

								tu_piecelist[j].piece_position[0] += (mouse_distance * (tu_piecelist[j].piece_position[0] - tu_piecelist[i].piece_position[0])
									/ piece_distance);		//x轴上换算的距离
								tu_piecelist[j].piece_position[1] += (mouse_distance * (tu_piecelist[j].piece_position[1] - tu_piecelist[i].piece_position[1])
									/ piece_distance);		//y轴上换算的距离

								//再判断距离，如果近了就动另外一个
								for (int m = 0; m < 12 && m != j && m != i; m++)
								{
									float dis_coll_2 = (tu_piecelist[m].piece_position[0] - tu_piecelist[j].piece_position[0]) * (tu_piecelist[m].piece_position[0] - tu_piecelist[j].piece_position[0])
										+ (tu_piecelist[m].piece_position[1] - tu_piecelist[j].piece_position[1]) * (tu_piecelist[m].piece_position[1] - tu_piecelist[j].piece_position[1]);
									if (dis_coll_2 < coll_limit)
									{
										tu_piecelist[m].piece_position[0] += (mouse_distance * (tu_piecelist[m].piece_position[0] - tu_piecelist[j].piece_position[0])
											/ piece_distance);		//x轴上换算的距离
										tu_piecelist[m].piece_position[1] += (mouse_distance * (tu_piecelist[m].piece_position[1] - tu_piecelist[j].piece_position[1])
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

	tu_control_puz_mouseposition_x_pre = tu_control_puz_posx;
	tu_control_puz_mouseposition_y_pre = tu_control_puz_posy;
}

