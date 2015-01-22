#include "word.h"

#define MAX_CHAR 128 

word::word(float pos[3], bool appear, int size, float color[4], char *disp, char *font)
{
	for (int i = 0; i < 3; i++)
	{
		word_pos[i] = pos[i];
	}

	for (int i = 0; i < 3; i++)
	{
		word_color[i] = color[i];
	}

	word_disp = disp;
	word_font = font;
	word_size = size;
	word_appear = appear;
}

void word::drawself()
{
	if (word_appear == true)
	{
		glColor4f(word_color[0], word_color[1], word_color[2], word_color[3]);     //����������ɫ  
		glRasterPos2f(word_pos[0], word_pos[1]);  //��ʼλ��
		selectFont(word_size, ANSI_CHARSET, word_font);
		drawString(word_disp);
	}
}


void word::drawString(char* str) //��Ļ��ʾ����  
{
	if (isFirstCall) {
		isFirstCall = 0;
		// ����MAX_CHAR����������ʾ�б���  
		lists = glGenLists(MAX_CHAR);
		// ��ÿ���ַ��Ļ������װ����Ӧ����ʾ�б���  
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	// ����ÿ���ַ���Ӧ����ʾ�б�����ÿ���ַ�  
	for (; *str != '\0'; ++str) {
		glCallList(lists + *str);
	}
}


void word::selectFont(int size, int charset, char* face) {
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
		charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
}