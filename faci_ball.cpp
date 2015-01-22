#include "faci_ball.h"
#include <GL\glut.h>
using namespace std;
#pragma comment(lib, "glaux")

AUX_RGBImageRec *faci_ball_Images[75];
GLuint faci_ball_ImageIDs[75];
char *faci_ball_pictures[75] = {
	"pictures\\ballgame\\1.bmp",		//0
	"pictures\\ballgame\\2.bmp",
	"pictures\\ballgame\\3.bmp",
	"pictures\\ballgame\\4.bmp",
	"pictures\\ballgame\\custom.bmp",
	"pictures\\ballgame\\bar.bmp",
	"pictures\\ballgame\\arrow.bmp",
	"pictures\\ballgame\\home.bmp",
	"pictures\\ballgame\\G1.bmp",
	"pictures\\ballgame\\G2.bmp",
	"pictures\\ballgame\\G3.bmp",
	"pictures\\ballgame\\G4.bmp",
	"pictures\\ballgame\\G5.bmp",
	"pictures\\ballgame\\G6.bmp",
	"pictures\\ballgame\\G7.bmp",
	"pictures\\ballgame\\G8.bmp",
	"pictures\\ballgame\\G9.bmp",
	"pictures\\ballgame\\G10.bmp",
	"pictures\\ballgame\\G11.bmp",
	"pictures\\ballgame\\G12.bmp",
	"pictures\\ballgame\\G13.bmp",
	"pictures\\ballgame\\G14.bmp",
	"pictures\\ballgame\\G15.bmp",
	"pictures\\ballgame\\G16.bmp",
	"pictures\\ballgame\\G17.bmp",
	"pictures\\ballgame\\G18.bmp",
	"pictures\\ballgame\\G19.bmp",
	"pictures\\ballgame\\G20.bmp",
	"pictures\\ballgame\\G21.bmp",
	"pictures\\ballgame\\G22.bmp",
	"pictures\\ballgame\\G23.bmp",
	"pictures\\ballgame\\G24.bmp",
	"pictures\\ballgame\\G25.bmp",
	"pictures\\ballgame\\G26.bmp",
	"pictures\\ballgame\\G27.bmp",
	"pictures\\ballgame\\G28.bmp",
	"pictures\\ballgame\\G29.bmp",
	"pictures\\ballgame\\G30.bmp",
	"pictures\\ballgame\\endless.bmp",

	"pictures\\wall\\1.bmp",		//39
	"pictures\\wall\\2.bmp",
	"pictures\\wall\\3.bmp",
	"pictures\\wall\\4.bmp",
	"pictures\\wall\\5.bmp",
	"pictures\\wall\\6.bmp",
	"pictures\\wall\\7.bmp",
	"pictures\\wall\\8.bmp",
	"pictures\\wall\\9.bmp",
	"pictures\\wall\\10.bmp",
	"pictures\\wall\\11.bmp",
	"pictures\\wall\\12.bmp",
	"pictures\\wall\\13.bmp",
	"pictures\\wall\\14.bmp",
	"pictures\\wall\\15.bmp",
	"pictures\\wall\\16.bmp",
	"pictures\\wall\\17.bmp",
	"pictures\\wall\\18.bmp",
	"pictures\\wall\\19.bmp",
	"pictures\\wall\\20.bmp",
	"pictures\\wall\\21.bmp",
	"pictures\\wall\\22.bmp",
	"pictures\\wall\\23.bmp",
	"pictures\\wall\\24.bmp",
	"pictures\\wall\\25.bmp",
	"pictures\\wall\\26.bmp",
	"pictures\\wall\\27.bmp",
	"pictures\\wall\\28.bmp",
	"pictures\\wall\\29.bmp",
	"pictures\\wall\\30.bmp",		//68

	"pictures\\ballgame\\level.bmp",	//69

	"pictures\\ballgame\\1on.bmp",		//70
	"pictures\\ballgame\\2on.bmp",		//71
	"pictures\\ballgame\\3on.bmp",		//72
	"pictures\\ballgame\\4on.bmp",		//73
	"pictures\\ballgame\\customon.bmp"		//74

};

void faci_ball::faci_ball_settexture()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(75, faci_ball_ImageIDs);
	for (int i = 0; i < 75; i++)
	{
		glBindTexture(GL_TEXTURE_2D, faci_ball_ImageIDs[i]);
		faci_ball_Images[i] = auxDIBImageLoadA(faci_ball_pictures[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, faci_ball_Images[i]->sizeX, faci_ball_Images[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, faci_ball_Images[i]->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	}
	glEnable(GL_TEXTURE_2D);
}


faci_ball::faci_ball(int kind, float position[3], float size[3], GLfloat color_ambient[4], GLfloat color_diffuse[4],
	GLfloat color_specular[4], GLfloat color_shine, bool appear)
{
	faci_ball_kind = kind;
	for (int i = 0; i <= 2; i++)
	{
		faci_ball_position[i] = position[i];		//一定要loop才可以传进去,传入位置
		faci_ball_size[i] = size[i];
	}
	for (int i = 0; i <= 3; i++)
	{
		faci_ball_color_ambient[i] = color_ambient[i];		//传入material
		faci_ball_color_diffuse[i] = color_diffuse[i];
		faci_ball_color_specular[i] = color_specular[i];
	}
	faci_ball_color_shine = color_shine;
	faci_ball_appear = appear;
}

faci_ball::faci_ball(int kind, float position[3], float size[3], int color, bool appear)		//用于贴图的重载
{
	faci_ball_kind = kind;
	for (int i = 0; i <= 2; i++)
	{
		faci_ball_position[i] = position[i];		//一定要loop才可以传进去,传入位置
		faci_ball_size[i] = size[i];
	}
	faci_ball_appear = appear;
	faci_ball_color = color;
}

void faci_ball::faci_ball_drawself()
{
	if (faci_ball_kind == 1)		//如果是幕，画矩形
	{
		glPushMatrix();

		//glScalef(faci_ball_size[0], faci_ball_size[1], faci_ball_size[2]);

		glTranslatef(faci_ball_position[0], faci_ball_position[1], faci_ball_position[2]);

		glMaterialfv(GL_FRONT, GL_AMBIENT, faci_ball_color_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, faci_ball_color_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, faci_ball_color_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, faci_ball_color_shine);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		for (int i = 0; i < 200; i++)
		{
			for (int j = 0; j < 200; j++)
			{
				glBegin(GL_QUADS);
				glVertex2f(-16.00 + 0.16*i, -9.00 + 0.09*j);
				glVertex2f(-16.00 + 0.16*i + 0.16, -9.00 + 0.09*j);
				glVertex2f(-16.00 + 0.16*i + 0.16, -9.00 + 0.09*j + 0.09);
				glVertex2f(-16.00 + 0.16*i, -9.00 + 0.09*j + 0.09);
				glEnd();
			}
		}
		glPopMatrix();
	}
	else if (faci_ball_kind == 2)		//如果是mouse，画球
	{
		glPushMatrix();
		glTranslatef(faci_ball_position[0], faci_ball_position[1], faci_ball_position[2]);
		glMaterialfv(GL_FRONT, GL_AMBIENT, faci_ball_color_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, faci_ball_color_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, faci_ball_color_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, faci_ball_color_shine);
		glutSolidSphere(faci_ball_size[0], 10, 10);
		glPopMatrix();
	}
	else if (faci_ball_kind == 3)
	{
		if (faci_ball_appear == true){
			glPushMatrix();
			glTranslatef(faci_ball_position[0], faci_ball_position[1], faci_ball_position[2]);
			glScalef(faci_ball_texture_scale, faci_ball_texture_scale, 0.0);

			glBindTexture(GL_TEXTURE_2D, faci_ball_ImageIDs[faci_ball_color]);
			glBegin(GL_POLYGON);
			glNormal3f(0.0, 0.0, 1.0);		//正面
			glTexCoord2f(0.0, 1.0);
			glVertex3f(-faci_ball_size[0] / 2.0, faci_ball_size[1] / 2.0, 0.0);

			glTexCoord2f(0.0, 0.0);
			glVertex3f(-faci_ball_size[0] / 2.0, -faci_ball_size[1] / 2.0, 0.0);

			glTexCoord2f(1.0, 0.0);
			glVertex3f(faci_ball_size[0] / 2.0, -faci_ball_size[1] / 2.0, 0.0);

			glTexCoord2f(1.0, 1.0);
			glVertex3f(faci_ball_size[0] / 2.0, faci_ball_size[1] / 2.0, 0.0);
			glEnd();

			glPopMatrix();
		}
	}
}

void faci_ball::faci_ball_emerge()
{
	if (faci_ball_appear == true && faci_ball_texture_scale < 1.0)
	{
		faci_ball_texture_scale += -0.2 * faci_ball_texture_scale + 0.2;
	}
}

void faci_ball::faci_ball_turnbig()			//方块变大
{
	if (faci_ball_texture_scale < 1.2)
	{
		faci_ball_texture_scale += -0.2 * faci_ball_texture_scale + 0.24;
		faci_ball_position[2] = 2.0;
	}
}

void faci_ball::faci_ball_turnsmall()			//方块变小
{
	if (faci_ball_texture_scale > 1.0)
	{
		faci_ball_texture_scale -= 0.2 * faci_ball_texture_scale - 0.2;
		faci_ball_position[2] = 1.0;
	}
}