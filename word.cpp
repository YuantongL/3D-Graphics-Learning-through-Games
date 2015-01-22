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
		glColor4f(word_color[0], word_color[1], word_color[2], word_color[3]);     //设置字体颜色  
		glRasterPos2f(word_pos[0], word_pos[1]);  //起始位置
		selectFont(word_size, ANSI_CHARSET, word_font);
		drawString(word_disp);
	}
}


void word::drawString(char* str) //屏幕显示字体  
{
	if (isFirstCall) {
		isFirstCall = 0;
		// 申请MAX_CHAR个连续的显示列表编号  
		lists = glGenLists(MAX_CHAR);
		// 把每个字符的绘制命令都装到对应的显示列表中  
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	// 调用每个字符对应的显示列表，绘制每个字符  
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