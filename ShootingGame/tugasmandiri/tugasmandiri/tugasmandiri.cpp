#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/GL.h>
#include <corona.h>
#include <Windows.h>

int width = 400, height = 480, shipPos = 8, shipLocX = 184, shipLocY = 30, bgIndex = 0;
float shipWidth = 32, shipHeight = 32;
GLuint texture[3];

void loadTexture(char filename[], int pos) {
	corona::Image *image = corona::OpenImage(filename);

	glGenTextures(1, &texture[pos]);
	glBindTexture(GL_TEXTURE_2D, texture[pos]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image->getPixels());
}

void displayText(
	float x,
	float y,
	float z,
	void *font,
	char *string,
	float r,
	float g,
	float b) {

	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3f(r, g, b);
	char *c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
	glColor3f(1.0f, 1.0f, 1.0f);
}

void display() {
	if (bgIndex == 0) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		loadTexture("Assets/bgMenu.png", 0);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[0]);

		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3i(0, 0, 0);
		glTexCoord2f(1.0f, 1.0f); glVertex3i(width, 0, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex3i(width, height, 0);
		glTexCoord2f(0.0f, 0.0f); glVertex3i(0, height, 0);
		glEnd();

		displayText(150, 435, 0, GLUT_BITMAP_HELVETICA_18, "DDemonstar", 255, 255, 255);
		displayText(0, 5, 0, GLUT_BITMAP_HELVETICA_12, "High Score : 200", 255, 255, 255);
		displayText(310, 5, 0, GLUT_BITMAP_HELVETICA_12, "Sound(M) : On", 255, 255, 255);
		displayText(150, 70, 0, GLUT_BITMAP_HELVETICA_12, "Back to Main Menu", 255, 255, 255);
		displayText(50, 90, 0, GLUT_BITMAP_HELVETICA_12, "How to Play : Press[W/A/S/D] Key to Move, and [ESC] to"
			, 255, 255, 255);
		displayText(100, 110, 0, GLUT_BITMAP_HELVETICA_18, "Press Enter To Start Game"
			, 255, 255, 255);
	}
	else if (bgIndex == 1) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		loadTexture("Assets/bg.png", 1);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[1]);

		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3i(0, 0, 0);
		glTexCoord2f(1.0f, 1.0f); glVertex3i(width, 0, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex3i(width, height, 0);
		glTexCoord2f(0.0f, 0.0f); glVertex3i(0, height, 0);
		glEnd();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		loadTexture("Assets/ships.png", 2);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[2]);

		glBegin(GL_QUADS);
		glTexCoord2f(shipWidth * shipPos / 544, shipHeight / 64);			glVertex3i(shipLocX, shipLocY, 0);
		glTexCoord2f(shipWidth * (shipPos + 1) / 544, shipHeight / 64);		glVertex3i(shipLocX + 32, shipLocY, 0);
		glTexCoord2f(shipWidth * (shipPos + 1) / 544, 0);					glVertex3i(shipLocX + 32, shipLocY + 32, 0);
		glTexCoord2f(shipWidth * shipPos / 544, 0);							glVertex3i(shipLocX, shipLocY + 32, 0);
		glEnd();

		displayText(180, 5, 0, GLUT_BITMAP_HELVETICA_18, "Wave : 1    Lv : 1    HP : 15"
			, 255, 255, 255);
	}
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
		if (key == 'a' && shipLocX > 0) {
			if (shipPos != 0){
				shipPos--;
			}
			shipLocX -= 10;
		}
		else if (key == 'd' && shipLocX < 368) {
			if (shipPos != 16) {
				shipPos++;
			}
			shipLocX += 10;
		}
		else if (key == 'w' && shipLocY < 448) {
			shipPos = 8;
			shipLocY += 10;
		}
		else if (key == 's' && shipLocY > 0) {
			shipPos = 8;
			shipLocY -= 10;
		}
		if (key == 13)
			bgIndex = 1;
		if (key == 27)
			bgIndex = 0;
		glutPostRedisplay();
}


int main(int argc, char **args) {
	glutInit(&argc, args);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutCreateWindow("DDemonstar");

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glMatrixMode(GL_PROJECTION);
	glOrtho(0, width, 0, height, 0, -1);
	glMatrixMode(GL_MODELVIEW);

	glutMainLoop();
}