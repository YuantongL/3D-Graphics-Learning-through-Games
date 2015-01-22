#pragma once
#include <windows.h>  
#include <GL/glut.h>  
#include <stdlib.h> 

class word
{
public:
	word();
	word(float pos[3], bool appear, int size, float color[4], char *disp, char *font);
	void drawself();
	void drawString(char* str);
	void selectFont(int size, int charset, char* face);

	char *word_disp;
	char *word_font;

	float word_color[4];
	float word_pos[3];
	int word_size;

	bool word_appear;

	int isFirstCall = 1;
	GLuint lists;
};

