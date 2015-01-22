#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include "middle.h"

using namespace std;

middle *middle1 = new middle();		//新建控制class

void myInit(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutFullScreen();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-16.0, 16.0, -9.0, 9.0, -10.0, 10.0);
	gluLookAt(0.0, 0.0, 9.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	(*middle1).init();

	(*middle1).mouseposition_x_pre = 0.0;
	(*middle1).mouseposition_y_pre = 0.0;

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}

void display()
{
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//得把两个都清空才能画得出来

	(*middle1).drawall();	//调用一个中间函数,drawall的用处是把所有的东西，该画的画出来

	glutSwapBuffers();
}

void idle()
{
	(*middle1).middle_idle();
}

void mymouse(GLint button, GLint state, GLint x, GLint y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		(*middle1).left_mouse_down = true;							//把鼠标的信息传入主控middle1
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
		(*middle1).left_mouse_down = false;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		(*middle1).right_mouse_down = true;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		(*middle1).right_mouse_down = false;
	}
	(*middle1).mouseposition_x = x;
	(*middle1).mouseposition_y = y;
	(*middle1).mouseevent();		//鼠标做改变之后再middle.mouseevent()中进行处理
	glutPostRedisplay();		//每次做出改变之后都会重新画一次
}

void mymouse_passive(GLint x, GLint y){			//记录鼠标在窗口的位置
	(*middle1).mouseposition_x = x;
	(*middle1).mouseposition_y = y;
	(*middle1).mouseevent_passive();

	glutPostRedisplay();
}

void mymouse_motion(GLint x, GLint y)		//拖拽动作
{
	(*middle1).mouseposition_x = x;
	(*middle1).mouseposition_y = y;
	(*middle1).mouseevent_motion();

	glutPostRedisplay();
}

void mykeyboard(unsigned char key, int x, int y)
{	
	(*middle1).keyboardevent(key);
	glutPostRedisplay();
}

void myspecial(GLint key, int x, int y)
{
	(*middle1).specialevent(key);
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //指定双缓冲窗口，制定RGB颜色模式的窗口
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1366, 768);
	glutCreateWindow("UI");
	myInit();
	glutMouseFunc(mymouse);
	glutPassiveMotionFunc(mymouse_passive);
	glutMotionFunc(mymouse_motion);
	glutKeyboardFunc(mykeyboard);
	glutSpecialFunc(myspecial);
	glutDisplayFunc(display);//显示回调
	glutIdleFunc(idle);
	glutMainLoop();
}