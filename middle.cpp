#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <GL/glut.h>
#include <GL/glaux.h>
#include "middle.h"
#include "facilities.h"
#include "control_ball.h"
#include "control_puz.h"
#include "endless_control_ball.h"
#include "tu_control_puz.h"
#include "word.h"

#pragma comment(lib, "glaux")	

using namespace std;

//--------------------------blocks------------------------------------
int page = 0;
int page_ver = 1;
float page_t = 0.0;		//菜单初始位置
float page_u = 0.0;

int blo_on = 0;
float blo_11_pos[3] = { -6.0, -3.0, 1.0 };
float blo_11_size[3] = { 7.85, 2.85, 9.0 };
float blo_12_pos[3] = { 8.0, 1.5, 1.0 };
float blo_12_size[3] = { 3.85, 5.85, 9.0 };
float blo_13_pos[3] = { -2.0, 1.5, 1.0 };
float blo_13_size[3] = { 15.85, 5.85, 9.0 };
float blo_14_pos[3] = { 2.0, -3.0, 1.0 };
float blo_14_size[3] = { 7.85, 2.85, 9.0 };
float blo_15_pos[3] = { 8.0, -3.0, 1.0 };
float blo_15_size[3] = { 3.85, 2.85, 9.0 };

facilities blolist_1[5] = {							//第一页的5个block
	facilities(1, 1, blo_11_pos, blo_11_size, true),
	facilities(1, 2, blo_12_pos, blo_12_size, true),
	facilities(1, 3, blo_13_pos, blo_13_size, true),
	facilities(1, 4, blo_14_pos, blo_14_size, true),
	facilities(1, 5, blo_15_pos, blo_15_size, true)
};

float blo_21_pos[3] = { -4.0, 0.0, 1.0 };
float blo_21_size[3] = { 11.85, 8.85, 9.0 };
float blo_22_pos[3] = { 6.0, 3.0, 1.0 };
float blo_22_size[3] = { 7.85, 2.85, 9.0 };
float blo_23_pos[3] = { 6.0, 0.0, 1.0 };
float blo_23_size[3] = { 7.85, 2.85, 9.0 };
float blo_24_pos[3] = { 6.0, -3.0, 1.0 };
float blo_24_size[3] = { 7.85, 2.85, 9.0 };
facilities blolist_2[4] = {								//第二页的4个block
	facilities(1, 6, blo_21_pos, blo_21_size, true),
	facilities(1, 7, blo_22_pos, blo_22_size, true),
	facilities(1, 8, blo_23_pos, blo_23_size, true),
	facilities(1, 9, blo_24_pos, blo_24_size, true),
};

float blo_31_pos[3] = { -5.75, 0.0, 1.0 };
float blo_31_size[3] = { 8.35, 8.85, 9.0 };
float blo_32_pos[3] = { 2.75, 0.0, 1.0 };
float blo_32_size[3] = { 8.35, 8.85, 9.0 };
float blo_33_pos[3] = { 8.5, 3.0, 1.0 };
float blo_33_size[3] = { 2.85, 2.85, 9.0 };
float blo_34_pos[3] = { 8.5, 0.0, 1.0 };
float blo_34_size[3] = { 2.85, 2.85, 9.0 };
float blo_35_pos[3] = { 8.5, -3.0, 1.0 };
float blo_35_size[3] = { 2.85, 2.85, 9.0 };

facilities blolist_3[5] = {							//第3页的5个block
	facilities(1, 10, blo_31_pos, blo_31_size, true),
	facilities(1, 11, blo_32_pos, blo_32_size, true),
	facilities(1, 12, blo_33_pos, blo_33_size, true),
	facilities(1, 13, blo_34_pos, blo_34_size, true),
	facilities(1, 14, blo_35_pos, blo_35_size, true)
};

bool back_bigsmall = true; //big

float back_pos[3] = { 48.0, 0.0, 0.0 };					//背景图片
float back_size[3] = { 128.0, 18.0, 0.0 };
facilities background(1, 0, back_pos, back_size, true);

float start_pos[3] = { 0.0, -3.0, 0.0 };					
float start_size[3] = { 4.0, 1.0, 0.0 };
facilities start(1, 15, start_pos, start_size, true);

float doc_pos[3] = { 0.0, -18.0, 0.0 };
float doc_size[3] = { 32.0, 18.0, 0.0 };
facilities doc(1, 19, doc_pos, doc_size, false);

float staff_pos[3] = { 0.0, -54.0, -0.1};	//staff
float staff_size[3] = { 32.0, 90.0, 0.0 };
facilities staff(1, 26, staff_pos, staff_size, false);

float cross_pos[3] = { 14.0, -11.0, 1.0 };
float cross_size[3] = { 1.0, 1.0, 0.0 };
facilities cross(2, 17, cross_pos, cross_size, false);

float out_pos[3] = { 14.0, 7.0, 1.0 };
facilities out(2, 28, out_pos, cross_size, false);	//脱出程序

float tuli_pos[3] = { 0.0, 0.0, 2.0 };
float tuli_size[3] = { 32.0, 18.0, 0.0 };
facilities tuli(2, 29, tuli_pos, tuli_size, true);	//图例


//=========================middles==================================================

tu_control_puz *tu_puzgame = new tu_control_puz();
control_ball *ballgame = new control_ball();
control_puz *puzgame = new control_puz();
endless_control_ball *endless_ballgame = new endless_control_ball();

//==================================================================================
middle::middle()
{
	gameon = 0;
	gamereallyon = 0;
}

void middle::init()
{
	blolist_1[0].settexture();
	(*tu_puzgame).tu_control_puz_init();
	(*ballgame).control_ball_init();
	(*endless_ballgame).endless_control_ball_init();
	(*puzgame).control_puz_init();
}

void middle::drawall()
{	
	switch (gamereallyon) {
	case 0:{				//如果是在UI界面运行
			   glPushMatrix();
			   
			   glTranslatef(0.0, page_u, 0.0);
			   out.drawself();
			   if (page != 0)
			   {
				   glDisable(GL_TEXTURE_2D);
				   if (page == 1)
				   {
					   glPushMatrix();
					   glTranslatef(-1.1, -6.0, 0.0);
					   glColor3f(1.0, 1.0, 1.0);
					   glBegin(GL_POLYGON);
					   glNormal3f(0.0, 0.0, 1.0);	
					   glVertex3f(-0.4, -0.1, 1.0);
					   glVertex3f(0.4, -0.1, 1.0);
					   glVertex3f(0.4, 0.1, 1.0);
					   glVertex3f(-0.4, 0.1, 1.0);
					   glEnd();
					   glPopMatrix();
				   }
				   else{
					   glPushMatrix();
					   glTranslatef(-1.1, -6.0, 0.0);
					   glColor3f(0.2, 0.2, 0.2);
					   glBegin(GL_POLYGON);
					   glNormal3f(0.0, 0.0, 1.0);	
					   glVertex3f(-0.4, -0.1, 1.0);
					   glVertex3f(0.4, -0.1, 1.0);
					   glVertex3f(0.4, 0.1, 1.0);
					   glVertex3f(-0.4, 0.1, 1.0);
					   glEnd();
					   glPopMatrix();
				   }

				   if (page == 2)
				   {
					   glPushMatrix();
					   glTranslatef(-0.0, -6.0, 0.0);
					   glColor3f(1.0, 1.0, 1.0);
					   glBegin(GL_POLYGON);
					   glNormal3f(0.0, 0.0, 1.0);	
					   glVertex3f(-0.4, -0.1, 1.0);
					   glVertex3f(0.4, -0.1, 1.0);
					   glVertex3f(0.4, 0.1, 1.0);
					   glVertex3f(-0.4, 0.1, 1.0);
					   glEnd();
					   glPopMatrix();
				   }
				   else{
					   glPushMatrix();
					   glTranslatef(-0.0, -6.0, 0.0);
					   glColor3f(0.2, 0.2, 0.2);
					   glBegin(GL_POLYGON);
					   glNormal3f(0.0, 0.0, 1.0);	
					   glVertex3f(-0.4, -0.1, 1.0);
					   glVertex3f(0.4, -0.1, 1.0);
					   glVertex3f(0.4, 0.1, 1.0);
					   glVertex3f(-0.4, 0.1, 1.0);
					   glEnd();
					   glPopMatrix();
				   }

				   if (page == 3)
				   {
					   glPushMatrix();
					   glTranslatef(1.1, -6.0, 0.0);
					   glColor3f(1.0, 1.0, 1.0);
					   glBegin(GL_POLYGON);
					   glNormal3f(0.0, 0.0, 1.0);	
					   glVertex3f(-0.4, -0.1, 1.0);
					   glVertex3f(0.4, -0.1, 1.0);
					   glVertex3f(0.4, 0.1, 1.0);
					   glVertex3f(-0.4, 0.1, 1.0);
					   glEnd();
					   glPopMatrix();
				   }
				   else{
					   glPushMatrix();
					   glTranslatef(1.1, -6.0, 0.0);
					   glColor3f(0.2, 0.2, 0.2);
					   glBegin(GL_POLYGON);
					   glNormal3f(0.0, 0.0, 1.0);		
					   glVertex3f(-0.4, -0.1, 1.0);
					   glVertex3f(0.4, -0.1, 1.0);
					   glVertex3f(0.4, 0.1, 1.0);
					   glVertex3f(-0.4, 0.1, 1.0);
					   glEnd();
					   glPopMatrix();
				   }

				   glEnable(GL_TEXTURE_2D);
			   }
			   
			   
			   staff.drawself();
			   doc.drawself();
			   cross.drawself();
			   

			   glPushMatrix();
			   glTranslatef(page_t, 0.0, 0.0);			//页面现在位置
			   start.drawself();
			   glTranslatef(32.0, 0.0, 0.0);			//第一页位置

			   tuli.drawself();		//先前覆盖上
			   for (int i = 0; i < 5; i++)
			   {
				   blolist_1[i].drawself();
			   }
			   glTranslatef(24.0, 0.0, 0.0);			//第二页位置

			   for (int i = 0; i < 4; i++)
			   {
				   blolist_2[i].drawself();
			   }
			   glTranslatef(24.0, 0.0, 0.0);			//第三页位置

			   for (int i = 0; i < 5; i++)
			   {
				   blolist_3[i].drawself();
			   }

			   glPopMatrix();

			   glPushMatrix();
			   glTranslatef(page_t*1.2, 0.0, 0.0);
			   background.drawself();					//画壁纸
			   glPopMatrix();

			   glPopMatrix();
			   break;
	}
	case 1:{				//如果是在拼图教学模式
			   glPushMatrix();
			   if (gameon == 0)
			   {
				   glEnable(GL_TEXTURE_2D);

				   glPushMatrix();
				   glTranslatef(0.0, page_u, 0.0);

				   glPushMatrix();
				   glTranslatef(page_t, 0.0, 0.0);			//页面现在位置
				   glTranslatef(32.0, 0.0, 0.0);			//第一页位置
				   for (int i = 0; i < 5; i++)
				   {
					   blolist_1[i].drawself();
				   }
				   glTranslatef(24.0, 0.0, 0.0);			//第二页位置
				   for (int i = 0; i < 4; i++)
				   {
					   blolist_2[i].drawself();
				   }
				   glPopMatrix();

				   glPushMatrix();
				   glTranslatef(page_t*1.2, 0.0, 0.0);
				   background.drawself();					//画壁纸
				   glPopMatrix();

				   glPopMatrix();
				   glDisable(GL_TEXTURE_2D);
				   glTranslatef(0.0, page_u - 18.0, 0.0);
			   }

			   (*tu_puzgame).tu_control_puz_drawall();
			   glPopMatrix();
			   break;
	}
	case 2:{				//如果是在球游戏中运行
			   glPushMatrix();

			   if (gameon == 0)
			   {
				   glEnable(GL_TEXTURE_2D);

				   glPushMatrix();
				   glTranslatef(0.0, page_u, 0.0);

				   glPushMatrix();
				   glTranslatef(page_t, 0.0, 0.0);			//页面现在位置
				   glTranslatef(32.0, 0.0, 0.0);			//第一页位置
				   for (int i = 0; i < 5; i++)
				   {
					   blolist_1[i].drawself();
				   }
				   glTranslatef(24.0, 0.0, 0.0);			//第二页位置
				   for (int i = 0; i < 4; i++)
				   {
					   blolist_2[i].drawself();
				   }

				   glTranslatef(24.0, 0.0, 0.0);			//第三页位置
				   for (int i = 0; i < 5; i++)
				   {
					   blolist_3[i].drawself();
				   }

				   glPopMatrix();

				   glPushMatrix();
				   glTranslatef(page_t*1.2, 0.0, 0.0);
				   background.drawself();					//画壁纸
				   glPopMatrix();

				   glPopMatrix();
				   glDisable(GL_TEXTURE_2D);
				   glTranslatef(0.0, page_u - 18.0, 0.0);
			   }

			   (*ballgame).control_ball_drawall();
			   glPopMatrix();

			   break;
	}
	case 3:{
			   glPushMatrix();
			   if (gameon == 0)
			   {
				   glEnable(GL_TEXTURE_2D);

				   glPushMatrix();
				   glTranslatef(0.0, page_u, 0.0);

				   glPushMatrix();
				   glTranslatef(page_t, 0.0, 0.0);			//页面现在位置
				   glTranslatef(32.0, 0.0, 0.0);			//第一页位置

				   glTranslatef(24.0, 0.0, 0.0);			//第二页位置
				   for (int i = 0; i < 4; i++)
				   {
					   blolist_2[i].drawself();
				   }
				   glTranslatef(24.0, 0.0, 0.0);			//第三页位置
				   for (int i = 0; i < 5; i++)
				   {
					   blolist_3[i].drawself();
				   }

				   glPopMatrix();

				   glPushMatrix();
				   glTranslatef(page_t*1.2, 0.0, 0.0);
				   background.drawself();					//画壁纸
				   glPopMatrix();

				   glPopMatrix();
				   glDisable(GL_TEXTURE_2D);
				   glTranslatef(0.0, page_u - 18.0, 0.0);
			   }

			   (*puzgame).control_puz_drawall();
			   glPopMatrix();
			   break;
	}
	case 4:
	{
			  glPushMatrix();
			  if (gameon == 0)
			  {
				  glEnable(GL_TEXTURE_2D);

				  glPushMatrix();
				  glTranslatef(0.0, page_u, 0.0);

				  glPushMatrix();
				  glTranslatef(page_t, 0.0, 0.0);			//页面现在位置
				  glTranslatef(32.0, 0.0, 0.0);			//第一页位置

				  glTranslatef(24.0, 0.0, 0.0);			//第二页位置
				  for (int i = 0; i < 4; i++)
				  {
					  blolist_2[i].drawself();
				  }
				  glTranslatef(24.0, 0.0, 0.0);			//第三页位置
				  for (int i = 0; i < 5; i++)
				  {
					  blolist_3[i].drawself();
				  }

				  glPopMatrix();

				  glPushMatrix();
				  glTranslatef(page_t*1.2, 0.0, 0.0);
				  background.drawself();					//画壁纸
				  glPopMatrix();

				  glPopMatrix();
				  glDisable(GL_TEXTURE_2D);
				  glTranslatef(0.0, page_u - 18.0, 0.0);
			  }

			  (*endless_ballgame).endless_control_ball_drawall();
			  glPopMatrix();
			  break;
	}
	}
}

void middle::middle_idle()
{
	switch (gamereallyon){
	case 0:{
			   if (page == 1 && page_t > -32.0)		//如果到第一页，还没翻过去
			   {
				   page_t -= 0.005 * page_t + 0.16;
			   }
			   else if (page == 0 && page_t < 0.0)			//如果到第零页，翻过了
			   {
				   page_t += -0.005 * page_t;
			   }
			   else if (page == 2 && page_t > -56.0)		//如果到第二页，没翻过去
			   {
				   page_t -= 0.005 * page_t + 0.28;
			   }
			   else if (page == 1 && page_t < -32.0)		//如果到第一页，翻过了
			   {
				   page_t += -0.005 * page_t - 0.16;
			   }
			   else if (page == 3 && page_t > -80.0)				//如果到第三页，没翻过去
			   {
				   page_t -= 0.005 * page_t + 0.4;
			   }
			   else if (page == 2 && page_t < -56.0)			//如果到第二页，翻过了
			   {
				   page_t += -0.005 * page_t - 0.28;
			   }


			   if (page_ver == -1 && page_u < 18.0)			//上下翻页
			   {
				   if (page_u < 18.0)
				   {
					   page_u += -0.01 * page_u + 0.18;
					   if (page_u > 17.8)
					   {
						   for (int i = 0; i < 5; i++)
						   {
							   blolist_1[i].UI_faci_appear = false;
							   blolist_3[i].UI_faci_appear = false;
						   }
						   for (int j = 0; j < 4; j++)
						   {
							   blolist_2[j].UI_faci_appear = false;
						   }
						   background.UI_faci_appear = false;
					   }
				   }
				   
				   if (staff.UI_faci_appear == true)
				   {
					   if (staff.UI_faci_position[1] < 18.0)	//如果没有移到最顶上
					   {
						   staff.UI_faci_position[1] += 0.002;
					   }
				   }
			   }
			   else if (page_ver == 1 && page_u >0.0)
			   {
				   page_u -= 0.01 * page_u;
				   if (page_u < 0.2)
				   {
					   doc.UI_faci_appear = false;
					   cross.UI_faci_appear = false;
					   staff.UI_faci_appear = false;
				   }
			   }

			   //------------------控制进入游戏的动画效果------------------------
			   if (gameon == 1 && page_u >= 17.9)
			   {
				   glMatrixMode(GL_PROJECTION);
				   glLoadIdentity();
				   glFrustum(-16.0, 16.0, -9.0, 9.0, 5.0, 30.0);
				   gluLookAt(0.0, 0.0, 9.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
				   glutSetCursor(GLUT_CURSOR_NONE);
				   glMatrixMode(GL_MODELVIEW);
				   glLoadIdentity();

				   glEnable(GL_TEXTURE_2D);
				   glClearColor(0.05, 0.05, 0.0, 1.0);
				   glLoadIdentity();
				   gamereallyon = 1;
				   (*tu_puzgame).tu_control_puz_randblock();
				   (*tu_puzgame).tu_control_puz_gameon = 1;
			   }
			   if (gameon == 2 && page_u >= 17.9)
			   {
				   glutSetCursor(GLUT_CURSOR_NONE);
				   glEnable(GL_LIGHTING);	//------------------------------进游戏的一刹那---------------------
				   
				   glDisable(GL_TEXTURE_2D);
				   glClearColor(0.0, 0.0, 0.0, 1.0);
				   gamereallyon = 2;
				   (*ballgame).control_ball_gameon = 2;
			   }
			   if (gameon == 3 && page_u >= 17.9)
			   {
				   glMatrixMode(GL_PROJECTION);
				   glLoadIdentity();
				   glFrustum(-16.0, 16.0, -9.0, 9.0, 5.0, 30.0);
				   gluLookAt(0.0, 0.0, 9.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
				   glutSetCursor(GLUT_CURSOR_NONE);
				   glMatrixMode(GL_MODELVIEW);
				   glLoadIdentity();

				   glEnable(GL_TEXTURE_2D);
				   glClearColor(0.0, 0.0, 0.1, 1.0);
				   glLoadIdentity();
				   gamereallyon = 3;
				   (*puzgame).control_puz_gameon = 3;
			   }
			   if (gameon == 4 && page_u >= 17.9)
			   {
				   glutSetCursor(GLUT_CURSOR_NONE);
				   glEnable(GL_LIGHTING);	//------------------------------进游戏的一刹那---------------------

				   glClearColor(0.0, 0.0, 0.0, 1.0);
				   glDisable(GL_TEXTURE_2D);
				   gamereallyon = 4;
				   (*endless_ballgame).endless_control_ball_gameon = 4;
			   }
			   
			   if (page != 0){		//在标题页的时候不动作
				   if (background.UI_faci_scale >1.3)
				   {
					   back_bigsmall = false;
				   }
				   else if (background.UI_faci_scale <1.0)
				   {
					   back_bigsmall = true;
				   }
				   if (back_bigsmall == true)
				   {
					   background.UI_faci_scale += 0.000002;
					   background.UI_faci_scale += 0.000002;
				   }
				   else if (back_bigsmall == false)
				   {
					   background.UI_faci_scale -= 0.000002;
					   background.UI_faci_scale -= 0.000002;
				   }
			   }

			   //---------------------------------字帖大小变化-------------------------------------------
			   switch (blo_on)
			   {
			   case 1:{
						  start.turn_big();
			   }
			   case 11: {
							blolist_1[0].turn_big();
							blolist_1[1].turn_small();
							blolist_1[2].turn_small();
							blolist_1[3].turn_small();
							blolist_1[4].turn_small();
							blolist_2[0].turn_small();
							blolist_2[1].turn_small();
							blolist_2[2].turn_small();
							blolist_2[3].turn_small();
							blolist_3[0].turn_small();
							blolist_3[1].turn_small();
							blolist_3[2].turn_small();
							blolist_3[3].turn_small();
							blolist_3[4].turn_small();
							out.turn_small();
							break;
			   }
			   case 12: {
							blolist_1[0].turn_small();
							blolist_1[1].turn_big();
							blolist_1[2].turn_small();
							blolist_1[3].turn_small();
							blolist_1[4].turn_small();
							blolist_2[0].turn_small();
							blolist_2[1].turn_small();
							blolist_2[2].turn_small();
							blolist_2[3].turn_small();
							blolist_3[0].turn_small();
							blolist_3[1].turn_small();
							blolist_3[2].turn_small();
							blolist_3[3].turn_small();
							blolist_3[4].turn_small();
							out.turn_small();
							break;
			   }
			   case 13: {
							blolist_1[0].turn_small();
							blolist_1[1].turn_small();
							blolist_1[2].turn_big();
							blolist_1[3].turn_small();
							blolist_1[4].turn_small();
							blolist_2[0].turn_small();
							blolist_2[1].turn_small();
							blolist_2[2].turn_small();
							blolist_2[3].turn_small();
							blolist_3[0].turn_small();
							blolist_3[1].turn_small();
							blolist_3[2].turn_small();
							blolist_3[3].turn_small();
							blolist_3[4].turn_small();
							out.turn_small();
							break;
			   }
			   case 14: {
							blolist_1[0].turn_small();
							blolist_1[1].turn_small();
							blolist_1[2].turn_small();
							blolist_1[3].turn_big();
							blolist_1[4].turn_small();
							blolist_2[0].turn_small();
							blolist_2[1].turn_small();
							blolist_2[2].turn_small();
							blolist_2[3].turn_small();
							blolist_3[0].turn_small();
							blolist_3[1].turn_small();
							blolist_3[2].turn_small();
							blolist_3[3].turn_small();
							blolist_3[4].turn_small();
							out.turn_small();
							break;
			   }
			   case 15: {
							blolist_1[0].turn_small();
							blolist_1[1].turn_small();
							blolist_1[2].turn_small();
							blolist_1[3].turn_small();
							blolist_1[4].turn_big();
							blolist_2[0].turn_small();
							blolist_2[1].turn_small();
							blolist_2[2].turn_small();
							blolist_2[3].turn_small();
							blolist_3[0].turn_small();
							blolist_3[1].turn_small();
							blolist_3[2].turn_small();
							blolist_3[3].turn_small();
							blolist_3[4].turn_small();
							out.turn_small();
							break;
			   }
			   case 21:{
						   blolist_1[0].turn_small();
						   blolist_1[1].turn_small();
						   blolist_1[2].turn_small();
						   blolist_1[3].turn_small();
						   blolist_1[4].turn_small();
						   blolist_2[0].turn_big();
						   blolist_2[1].turn_small();
						   blolist_2[2].turn_small();
						   blolist_2[3].turn_small();
						   blolist_3[0].turn_small();
						   blolist_3[1].turn_small();
						   blolist_3[2].turn_small();
						   blolist_3[3].turn_small();
						   blolist_3[4].turn_small();
						   out.turn_small();
						   break;
			   }
			   case 22: {
							blolist_1[0].turn_small();
							blolist_1[1].turn_small();
							blolist_1[2].turn_small();
							blolist_1[3].turn_small();
							blolist_1[4].turn_small();
							blolist_2[0].turn_small();
							blolist_2[1].turn_big();
							blolist_2[2].turn_small();
							blolist_2[3].turn_small();
							blolist_3[0].turn_small();
							blolist_3[1].turn_small();
							blolist_3[2].turn_small();
							blolist_3[3].turn_small();
							blolist_3[4].turn_small();
							out.turn_small();
							break;
			   }
			   case 23: {
							blolist_1[0].turn_small();
							blolist_1[1].turn_small();
							blolist_1[2].turn_small();
							blolist_1[3].turn_small();
							blolist_1[4].turn_small();
							blolist_2[0].turn_small();
							blolist_2[1].turn_small();
							blolist_2[2].turn_big();
							blolist_2[3].turn_small();
							blolist_3[0].turn_small();
							blolist_3[1].turn_small();
							blolist_3[2].turn_small();
							blolist_3[3].turn_small();
							blolist_3[4].turn_small();
							out.turn_small();
							break;
			   }
			   case 24: {
							blolist_1[0].turn_small();
							blolist_1[1].turn_small();
							blolist_1[2].turn_small();
							blolist_1[3].turn_small();
							blolist_1[4].turn_small();
							blolist_2[0].turn_small();
							blolist_2[1].turn_small();
							blolist_2[2].turn_small();
							blolist_2[3].turn_big();
							blolist_3[0].turn_small();
							blolist_3[1].turn_small();
							blolist_3[2].turn_small();
							blolist_3[3].turn_small();
							blolist_3[4].turn_small();
							out.turn_small();
							break;
			   }
			   case 31:{
						   blolist_1[0].turn_small();
						   blolist_1[1].turn_small();
						   blolist_1[2].turn_small();
						   blolist_1[3].turn_small();
						   blolist_1[4].turn_small();
						   blolist_2[0].turn_small();
						   blolist_2[1].turn_small();
						   blolist_2[2].turn_small();
						   blolist_2[3].turn_small();
						   blolist_3[0].turn_big();
						   blolist_3[1].turn_small();
						   blolist_3[2].turn_small();
						   blolist_3[3].turn_small();
						   blolist_3[4].turn_small();
						   out.turn_small();
						   break;
			   }
			   case 32:{
						   blolist_1[0].turn_small();
						   blolist_1[1].turn_small();
						   blolist_1[2].turn_small();
						   blolist_1[3].turn_small();
						   blolist_1[4].turn_small();
						   blolist_2[0].turn_small();
						   blolist_2[1].turn_small();
						   blolist_2[2].turn_small();
						   blolist_2[3].turn_small();
						   blolist_3[0].turn_small();
						   blolist_3[1].turn_big();
						   blolist_3[2].turn_small();
						   blolist_3[3].turn_small();
						   blolist_3[4].turn_small();
						   out.turn_small();
						   break;
			   }
			   case 33:{
						   blolist_1[0].turn_small();
						   blolist_1[1].turn_small();
						   blolist_1[2].turn_small();
						   blolist_1[3].turn_small();
						   blolist_1[4].turn_small();
						   blolist_2[0].turn_small();
						   blolist_2[1].turn_small();
						   blolist_2[2].turn_small();
						   blolist_2[3].turn_small();
						   blolist_3[0].turn_small();
						   blolist_3[1].turn_small();
						   blolist_3[2].turn_big();
						   blolist_3[3].turn_small();
						   blolist_3[4].turn_small();
						   out.turn_small();
						   break;
			   }
			   case 34:{
						   blolist_1[0].turn_small();
						   blolist_1[1].turn_small();
						   blolist_1[2].turn_small();
						   blolist_1[3].turn_small();
						   blolist_1[4].turn_small();
						   blolist_2[0].turn_small();
						   blolist_2[1].turn_small();
						   blolist_2[2].turn_small();
						   blolist_2[3].turn_small();
						   blolist_3[0].turn_small();
						   blolist_3[1].turn_small();
						   blolist_3[2].turn_small();
						   blolist_3[3].turn_big();
						   blolist_3[4].turn_small();
						   out.turn_small();
						   break;
			   }
			   case 35:{
						   blolist_1[0].turn_small();
						   blolist_1[1].turn_small();
						   blolist_1[2].turn_small();
						   blolist_1[3].turn_small();
						   blolist_1[4].turn_small();
						   blolist_2[0].turn_small();
						   blolist_2[1].turn_small();
						   blolist_2[2].turn_small();
						   blolist_2[3].turn_small();
						   blolist_3[0].turn_small();
						   blolist_3[1].turn_small();
						   blolist_3[2].turn_small();
						   blolist_3[3].turn_small();
						   blolist_3[4].turn_big();
						   out.turn_small();
						   break;
			   }
			   case -1: {
							cross.turn_big();
							break;
			   }
			   case -2:{
						   for (int i = 0; i < 5; i++)
						   {
							   blolist_1[i].turn_small();
							   blolist_3[i].turn_small();
						   }
						   for (int j = 0; j < 4; j++)
						   {
							   blolist_2[j].turn_small();
						   }
						   out.turn_big();
						   break;
			   }
			   default: {
							for (int i = 0; i < 5; i++)
							{
								blolist_1[i].turn_small();
								blolist_3[i].turn_small();
							}
							for (int j = 0; j < 4; j++)
							{
								blolist_2[j].turn_small();
							}
							start.turn_small();
							cross.turn_small();
							out.turn_small();
							break;
			   }
			   }
			   break;
	}
	case 1:{
			   gameon = (*tu_puzgame).tu_control_puz_gameon;

			   if (gameon == 0 && page_u > 0.0)			//上下翻页
			   {
				   page_u -= 0.01 * page_u;

				   glMatrixMode(GL_PROJECTION);
				   glLoadIdentity();
				   glOrtho(-16.0, 16.0, -9.0, 9.0, -10.0, 10.0);
				   gluLookAt(0.0, 0.0, 9.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
				   glMatrixMode(GL_MODELVIEW);
				   glLoadIdentity();

				   glEnable(GL_TEXTURE_2D);
				   glLoadIdentity();

				   for (int i = 0; i < 5; i++)
				   {
					   blolist_1[i].UI_faci_appear = true;
					   blolist_3[i].UI_faci_appear = true;
				   }
				   for (int j = 0; j < 4; j++)
				   {
					   blolist_2[j].UI_faci_appear = true;
				   }
				   background.UI_faci_appear = true;
			   }

			   if (page_u < 0.05)
			   {
				   gamereallyon = 0;
				   page_ver = 1;
				   page_u = 0.0;
				   glutSetCursor(CURSOR_SHOWING);//---------------------------------返回的一刹那
			   }

			   (*tu_puzgame).tu_control_puz_idle();
			   break;
	}
	case 2:{
			   gameon = (*ballgame).control_ball_gameon;
			   if (gameon == 0 && page_u > 0.0)			//上下翻页
			   {
				   page_u -= 0.1 * page_u;
				   for (int i = 0; i < 5; i++)
				   {
					   blolist_1[i].UI_faci_appear = true;
					   blolist_3[i].UI_faci_appear = true;
				   }
				   for (int j = 0; j < 4; j++)
				   {
					   blolist_2[j].UI_faci_appear = true;
				   }
				   background.UI_faci_appear = true;
			   }

			   if (page_u < 0.2)
			   {
				   gamereallyon = 0;
				   page_ver = 1;
				   page_u = 0.0;
				   glutSetCursor(CURSOR_SHOWING);//---------------------------------返回的一刹那
			   }

			   (*ballgame).control_ball_idle();

			   break;
	}
	case 3:{
			   gameon = (*puzgame).control_puz_gameon;

			   if (gameon == 0 && page_u > 0.0)			//上下翻页
			   {
				   page_u -= 0.01 * page_u;

				   glMatrixMode(GL_PROJECTION);
				   glLoadIdentity();
				   glOrtho(-16.0, 16.0, -9.0, 9.0, -10.0, 10.0);
				   gluLookAt(0.0, 0.0, 9.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
				   glMatrixMode(GL_MODELVIEW);
				   glLoadIdentity();

				   glEnable(GL_TEXTURE_2D);
				   glLoadIdentity();

				   for (int i = 0; i < 5; i++)
				   {
					   blolist_1[i].UI_faci_appear = true;
					   blolist_3[i].UI_faci_appear = true;
				   }
				   for (int j = 0; j < 4; j++)
				   {
					   blolist_2[j].UI_faci_appear = true;
				   }
				   background.UI_faci_appear = true;
			   }

			   if (page_u < 0.05)
			   {
				   gamereallyon = 0;
				   page_ver = 1;
				   page_u = 0.0;
				   glutSetCursor(CURSOR_SHOWING);//---------------------------------返回的一刹那
			   }

			   (*puzgame).control_puz_idle();
			   break;
	}
	case 4:{
			   gameon = (*endless_ballgame).endless_control_ball_gameon;

			   if (gameon == 0 && page_u > 0.0)			//上下翻页
			   {
				   page_u -= 0.1 * page_u;
				   for (int i = 0; i < 5; i++)
				   {
					   blolist_1[i].UI_faci_appear = true;
					   blolist_3[i].UI_faci_appear = true;
				   }
				   for (int j = 0; j < 4; j++)
				   {
					   blolist_2[j].UI_faci_appear = true;
				   }
				   background.UI_faci_appear = true;
			   }

			   if (page_u < 0.2)
			   {
				   gamereallyon = 0;
				   page_ver = 1;
				   page_u = 0.0;
				   glutSetCursor(CURSOR_SHOWING);//---------------------------------返回的一刹那
			   }

			   (*endless_ballgame).endless_control_ball_idle();
			   break;
	}
	}
	
	glutPostRedisplay();
}

void middle::mouseevent()
{
	switch (gamereallyon){
	case 0:
	{
			  posx = mouseposition_x * 32.0 / 1366.0 - 16.0;
			  posy = 9.0 - mouseposition_y * 18.0 / 768.0;

			  if (left_mouse_down == true){
				  if (page_ver == 1)
				  {
					  //-----------------------------------------点击方块-------------------------------------------
					  if (page == 0)
					  {
						  if (posx  > -2.0 && posx < 2.0 && posy > -3.5 && posy < -2.5)
						  {
							  start.UI_faci_scale = 1.05;
							  page++;
							  out.UI_faci_appear = true;
							  for (int i = 0; i < 4; i++)
							  {
								  blolist_2[i].UI_faci_appear = true;
							  }
						  }
					  }
					  else if (page == 1)
					  {
						  if (tuli.UI_faci_appear == true)
						  {
							  tuli.UI_faci_appear = false;
						  }
						  else{
							  start.UI_faci_appear = false;
							  if (posx > -10.0 && posx < -2.0 && posy > -4.5 && posy < -1.5)		//1-1
							  {
								  blolist_1[0].UI_faci_scale = 1.05;
								  doc.UI_faci_color = 18;
								  page_ver = -1;
								  doc.UI_faci_appear = true;
								  cross.UI_faci_appear = true;
							  }
							  else if (posx > 6.0 && posx < 10.0 && posy > -1.5 && posy < 4.5)
							  {
								  blolist_1[1].UI_faci_scale = 1.05;
								  doc.UI_faci_color = 19;
								  page_ver = -1;
								  doc.UI_faci_appear = true;
								  cross.UI_faci_appear = true;
							  }
							  else if (posx > -10.0 && posx < 6.0 && posy > -1.5 && posy < 4.5)
							  {
								  blolist_1[2].UI_faci_scale = 1.05;
								  page_ver = -1;
								  gameon = 1;//===========================================================================
							  }
							  else if (posx > -2.0 && posx < 6.0 && posy > -4.5 && posy < -1.5)
							  {
								  blolist_1[3].UI_faci_scale = 1.05;
								  doc.UI_faci_color = 20;
								  page_ver = -1;
								  doc.UI_faci_appear = true;
								  cross.UI_faci_appear = true;
							  }
							  else if (posx > 6.0 && posx < 10.0 && posy > -4.5 && posy < -1.5)
							  {
								  blolist_1[4].UI_faci_scale = 1.05;
								  doc.UI_faci_color = 21;
								  page_ver = -1;
								  doc.UI_faci_appear = true;
								  cross.UI_faci_appear = true;
							  }
							  else if (posx > 14.0 && posy < 6.0 && page != 3)
							  {		//翻页
								  page++;
							  }
							  else if (posx < -14.0 && page != 0 && page != 1){
								  page--;
							  }
							  else if (posx > 13.5 && posx < 14.5 && posy > 6.5 && posy < 7.5)
							  {
								  out.UI_faci_scale = 1.05;
								  exit(0);
							  }
						  }
					  }
					  else if (page == 2)
					  {
						  if (posx > -10.0 && posx < 2.0 && posy > -4.5 && posy < 4.5)		//1-1
						  {
							  blolist_2[0].UI_faci_scale = 1.05;
							  page_ver = -1;
							  gameon = 2;			//=================================================================

						  }
						  else if (posx > 2.0 && posx < 10.0 && posy > 1.5 && posy < 4.5)
						  {
							  blolist_2[1].UI_faci_scale = 1.05;
							  doc.UI_faci_color = 22;
							  page_ver = -1;
							  doc.UI_faci_appear = true;
							  cross.UI_faci_appear = true;
						  }
						  else if (posx > 2.0 && posx < 10.0 && posy > -1.5 && posy < 1.5)
						  {
							  blolist_2[2].UI_faci_scale = 1.05;
							  doc.UI_faci_color = 23;
							  page_ver = -1;
							  doc.UI_faci_appear = true;
							  cross.UI_faci_appear = true;
						  }
						  else if (posx > 2.0 && posx < 10.0 && posy > -4.5 && posy < -1.5)
						  {
							  blolist_2[3].UI_faci_scale = 1.05;
							  doc.UI_faci_color = 24;
							  page_ver = -1;
							  doc.UI_faci_appear = true;
							  cross.UI_faci_appear = true;
						  }
						  else if (posx > 14.0 && posy < 6.0 && page != 3)
						  {		//翻页
							  page++;
						  }
						  else if (posx < -14.0 && page != 0 && page != 1){
							  page--;
						  }
						  else if (posx > 13.5 && posx < 14.5 && posy > 6.5 && posy < 7.5)
						  {
							  out.UI_faci_scale = 1.05;
							  exit(0);
						  }
					  }
					  else if (page == 3)
					  {
						  if (posx > -10.0 && posx < -1.5 && posy > -4.5 && posy < 4.5)
						  {
							  blolist_3[0].UI_faci_scale = 1.05;//--------------------------endless ball entrance----------------
							  page_ver = -1;
							  gameon = 3;
						  }
						  else if (posx > -1.5 && posx < 7.0 && posy > -4.5 && posy < 4.5)
						  {
							  blolist_3[1].UI_faci_scale = 1.05;//----------------------------endless puz entrance---------------
							  page_ver = -1;
							  gameon = 4;
						  }
						  else if (posx > 7.0 && posx < 10.0 && posy > 1.5 && posy < 4.5)
						  {
							  blolist_3[2].UI_faci_scale = 1.05;
							  doc.UI_faci_color = 25;
							  page_ver = -1;
							  doc.UI_faci_appear = true;
							  cross.UI_faci_appear = true;
						  }
						  else if (posx > 7.0 && posx < 10.0 && posy > -1.5 && posy < 1.5)		//staff 进入--------------------------
						  {
							  blolist_3[3].UI_faci_scale = 1.05;
							  page_ver = -1;
							  staff.UI_faci_position[1] = -54.0;
							  staff.UI_faci_appear = true;
							  cross.UI_faci_appear = true;
						  }
						  else if (posx > 7.0 && posx < 10.0 && posy > -4.5 && posy < -1.5)
						  {
							  blolist_3[4].UI_faci_scale = 1.05;
							  doc.UI_faci_color = 27;
							  page_ver = -1;
							  doc.UI_faci_appear = true;
							  cross.UI_faci_appear = true;
						  }
						  else if (posx > 14.0 && posy < 6.0 && page != 3)
						  {		//翻页
							  page++;
						  }
						  else if (posx < -14.0 && page != 0 && page != 1){
							  page--;
						  }
						  else if (posx > 13.5 && posx < 14.5 && posy > 6.5 && posy < 7.5)
						  {
							  out.UI_faci_scale = 1.05;
							  exit(0);
						  }
					  } 
				  }
				  else if (page_ver == -1)
				  {
					  if (posx > 13.5 && posx < 14.5 && posy > 6.5 && posy < 7.5)
					  {
						  cross.UI_faci_scale = 1.05;
						  page_ver = 1;
						  for (int i = 0; i < 5; i++)
						  {
							  blolist_1[i].UI_faci_appear = true;
							  blolist_3[i].UI_faci_appear = true;
						  }
						  for (int j = 0; j < 4; j++)
						  {
							  blolist_2[j].UI_faci_appear = true;
						  }
						  background.UI_faci_appear = true;
					  }
				  }
			  }
			  break;
	}
	case 1:{
			   (*tu_puzgame).tu_control_puz_mouseposition_x = mouseposition_x;
			   (*tu_puzgame).tu_control_puz_mouseposition_y = mouseposition_y;
			   (*tu_puzgame).tu_control_puz_left_mouse_down = left_mouse_down;
			   (*tu_puzgame).tu_control_puz_right_mouse_down = right_mouse_down;
			   (*tu_puzgame).tu_control_puz_mouseevent();
			   break;
	}
	case 2:{
			   (*ballgame).control_ball_mouseposition_x = mouseposition_x;
			   (*ballgame).control_ball_mouseposition_y = mouseposition_y;
			   (*ballgame).control_ball_left_mouse_down = left_mouse_down;
			   (*ballgame).control_ball_mouseevent();
			   break;
	}
	case 3:{
			   (*puzgame).control_puz_mouseposition_x = mouseposition_x;
			   (*puzgame).control_puz_mouseposition_y = mouseposition_y;
			   (*puzgame).control_puz_left_mouse_down = left_mouse_down;
			   (*puzgame).control_puz_right_mouse_down = right_mouse_down;
			   (*puzgame).control_puz_mouseevent();

			   break;
	}
	case 4:{
			   (*endless_ballgame).endless_control_ball_mouseposition_x = mouseposition_x;
			   (*endless_ballgame).endless_control_ball_mouseposition_y = mouseposition_y;
			   (*endless_ballgame).endless_control_ball_left_mouse_down = left_mouse_down;
			   (*endless_ballgame).endless_control_ball_mouseevent();
			   break;
	}
	}
}

void middle::mouseevent_motion()
{
	switch (gamereallyon){
	case 0:{

			   break;
	}
	case 1:{
			   (*tu_puzgame).tu_control_puz_mouseposition_x = mouseposition_x;
			   (*tu_puzgame).tu_control_puz_mouseposition_y = mouseposition_y;
			   (*tu_puzgame).tu_control_puz_mouseevent_motion();
			   break;
	}
	case 2:{
			   (*ballgame).control_ball_mouseposition_x = mouseposition_x;
			   (*ballgame).control_ball_mouseposition_y = mouseposition_y;
			   (*ballgame).control_ball_mouseevent_motion();
			   break;
	}
	case 3:{
			   (*puzgame).control_puz_mouseposition_x = mouseposition_x;
			   (*puzgame).control_puz_mouseposition_y = mouseposition_y;
			   (*puzgame).control_puz_mouseevent_motion();
			   break;
	}
	case 4:{
			   (*endless_ballgame).endless_control_ball_mouseposition_x = mouseposition_x;
			   (*endless_ballgame).endless_control_ball_mouseposition_y = mouseposition_y;
			   (*endless_ballgame).endless_control_ball_mouseevent_motion();
			   break;
	}
	}
}

void middle::mouseevent_passive()
{
	switch (gamereallyon){
	case 0:{
			   posx = mouseposition_x * 32.0 / 1366.0 - 16.0;
			   posy = 9.0 - mouseposition_y * 18.0 / 768.0;
			   
			   if (page_ver == 1)
			   {
				   if (page == 0)
				   {
					   if (posx > -2.0 && posx < 2.0 && posy > -3.5 && posy < -2.5)
					   {
						   blo_on = 1;
					   }
					   else{
						   blo_on = 0;
					   }
				   }
				   else if (page == 1)
				   {
					   if (posx > -10.0 && posx < -2.0 && posy > -4.5 && posy < -1.5)		//1-1
					   {
						   blo_on = 11;
					   }
					   else if (posx > 6.0 && posx < 10.0 && posy > -1.5 && posy < 4.5)
					   {
						   blo_on = 12;
					   }
					   else if (posx > -10.0 && posx < 6.0 && posy > -1.5 && posy < 4.5)
					   {
						   blo_on = 13;
					   }
					   else if (posx > -2.0 && posx < 6.0 && posy > -4.5 && posy < -1.5)
					   {
						   blo_on = 14;
					   }
					   else if (posx > 6.0 && posx < 10.0 && posy > -4.5 && posy < -1.5)
					   {
						   blo_on = 15;
					   }
					   else if (posx > 13.5 && posx < 14.5 && posy > 6.5 && posy < 7.5)
					   {
						   blo_on = -2;
					   }
					   else{
						   blo_on = 0;
					   }
				   }
				   else if (page == 2)
				   {
					   if (posx > -10.0 && posx < 2.0 && posy > -4.5 && posy < 4.5)		//1-1
					   {
						   blo_on = 21;
					   }
					   else if (posx > 2.0 && posx < 10.0 && posy > 1.5 && posy < 4.5)
					   {
						   blo_on = 22;
					   }
					   else if (posx > 2.0 && posx < 10.0 && posy > -1.5 && posy < 1.5)
					   {
						   blo_on = 23;
					   }
					   else if (posx > 2.0 && posx < 10.0 && posy > -4.5 && posy < -1.5)
					   {
						   blo_on = 24;
					   }
					   else if (posx > 13.5 && posx < 14.5 && posy > 6.5 && posy < 7.5)
					   {
						   blo_on = -2;
					   }
					   else{
						   blo_on = 0;
					   }
				   }
				   else if (page == 3)
				   {
					   if (posx > -10.0 && posx < -1.5 && posy > -4.5 && posy < 4.5)
					   {
						   blo_on = 31;
					   }
					   else if (posx > -1.5 && posx < 7.0 && posy > -4.5 && posy < 4.5)
					   {
						   blo_on = 32;
					   }
					   else if (posx > 7.0 && posx < 10.0 && posy > 1.5 && posy < 4.5)
					   {
						   blo_on = 33;
					   }
					   else if (posx > 7.0 && posx < 10.0 && posy > -1.5 && posy < 1.5)
					   {
						   blo_on = 34;
					   }
					   else if (posx > 7.0 && posx < 10.0 && posy > -4.5 && posy < -1.5)
					   {
						   blo_on = 35;
					   }
					   else if (posx > 13.5 && posx < 14.5 && posy > 6.5 && posy < 7.5)
					   {
						   blo_on = -2;
					   }
					   else{
						   blo_on = 0;
					   }
				   }
			   }else if (page_ver == -1)
			   {
				   if (posx > 13.5 && posx < 14.5 && posy > 6.5 && posy < 7.5)
				   {
					   blo_on = -1;		//点在叉上
				   }
				   else{
					   blo_on = 0;
				   }
			   }

			   break;
	}
	case 1:{
			   (*tu_puzgame).tu_control_puz_mouseposition_x = mouseposition_x;
			   (*tu_puzgame).tu_control_puz_mouseposition_y = mouseposition_y;
			   (*tu_puzgame).tu_control_puz_mouseevent_passive();
			   break;
	}
	case 2:{
			   (*ballgame).control_ball_mouseposition_x = mouseposition_x;
			   (*ballgame).control_ball_mouseposition_y = mouseposition_y;
			   (*ballgame).control_ball_mouseevent_passive();
			   break;
	}
	case 3:{
			   (*puzgame).control_puz_mouseposition_x = mouseposition_x;
			   (*puzgame).control_puz_mouseposition_y = mouseposition_y;
			   (*puzgame).control_puz_mouseevent_passive();
			   break;
	}
	case 4:{
			   (*endless_ballgame).endless_control_ball_mouseposition_x = mouseposition_x;
			   (*endless_ballgame).endless_control_ball_mouseposition_y = mouseposition_y;
			   (*endless_ballgame).endless_control_ball_mouseevent_passive();
			   break;
	}
	}

}

void middle::keyboardevent(unsigned char a)
{
	if (page == 0){
		page++;
		out.UI_faci_appear = true;
	}
	else{
		if (tuli.UI_faci_appear == true)
		{
			tuli.UI_faci_appear = false;
		}
		else{
			if (gamereallyon == 0 && a == 27)		//退出程序
			{
				exit(0);
			}
		}
	}
}

void middle::specialevent(GLint a)
{
	if (gamereallyon == 0)		//左右翻页
	{
		if (page == 0)		//如果是在初始页
		{
			page++;
			out.UI_faci_appear = true;
		}
		else{		//如果已经过了初始页
			if (tuli.UI_faci_appear == true)	//如果图例还开着就把它关上
			{
				tuli.UI_faci_appear = false;
			}
			else{
				switch (a){
				case GLUT_KEY_RIGHT:
				{
									   if (page == 1 || page == 2)
									   {
										   page++;
									   }
									   break;

				}
				case GLUT_KEY_LEFT:
				{
									  if (page != 1)
									  {
										  page--;
									  }
									  break;
				}
				}
			}
		}
	}
}