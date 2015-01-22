#include "piece.h"
using namespace std;
#pragma comment(lib, "glaux")

AUX_RGBImageRec *piece_Images[201];
GLuint piece_ImageIDs[201];
char *piece_pictures[201] = {
	"pictures\\AP.bmp",	//0
	"pictures\\BP.bmp",
	"pictures\\CP.bmp",
	"pictures\\DP.bmp",
	"pictures\\EP.bmp",
	"pictures\\FP.bmp",
	"pictures\\GP.bmp",
	"pictures\\HP.bmp",
	"pictures\\IP.bmp",	//8

	"pictures\\A\\A1.bmp",		//9
	"pictures\\A\\A2.bmp",
	"pictures\\A\\A3.bmp",
	"pictures\\A\\A4.bmp",
	"pictures\\A\\A5.bmp",
	"pictures\\A\\A6.bmp",
	"pictures\\A\\A7.bmp",
	"pictures\\A\\A8.bmp",
	"pictures\\A\\A9.bmp",
	"pictures\\A\\A10.bmp",
	"pictures\\A\\A11.bmp",
	"pictures\\A\\A12.bmp",	//20

	"pictures\\B\\B1.bmp",		//21
	"pictures\\B\\B2.bmp",
	"pictures\\B\\B3.bmp",
	"pictures\\B\\B4.bmp",
	"pictures\\B\\B5.bmp",
	"pictures\\B\\B6.bmp",
	"pictures\\B\\B7.bmp",
	"pictures\\B\\B8.bmp",
	"pictures\\B\\B9.bmp",
	"pictures\\B\\B10.bmp",
	"pictures\\B\\B11.bmp",
	"pictures\\B\\B12.bmp",		//32

	"pictures\\C\\C1.bmp",			//33
	"pictures\\C\\C2.bmp",
	"pictures\\C\\C3.bmp",
	"pictures\\C\\C4.bmp",
	"pictures\\C\\C5.bmp",
	"pictures\\C\\C6.bmp",
	"pictures\\C\\C7.bmp",
	"pictures\\C\\C8.bmp",
	"pictures\\C\\C9.bmp",
	"pictures\\C\\C10.bmp",
	"pictures\\C\\C11.bmp",
	"pictures\\C\\C12.bmp",		//44

	"pictures\\D\\D1.bmp",		//45
	"pictures\\D\\D2.bmp",
	"pictures\\D\\D3.bmp",
	"pictures\\D\\D4.bmp",
	"pictures\\D\\D5.bmp",
	"pictures\\D\\D6.bmp",
	"pictures\\D\\D7.bmp",
	"pictures\\D\\D8.bmp",
	"pictures\\D\\D9.bmp",
	"pictures\\D\\D10.bmp",
	"pictures\\D\\D11.bmp",
	"pictures\\D\\D12.bmp",		//56

	"pictures\\E\\E1.bmp",			//57
	"pictures\\E\\E2.bmp",
	"pictures\\E\\E3.bmp",
	"pictures\\E\\E4.bmp",
	"pictures\\E\\E5.bmp",
	"pictures\\E\\E6.bmp",
	"pictures\\E\\E7.bmp",
	"pictures\\E\\E8.bmp",
	"pictures\\E\\E9.bmp",
	"pictures\\E\\E10.bmp",
	"pictures\\E\\E11.bmp",
	"pictures\\E\\E12.bmp",	//68

	"pictures\\F\\F1.bmp",		//69
	"pictures\\F\\F2.bmp",
	"pictures\\F\\F3.bmp",
	"pictures\\F\\F4.bmp",
	"pictures\\F\\F5.bmp",
	"pictures\\F\\F6.bmp",
	"pictures\\F\\F7.bmp",
	"pictures\\F\\F8.bmp",
	"pictures\\F\\F9.bmp",
	"pictures\\F\\F10.bmp",
	"pictures\\F\\F11.bmp",
	"pictures\\F\\F12.bmp",	//80

	"pictures\\G\\G1.bmp",		//81
	"pictures\\G\\G2.bmp",
	"pictures\\G\\G3.bmp",
	"pictures\\G\\G4.bmp",
	"pictures\\G\\G5.bmp",
	"pictures\\G\\G6.bmp",
	"pictures\\G\\G7.bmp",
	"pictures\\G\\G8.bmp",
	"pictures\\G\\G9.bmp",
	"pictures\\G\\G10.bmp",
	"pictures\\G\\G11.bmp",
	"pictures\\G\\G12.bmp",	//92

	"pictures\\H\\H1.bmp",		//93
	"pictures\\H\\H2.bmp",
	"pictures\\H\\H3.bmp",
	"pictures\\H\\H4.bmp",
	"pictures\\H\\H5.bmp",
	"pictures\\H\\H6.bmp",
	"pictures\\H\\H7.bmp",
	"pictures\\H\\H8.bmp",
	"pictures\\H\\H9.bmp",
	"pictures\\H\\H10.bmp",
	"pictures\\H\\H11.bmp",
	"pictures\\H\\H12.bmp",	//104

	"pictures\\I\\I1.bmp",		//105
	"pictures\\I\\I2.bmp",
	"pictures\\I\\I3.bmp",
	"pictures\\I\\I4.bmp",
	"pictures\\I\\I5.bmp",
	"pictures\\I\\I6.bmp",
	"pictures\\I\\I7.bmp",
	"pictures\\I\\I8.bmp",
	"pictures\\I\\I9.bmp",
	"pictures\\I\\I10.bmp",
	"pictures\\I\\I11.bmp",
	"pictures\\I\\I12.bmp",//116

	"pictures\\wood.bmp",	//117
	"pictures\\puzgame\\back.bmp",//118
	"pictures\\puzgame\\refresh.bmp",//119
	"pictures\\puzgame\\next.bmp",	//120
	"pictures\\puzgame\\nextno.bmp",//121
	"pictures\\puzgame\\tu.bmp",//122
	"pictures\\puzgame\\mouse.bmp",//123
	"pictures\\puzgame\\home.bmp",//124

	"pictures\\AL.bmp",	//125
	"pictures\\BL.bmp",
	"pictures\\CL.bmp",
	"pictures\\DL.bmp",
	"pictures\\EL.bmp",
	"pictures\\FL.bmp",
	"pictures\\GL.bmp",
	"pictures\\HL.bmp",
	"pictures\\IL.bmp",	//133

	"pictures\\Q.bmp",	//134
	"pictures\\R.bmp",
	"pictures\\S.bmp",
	"pictures\\T.bmp",	//137

	"pictures\\Q\\Q1.bmp",	//138
	"pictures\\Q\\Q2.bmp",
	"pictures\\Q\\Q3.bmp",
	"pictures\\Q\\Q4.bmp",
	"pictures\\Q\\Q5.bmp",
	"pictures\\Q\\Q6.bmp",
	"pictures\\Q\\Q7.bmp",
	"pictures\\Q\\Q8.bmp",
	"pictures\\Q\\Q9.bmp",
	"pictures\\Q\\Q10.bmp",
	"pictures\\Q\\Q11.bmp",
	"pictures\\Q\\Q12.bmp",	//149

	"pictures\\R\\R1.bmp",	//150
	"pictures\\R\\R2.bmp",
	"pictures\\R\\R3.bmp",
	"pictures\\R\\R4.bmp",
	"pictures\\R\\R5.bmp",
	"pictures\\R\\R6.bmp",
	"pictures\\R\\R7.bmp",
	"pictures\\R\\R8.bmp",
	"pictures\\R\\R9.bmp",
	"pictures\\R\\R10.bmp",
	"pictures\\R\\R11.bmp",
	"pictures\\R\\R12.bmp",	//161

	"pictures\\S\\S1.bmp",		//162
	"pictures\\S\\S2.bmp",
	"pictures\\S\\S3.bmp",
	"pictures\\S\\S4.bmp",
	"pictures\\S\\S5.bmp",
	"pictures\\S\\S6.bmp",
	"pictures\\S\\S7.bmp",
	"pictures\\S\\S8.bmp",
	"pictures\\S\\S9.bmp",
	"pictures\\S\\S10.bmp",
	"pictures\\S\\S11.bmp",
	"pictures\\S\\S12.bmp",	//173

	"pictures\\T\\T1.bmp",	//174
	"pictures\\T\\T2.bmp",
	"pictures\\T\\T3.bmp",
	"pictures\\T\\T4.bmp",
	"pictures\\T\\T5.bmp",
	"pictures\\T\\T6.bmp",
	"pictures\\T\\T7.bmp",
	"pictures\\T\\T8.bmp",
	"pictures\\T\\T9.bmp",
	"pictures\\T\\T10.bmp",
	"pictures\\T\\T11.bmp",
	"pictures\\T\\T12.bmp",	//185

	"pictures\\puzgame\\stage1.bmp", //186
	"pictures\\puzgame\\stage2.bmp",	//187
	"pictures\\puzgame\\stage3.bmp",	//188
	"pictures\\puzgame\\mix.bmp",	//189
	"pictures\\puzgame\\stage5.bmp",	//190
	"pictures\\wood2.bmp",	//191

	"pictures\\puzgame\\stage1on.bmp", //192
	"pictures\\puzgame\\stage2on.bmp",	//193
	"pictures\\puzgame\\stage3on.bmp",	//194
	"pictures\\puzgame\\mixon.bmp",	//195
	"pictures\\puzgame\\stage5on.bmp",	//196

	"pictures\\puzgame\\stage1ppt.bmp",	//197
	"pictures\\puzgame\\stage2ppt.bmp",	//198
	"pictures\\puzgame\\stage3ppt.bmp",	//199
	"pictures\\puzgame\\stage4ppt.bmp"		//200
};

void piece::piece_settexture()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(201, piece_ImageIDs);
	for (int i = 0; i < 201; i++)
	{
		glBindTexture(GL_TEXTURE_2D, piece_ImageIDs[i]);
		piece_Images[i] = auxDIBImageLoadA(piece_pictures[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, piece_Images[i]->sizeX, piece_Images[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, piece_Images[i]->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	}
	glEnable(GL_TEXTURE_2D);
}

piece::piece(int kind, float position[3], float size[3], float angle, int color, int scolor, bool appear, bool mouseon, bool mouserotate)
{
	for (int i = 0; i <= 2; i++)
	{
		piece_position[i] = position[i];		//一定要loop才可以传进去,传入位置
		piece_size[i] = size[i];
	}
	piece_kind = kind;
	piece_angle = angle;
	piece_color = color;
	side_color = scolor;
	piece_appear = appear;
	piece_mouseon = mouseon;
	piece_rotateon = mouserotate;
	piece_scale = 1.0;
}

void piece::piece_drawself()
{
	if (piece_kind == 0)	//画block
	{
		if (piece_appear == true)		//如果显示就画
		{
			glPushMatrix();
			
			glTranslatef(piece_position[0], piece_position[1], piece_position[2]);		//平移到位
			
			glRotatef(piece_angle, 0.0, 0.0, 1.0);
			
			glDisable(GL_TEXTURE_2D);
			glColor3f(0.9, 0.9, 0.0);
			glLineWidth(2);
			if (piece_axis == true)		//画自身坐标系
			{
				glBegin(GL_LINES);
				glVertex3f(-4.0, 0.0, 0.01);
				glVertex3f(4.0, 0.0, 0.01);
				glEnd();

				glBegin(GL_LINES);
				glVertex3f(0.0, -4.0, 0.01);
				glVertex3f(0.0, 4.0, 0.01);
				glEnd();
			}

			glColor3f(0.0, 0.1, 1.0);
			glRotatef(piece_angle2, 0.0, 0.0, 1.0);		//中心时旋转

			if (piece_rotateon == true)		//如果在旋转区，就画圆圈
			{
				glPushMatrix();
				glTranslatef(0.0, 0.0, 0.01);
				glBegin(GL_LINE_LOOP);
				int n = 50;
				for (int i = 0; i < n; ++i)
					glVertex2f(2.828 *cos(2 * 3.14159265354 / n*i), 2.828*sin(2 * 3.14159265354 / n*i));
				glEnd();
				glPopMatrix();

				glColor3f(0.9, 0.9, 0.0);
				

				if (piece_axis == true)
				{
					glPushMatrix();

					glRotatef(-piece_angle2, 0.0, 0.0, 1.0);
					glBegin(GL_LINES);
					glVertex3f(-4.0, 0.0, 0.01);
					glVertex3f(4.0, 0.0, 0.01);
					glEnd();

					glBegin(GL_LINES);
					glVertex3f(0.0, -4.0, 0.01);
					glVertex3f(0.0, 4.0, 0.01);
					glEnd();
					glPopMatrix();
				}
			}
			if (piece_mouseon == true)		//如果鼠标在位移区，就画叉
			{
				glColor3f(0.0, 0.1, 1.0);
				glBegin(GL_LINES);
				glVertex3f(-2.0, -2.0, 0.01);
				glVertex3f(2.0, 2.0, 0.01);
				glEnd();

				glBegin(GL_LINES);
				glVertex3f(-2.0, 2.0, 0.01);
				glVertex3f(2.0, -2.0, 0.01);
				glEnd();
			}

			glEnable(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, piece_ImageIDs[piece_color]);
			glBegin(GL_POLYGON);
			glNormal3f(0.0, 0.0, 1.0);		//正面
			glTexCoord2f(0.0, 1.0);
			glVertex3f(-2.0, 2.0, 0.0);

			glTexCoord2f(0.0, 0.0);
			glVertex3f(-2.0, -2.0, 0.0);

			glTexCoord2f(1.0, 0.0);
			glVertex3f(2.0, -2.0, 0.0);

			glTexCoord2f(1.0, 1.0);
			glVertex3f(2.0, 2.0, 0.0);
			glEnd();

			glColor4f(0.0, 0.3, 0.0, 1.0);

			glBindTexture(GL_TEXTURE_2D, piece_ImageIDs[side_color]);
			glBegin(GL_POLYGON);			//背面
			glTexCoord2f(0.0, 1.0);
			glVertex3f(2.0, 2.0, -2.0);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(-2.0, 2.0, -2.0);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(-2.0, -2.0, -2.0);
			glTexCoord2f(1.0, 1.0);
			glVertex3f(2.0, -2.0, -2.0);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, piece_ImageIDs[side_color]);
			glBegin(GL_POLYGON);			//右侧面
			glTexCoord2f(0.0, 1.0);
			glVertex3f(2.0, 2.0, 0.0);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(2.0, 2.0, -2.0);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(2.0, -2.0, -2.0);
			glTexCoord2f(1.0, 1.0);
			glVertex3f(2.0, -2.0, 0.0);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, piece_ImageIDs[side_color]);
			glBegin(GL_POLYGON);			//左侧面
			glTexCoord2f(0.0, 1.0);
			glVertex3f(-2.0, 2.0, 0.0);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(-2.0, 2.0, -2.0);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(-2.0, -2.0, -2.0);
			glTexCoord2f(1.0, 1.0);
			glVertex3f(-2.0, -2.0, 0.0);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, piece_ImageIDs[side_color]);
			glBegin(GL_POLYGON);			//上侧面
			glTexCoord2f(0.0, 1.0);
			glVertex3f(2.0, 2.0, 0.0);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(2.0, 2.0, -2.0);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(-2.0, 2.0, -2.0);
			glTexCoord2f(1.0, 1.0);
			glVertex3f(-2.0, 2.0, 0.0);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, piece_ImageIDs[side_color]);
			glBegin(GL_POLYGON);			//下侧面
			glTexCoord2f(0.0, 1.0);
			glVertex3f(2.0, -2.0, 0.0);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(2.0, -2.0, -2.0);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(-2.0, -2.0, -2.0);
			glTexCoord2f(1.0, 1.0);
			glVertex3f(-2.0, -2.0, 0.0);
			glEnd();

			
			glPopMatrix();
		}
	}
	else if (piece_kind == 1){		//画大圆圈
		if (piece_appear == true)
		{
			glPushMatrix();
			glTranslatef(0.0, 0.0, 0.01);
			glColor3f(0.4, 0.4, 0.4);
			glBegin(GL_LINE_LOOP);
			int n = 50;
			float r = piece_position[0];   //用这个代存半径
			for (int i = 0; i < n; ++i)
				glVertex2f(r *cos(2 * 3.14159265354 / n*i), r *sin(2 * 3.14159265354 / n*i));
			glEnd();
			glPopMatrix();
		}
	}
	else if (piece_kind = 2){		//画buttons
		if (piece_appear == true){
			glPushMatrix();

			glTranslatef(piece_position[0], piece_position[1], piece_position[2]);			//画一个字帖
			glScalef(piece_scale, piece_scale, 0.0);

			glBindTexture(GL_TEXTURE_2D, piece_ImageIDs[piece_color]);
			glBegin(GL_POLYGON);
			glNormal3f(0.0, 0.0, 1.0);		//正面
			glTexCoord2f(0.0, 1.0);
			glVertex3f(-piece_size[0] / 2.0, piece_size[1] / 2.0, -1.0);

			glTexCoord2f(0.0, 0.0);
			glVertex3f(-piece_size[0] / 2.0, -piece_size[1] / 2.0, -1.0);

			glTexCoord2f(1.0, 0.0);
			glVertex3f(piece_size[0] / 2.0, -piece_size[1] / 2.0, -1.0);

			glTexCoord2f(1.0, 1.0);
			glVertex3f(piece_size[0] / 2.0, piece_size[1] / 2.0, -1.0);
			glEnd();

			glPopMatrix();
		}
	}
}

void piece::piece_turn_big()			//方块变大
{
	if (piece_scale < 1.1)
	{
		piece_scale += -0.04 * piece_scale + 0.044;
		piece_position[2] = 0.11;
	}
}

void piece::piece_turn_small()			//方块变小
{
	if (piece_scale > 1.0)
	{
		piece_scale -= 0.04 * piece_scale - 0.04;
		piece_position[2] = 0.1;
	}
}