#include "facilities.h"

using namespace std;
#pragma comment(lib, "glaux")

AUX_RGBImageRec *UI_fac_Images[30];
GLuint UI_fac_ImageIDs[30];
char *UI_fac_pictures[30] = {
	"pictures\\back9.bmp",
	"pictures\\11.bmp",
	"pictures\\12.bmp",
	"pictures\\13.bmp",
	"pictures\\14.bmp",
	"pictures\\15.bmp",
	"pictures\\21.bmp",
	"pictures\\22.bmp",
	"pictures\\23.bmp",
	"pictures\\24.bmp",
	"pictures\\endlesspuz.bmp",
	"pictures\\endlessball.bmp",
	"pictures\\33.bmp",
	"pictures\\34.bmp",
	"pictures\\35.bmp",
	"pictures\\start164.bmp",
	"pictures\\00.bmp",
	"pictures\\cross.bmp",	//17

	"pictures\\doc\\11s.bmp",	//18
	"pictures\\doc\\12s.bmp",	//19
	"pictures\\doc\\14s.bmp",
	"pictures\\doc\\15s.bmp",
	"pictures\\doc\\22s.bmp",
	"pictures\\doc\\23s.bmp",
	"pictures\\doc\\24s.bmp",
	"pictures\\doc\\33s.bmp",
	"pictures\\doc\\34s.bmp",
	"pictures\\doc\\35s.bmp",	//27

	"pictures\\out.bmp",	//28
	"pictures\\tuli.bmp"	//29
};

void facilities::settexture()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glEnable(GL_TEXTURE_2D);
	
	glGenTextures(30, UI_fac_ImageIDs);
	for (int i = 0; i < 30; i++)
	{
		glBindTexture(GL_TEXTURE_2D, UI_fac_ImageIDs[i]);
		UI_fac_Images[i] = auxDIBImageLoadA(UI_fac_pictures[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, UI_fac_Images[i]->sizeX, UI_fac_Images[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, UI_fac_Images[i]->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}

	
	
}

facilities::facilities(int kind, int color, float position[3], float size[3], bool appear)
{
	UI_faci_kind = kind;		//cross = 2
	UI_faci_color = color;
	for (int i = 0; i <= 2; i++)
	{
		UI_faci_position[i] = position[i];		//一定要loop才可以传进去,传入位置
		UI_faci_size[i] = size[i];
	}
	UI_faci_appear = appear;
}	

void facilities::drawself()
{
	if (UI_faci_appear == true){
		glPushMatrix();

		glTranslatef(UI_faci_position[0], UI_faci_position[1], UI_faci_position[2]);			//画一个字帖
		glScalef(UI_faci_scale, UI_faci_scale, 0.0);

		glBindTexture(GL_TEXTURE_2D, UI_fac_ImageIDs[UI_faci_color]);
		glBegin(GL_POLYGON);
		glNormal3f(0.0, 0.0, 1.0);		//正面
		glTexCoord2f(0.0, 1.0);
		glVertex3f(-UI_faci_size[0] / 2.0, UI_faci_size[1] / 2.0, -1.0);

		glTexCoord2f(0.0, 0.0);
		glVertex3f(-UI_faci_size[0] / 2.0, -UI_faci_size[1] / 2.0, -1.0);

		glTexCoord2f(1.0, 0.0);
		glVertex3f(UI_faci_size[0] / 2.0, -UI_faci_size[1] / 2.0, -1.0);

		glTexCoord2f(1.0, 1.0);
		glVertex3f(UI_faci_size[0] / 2.0, UI_faci_size[1] / 2.0, -1.0);
		glEnd();

		glPopMatrix();
	}
}

void facilities::turn_big()			//方块变大
{
	if (UI_faci_kind == 1)
	{
		if (UI_faci_scale < 1.1)
		{
			UI_faci_scale += -0.04 * UI_faci_scale + 0.044;
			UI_faci_position[2] = 2.0;
		}
	}
	else{
		if (UI_faci_scale < 1.2)
		{
			UI_faci_scale += -0.04 * UI_faci_scale + 0.048;
			UI_faci_position[2] = 2.0;
		}
	}
}

void facilities::turn_small()			//方块变小
{
	if (UI_faci_scale > 1.0)
	{
		UI_faci_scale -= 0.04 * UI_faci_scale - 0.04;
		UI_faci_position[2] = 1.0;
	}
}