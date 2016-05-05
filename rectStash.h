#ifndef RECTSTASH_H
#define RECTSTASH_H
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <ctime>
#include <random>
#include <string>
#include "app_window.h"
#include <mmsystem.h>
#include <Windows.h>
#include "Ticker.h" // Brian's millisecond counter
#include "C:\Users\Amar\Desktop\Final Project\freeglutapp\Simple OpenGL Image Library\lib\SOIL.h"

using namespace std;

class Vec {

public:


	float x;
	float y;

	Vec() {

		x = 0;
		y = 0;

	}

	Vec(float x, float y) {

		this->x = x;
		this->y = y;

	}

	void add(Vec v) {

		x += v.x;
		y += v.y;

	}

	void print() {

		cout << "(" << x << ", " << y << ")";
		cout << endl;

	}

};

class GrRect {

public:

	float _markx;
	float _marky;
	float upleftX;
	float upleftY;
	float width;
	float height;
	float zValue;
	float r;
	float g;
	float b;
	bool select;
	bool focus;
	bool noBar;
	vector <Vec> myPoints;
	bool displayBrick;

	GrRect() {
		select = false;
		focus = false;
		noBar = false;

	}

	GrRect(float upleftX, float upleftY, float width, float height) {
		_markx = 0;
		_marky = 0;
		select = false;
		focus = false;
		noBar = false;
		this->upleftX = upleftX;
		this->upleftY = upleftY;
		this->width = width;
		this->height = height;

	}


	GrRect(float upleftX, float upleftY, float width, float height, float r, float g, float b) {
		_markx = 0;
		_marky = 0;
		select = false;
		focus = false;
		noBar = false;
		this->upleftX = upleftX;
		this->upleftY = upleftY;
		this->width = width;
		this->height = height;
		this->r = r;
		this->g = g;
		this->b = b;

	}
	int contains(Vec v) {

		int xCheck = 0;
		int yCheck = 0;

		if ((v.x > upleftX) && (v.x < upleftX + width)) {

			xCheck = 1;

		}

		if ((v.y < upleftY) && (v.y > upleftY - height)) {

			yCheck = 1;

		}

		if ((xCheck == 1) && (yCheck == 1)) {

			return 1;

		}

		return 0;


	}

	void draw()
	{

		glColor3f(r, g, b);

		if (focus) {

			glColor3f(0.0, 0.0, 1.0);

		}

		glBegin(GL_POLYGON);
		glVertex3d(upleftX, upleftY, zValue);
		glVertex3d(upleftX + width, upleftY, zValue);
		glVertex3d(upleftX + width, upleftY - height, zValue);
		glVertex3d(upleftX, upleftY - height, zValue);
		glEnd();

		if (!noBar) {

			glColor3f(0.8, 0.8, 0.8);
			glBegin(GL_POLYGON);
			glVertex3d(upleftX, upleftY, zValue - 0.000001);
			glVertex3d(upleftX + width, upleftY, zValue - 0.000001);
			glVertex3d(upleftX + width, upleftY - 0.05, zValue - 0.000001);
			glVertex3d(upleftX, upleftY - 0.05, zValue - 0.000001);
			glEnd();

		}

		if (select == true) {

			glColor3d(1.0, 1.0, 1.0);
			glBegin(GL_LINES);
			glVertex3d(upleftX, upleftY, zValue - 0.000002);
			glVertex3d(upleftX + width, upleftY, zValue - 0.000002);
			glVertex3d(upleftX + width, upleftY, zValue - 0.000002);
			glVertex3d(upleftX + width, upleftY - height, zValue - 0.000002);
			glVertex3d(upleftX + width, upleftY - height, zValue - 0.000002);
			glVertex3d(upleftX, upleftY - height, zValue - 0.000002);
			glVertex3d(upleftX, upleftY - height, zValue - 0.000002);
			glVertex3d(upleftX, upleftY, zValue - 0.000002);
			glEnd();

		}

	}

	void draw(GLuint rect)
	{

		glBindTexture(GL_TEXTURE_2D, rect);

		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);

		glColor3f(1, 1, 1);

		glTexCoord3f(0.0, 0.0, zValue - 0.000001);
		glVertex3f(upleftX, upleftY - height, zValue - 0.000001);
		glTexCoord3f(1.0, 0, zValue - 0.000001);
		glVertex3f(upleftX + width, upleftY - height, zValue - 0.000001);
		glTexCoord3f(1.0, 1.0, zValue - 0.000001);
		glVertex3f(upleftX + width, upleftY, zValue - 0.000001);
		glTexCoord3f(0.0, 1.0, zValue - 0.000001);
		glVertex3f(upleftX, upleftY, zValue - 0.000001);

		glEnd();
		glDisable(GL_TEXTURE_2D);

	}

};

class mainMenu {
public:

	vector <GrRect> myGameRects;
	char* currentTime;
	char coinCount;
	char gameCount;
	char attemptCount;
	int difficultly;
	bool notPlaying;
	GrRect retry;
	GLuint bg;
	bool notPlayed;

	mainMenu() {

		coinCount = '1';
		gameCount = '0';
		attemptCount = '0';
		difficultly = 0;
		notPlaying = true;
		notPlayed = true;

		GrRect tempRect;

		tempRect.width = 0.4;
		tempRect.height = 0.4;
		tempRect.r = 0.15;
		tempRect.g = 0.15;
		tempRect.b = 0.15;
		tempRect.zValue = 0.99;
		tempRect.select = true;

		tempRect.upleftX = -0.9;
		tempRect.upleftY = 0.6;

		myGameRects.push_back(tempRect);

		tempRect.upleftX = -0.45;
		tempRect.upleftY = 0.1;

		myGameRects.push_back(tempRect);

		tempRect.upleftX = 0.0;
		tempRect.upleftY = 0.6;

		myGameRects.push_back(tempRect);

		tempRect.upleftX = 0.45;
		tempRect.upleftY = 0.1;

		myGameRects.push_back(tempRect);

		retry.upleftX = -0.2;
		retry.upleftY = -0.725;
		retry.width = 0.3;
		retry.height = 0.2;
		retry.zValue = 0.99;
		retry.r = 1.0;
		retry.g = 0.0;
		retry.b = 0.0;
		retry.noBar = true;	// Used to not draw the bar on the retry rectangle
		retry.select = true;

	}

	 void draw() {

		 if (notPlayed) {

			 bg = SOIL_load_OGL_texture(
				 "img1.png",
				 SOIL_LOAD_AUTO,
				 SOIL_CREATE_NEW_ID,
				 SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
			 );

			 notPlayed = false;

		 }

		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glColor3f(1, 1, 1);
		glTexCoord3f(0.0, 0.0, 0.999);
		glVertex3f(-1.0, -0.4, 0.999);
		glTexCoord3f(1.0, 0, 0.999);
		glVertex3f(1.0, -0.4, 0.999);
		glTexCoord3f(1.0, 1.0, 0.999);
		glVertex3f(1.0, 1.0, 0.999);
		glTexCoord3f(0.0, 1.0, 0.999);
		glVertex3f(-1.0, 1.0, 0.999);
		glEnd();
		glDisable(GL_TEXTURE_2D);

		for (unsigned int i = 0; i < myGameRects.size(); i++) {

			myGameRects[i].draw();

		}

		glColor3d(0.15, 0.15, 0.15);
		glBegin(GL_LINES);
		glVertex2d(-1.0, -0.4);
		glVertex2d(1.0, -0.4);
		glEnd();

		glColor3d(1.0, 1.0, 1.0);
		glRasterPos2f(-0.25, 0.82);
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)("Welcome to the"));

		glColor3d(1.0, 0.0, 0.0);
		glRasterPos2f(-0.375, 0.7);
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)("ARCADE"));

		glColor3d(0.0, 0.0, 1.0);
		glRasterPos2f(-0.025, 0.7);
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)("CARNIVAL!"));

		glColor3d(1.0, 1.0, 0.0);
		glRasterPos2f(-0.85, 0.4);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("Dodging the \n    Spikes"));

		glColor3d(1.0, 1.0, 0.0);
		glRasterPos2f(-0.34, -0.1);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("Sliding \n  Tiles"));

		glColor3d(1.0, 1.0, 0.0);
		glRasterPos2f(0.10, 0.41);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("  Brick \nBreaker"));

		glColor3d(1.0, 1.0, 0.0);
		glRasterPos2f(0.54, -0.1);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("   Alien \nInvaders"));

		glColor3d(1.0, 1.0, 1.0);
		glRasterPos2f(0.275, -0.975);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)(currentTime));

		glColor3d(1.0, 1.0, 0.0);
		glRasterPos2f(-0.975, -0.6);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("Coins Left:"));

		glColor3d(1.0, 0.0, 0.0);
		glRasterPos2f(-0.675, -0.6);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (const unsigned char)(coinCount));

		glColor3d(0.0, 1.0, 1.0);
		glRasterPos2f(-0.975, -0.75);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("Games Completed:"));

		glColor3d(1.0, 0.0, 0.0);
		glRasterPos2f(-0.46, -0.75);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (const unsigned char)(gameCount));

		glColor3d(1.0, 0.0, 1.0);
		glRasterPos2f(-0.975, -0.9);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("Attempts:"));

		glColor3d(1.0, 0.0, 0.0);
		glRasterPos2f(-0.7, -0.9);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (const unsigned char)(attemptCount));

		glColor3d(1.0, 1.0, 1.0);
		glRasterPos2f(-0.2, -0.5);
		glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)("(Click on the game to view it's difficultly)"));

		glColor3d(1.0, 0.0, 1.0);
		glRasterPos2f(-0.2, -0.65);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("Difficultly:"));

		if (difficultly == 1) {

			glColor3d(1.0, 0.0, 0.0);
			glRasterPos2f(0.1, -0.65);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("Demon"));

		}

		if (difficultly == 2) {

			glColor3d(0.0, 1.0, 0.0);
			glRasterPos2f(0.1, -0.65);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("Easy"));

		}

		if (difficultly == 3) {

			glColor3d(1.0, 1.0, 0.0);
			glRasterPos2f(0.1, -0.65);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("Medium"));

		}

		if (difficultly == 4) {

			glColor3d(1.0, 1.0, 0.0);
			glRasterPos2f(0.1, -0.65);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("Medium"));

		}

		if (coinCount == '0') {		// Game Over Screen

			if ((time(NULL) % 2) == 1) {

				glColor3d(1.0, 0.0, 0.0);

			}

			else {

				glColor3d(0.0, 1.0, 0.0);

			}

			glRasterPos2f(0.45, -0.8);
			glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)("GAME OVER"));

			retry.draw();
			glColor3d(0.0, 1.0, 0.0);
			glRasterPos2f(-0.13, -0.85);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("Retry?"));

		}

	}

};

class Game {

public:

	char coin;
	bool playCheck;
	time_t seconds;
	time_t startTime;
	time_t endTime;
	float msStart;	//Start Time in miliseconds
	float msEnd;	//End Time in miliseconds
	GLuint bg;

	Game() {

		coin = '0';
		playCheck = false;

	}

	virtual char play() {

		return coin;

	}

	virtual void click(double x, double y) // for mouse click events
	{
		return;
	}
	virtual void keyboard(char z) // for keyboard events
	{
		return;
	}
	virtual void motion(double x, double y) // for mouse move events
	{
		return;
	}
	virtual void leftKey(bool check) {
		return;
	}
	virtual void rightKey(bool check) {
		return;
	}
};

class Spike {

public:

	Vec cord1;
	Vec cord2;
	Vec cord3;
	float r;
	float g;
	float b;
	bool notInitialized;

	Spike() {



	}

	Spike(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b) {

		this->r = r;
		this->g = g;
		this->b = b;
		cord1.x = x1;
		cord1.y = y1;
		cord2.x = x2;
		cord2.y = y2;
		cord3.x = x3;
		cord3.y = y3;
		notInitialized = false;

	}

	Spike(string type, GrRect userRect, float r, float g, float b) {

		this->r = r;
		this->g = g;
		this->b = b;
		notInitialized = false;

		if (type == "left") {

			cord1.x = 1.0;
			cord1.y = userRect.upleftY - userRect.height / 2;
			cord2.x = 1.1;
			cord2.y = userRect.upleftY - userRect.height / 2 + 0.1;
			cord3.x = 1.1;
			cord3.y = userRect.upleftY - userRect.height / 2 - 0.1;

		}

		else if (type == "right") {

			cord1.x = -1.0;
			cord1.y = userRect.upleftY - userRect.height / 2;
			cord2.x = -1.1;
			cord2.y = userRect.upleftY - userRect.height / 2 + 0.1;
			cord3.x = -1.1;
			cord3.y = userRect.upleftY - userRect.height / 2 - 0.1;

		}

		else if (type == "up") {

			cord1.x = userRect.upleftX + userRect.width / 2;
			cord1.y = -1.0;
			cord2.x = userRect.upleftX + userRect.width / 2 - 0.1;
			cord2.y = -1.1;
			cord3.x = userRect.upleftX + userRect.width / 2 + 0.1;
			cord3.y = -1.1;

		}

		else if (type == "down") {

			cord1.x = userRect.upleftX + userRect.width / 2;
			cord1.y = 1.0;
			cord2.x = userRect.upleftX + userRect.width / 2 - 0.1;
			cord2.y = 1.1;
			cord3.x = userRect.upleftX + userRect.width / 2 + 0.1;
			cord3.y = 1.1;

		}

	}

};

class DodgingSpikes : public Game {

public:

	GrRect userRect;
	GrRect backgroundRect;
	float miliseconds;
	float frames;
	float beatFrames;
	int beatSwitch;
	int power1Check;
	int power2Check;
	int power3Check;
	int power4Check;
	char lives;
	float immune;
	GLuint cube;

	Spike left1, right1;

	Spike diag3;

	Spike up1, down1;

	Spike diag4;

	Spike right2, up2;

	Spike diag1, diag2;

	Spike left2, down2;

	Spike left3, right3, up3, down3;

	Spike left4, diag5;

	Spike down4, diag6;

	Spike right4, right5, up4;

	Spike down5, up5, left5;

	Spike diag7, diag8, right6;

	Spike left6, right7, up6, down6;

	Spike left7, right8, up7, down7;

	Spike left8, right9, up8, down8;

	Spike left9, right10, up9,down9;

	Spike left10, right11, up10, down10;

	Spike diag9, diag10, diag11, diag12;

	Spike left11;

	Spike down11;

	Spike up11;

	Spike left12, down12;

	Spike right12, up12;

	Spike left13, right13;

	Spike up13, down13;

	Spike left14, right14, down14;

	Spike diag13, diag14;

	Spike up14, up15, up16, up17, up18, up19, up20, up22;

	Spike left15, down15;

	Spike right15, down16, up23;

	Spike left16, diag15;

	Spike left17, right17, down17;

	Spike up24, diag16;

	Spike left18, right18, down18;

	Spike left19, right19, up25, down19;

	Spike diag17, diag18, diag19, diag20;

	Spike left20;

	Spike down20, down21, down22, down23, down24, down25, down26, down27;

	Spike right20, right21, right22, right23, right24, right25, right26, right27;

	Spike up21, up26, up27, up28, up29, up30, up31, up32;

	Spike down28, down29, down30, down31, down32, down33, down34, down35;

	Spike down36;

	Spike left21, left22, left23, left24, left25, left26, left27, left28, left29, left30;

	Spike up33, up34, up35, up36, up37, up38, up39, up40, up41, up42;

	Spike up43, up44, up45, up46, up47, up48, up49, up50, up51, up52;

	Spike right28, right29, right30, right31, right32, right33, right34, right35, right36, right37;

	Spike down37, down38, down39, down40, down41, down42, down43, down44, down45, down46;

	DodgingSpikes() {

		coin = '1';

		userRect = GrRect(-0.95, -0.65, 0.3, 0.3);
		userRect.r = 0.0;
		userRect.g = 1.0;
		userRect.b = 1.0;
		userRect.zValue = 0.98;
		userRect.noBar = true;

		backgroundRect = GrRect(-1.0, 1.0, 2.0, 2.0);
		backgroundRect.r = 0.15;
		backgroundRect.g = 0.15;
		backgroundRect.b = 0.15;
		backgroundRect.zValue = 0.99;
		backgroundRect.noBar = true;

		frames = 22.53;
		beatFrames = 3.75;
		beatSwitch = 0;
		power1Check = 0;
		power2Check = 0;
		power3Check = 0;
		power4Check = 0;
		lives = '3';
		immune = 0.0;

		cube = SOIL_load_OGL_texture(
			"cube.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

		left1 = Spike(1.0, 0.5, 1.1, 0.6, 1.1, 0.4, 1.0, 0.0, 0.0);
		right1 = Spike(-1.0, -0.5, -1.1, -0.4, -1.1, -0.6, 1.0, 0.0, 0.0);

		diag3 = Spike(-1.0, -1.0, -1.1, -1.0, -1.0, -1.1, 1.0, 0.0, 1.0);

		up1 = Spike(-0.5, -1.0, -0.6, -1.1, -0.4, -1.1, 1.0, 0.0, 0.0);
		down1 = Spike(0.5, 1.0, 0.4, 1.1, 0.6, 1.1, 1.0, 0.0, 0.0);

		diag4 = Spike(1.0, -1.0, 1.1, -1.0, 1.0, -1.1, 1.0, 0.0, 1.0);

		right2 = Spike(-1.0, -0.75, -1.1, -0.65, -1.1, -0.85, 0.0, 1.0, 0.0);
		up2 = Spike(-0.75, -1.0, -0.65, -1.1, -0.85, -1.1, 0.0, 1.0, 0.0);

		diag1 = Spike(1.0, 1.0, 1.0, 1.1, 1.1, 1.0, 0.0, 0.0, 1.0);
		diag2 = Spike(-1.0, 1.0, -1.0, 1.1, -1.1, 1.0, 0.0, 0.0, 1.0);

		left2 = Spike(1.0, 0.75, 1.1, 0.85, 1.1, 0.65, 0.0, 1.0, 0.0);
		down2 = Spike(0.75, 1.0, 0.65, 1.1, 0.85, 1.1, 0.0, 1.0, 0.0);

		left3 = Spike(1.0, 0.5, 1.1, 0.6, 1.1, 0.4, 1.0, 0.0, 1.0);
		right3 = Spike(-1.0, -0.5, -1.1, -0.4, -1.1, -0.6, 1.0, 0.0, 1.0);
		up3 = Spike(-0.5, -1.0, -0.6, -1.1, -0.4, -1.1, 1.0, 0.0, 1.0);
		down3 = Spike(0.5, 1.0, 0.4, 1.1, 0.6, 1.1, 1.0, 0.0, 1.0);

		left4 = Spike(1.0, 0.5, 1.1, 0.4, 1.1, 0.6, 1.0, 0.0, 0.0);
		diag5 = Spike(1.0, -1.0, 1.1, -1.0, 1.0, -1.1, 1.0, 0.0, 1.0);

		down4 = Spike(-0.5, 1.0, -0.4, 1.1, -0.6, 1.1, 1.0, 0.0, 0.0);
		diag6 = Spike(1.0, 1.0, 1.0, 1.1, 1.1, 1.0, 1.0, 0.0, 1.0);

		right4 = Spike(-1.0, 0.5, -1.1, 0.4, -1.1, 0.6, 1.0, 1.0, 0.0);
		right5 = Spike(-1.0, -0.5, -1.1, -0.4, -1.1, -0.6, 1.0, 1.0, 0.0);
		up4 = Spike(0.5, -1.0, 0.4, -1.1, 0.6, -1.1, 1.0, 0.0, 1.0);

		down5 = Spike(-0.5, 1.0, -0.4, 1.1, -0.6, 1.1, 1.0, 1.0, 0.0);
		up5 = Spike(0.5, -1.0, 0.4, -1.1, 0.6, -1.1, 1.0, 1.0, 0.0);
		left5 = Spike(1.0, 0.0, 1.1, -0.1, 1.1, 0.1, 1.0, 0.0, 1.0);

		diag7 = Spike(-1.0, 1.0, -1.1, 1.0, -1.0, 1.1, 0.0, 0.0, 1.0);
		diag8 = Spike(1.0, 1.0, 1.1, 1.0, 1.0, 1.1, 0.0, 0.0, 1.0);
		right6 = Spike(-1.0, 0.0, -1.1, 0.1, -1.1, -0.1, 1.0, 1.0, 0.0);

		left6 = Spike(1.0, 0.9, 1.1, 0.8, 1.1, 1.0, 1.0, 0.0, 0.0);
		right7 = Spike(-1.0, -0.9, -1.1, -0.8, -1.1, -1.0, 1.0, 0.0, 0.0);
		up6 = Spike(-0.9, -1.0, -1.0, -1.1, -0.8, -1.1, 1.0, 0.0, 0.0);
		down6 = Spike(0.9, 1.0, 0.8, 1.1, 1.0, 1.1, 1.0, 0.0, 0.0);

		left7 = Spike(1.0, 0.75, 1.1, 0.65, 1.1, 0.85, 1.0, 1.0, 0.0);
		right8 = Spike(-1.0, -0.75, -1.1, -0.85, -1.1, -0.65, 1.0, 1.0, 0.0);
		up7 = Spike(-0.75, -1.0, -0.85, -1.1, -0.65, -1.1, 1.0, 1.0, 0.0);
		down7 = Spike(0.75, 1.0, 0.65, 1.1, 0.85, 1.1, 1.0, 1.0, 0.0);

		left8 = Spike(1.0, 0.6, 1.1, 0.5, 1.1, 0.7, 0.0, 1.0, 0.0);
		right9 = Spike(-1.0, -0.6, -1.1, -0.7, -1.1, -0.5, 0.0, 1.0, 0.0);
		up8 = Spike(-0.6, -1.0, -0.7, -1.1, -0.5, -1.1, 0.0, 1.0, 0.0);
		down8 = Spike(0.6, 1.0, 0.5, 1.1, 0.7, 1.1, 0.0, 1.0, 0.0);

		left9 = Spike(1.0, 0.45, 1.1, 0.35, 1.1, 0.55, 1.0, 0.0, 1.0);
		right10 = Spike(-1.0, -0.45, -1.1, -0.55, -1.1, -0.35, 1.0, 0.0, 1.0);
		up9 = Spike(-0.45, -1.0, -0.55, -1.1, -0.35, -1.1, 1.0, 0.0, 1.0);
		down9 = Spike(0.45, 1.0, 0.35, 1.1, 0.55, 1.1, 1.0, 0.0, 1.0);

		left10 = Spike(1.0, 0.0, 1.1, -0.1, 1.1, 0.1, 0.0, 0.0, 1.0);
		right11 = Spike(-1.0, 0.0, -1.1, -0.1, -1.1, 0.1, 0.0, 0.0, 1.0);
		up10 = Spike(0.0, -1.0, -0.1, -1.1, 0.1, -1.1, 0.0, 0.0, 1.0);
		down10 = Spike(0.0, 1.0, -0.1, 1.1, 0.1, 1.1, 0.0, 0.0, 1.0);

		diag9 = Spike(1.0, 1.0, 1.1, 1.0, 1.0, 1.1, 0.0, 1.0, 0.0);
		diag10 = Spike(-1.0, 1.0, -1.1, 1.0, -1.0, 1.1, 0.0, 1.0, 0.0);
		diag11 = Spike(-1.0, -1.0, -1.1, -1.0, -1.0, -1.1, 0.0, 1.0, 0.0);
		diag12 = Spike(1.0, -1.0, 1.1, -1.0, 1.0, -1.1, 0.0, 1.0, 0.0);

		up13 = Spike(0.0, -1.0, -0.1, -1.1, 0.1, -1.1, 0.0, 0.0, 1.0);
		down13 = Spike(0.75, 1.0, 0.65, 1.1, 0.85, 1.1, 0.0, 0.0, 1.0);

		diag13 = Spike(-1.0, -1.0, -1.1, -1.0, -1.0, -1.1, 0.0, 1.0, 0.0);
		diag14 = Spike(1.0, -1.0, 1.1, -1.0, 1.0, -1.1, 0.0, 1.0, 0.0);

		up14 = Spike(-0.9, -1.0, -1.0, -1.1, -0.8, -1.1, 1.0, 0.0, 1.0);
		up15 = Spike(-0.7, -1.0, -0.8, -1.1, -0.6, -1.1, 1.0, 0.0, 1.0);
		up16 = Spike(-0.5, -1.0, -0.6, -1.1, -0.4, -1.1, 1.0, 0.0, 1.0);
		up17 = Spike(-0.3, -1.0, -0.4, -1.1, -0.2, -1.1, 1.0, 0.0, 1.0);
		up18 = Spike(-0.1, -1.0, -0.2, -1.1, 0.0, -1.1, 1.0, 0.0, 1.0);
		up19 = Spike(0.1, -1.0, 0.0, -1.1, 0.2, -1.1, 1.0, 0.0, 1.0);
		up20 = Spike(0.3, -1.0, 0.2, -1.1, 0.4, -1.1, 1.0, 0.0, 1.0);
		up22 = Spike(0.9, -1.0, 0.8, -1.1, 1.0, -1.1, 1.0, 0.0, 1.0);

		diag15 = Spike(1.0, 1.0, 1.1, 1.0, 1.0, 1.1, 0.0, 1.0, 0.0);

		diag16 = Spike(-1.0, 1.0, -1.1, 1.0, -1.0, 1.1, 0.0, 1.0, 0.0);

		left18 = Spike(1.0, 0.5, 1.1, 0.6, 1.1, 0.4, 1.0, 0.0, 0.0);
		right18 = Spike(-1.0, -0.5, -1.1, -0.6, -1.1, -0.4, 1.0, 0.0, 0.0);
		down18 = Spike(0.0, 1.0, -0.1, 1.1, 0.1, 1.1, 0.0, 1.0, 0.0);

		diag17 = Spike(1.0, 1.0, 1.1, 1.0, 1.0, 1.1, 0.0, 1.0, 0.0);
		diag18 = Spike(-1.0, 1.0, -1.1, 1.0, -1.0, 1.1, 0.0, 1.0, 0.0);
		diag19 = Spike(-1.0, -1.0, -1.1, -1.0, -1.0, -1.1, 0.0, 1.0, 0.0);
		diag20 = Spike(1.0, -1.0, 1.1, -1.0, 1.0, -1.1, 0.0, 1.0, 0.0);

		left20 = Spike(1.0, 0.5, 1.1, 0.6, 1.1, 0.4, 1.0, 0.0, 0.0);

		down20 = Spike(-0.9, 1.0, -1.0, 1.1, -0.8, 1.1, 1.0, 0.0, 1.0);
		down21 = Spike(-0.7, 1.0, -0.8, 1.1, -0.6, 1.1, 1.0, 0.0, 1.0);
		down22 = Spike(-0.5, 1.0, -0.6, 1.1, -0.4, 1.1, 1.0, 0.0, 1.0);
		down23 = Spike(-0.3, 1.0, -0.4, 1.1, -0.2, 1.1, 1.0, 0.0, 1.0);
		down24 = Spike(-0.1, 1.0, -0.2, 1.1, 0.0, 1.1, 1.0, 0.0, 1.0);
		down25 = Spike(0.1, 1.0, 0.0, 1.1, 0.2, 1.1, 1.0, 0.0, 1.0);
		down26 = Spike(0.3, 1.0, 0.2, 1.1, 0.4, 1.1, 1.0, 0.0, 1.0);
		down27 = Spike(0.9, 1.0, 0.8, 1.1, 1.0, 1.1, 1.0, 0.0, 1.0);

		right20 = Spike(-1.0, 0.9, -1.1, 1.0, -1.1, 0.8, 1.0, 1.0, 0.0);
		right21 = Spike(-1.0, 0.3, -1.1, 0.4, -1.1, 0.2, 1.0, 1.0, 0.0);
		right22 = Spike(-1.0, 0.1, -1.1, 0.2, -1.1, 0.0, 1.0, 1.0, 0.0);
		right23 = Spike(-1.0, -0.1, -1.1, 0.0, -1.1, -0.2, 1.0, 1.0, 0.0);
		right24 = Spike(-1.0, -0.3, -1.1, -0.2, -1.1, -0.4, 1.0, 1.0, 0.0);
		right25 = Spike(-1.0, -0.5, -1.1, -0.4, -1.1, -0.6, 1.0, 1.0, 0.0);
		right26 = Spike(-1.0, -0.7, -1.1, -0.6, -1.1, -0.8, 1.0, 1.0, 0.0);
		right27 = Spike(-1.0, -0.9, -1.1, -0.8, -1.1, -10, 1.0, 1.0, 0.0);

		up21 = Spike(-0.9, -1.0, -1.0, -1.1, -0.8, -1.1, 1.0, 0.0, 1.0);
		up26 = Spike(-0.3, -1.0, -0.4, -1.1, -0.2, -1.1, 1.0, 0.0, 1.0);
		up27 = Spike(-0.1, -1.0, -0.2, -1.1, 0.0, -1.1, 1.0, 0.0, 1.0);
		up28 = Spike(0.1, -1.0, 0.0, -1.1, 0.2, -1.1, 1.0, 0.0, 1.0);
		up29 = Spike(0.3, -1.0, 0.2, -1.1, 0.4, -1.1, 1.0, 0.0, 1.0);
		up30 = Spike(0.5, -1.0, 0.4, -1.1, 0.6, -1.1, 1.0, 0.0, 1.0);
		up31 = Spike(0.7, -1.0, 0.6, -1.1, 0.8, -1.1, 1.0, 0.0, 1.0);
		up32 = Spike(0.9, -1.0, 0.8, -1.1, 1.0, -1.1, 1.0, 0.0, 1.0);

		down28 = Spike(-0.9, 1.0, -1.0, 1.1, -0.8, 1.1, 0.0, 0.0, 1.0);
		down29 = Spike(-0.3, 1.0, -0.4, 1.1, -0.2, 1.1, 0.0, 0.0, 1.0);
		down30 = Spike(-0.1, 1.0, -0.2, 1.1, 0.0, 1.1, 0.0, 0.0, 1.0);
		down31 = Spike(0.1, 1.0, 0.0, 1.1, 0.2, 1.1, 0.0, 0.0, 1.0);
		down32 = Spike(0.3, 1.0, 0.2, 1.1, 0.4, 1.1, 0.0, 0.0, 1.0);
		down35 = Spike(0.9, 1.0, 0.8, 1.1, 1.0, 1.1, 0.0, 0.0, 1.0);

		down36 = Spike(0.6, 1.0, 0.5, 1.1, 0.7, 1.1, 1.0, 0.0, 1.0);

		left21 = Spike(1.0, 0.9, 1.1, 1.0, 1.1, 0.8, 1.0, 0.0, 1.0);
		left22 = Spike(1.0, 0.7, 1.1, 0.8, 1.1, 0.6, 1.0, 0.0, 1.0);
		left23 = Spike(1.0, 0.5, 1.1, 0.6, 1.1, 0.4, 1.0, 0.0, 1.0);
		left24 = Spike(1.0, 0.3, 1.1, 0.4, 1.1, 0.2, 1.0, 0.0, 1.0);
		left25 = Spike(1.0, 0.1, 1.1, 0.2, 1.1, 0.0, 1.0, 0.0, 1.0);
		left26 = Spike(1.0, -0.1, 1.1, 0.0, 1.1, -0.2, 1.0, 0.0, 1.0);
		left27 = Spike(1.0, -0.3, 1.1, -0.2, 1.1, -0.4, 1.0, 0.0, 1.0);
		left28 = Spike(1.0, -0.5, 1.1, -0.4, 1.1, -0.6, 1.0, 0.0, 1.0);
		left29 = Spike(1.0, -0.7, 1.1, -0.6, 1.1, -0.8, 1.0, 0.0, 1.0);
		left30 = Spike(1.0, -0.9, 1.1, -0.8, 1.1, -1.0, 1.0, 0.0, 1.0);

		up33 = Spike(-0.9, -1.0, -1.0, -1.1, -0.8, -1.1, 1.0, 0.0, 1.0);
		up34 = Spike(-0.7, -1.0, -0.8, -1.1, -0.6, -1.1, 1.0, 0.0, 1.0);
		up35 = Spike(-0.5, -1.0, -0.6, -1.1, -0.4, -1.1, 1.0, 0.0, 1.0);
		up36 = Spike(-0.3, -1.0, -0.4, -1.1, -0.2, -1.1, 1.0, 0.0, 1.0);
		up37 = Spike(-0.1, -1.0, -0.2, -1.1, 0.0, -1.1, 1.0, 0.0, 1.0);
		up38 = Spike(0.1, -1.0, 0.0, -1.1, 0.2, -1.1, 1.0, 0.0, 1.0);
		up39 = Spike(0.3, -1.0, 0.2, -1.1, 0.4, -1.1, 1.0, 0.0, 1.0);
		up40 = Spike(0.5, -1.0, 0.4, -1.1, 0.6, -1.1, 1.0, 0.0, 1.0);
		up41 = Spike(0.7, -1.0, 0.6, -1.1, 0.8, -1.1, 1.0, 0.0, 1.0);
		up42 = Spike(0.9, -1.0, 0.8, -1.1, 1.0, -1.1, 1.0, 0.0, 1.0);

		up43 = Spike(-0.9, -1.0, -1.0, -1.1, -0.8, -1.1, 0.0, 0.0, 1.0);
		up44 = Spike(-0.7, -1.0, -0.8, -1.1, -0.6, -1.1, 0.0, 0.0, 1.0);
		up45 = Spike(-0.5, -1.0, -0.6, -1.1, -0.4, -1.1, 0.0, 0.0, 1.0);
		up46 = Spike(-0.3, -1.0, -0.4, -1.1, -0.2, -1.1, 0.0, 0.0, 1.0);
		up47 = Spike(-0.1, -1.0, -0.2, -1.1, 0.0, -1.1, 0.0, 0.0, 1.0);
		up48 = Spike(0.1, -1.0, 0.0, -1.1, 0.2, -1.1, 0.0, 0.0, 1.0);
		up49 = Spike(0.3, -1.0, 0.2, -1.1, 0.4, -1.1, 0.0, 0.0, 1.0);
		up50 = Spike(0.5, -1.0, 0.4, -1.1, 0.6, -1.1, 0.0, 0.0, 1.0);
		up51 = Spike(0.7, -1.0, 0.6, -1.1, 0.8, -1.1, 0.0, 0.0, 1.0);
		up52 = Spike(0.9, -1.0, 0.8, -1.1, 1.0, -1.1, 0.0, 0.0, 1.0);

		right28 = Spike(-1.0, 0.9, -1.1, 1.0, -1.1, 0.8, 0.0, 0.0, 1.0);
		right29 = Spike(-1.0, 0.7, -1.1, 0.8, -1.1, 0.6, 0.0, 0.0, 1.0);
		right30 = Spike(-1.0, 0.5, -1.1, 0.6, -1.1, 0.4, 0.0, 0.0, 1.0);
		right31 = Spike(-1.0, 0.3, -1.1, 0.4, -1.1, 0.2, 0.0, 0.0, 1.0);
		right32 = Spike(-1.0, 0.1, -1.1, 0.2, -1.1, 0.0, 0.0, 0.0, 1.0);
		right33 = Spike(-1.0, -0.1, -1.1, 0.0, -1.1, -0.2, 0.0, 0.0, 1.0);
		right34 = Spike(-1.0, -0.3, -1.1, -0.2, -1.1, -0.4, 0.0, 0.0, 1.0);
		right35 = Spike(-1.0, -0.5, -1.1, -0.4, -1.1, -0.6, 0.0, 0.0, 1.0);
		right36 = Spike(-1.0, -0.7, -1.1, -0.6, -1.1, -0.8, 0.0, 0.0, 1.0);
		right37 = Spike(-1.0, -0.9, -1.1, -0.8, -1.1, -1.0, 0.0, 0.0, 1.0);

		down37 = Spike(-0.9, 1.0, -1.0, 1.1, -0.8, 1.1, 1.0, 0.0, 1.0);
		down38 = Spike(-0.7, 1.0, -0.8, 1.1, -0.6, 1.1, 1.0, 0.0, 1.0);
		down39 = Spike(-0.5, 1.0, -0.6, 1.1, -0.4, 1.1, 1.0, 0.0, 1.0);
		down40 = Spike(-0.3, 1.0, -0.4, 1.1, -0.2, 1.1, 1.0, 0.0, 1.0);
		down41 = Spike(-0.1, 1.0, -0.2, 1.1, 0.0, 1.1, 1.0, 0.0, 1.0);
		down42 = Spike(0.1, 1.0, 0.0, 1.1, 0.2, 1.1, 1.0, 0.0, 1.0);
		down43 = Spike(0.3, 1.0, 0.2, 1.1, 0.4, 1.1, 1.0, 0.0, 1.0);
		down44 = Spike(0.5, 1.0, 0.4, 1.1, 0.6, 1.1, 1.0, 0.0, 1.0);
		down45 = Spike(0.7, 1.0, 0.6, 1.1, 0.8, 1.1, 1.0, 0.0, 1.0);
		down46 = Spike(0.9, 1.0, 0.8, 1.1, 1.0, 1.1, 1.0, 0.0, 1.0);

	}

	void motion(double x, double y) {

		if (userRect.select) {

			if ((userRect.upleftX + userRect.width + x < 1.0) && (userRect.upleftX + x > -1.0) && (userRect.upleftY + y < 1.0) && (userRect.upleftY - userRect.height + y > -1.0)) {

				userRect.upleftX += x;
				userRect.upleftY += y;

			}

		}

	}

	void click(double x, double y) {

		if (userRect.contains(Vec(x, y))) {

			userRect.select = true;

		}

		else {

			userRect.select = false;

		}

	}

	void drawSpike(Spike spikey) {

		glColor3d(spikey.r, spikey.g, spikey.b);
		glBegin(GL_TRIANGLES);
		glVertex2d(spikey.cord1.x, spikey.cord1.y);
		glVertex2d(spikey.cord2.x, spikey.cord2.y);
		glVertex2d(spikey.cord3.x, spikey.cord3.y);
		glEnd();

	}

	Spike leftSpike(Spike left) {

		left.cord1.x -= 0.05;
		left.cord2.x -= 0.05;
		left.cord3.x -= 0.05;

		hitCheck(left);

		return left;

	}

	Spike rightSpike(Spike right) {

		right.cord1.x += 0.05;
		right.cord2.x += 0.05;
		right.cord3.x += 0.05;

		hitCheck(right);

		return right;

	}

	Spike upSpike(Spike up) {

		up.cord1.y += 0.05;
		up.cord2.y += 0.05;
		up.cord3.y += 0.05;

		hitCheck(up);

		return up;

	}

	Spike downSpike(Spike down) {

		down.cord1.y -= 0.05;
		down.cord2.y -= 0.05;
		down.cord3.y -= 0.05;

		hitCheck(down);

		return down;

	}

	Spike urSpike(Spike diag) {

		diag.cord1.x += 0.05;
		diag.cord2.x += 0.05;
		diag.cord3.x += 0.05;
		diag.cord1.y += 0.05;
		diag.cord2.y += 0.05;
		diag.cord3.y += 0.05;

		hitCheck(diag);

		return diag;

	}

	Spike ulSpike(Spike diag) {

		diag.cord1.x -= 0.05;
		diag.cord2.x -= 0.05;
		diag.cord3.x -= 0.05;
		diag.cord1.y += 0.05;
		diag.cord2.y += 0.05;
		diag.cord3.y += 0.05;

		hitCheck(diag);

		return diag;

	}

	Spike drSpike(Spike diag) {

		diag.cord1.x += 0.05;
		diag.cord2.x += 0.05;
		diag.cord3.x += 0.05;
		diag.cord1.y -= 0.05;
		diag.cord2.y -= 0.05;
		diag.cord3.y -= 0.05;

		hitCheck(diag);

		return diag;

	}

	Spike dlSpike(Spike diag) {

		diag.cord1.x -= 0.05;
		diag.cord2.x -= 0.05;
		diag.cord3.x -= 0.05;
		diag.cord1.y -= 0.05;
		diag.cord2.y -= 0.05;
		diag.cord3.y -= 0.05;

		hitCheck(diag);

		return diag;

	}

	void hitCheck(Spike spikey) {

		if ((userRect.contains(Vec(spikey.cord1.x, spikey.cord1.y))) || (userRect.contains(Vec(spikey.cord2.x, spikey.cord2.y))) || (userRect.contains(Vec(spikey.cord3.x, spikey.cord3.y)))) {

			hit();

		}

	}

	void powerUp1() {

		glColor3d(0.0, 1.0, 1.0);
		glBegin(GL_POINTS);
		glVertex2d(0.75, -0.15);
		glEnd();

		power1Check = userRect.contains(Vec(0.75, -0.15));

	}

	void powerUp2() {

		glColor3d(0.0, 1.0, 0.0);
		glBegin(GL_POINTS);
		glVertex2d(-0.75, -0.15);
		glEnd();

		power2Check = userRect.contains(Vec(-0.75, -0.15));

		if (power2Check == 1) {

			lives++;

		}

	}

	void powerUp3() {

		glColor3d(1.0, 0.0, 0.0);
		glBegin(GL_POINTS);
		glVertex2d(-0.75, 0.75);
		glEnd();

		power3Check = userRect.contains(Vec(-0.75, 0.75));

	}

	void powerUp4() {

		glColor3d(1.0, 0.0, 0.0);
		glBegin(GL_POINTS);
		glVertex2d(0.5, 0.0);
		glEnd();

		power4Check = userRect.contains(Vec(0.5, 0.0));

	}

	void hit() {

		if (immune == 0.0) {

			lives--;
			immune = miliseconds + 0.75;

		}

		if (lives == '0') {

			playCheck = false;
			coin = '0';
			PlaySound("Death.wav", NULL, SND_ASYNC);
			Sleep(4000);
			PlaySound("Runescape.wav", NULL, SND_LOOP | SND_ASYNC);

		}

	}

	char play() {

		miliseconds = glutGet(GLUT_ELAPSED_TIME);
		miliseconds = miliseconds / 1000;

		if (miliseconds >= immune) {

			immune = 0.0;

		}

		if ((miliseconds >= msStart + 2) && (miliseconds <= msStart + 22.5)) {

			glColor3d(0.9, 0.9, 0.9);
			glRasterPos2f(-0.45, 0.3);
			glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)("Welcome to Dodging Spikes!"));

		}

		if ((miliseconds >= msStart + 5) && (miliseconds <= msStart + 22.5)) {

			glColor3d(0.0, 1.0, 1.0);
			glRasterPos2f(-0.725, 0.15);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("In order to WIN, you (The Rectangle), can't hit ANY spikes!"));

		}

		if ((miliseconds >= msStart + 8) && (miliseconds <= msStart + 22.5)) {

			glColor3d(1.0, 1.0, 0.0);
			glRasterPos2f(-0.3, 0.0);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("You only have 3 Lives!"));

		}

		if ((miliseconds >= msStart + 11) && (miliseconds <= msStart + 22.5)) {

			glColor3d(1.0, 0.0, 1.0);
			glRasterPos2f(-0.725, -0.15);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("Controls: Click & Drag the Rectangle to move it around"));

		}

		if ((miliseconds >= msStart + 14) && (miliseconds <= msStart + 22.5)) {

			glColor3d(0.0, 1.0, 0.0);
			glRasterPos2f(-0.4, -0.3);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("Song: 'Clubstep' by DJ-Nate"));

		}

		if ((miliseconds >= msStart + 18) && (miliseconds <= msStart + 22.5)) {

			glColor3d(1.0, 0.0, 0.0);
			glRasterPos2f(-0.3, -0.55);
			glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)("GOOD LUCK!"));

		}

		if ((miliseconds >= msStart + 18.5) && (miliseconds < msStart + 22.5)) {

			glColor3d(0.0, 1.0, 0.0);
			glRasterPos2f(-0.25, -0.7);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("Starting in:"));

		}

		if ((miliseconds >= msStart + 18.5) && (miliseconds < msStart + 19.5)) {

			glColor3d(0.0, 1.0, 0.0);
			glRasterPos2f(0.05, -0.7);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("3"));

		}

		if ((miliseconds >= msStart + 19.5) && (miliseconds < msStart + 20.5)) {

			glColor3d(1.0, 1.0, 0.0);
			glRasterPos2f(0.05, -0.7);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("2"));

			backgroundRect.r = 0.1;
			backgroundRect.g = 0.1;
			backgroundRect.b = 0.1;

		}

		if ((miliseconds >= msStart + 20.5) && (miliseconds < msStart + 21.5)) {

			glColor3d(1.0, 0.0, 0.0);
			glRasterPos2f(0.05, -0.7);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("1"));

			backgroundRect.r = 0.05;
			backgroundRect.g = 0.05;
			backgroundRect.b = 0.05;

		}

		if ((miliseconds >= msStart + 21.5) && (miliseconds <= msStart + 22.5)) {

			glColor3d(1.0, 0.0, 0.0);
			glRasterPos2f(0.05, -0.7);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("GO!"));

			backgroundRect.r = 0.0;
			backgroundRect.g = 0.0;
			backgroundRect.b = 0.0;

		}

		
		if ((miliseconds >= msStart + 8) && (miliseconds < msStart + 200)) {

			glColor3d(0.7, 0.7, 0.7);
			glRasterPos2f(-0.15, -0.95);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("Lives:"));

			glColor3d(0.7, 0.7, 0.7);
			glRasterPos2f(0.025, -0.95);
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (const unsigned char)(lives));

		}

		if ((miliseconds >= msStart + 18) && (miliseconds < msStart + 42)) {

			glColor3d(0.7, 0.7, 0.7);
			glRasterPos2f(0.75, -0.95);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("Wave 1"));

		}

		if ((miliseconds >= msStart + 56) && (miliseconds < msStart + 100)) {

			glColor3d(0.7, 0.7, 0.7);
			glRasterPos2f(0.75, -0.95);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("Wave 2"));

		}



		if ((miliseconds >= msStart + 3) && (miliseconds <= msStart + 12)) {

			if (miliseconds >= msStart + beatFrames) {

				if (beatSwitch == 0) {

					backgroundRect.r = 0.25;
					backgroundRect.g = 0.25;
					backgroundRect.b = 0.25;
					beatSwitch = 1;

				}

				else if (beatSwitch == 1) {

					backgroundRect.r = 0.15;
					backgroundRect.g = 0.15;
					backgroundRect.b = 0.15;
					beatSwitch = 0;

				}

				beatFrames += 0.475;

			}

		}

		if ((miliseconds >= msStart + 13) && (miliseconds <= msStart + 14)) {

			beatFrames = 22.5;
			beatSwitch = 1;

		}

		if ((miliseconds >= msStart + 22.47) && (miliseconds <= msStart + 29)) {

			if (miliseconds >= msStart + beatFrames) {

				if (beatSwitch == 0) {

					backgroundRect.r = 0.25;
					backgroundRect.g = 0.0;
					backgroundRect.b = 0.0;
					beatSwitch = 1;

				}

				else if (beatSwitch == 1) {

					backgroundRect.r = 0.15;
					backgroundRect.g = 0.0;
					backgroundRect.b = 0.0;
					beatSwitch = 0;

				}

				beatFrames += 0.475;

			}

		}

		if ((miliseconds >= msStart + 29.01) && (miliseconds <= msStart + 29.05)) {

			beatFrames = 29.4;
			beatSwitch = 2;

		}

		if ((miliseconds >= msStart + 29.37) && (miliseconds <= msStart + 30)) {

			if (miliseconds >= msStart + beatFrames) {

				if (beatSwitch == 2) {

					backgroundRect.r = 0.35;
					backgroundRect.g = 0.0;
					backgroundRect.b = 0.35;
					beatSwitch = 3;

				}

				else if (beatSwitch == 3) {

					backgroundRect.r = 0.25;
					backgroundRect.g = 0.0;
					backgroundRect.b = 0.25;
					beatSwitch = 2;

				}

				beatFrames += 0.15;

			}

		}

		if ((miliseconds >= msStart + 30) && (miliseconds <= msStart + 30.04)) {

			beatFrames = 30.1;
			beatSwitch = 1;

		}

		if ((miliseconds >= msStart + 30.07) && (miliseconds <= msStart + 36.3)) {

			if (miliseconds >= msStart + beatFrames) {

				if (beatSwitch == 0) {

					backgroundRect.r = 0.25;
					backgroundRect.g = 0.0;
					backgroundRect.b = 0.0;
					beatSwitch = 1;

				}

				else if (beatSwitch == 1) {

					backgroundRect.r = 0.15;
					backgroundRect.g = 0.0;
					backgroundRect.b = 0.0;
					beatSwitch = 0;

				}

				beatFrames += 0.475;

			}

		}

		if ((miliseconds >= msStart + 36.31) && (miliseconds <= msStart + 36.35)) {

			beatFrames = 36.5;
			beatSwitch = 2;

		}

		if ((miliseconds >= msStart + 36.47) && (miliseconds <= msStart + 37.5)) {

			if (miliseconds >= msStart + beatFrames) {

				if (beatSwitch == 2) {

					backgroundRect.r = 0.0;
					backgroundRect.g = 0.0;
					backgroundRect.b = 0.35;
					beatSwitch = 3;

				}

				else if (beatSwitch == 3) {

					backgroundRect.r = 0.0;
					backgroundRect.g = 0.0;
					backgroundRect.b = 0.25;
					beatSwitch = 2;

				}

				beatFrames += 0.125;

			}

		}

		if ((miliseconds >= msStart + 37.51) && (miliseconds <= msStart + 37.55)) {

			beatFrames = 37.6;
			beatSwitch = 1;

		}

		if ((miliseconds >= msStart + 37.57) && (miliseconds <= msStart + 50)) {

			if (miliseconds >= msStart + beatFrames) {

				if (beatSwitch == 0) {

					backgroundRect.r = 0.25;
					backgroundRect.g = 0.0;
					backgroundRect.b = 0.0;
					beatSwitch = 1;

				}

				else if (beatSwitch == 1) {

					backgroundRect.r = 0.15;
					backgroundRect.g = 0.0;
					backgroundRect.b = 0.0;
					beatSwitch = 0;

				}

				beatFrames += 0.475;

			}

		}

		if ((miliseconds >= msStart + 50.01) && (miliseconds <= msStart + 50.05)) {

			beatFrames = 50.5;
			beatSwitch = 0;

		}

		if ((miliseconds >= msStart + 50.47) && (miliseconds <= msStart + 51.2)) {

			if (miliseconds >= msStart + beatFrames) {

				if (beatSwitch == 0) {

					backgroundRect.r = 0.1;
					backgroundRect.g = 0.0;
					backgroundRect.b = 0.0;
					beatSwitch = 1;

				}

				else if (beatSwitch == 1) {

					backgroundRect.r = 0.05;
					backgroundRect.g = 0.0;
					backgroundRect.b = 0.0;
					beatSwitch = 2;

				}

				else if (beatSwitch == 2) {

					backgroundRect.r = 0.0;
					backgroundRect.g = 0.0;
					backgroundRect.b = 0.0;
					beatSwitch = 3;

				}

				beatFrames += 0.225;

			}

		}

		if ((miliseconds >= msStart + 51.2) && (miliseconds <= msStart + 52.3)) {

			if (miliseconds >= msStart + beatFrames) {

				if (beatSwitch == 3) {

					backgroundRect.r = 0.25;
					backgroundRect.g = 0.0;
					backgroundRect.b = 0.25;
					beatSwitch = 4;

				}

				else if (beatSwitch == 4) {

					backgroundRect.r = 0.35;
					backgroundRect.g = 0.0;
					backgroundRect.b = 0.35;
					beatSwitch = 3;

				}

				beatFrames += 0.1;

			}

		}

		if ((miliseconds >= msStart + 52.4) && (miliseconds <= msStart + 72)) {

			backgroundRect.r = 0.15;
			backgroundRect.g = 0.15;
			backgroundRect.b = 0.15;

			beatFrames = 72.03;
			beatSwitch = 1;

		}


		if ((miliseconds >= msStart + 53.5) && (miliseconds <= msStart + 72)) {

			glColor3d(0.0, 1.0, 0.0);
			glRasterPos2f(-0.25, 0.7);
			glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)("Congratulations!"));
			frames = 72.3;

		}

		if ((miliseconds >= msStart + 56) && (miliseconds <= msStart + 72)) {

			glColor3d(0.0, 1.0, 1.0);
			glRasterPos2f(-0.265, 0.55);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("You passed Wave 1!"));

			glColor3d(1.0, 1.0, 0.0);
			glRasterPos2f(-0.44, 0.4);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("Two more Waves left until you Win"));

			glColor3d(1.0, 0.0, 0.0);
			glRasterPos2f(-0.975, -0.85);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("(P.S. These next spikes will target you based on your location)"));

		}

		if ((miliseconds >= msStart + 59) && (miliseconds <= msStart + 72)) {

			glColor3d(1.0, 0.0, 1.0);
			glRasterPos2f(-0.7, 0.25);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("The next Wave will include Power-Ups to help you survive!"));

		}

		if ((miliseconds >= msStart + 62) && (miliseconds <= msStart + 72)) {

			glColor3d(0.0, 1.0, 1.0);
			glRasterPos2f(-0.75, 0.1);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("Picking up the cyan (light blue) pixels will temporarily reduce"));

			glColor3d(0.0, 1.0, 1.0);
			glRasterPos2f(-0.25, 0.0);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("your rectangle size"));

		}

		if ((miliseconds >= msStart + 65) && (miliseconds <= msStart + 72)) {

			glColor3d(0.0, 1.0, 0.0);
			glRasterPos2f(-0.5, -0.15);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("Pick up that cyan pixel to try it out!"));

		}

		if ((miliseconds >= msStart + 65) && (miliseconds <= msStart + 71)) {

			if (power1Check == 0) {

				powerUp1();

			}

		}

		if ((miliseconds >= msStart + 67.5) && (miliseconds <= msStart + 72)) {

			glColor3d(1.0, 0.0, 0.0);
			glRasterPos2f(-0.3, -0.55);
			glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)("GOOD LUCK!"));

		}

		if ((miliseconds >= msStart + 68) && (miliseconds < msStart + 72)) {

			glColor3d(0.0, 1.0, 0.0);
			glRasterPos2f(-0.25, -0.7);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("Starting in:"));

		}

		if ((miliseconds >= msStart + 68) && (miliseconds < msStart + 69)) {

			glColor3d(0.0, 1.0, 0.0);
			glRasterPos2f(0.05, -0.7);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("3"));

		}

		if ((miliseconds >= msStart + 69) && (miliseconds < msStart + 70)) {

			glColor3d(1.0, 1.0, 0.0);
			glRasterPos2f(0.05, -0.7);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("2"));

			backgroundRect.r = 0.1;
			backgroundRect.g = 0.1;
			backgroundRect.b = 0.1;

		}

		if ((miliseconds >= msStart + 70) && (miliseconds < msStart + 71)) {

			glColor3d(1.0, 0.0, 0.0);
			glRasterPos2f(0.05, -0.7);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("1"));

			backgroundRect.r = 0.05;
			backgroundRect.g = 0.05;
			backgroundRect.b = 0.05;

		}

		if ((miliseconds >= msStart + 71) && (miliseconds <= msStart + 72)) {

			glColor3d(1.0, 0.0, 0.0);
			glRasterPos2f(0.05, -0.7);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("GO!"));

			backgroundRect.r = 0.0;
			backgroundRect.g = 0.0;
			backgroundRect.b = 0.0;

			power1Check = 0;

		}


		if ((miliseconds >= msStart + 72) && (miliseconds <= msStart + 85.3)) {

			if (miliseconds >= msStart + beatFrames) {

				if (beatSwitch == 0) {

					backgroundRect.r = 0.25;
					backgroundRect.g = 0.0;
					backgroundRect.b = 0.0;
					beatSwitch = 1;

				}

				else if (beatSwitch == 1) {

					backgroundRect.r = 0.15;
					backgroundRect.g = 0.0;
					backgroundRect.b = 0.0;
					beatSwitch = 0;

				}

				beatFrames += 0.475;

			}

		}

		if ((miliseconds >= msStart + 85.33) && (miliseconds <= msStart + 85.37)) {

			beatFrames = 85.53;
			beatSwitch = 0;

		}

		if ((miliseconds >= msStart + 85.5) && (miliseconds <= msStart + 86.12)) {

			if (miliseconds >= msStart + beatFrames) {

				if (beatSwitch == 0) {

					backgroundRect.r = 0.35;
					backgroundRect.g = 0.0;
					backgroundRect.b = 0.35;
					beatSwitch = 1;

				}

				else if (beatSwitch == 1) {

					backgroundRect.r = 0.25;
					backgroundRect.g = 0.0;
					backgroundRect.b = 0.25;
					beatSwitch = 0;

				}

				beatFrames += 0.15;

			}

		}

		if ((miliseconds >= msStart + 86.13) && (miliseconds <= msStart + 86.6)) {

			if (miliseconds >= msStart + beatFrames) {

				if (beatSwitch == 0) {

					backgroundRect.r = 0.0;
					backgroundRect.g = 0.0;
					backgroundRect.b = 0.15;
					beatSwitch = 1;

				}

				else if (beatSwitch == 1) {

					backgroundRect.r = 0.0;
					backgroundRect.g = 0.0;
					backgroundRect.b = 0.25;
					beatSwitch = 0;

				}

				else if (beatSwitch == 2) {

					backgroundRect.r = 0.0;
					backgroundRect.g = 0.0;
					backgroundRect.b = 0.35;
					beatSwitch = 0;

				}

				beatFrames += 0.125;

			}

		}

		if ((miliseconds >= msStart + 86.63) && (miliseconds <= msStart + 86.67)) {

			beatFrames = 86.73;
			beatSwitch = 0;

		}

		if ((miliseconds >= msStart + 86.7) && (miliseconds <= msStart + 100.3)) {

			if (miliseconds >= msStart + beatFrames) {

				if (beatSwitch == 0) {

					backgroundRect.r = 0.25;
					backgroundRect.g = 0.0;
					backgroundRect.b = 0.0;
					beatSwitch = 1;

				}

				else if (beatSwitch == 1) {

					backgroundRect.r = 0.15;
					backgroundRect.g = 0.0;
					backgroundRect.b = 0.0;
					beatSwitch = 0;

				}

				beatFrames += 0.475;

			}

		}

		if ((miliseconds >= msStart + 100.33) && (miliseconds <= msStart + 100.37)) {

			beatFrames = 100.53;
			beatSwitch = 0;

		}

		if ((miliseconds >= msStart + 100.5) && (miliseconds <= msStart + 101.12)) {

			if (miliseconds >= msStart + beatFrames) {

				if (beatSwitch == 0) {

					backgroundRect.r = 0.35;
					backgroundRect.g = 0.0;
					backgroundRect.b = 0.35;
					beatSwitch = 1;

				}

				else if (beatSwitch == 1) {

					backgroundRect.r = 0.25;
					backgroundRect.g = 0.0;
					backgroundRect.b = 0.25;
					beatSwitch = 0;

				}

				beatFrames += 0.15;

			}

		}

		if ((miliseconds >= msStart + 101.13) && (miliseconds <= msStart + 102)) {

			if (miliseconds >= msStart + beatFrames) {

				if (beatSwitch == 0) {

					backgroundRect.r = 0.0;
					backgroundRect.g = 0.0;
					backgroundRect.b = 0.15;
					beatSwitch = 1;

				}

				else if (beatSwitch == 1) {

					backgroundRect.r = 0.0;
					backgroundRect.g = 0.0;
					backgroundRect.b = 0.25;
					beatSwitch = 0;

				}

				else if (beatSwitch == 2) {

					backgroundRect.r = 0.0;
					backgroundRect.g = 0.0;
					backgroundRect.b = 0.35;
					beatSwitch = 0;

				}

				beatFrames += 0.125;

			}

		}

		if ((miliseconds >= msStart + 102) && (miliseconds <= msStart + 102.4)) {

			backgroundRect.r = 0.15;
			backgroundRect.g = 0.15;
			backgroundRect.b = 0.15;

			beatFrames = 118.53;
			beatSwitch = 0;

		}

		if ((miliseconds >= msStart + 103) && (miliseconds <= msStart + 118)) {

			glColor3d(0.0, 1.0, 0.0);
			glRasterPos2f(-0.35, 0.3);
			glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)("You're Almost Done!"));
			frames = 118.3;

		}

		if ((miliseconds >= msStart + 106) && (miliseconds <= msStart + 118)) {

			glColor3d(1.0, .0, 0.0);
			glRasterPos2f(-0.55, 0.1);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("One Wave left! This is the FINAL Wave!"));

		}

		if ((miliseconds >= msStart + 109) && (miliseconds <= msStart + 118)) {

			glColor3d(0.0, 1.0, 1.0);
			glRasterPos2f(-0.575, -0.05);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("Pick up that Green Pixel for an extra life!"));

			glColor3d(1.0, 0.0, 1.0);
			glRasterPos2f(-0.4, -0.2);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("Trust me... You'll need it :P"));

			if (power2Check == 0) {

				powerUp2();

			}

		}

		if ((miliseconds >= msStart + 112) && (miliseconds <= msStart + 118)) {

			glColor3d(1.0, 1.0, 0.0);
			glRasterPos2f(-0.65, -0.35);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("Also, this Wave has Red pixels to reverse Spikes!"));

		}

		if ((miliseconds >= msStart + 113.5) && (miliseconds <= msStart + 72)) {

			glColor3d(1.0, 0.0, 0.0);
			glRasterPos2f(-0.3, -0.55);
			glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)("GOOD LUCK!"));

		}

		if ((miliseconds >= msStart + 114) && (miliseconds < msStart + 118)) {

			glColor3d(0.0, 1.0, 0.0);
			glRasterPos2f(-0.25, -0.7);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("Starting in:"));

		}

		if ((miliseconds >= msStart + 114) && (miliseconds < msStart + 115)) {

			glColor3d(0.0, 1.0, 0.0);
			glRasterPos2f(0.05, -0.7);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("3"));

		}

		if ((miliseconds >= msStart + 115) && (miliseconds < msStart + 116)) {

			glColor3d(1.0, 1.0, 0.0);
			glRasterPos2f(0.05, -0.7);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("2"));

			backgroundRect.r = 0.1;
			backgroundRect.g = 0.1;
			backgroundRect.b = 0.1;

		}

		if ((miliseconds >= msStart + 116) && (miliseconds < msStart + 117)) {

			glColor3d(1.0, 0.0, 0.0);
			glRasterPos2f(0.05, -0.7);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("1"));

			backgroundRect.r = 0.05;
			backgroundRect.g = 0.05;
			backgroundRect.b = 0.05;

		}

		if ((miliseconds >= msStart + 117) && (miliseconds <= msStart + 118)) {

			glColor3d(1.0, 0.0, 0.0);
			glRasterPos2f(0.05, -0.7);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("GO!"));

			backgroundRect.r = 0.0;
			backgroundRect.g = 0.0;
			backgroundRect.b = 0.0;

			power1Check = 0;

		}

		if ((miliseconds >= msStart + 118) && (miliseconds <= msStart + 130.5)) {

			if (miliseconds >= msStart + beatFrames) {

				if (beatSwitch == 0) {

					backgroundRect.r = 0.0;
					backgroundRect.g = 0.0;
					backgroundRect.b = 0.25;
					beatSwitch = 1;

				}

				else if (beatSwitch == 1) {

					backgroundRect.r = 0.25;
					backgroundRect.g = 0.0;
					backgroundRect.b = 0.0;
					beatSwitch = 2;

				}

				else if (beatSwitch == 2) {

					backgroundRect.r = 0.25;
					backgroundRect.g = 0.0;
					backgroundRect.b = 0.25;
					beatSwitch = 3;

				}

				else if (beatSwitch == 3) {

					backgroundRect.r = 0.0;
					backgroundRect.g = 0.25;
					backgroundRect.b = 0.25;
					beatSwitch = 4;

				}

				else if (beatSwitch == 4) {

					backgroundRect.r = 0.0;
					backgroundRect.g = 0.25;
					backgroundRect.b = 0.0;
					beatSwitch = 0;

				}

				beatFrames += 1.9;

			}

		}

		if ((miliseconds >= msStart + 130.6) && (miliseconds <= msStart + 130.9)) {

			beatFrames = 131.3;
			beatSwitch = 0;

		}

		if ((miliseconds >= msStart + 131.1) && (miliseconds <= msStart + 132)) {

			if (miliseconds >= msStart + beatFrames) {

				if (beatSwitch == 0) {

					backgroundRect.r = 0.35;
					backgroundRect.g = 0.0;
					backgroundRect.b = 0.35;
					beatSwitch = 1;

				}

				else if (beatSwitch == 1) {

					backgroundRect.r = 0.25;
					backgroundRect.g = 0.0;
					backgroundRect.b = 0.25;
					beatSwitch = 0;

				}

				beatFrames += 0.15;

			}

		}





		if ((miliseconds >= msStart + 8) && (miliseconds <= msEnd)) {

			if (power1Check == 1) {

				userRect.width = 0.2;
				userRect.height = 0.2;

			}

			else if (power1Check == 0) {

				userRect.width = 0.3;
				userRect.height = 0.3;

			}

			userRect.draw();
			userRect.draw(cube);

		}

		backgroundRect.draw();

		static Spike test(1.0, 0.5, 1.1, 0.6, 1.1, 0.4, 1.0, 0.0, 0.0);

		glColor3d(1.0, 0.0, 0.0);
		glBegin(GL_TRIANGLES);
		glVertex2d(test.cord1.x, test.cord1.y);
		glVertex2d(test.cord2.x, test.cord2.y);
		glVertex2d(test.cord3.x, test.cord3.y);
		glEnd();

		test.cord1.x -= 0.0015;
		test.cord2.x -= 0.0015;
		test.cord3.x -= 0.0015;

		if ((miliseconds >= msStart + 22.5) && (miliseconds <= msStart + 24)) {

			if (miliseconds >= msStart + frames) {

				left1 = leftSpike(left1);
				right1 = rightSpike(right1);

				frames += 0.03;

			}

			drawSpike(left1);
			drawSpike(right1);

		}


		if ((miliseconds >= msStart + 24) && (miliseconds <= msStart + 25.5)) {

			if (miliseconds >= msStart + frames) {

				diag3 = urSpike(diag3);
				frames += 0.03;

			}

			drawSpike(diag3);

		}


		if ((miliseconds >= msStart + 25.5) && (miliseconds <= msStart + 27)) {

			if (miliseconds >= msStart + frames) {

				up1 = upSpike(up1);
				down1 = downSpike(down1);
				frames += 0.03;

			}

			drawSpike(up1);
			drawSpike(down1);

		}


		if ((miliseconds >= msStart + 27) && (miliseconds <= msStart + 28.5)) {

			if (miliseconds >= msStart + frames) {

				diag4 = ulSpike(diag4);
				frames += 0.03;

			}

			drawSpike(diag4);

		}


		if ((miliseconds >= msStart + 28.5) && (miliseconds <= msStart + 30)) {

			if (miliseconds >= msStart + frames) {

				right2 = rightSpike(right2);
				up2 = upSpike(up2);
				frames += 0.03;

			}

			drawSpike(right2);
			drawSpike(up2);

		}


		if ((miliseconds >= msStart + 30) && (miliseconds <= msStart + 31.5)) {

			if (miliseconds >= msStart + frames) {

				diag1 = dlSpike(diag1);
				diag2 = drSpike(diag2);
				frames += 0.03;

			}

			drawSpike(diag1);
			drawSpike(diag2);

		}


		if ((miliseconds >= msStart + 31.5) && (miliseconds <= msStart + 33)) {

			if (miliseconds >= msStart + frames) {

				left2 = leftSpike(left2);
				down2 = downSpike(down2);
				frames += 0.03;

			}

			drawSpike(left2);
			drawSpike(down2);

		}


		if ((miliseconds >= msStart + 33) && (miliseconds <= msStart + 34.5)) {

			if (miliseconds >= msStart + frames) {

				left3 = leftSpike(left3);
				right3 = rightSpike(right3);
				up3 = upSpike(up3);
				down3 = downSpike(down3);
				frames += 0.03;

			}

			drawSpike(left3);
			drawSpike(right3);
			drawSpike(up3);
			drawSpike(down3);

		}


		if ((miliseconds >= msStart + 34.5) && (miliseconds <= msStart + 36)) {

			if (miliseconds >= msStart + frames) {

				left4 = leftSpike(left4);
				diag5 = ulSpike(diag5);
				frames += 0.03;

			}

			drawSpike(left4);
			drawSpike(diag5);

		}


		if ((miliseconds >= msStart + 36) && (miliseconds <= msStart + 37.5)) {

			if (miliseconds >= msStart + frames) {

				down4 = downSpike(down4);
				diag6 = dlSpike(diag6);
				frames += 0.03;

			}

			drawSpike(down4);
			drawSpike(diag6);

		}


		if ((miliseconds >= msStart + 37.5) && (miliseconds <= msStart + 39)) {

			if (miliseconds >= msStart + frames) {

				right4 = rightSpike(right4);
				right5 = rightSpike(right5);
				up4 = upSpike(up4);
				frames += 0.03;

			}

			drawSpike(right4);
			drawSpike(right5);
			drawSpike(up4);

		}


		if ((miliseconds >= msStart + 39) && (miliseconds <= msStart + 40.5)) {

			if (miliseconds >= msStart + frames) {

				down5 = downSpike(down5);
				up5 = upSpike(up5);
				left5 = leftSpike(left5);
				frames += 0.03;

			}

			drawSpike(down5);
			drawSpike(up5);
			drawSpike(left5);

		}


		if ((miliseconds >= msStart + 40.5) && (miliseconds <= msStart + 42)) {

			if (miliseconds >= msStart + frames) {

				diag7 = drSpike(diag7);
				diag8 = dlSpike(diag8);
				right6 = rightSpike(right6);
				frames += 0.03;

			}

			drawSpike(diag7);
			drawSpike(diag8);
			drawSpike(right6);

		}


		if ((miliseconds >= msStart + 42) && (miliseconds <= msStart + 43.5)) {

			if (miliseconds >= msStart + frames) {

				left6 = leftSpike(left6);
				right7 = rightSpike(right7);
				up6 = upSpike(up6);
				down6 = downSpike(down6);
				frames += 0.03;

			}

			drawSpike(left6);
			drawSpike(right7);
			drawSpike(up6);
			drawSpike(down6);

		}


		if ((miliseconds >= msStart + 43.5) && (miliseconds <= msStart + 45)) {

			if (miliseconds >= msStart + frames) {

				left7 = leftSpike(left7);
				right8 = rightSpike(right8);
				up7 = upSpike(up7);
				down7 = downSpike(down7);
				frames += 0.03;

			}

			drawSpike(left7);
			drawSpike(right8);
			drawSpike(up7);
			drawSpike(down7);

		}


		if ((miliseconds >= msStart + 45) && (miliseconds <= msStart + 46.5)) {

			if (miliseconds >= msStart + frames) {

				left8 = leftSpike(left8);
				right9 = rightSpike(right9);
				up8 = upSpike(up8);
				down8 = downSpike(down8);
				frames += 0.03;

			}

			drawSpike(left8);
			drawSpike(right9);
			drawSpike(up8);
			drawSpike(down8);

		}


		if ((miliseconds >= msStart + 46.5) && (miliseconds <= msStart + 48)) {

			if (miliseconds >= msStart + frames) {

				left9 = leftSpike(left9);
				right10 = rightSpike(right10);
				up9 = upSpike(up9);
				down9 = downSpike(down9);
				frames += 0.03;

			}

			drawSpike(left9);
			drawSpike(right10);
			drawSpike(up9);
			drawSpike(down9);

		}


		if ((miliseconds >= msStart + 48) && (miliseconds <= msStart + 49.5)) {

			if (miliseconds >= msStart + frames) {

				left10 = leftSpike(left10);
				right11 = rightSpike(right11);
				up10 = upSpike(up10);
				down10 = downSpike(down10);
				frames += 0.03;

			}

			drawSpike(left10);
			drawSpike(right11);
			drawSpike(up10);
			drawSpike(down10);

		}

		if ((miliseconds >= msStart + 49.5) && (miliseconds <= msStart + 51)) {

			if (miliseconds >= msStart + frames) {

				diag9 = dlSpike(diag9);
				diag10 = drSpike(diag10);
				diag11 = urSpike(diag11);
				diag12 = ulSpike(diag12);
				frames += 0.03;

			}

			drawSpike(diag9);
			drawSpike(diag10);
			drawSpike(diag11);
			drawSpike(diag12);

		}

		if ((miliseconds >= msStart + 72) && (miliseconds <= msStart + 73.5)) {

			if (miliseconds >= msStart + frames) {

				if (left11.notInitialized) {

					left11 = Spike("left", userRect, 0.0, 1.0, 0.0);

				}

				left11 = leftSpike(left11);
				frames += 0.03;

			}

			drawSpike(left11);

		}

		if ((miliseconds >= msStart + 73.5) && (miliseconds <= msStart + 75)) {

			if (miliseconds >= msStart + frames) {

				if (down11.notInitialized) {

					down11 = Spike("down", userRect, 0.0, 1.0, 0.0);

				}

				down11 = downSpike(down11);
				frames += 0.03;

			}

			drawSpike(down11);

		}

		if ((miliseconds >= msStart + 75) && (miliseconds <= msStart + 76.5)) {

			if (miliseconds >= msStart + frames) {

				if (up11.notInitialized) {

					up11 = Spike("up", userRect, 0.0, 1.0, 0.0);

				}

				up11 = upSpike(up11);
				frames += 0.03;

			}

			drawSpike(up11);

		}

		if ((miliseconds >= msStart + 76.5) && (miliseconds <= msStart + 78)) {

			if (miliseconds >= msStart + frames) {

				if (left12.notInitialized && down12.notInitialized) {

					left12 = Spike("left", userRect, 1.0, 0.0, 1.0);
					down12 = Spike("down", userRect, 1.0, 0.0, 1.0);

				}

				left12 = leftSpike(left12);
				down12 = downSpike(down12);

				drawSpike(left12);
				drawSpike(down12);

				frames += 0.03;

			}

			drawSpike(left12);
			drawSpike(down12);

		}

		if ((miliseconds >= msStart + 78) && (miliseconds <= msStart + 79.5)) {

			if (miliseconds >= msStart + frames) {

				if (right12.notInitialized && up12.notInitialized) {

					right12 = Spike("right", userRect, 1.0, 0.0, 1.0);
					up12 = Spike("up", userRect, 1.0, 0.0, 1.0);

				}

				right12 = rightSpike(right12);
				up12 = upSpike(up12);
				frames += 0.03;

			}

			drawSpike(right12);
			drawSpike(up12);

		}

		if ((miliseconds >= msStart + 79.5) && (miliseconds <= msStart + 81)) {

			if (miliseconds >= msStart + frames) {

				if (left13.notInitialized && right13.notInitialized) {

					left13 = Spike("left", userRect, 1.0, 1.0, 0.0);
					right13 = Spike("right", userRect, 1.0, 1.0, 0.0);

				}

				left13 = leftSpike(left13);
				right13 = rightSpike(right13);
				frames += 0.03;

			}

			drawSpike(left13);
			drawSpike(right13);

		}

		if ((miliseconds >= msStart + 79.5) && (miliseconds <= msStart + 84)) {

			if (power1Check == 0) {

				powerUp1();

			}

		}

		if ((miliseconds >= msStart + 81) && (miliseconds <= msStart + 82.5)) {

			if (miliseconds >= msStart + frames) {

				up13 = upSpike(up13);
				down13 = downSpike(down13);
				frames += 0.03;

			}

			drawSpike(up13);
			drawSpike(down13);

		}

		if ((miliseconds >= msStart + 82.5) && (miliseconds <= msStart + 84)) {

			if (miliseconds >= msStart + frames) {

				if (left14.notInitialized && right14.notInitialized && down14.notInitialized) {

					left14 = Spike("left", userRect, 1.0, 1.0, 0.0);
					right14 = Spike("right", userRect, 1.0, 1.0, 0.0);
					down14 = Spike("down", userRect, 1.0, 0.0, 1.0);

				}

				left14 = leftSpike(left14);
				right14 = rightSpike(right14);
				down14 = downSpike(down14);
				frames += 0.03;

			}

			drawSpike(left14);
			drawSpike(right14);
			drawSpike(down14);

		}

		if ((miliseconds >= msStart + 84) && (miliseconds <= msStart + 85.5)) {

			if (miliseconds >= msStart + frames) {

				diag13 = urSpike(diag13);
				diag14 = ulSpike(diag14);
				frames += 0.03;

			}

			drawSpike(diag13);
			drawSpike(diag14);

		}

		if ((miliseconds >= msStart + 85.5) && (miliseconds <= msStart + 87)) {

			if (miliseconds >= msStart + frames) {

				up13 = upSpike(up13);
				up14 = upSpike(up14);
				up15 = upSpike(up15);
				up16 = upSpike(up16);
				up17 = upSpike(up17);
				up18 = upSpike(up18);
				up19 = upSpike(up19);
				up20 = upSpike(up20);
				up22 = upSpike(up22);
				frames += 0.03;

			}

			drawSpike(up13);
			drawSpike(up14);
			drawSpike(up15);
			drawSpike(up16);
			drawSpike(up17);
			drawSpike(up18);
			drawSpike(up19);
			drawSpike(up20);
			drawSpike(up22);

		}

		if ((miliseconds >= msStart + 87) && (miliseconds <= msStart + 88.5)) {

			if (miliseconds >= msStart + frames) {

				if (left15.notInitialized && down15.notInitialized) {

					left15 = Spike("left", userRect, 1.0, 0.0, 0.0);
					down15 = Spike("down", userRect, 1.0, 0.0, 0.0);

				}

				left15 = leftSpike(left15);
				down15 = downSpike(down15);
				frames += 0.03;

			}

			drawSpike(left15);
			drawSpike(down15);

		}

		if ((miliseconds >= msStart + 88.5) && (miliseconds <= msStart + 90)) {

			if (miliseconds >= msStart + frames) {

				if (right15.notInitialized && up23.notInitialized && down16.notInitialized) {

					right15 = Spike("right", userRect, 1.0, 0.0, 1.0);
					up23 = Spike("up", userRect, 1.0, 0.0, 1.0);
					down16 = Spike("down", userRect, 1.0, 0.0, 1.0);

				}

				right15 = rightSpike(right15);
				up23 = upSpike(up23);
				down16 = downSpike(down16);
				frames += 0.03;

			}

			drawSpike(right15);
			drawSpike(up23);
			drawSpike(down16);

		}

		if ((miliseconds >= msStart + 90) && (miliseconds <= msStart + 91.5)) {

			if (miliseconds >= msStart + frames) {

				if (left16.notInitialized) {

					left16 = Spike("left", userRect, 1.0, 1.0, 0.0);

				}

				left16 = leftSpike(left16);
				diag15 = dlSpike(diag15);
				frames += 0.03;

			}

			drawSpike(left16);
			drawSpike(diag15);

		}

		if ((miliseconds >= msStart + 91.5) && (miliseconds <= msStart + 93)) {

			if (miliseconds >= msStart + frames) {

				if (left17.notInitialized && right17.notInitialized && down17.notInitialized) {

					left17 = Spike("left", userRect, 1.0, 0.0, 1.0);
					right17 = Spike("right", userRect, 1.0, 0.0, 1.0);
					down17 = Spike("down", userRect, 1.0, 0.0, 0.0);

				}

				left17 = leftSpike(left17);
				right17 = rightSpike(right17);
				down17 = downSpike(down17);
				frames += 0.03;

			}

			drawSpike(left17);
			drawSpike(right17);
			drawSpike(down17);

		}

		if ((miliseconds >= msStart + 93) && (miliseconds <= msStart + 94.5)) {

			if (miliseconds >= msStart + frames) {

				if (up24.notInitialized) {

					up24 = Spike("up", userRect, 1.0, 1.0, 0.0);

				}

				up24 = upSpike(up24);
				diag16 = drSpike(diag16);
				frames += 0.03;

			}

			drawSpike(up24);
			drawSpike(diag16);

		}

		if ((miliseconds >= msStart + 94.5) && (miliseconds <= msStart + 96)) {

			if (miliseconds >= msStart + frames) {

				left18 = leftSpike(left18);
				right18 = rightSpike(right18);
				down18 = downSpike(down18);
				frames += 0.03;

			}

			drawSpike(left18);
			drawSpike(right18);
			drawSpike(down18);

			power1Check = false;

		}

		if ((miliseconds >= msStart + 96) && (miliseconds <= msStart + 97.5)) {

			if (miliseconds >= msStart + frames) {

				if (left19.notInitialized && right19.notInitialized && up25.notInitialized&& down19.notInitialized) {

					left19 = Spike("left", userRect, 1.0, 1.0, 0.0);
					right19 = Spike("right", userRect, 1.0, 1.0, 0.0);
					up25 = Spike("up", userRect, 1.0, 1.0, 0.0);
					down19 = Spike("down", userRect, 1.0, 1.0, 0.0);

				}

				left19 = leftSpike(left19);
				right19 = rightSpike(right19);
				up25 = upSpike(up25);
				down19 = downSpike(down19);
				frames += 0.03;

			}

			drawSpike(left19);
			drawSpike(right19);
			drawSpike(up25);
			drawSpike(down19);

		}

		if ((miliseconds >= msStart + 97.5) && (miliseconds <= msStart + 99)) {

			if (miliseconds >= msStart + frames) {

				diag17 = dlSpike(diag17);
				diag18 = drSpike(diag18);
				diag19 = urSpike(diag19);
				diag20 = ulSpike(diag20);
				frames += 0.03;

			}

			drawSpike(diag17);
			drawSpike(diag18);
			drawSpike(diag19);
			drawSpike(diag20);

		}

		if ((miliseconds >= msStart + 97.5) && (miliseconds <= msStart + 100.5)) {

			if (power1Check == false) {

				powerUp1();

			}

		}

		if ((miliseconds >= msStart + 99) && (miliseconds <= msStart + 100.5)) {

			if (miliseconds >= msStart + frames) {

				left20 = leftSpike(left20);
				frames += 0.03;

			}

			drawSpike(left20);

		}

		if ((miliseconds >= msStart + 100.5) && (miliseconds <= msStart + 102)) {

			if (miliseconds >= msStart + frames) {

				down20 = downSpike(down20);
				down21 = downSpike(down21);
				down22 = downSpike(down22);
				down23 = downSpike(down23);
				down24 = downSpike(down24);
				down25 = downSpike(down25);
				down26 = downSpike(down26);
				down27 = downSpike(down27);
				frames += 0.03;

			}

			drawSpike(down20);
			drawSpike(down21);
			drawSpike(down22);
			drawSpike(down23);
			drawSpike(down24);
			drawSpike(down25);
			drawSpike(down26);
			drawSpike(down27);

		}

		if ((miliseconds >= msStart + 118) && (miliseconds <= msStart + 120)) {

			if (power1Check == 0) {

				powerUp1();

			}

		}

		if ((miliseconds >= msStart + 118.5) && (miliseconds <= msStart + 120)) {

			if (miliseconds >= msStart + frames) {

				right20 = rightSpike(right20);
				right21 = rightSpike(right21);
				right22 = rightSpike(right22);
				right23 = rightSpike(right23);
				right24 = rightSpike(right24);
				right25 = rightSpike(right25);
				right26 = rightSpike(right26);
				right27 = rightSpike(right27);
				frames += 0.03;

			}

			drawSpike(right20);
			drawSpike(right21);
			drawSpike(right22);
			drawSpike(right23);
			drawSpike(right24);
			drawSpike(right25);
			drawSpike(right26);
			drawSpike(right27);

		}

		if ((miliseconds >= msStart + 120) && (miliseconds <= msStart + 121.5)) {

			if (miliseconds >= msStart + frames) {

				up21 = upSpike(up21);
				up26 = upSpike(up26);
				up27 = upSpike(up27);
				up28 = upSpike(up28);
				up29 = upSpike(up29);
				up30 = upSpike(up30);
				up31 = upSpike(up31);
				up32 = upSpike(up32);
				frames += 0.03;

			}

			drawSpike(up21);
			drawSpike(up26);
			drawSpike(up27);
			drawSpike(up28);
			drawSpike(up29);
			drawSpike(up30);
			drawSpike(up31);
			drawSpike(up32);

		}

		if ((miliseconds >= msStart + 121.5) && (miliseconds <= msStart + 123.5)) {

			if (miliseconds >= msStart + frames) {

				down28 = downSpike(down28);
				down29 = downSpike(down29);
				down30 = downSpike(down30);
				down31 = downSpike(down31);
				down32 = downSpike(down32);
				down33 = downSpike(down33);
				down34 = downSpike(down34);
				down35 = downSpike(down35);

				if (miliseconds >= msStart + 121.75) {

					down36 = downSpike(down36);

				}

				frames += 0.03;

			}

			drawSpike(down28);
			drawSpike(down29);
			drawSpike(down30);
			drawSpike(down31);
			drawSpike(down32);
			drawSpike(down33);
			drawSpike(down34);
			drawSpike(down35);
			drawSpike(down36);

		}

		if ((miliseconds >= msStart + 123.5) && (miliseconds <= msStart + 126.5)) {

			if (power3Check == 0) {

				powerUp3();

			}

			if (miliseconds >= msStart + frames) {

				if (power3Check == 0) {

					up33 = upSpike(up33);
					up34 = upSpike(up34);
					up35 = upSpike(up35);
					up36 = upSpike(up36);
					up37 = upSpike(up37);
					up38 = upSpike(up38);
					up39 = upSpike(up39);
					up40 = upSpike(up40);
					up41 = upSpike(up41);
					up42 = upSpike(up42);

					left21 = leftSpike(left21);
					left22 = leftSpike(left22);
					left23 = leftSpike(left23);
					left24 = leftSpike(left24);
					left25 = leftSpike(left25);
					left26 = leftSpike(left26);
					left27 = leftSpike(left27);
					left28 = leftSpike(left28);
					left29 = leftSpike(left29);
					left30 = leftSpike(left30);

					frames += 0.03;

				}

				if (power3Check == 1) {

					up33 = downSpike(up33);
					up34 = downSpike(up34);
					up35 = downSpike(up35);
					up36 = downSpike(up36);
					up37 = downSpike(up37);
					up38 = downSpike(up38);
					up39 = downSpike(up39);
					up40 = downSpike(up40);
					up41 = downSpike(up41);
					up42 = downSpike(up42);

					left21 = rightSpike(left21);
					left22 = rightSpike(left22);
					left23 = rightSpike(left23);
					left24 = rightSpike(left24);
					left25 = rightSpike(left25);
					left26 = rightSpike(left26);
					left27 = rightSpike(left27);
					left28 = rightSpike(left28);
					left29 = rightSpike(left29);
					left30 = rightSpike(left30);

					frames += 0.03;

				}

			}

			drawSpike(up33);
			drawSpike(up34);
			drawSpike(up35);
			drawSpike(up36);
			drawSpike(up37);
			drawSpike(up38);
			drawSpike(up39);
			drawSpike(up40);
			drawSpike(up41);
			drawSpike(up42);

			drawSpike(left21);
			drawSpike(left22);
			drawSpike(left23);
			drawSpike(left24);
			drawSpike(left25);
			drawSpike(left26);
			drawSpike(left27);
			drawSpike(left28);
			drawSpike(left29);
			drawSpike(left30);

		}

		if ((miliseconds >= msStart + 126.5) && (miliseconds <= msStart + 132.5)) {

			if (power4Check == 0) {

				powerUp4();

			}

			if (miliseconds >= msStart + frames) {

				if (power4Check == 0) {

					up43 = upSpike(up43);
					up44 = upSpike(up44);
					up45 = upSpike(up45);
					up46 = upSpike(up46);
					up47 = upSpike(up47);
					up48 = upSpike(up48);
					up49 = upSpike(up49);
					up50 = upSpike(up50);
					up51 = upSpike(up51);
					up52 = upSpike(up52);

					right28 = rightSpike(right28);
					right29 = rightSpike(right29);
					right30 = rightSpike(right30);
					right31 = rightSpike(right31);
					right32 = rightSpike(right32);
					right33 = rightSpike(right33);
					right34 = rightSpike(right34);
					right35 = rightSpike(right35);
					right36 = rightSpike(right36);
					right37 = rightSpike(right37);

					down37 = downSpike(down37);
					down38 = downSpike(down38);
					down39 = downSpike(down39);
					down40 = downSpike(down40);
					down41 = downSpike(down41);
					down42 = downSpike(down42);
					down43 = downSpike(down43);
					down44 = downSpike(down44);
					down45 = downSpike(down45);
					down46 = downSpike(down46);

					frames += 0.03;

				}

				if (power4Check == 1) {

					up43 = downSpike(up43);
					up44 = downSpike(up44);
					up45 = downSpike(up45);
					up46 = downSpike(up46);
					up47 = downSpike(up47);
					up48 = downSpike(up48);
					up49 = downSpike(up49);
					up50 = downSpike(up50);
					up51 = downSpike(up51);
					up52 = downSpike(up52);

					right28 = leftSpike(right28);
					right29 = leftSpike(right29);
					right30 = leftSpike(right30);
					right31 = leftSpike(right31);
					right32 = leftSpike(right32);
					right33 = leftSpike(right33);
					right34 = leftSpike(right34);
					right35 = leftSpike(right35);
					right36 = leftSpike(right36);
					right37 = leftSpike(right37);

					down37 = upSpike(down37);
					down38 = upSpike(down38);
					down39 = upSpike(down39);
					down40 = upSpike(down40);
					down41 = upSpike(down41);
					down42 = upSpike(down42);
					down43 = upSpike(down43);
					down44 = upSpike(down44);
					down45 = upSpike(down45);
					down46 = upSpike(down46);

					frames += 0.03;

				}

			}

			drawSpike(up43);
			drawSpike(up44);
			drawSpike(up45);
			drawSpike(up46);
			drawSpike(up47);
			drawSpike(up48);
			drawSpike(up49);
			drawSpike(up50);
			drawSpike(up51);
			drawSpike(up52);

			drawSpike(right28);
			drawSpike(right29);
			drawSpike(right30);
			drawSpike(right31);
			drawSpike(right32);
			drawSpike(right33);
			drawSpike(right34);
			drawSpike(right35);
			drawSpike(right36);
			drawSpike(right37);

			drawSpike(down37);
			drawSpike(down38);
			drawSpike(down39);
			drawSpike(down40);
			drawSpike(down41);
			drawSpike(down42);
			drawSpike(down43);
			drawSpike(down44);
			drawSpike(down45);
			drawSpike(down46);

		}

		if (miliseconds > msEnd) {

			playCheck = false;
			PlaySound("Runescape.wav", NULL, SND_LOOP | SND_ASYNC);

		}

		return coin;

	}

};



// Tile class for puzzles
class Tile
	{
		double x, y;
		int type; // 9 is empty square
	public:
		Tile(int placement, double X=0, double Y=0)
		{
			type = placement;
			x = X; y = Y;
		}
		// checks if (X, Y) are within the tile
		bool contains(double X, double Y)
		{
			if (X >= x && X <= x+0.5 && Y >= y-0.5 && Y <= y)
			{
				return true;
			}
			return false;
		}
		double getX(){return x;}
		double getY(){return y;}
		void setX(double X){x = X;}
		void setY(double Y){y = Y;}
		// swaps data with Tile t
		void swap(Tile* t)
		{
			/*double xTemp = t->getX(), yTemp = t->getY();
			cout << "PUZZLE::SWAP: getting (" << xTemp << ", " << yTemp << ")\n";
			t->setX(x); t->setY(y);
			cout << "PUZZLE::SWAP: giving (" << x << ", " << y << ")\n";
			x = xTemp; y = yTemp;*/
			int temp = t->getType();
			t->setType(type);
			type = temp;
		}
		int getType(){return type;};
		void setType(int t){type = t;}
		bool isEmpty()
		{
			if (type == 9)
			{
				return true;
			}
			return false;
		}
		// design a 3x3 tiled picture * each tile is 0.5x0.5
		void draw()
		{
			switch (type)
			{
				case 1:
					//cout << type << " ";
					glColor3d(1,1,1); // white
					glBegin(GL_POLYGON);
					glVertex2d(x,y);
					glVertex2d(x+0.5,y);
					glVertex2d(x+0.5,y-0.5);
					glVertex2d(x,y-0.5);
					glEnd();
					return;
				case 2:
					//cout << type << " ";
					glColor3d(1,0,0); // red
					glBegin(GL_POLYGON);
					glVertex2d(x,y);
					glVertex2d(x+0.5,y);
					glVertex2d(x+0.5,y-0.5);
					glVertex2d(x,y-0.5);
					glEnd();
					return;
				case 3:
					//cout << type << " ";
					glColor3d(1,0.5,0); // orange
					glBegin(GL_POLYGON);
					glVertex2d(x,y);
					glVertex2d(x+0.5,y);
					glVertex2d(x+0.5,y-0.5);
					glVertex2d(x,y-0.5);
					glEnd();
					return;
				case 4:
					//cout << type << " ";
					glColor3d(1,1,0); // yellow
					glBegin(GL_POLYGON);
					glVertex2d(x,y);
					glVertex2d(x+0.5,y);
					glVertex2d(x+0.5,y-0.5);
					glVertex2d(x,y-0.5);
					glEnd();
					return;
				case 5:
					//cout << type << " ";
					glColor3d(0,1,0); // green
					glBegin(GL_POLYGON);
					glVertex2d(x,y);
					glVertex2d(x+0.5,y);
					glVertex2d(x+0.5,y-0.5);
					glVertex2d(x,y-0.5);
					glEnd();
					return;
				case 6:
					//cout << type << " ";
					glColor3d(0,0,1); // blue
					glBegin(GL_POLYGON);
					glVertex2d(x,y);
					glVertex2d(x+0.5,y);
					glVertex2d(x+0.5,y-0.5);
					glVertex2d(x,y-0.5);
					glEnd();
					return;
				case 7:
					//cout << type << " ";
					glColor3d(0.5,0,1); // indigo
					glBegin(GL_POLYGON);
					glVertex2d(x,y);
					glVertex2d(x+0.5,y);
					glVertex2d(x+0.5,y-0.5);
					glVertex2d(x,y-0.5);
					glEnd();
					return;
				case 8:
					//cout << type << " ";
					glColor3d(1,0,1); // violet
					glBegin(GL_POLYGON);
					glVertex2d(x,y);
					glVertex2d(x+0.5,y);
					glVertex2d(x+0.5,y-0.5);
					glVertex2d(x,y-0.5);
					glEnd();
					return;
				case 9: // empty square @ bottom right corner
					//cout << type << " ";
					glColor3d(0,0,0); // black
					glBegin(GL_POLYGON);
					glVertex2d(x,y);
					glVertex2d(x+0.5,y);
					glVertex2d(x+0.5,y-0.5);
					glVertex2d(x,y-0.5);
					glEnd();
					return;
			}
		}
	};
// creates a sliding tiles puzzle square(1.5x1.5) at (-0.75, 0.75)
class PuzzleTiles : public Game
{
	vector< vector<Tile*> > pieces;//(3, vector<Tile*>(3)); // address with pieces[row][col]
	// returns random value between 1 and a
	double random(int a, double floor = 1)
	{
		random_device rd;
		return (double) (rd()%a+floor); // for windows
		//return (double) (rand()%a)+1.0+floor;	// for linux
	}
	bool won;
public:
	// creates puzzle with randomly assigned tile piece to each position
	PuzzleTiles()
	{
		won = false;
		playCheck = false;
		coin = '0';
		pieces = vector< vector<Tile*> >(3, vector<Tile*>(3));
		double X = 0, Y = 0, placement = 0;
		vector<int> ints(9, 0);
		for (int i = 1; i < 10; ++i)
		{
			bool repeat = true;
			do
			{
				placement = (int)random(9)-1; // maybe 8?
				if (ints[placement] == 0)
				{
					ints[placement] = i;
					repeat = false;
				}
			}while(repeat);
		}
		for (int i = 0; i < 3; ++i) // i = row
		{
			switch (i)
			{
				case 0:
					//X = -0.75;
					Y = 0.75;
					break;
				case 1:
					//X = -0.25;
					Y = 0.25;
					break;
				default:
					//X = 0.25;
					Y = -0.25;
					break;
			}
			for (int j = 0; j < 3; ++j) // j = col
			{
				switch (j)
				{
					case 0:
						//Y = 0.75;
						X = -0.75;
						break;
					case 1:
						//Y = 0.25;
						X = -0.25;
						break;
					default:
						//Y = -0.25;
						X = 0.25;
						break;
				}
				pieces[i][j] = new Tile(ints[0], X, Y);
				ints.erase(ints.begin());
			}
		}
	}
	bool contains(double X, double Y)
	{
		if (X >= -0.75 && X <= 0.75 && Y >= -0.75 && Y <= 0.75)
		{
			return true;
		}
		return false;
	}

	// checks if puzzle pieces are in correct positions
	bool win()
	{
		if (pieces[0][0]->getType() == 1
			&&
			pieces[0][1]->getType() == 2
			&&
			pieces[0][2]->getType() == 3
			&&
			pieces[1][0]->getType() == 4
			&&
			pieces[1][1]->getType() == 5
			&&
			pieces[1][2]->getType() == 6
			&&
			pieces[2][0]->getType() == 7
			&&
			pieces[2][1]->getType() == 8
			&&
			pieces[2][2]->getType() == 9
			)
			{won = true; return true;}
		return false;
	}
	// selects Tile at (X, Y) and swaps with adjacent empty square
	void click(double X , double Y)
	{
		Tile* selected;
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				if (pieces[i][j]->contains(X, Y))
				{
					selected = pieces[i][j];
					bool swapped = false;
					switch (i)
					{
						case 2:
						case 1:
							if (pieces[i-1][j]->isEmpty())
							{
								selected->swap(pieces[i-1][j]);
								swapped = true;
								i = j = 4;
								PlaySound("soft-hitclap.wav", NULL, SND_ASYNC); // SND_FILENAME
								break;
							}
							if (i == 2)
							{
								break;
							}
						case 0:
							if (pieces[i+1][j]->isEmpty())
							{
								selected->swap(pieces[i+1][j]);
								swapped = true;
								i = j = 4;
								PlaySound("soft-hitclap.wav", NULL, SND_ASYNC);
								break;
							}
					};
					if (!swapped)
					{
						switch (j)
						{
							case 2:
							case 1:
								if (pieces[i][j-1]->isEmpty())
								{
									selected->swap(pieces[i][j-1]);
									swapped = true;
									i = j = 4;
									PlaySound("soft-hitclap.wav", NULL, SND_ASYNC);
									break;
								}
								if (j == 2)
								{
									break;
								}
							case 0:
								if (pieces[i][j+1]->isEmpty())
								{
									selected->swap(pieces[i][j+1]);
									i = j = 4;
									PlaySound("soft-hitclap.wav", NULL, SND_ASYNC);
									break;
								}
						};
					}
				}
			}
		}
		if (win())
		{
			cout << "CONGRATULATIONS\nYOU'VE WON!" << endl; // do something for this.
			coin = '1';
		}
	}
	// for testing purposes only. Returns the coordinate of each tile's top right corner
	void checkPos()
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				cout << "(" << pieces[i][j]->getX() << ", " << pieces[i][j]->getY() << ") ";
			}
			cout << endl;
		}
	}
	// this should be called draw, but ok
	char play()
	{

		seconds = time(NULL);
		int I = 0, J = 0;
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				pieces[i][j]->draw();
			}
			//cout << endl; // testing
		}
		if ((seconds > endTime) || won)
		{
			playCheck = false;
			Sleep(4000);
			PlaySound("Runescape.wav", NULL, SND_ASYNC | SND_LOOP);
			return coin;
		}
		glColor3d(0.6, 0.6, 0.6);
		glRasterPos2f(-0.75, 0.8);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("White Red Orange Yellow Green Blue Indigo Violet Black"));

		glColor3d(0.6, 0.6, 0.6);
		glRasterPos2f(0.35, -0.9);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("Time Remaining:"));

		glColor3d(0.6, 0.6, 0.6);
		glRasterPos2f(0.8, -0.9);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)(to_string(endTime - time(NULL)).c_str())); //Displays Remaining Time
		return coin;
	}
	// does nothing with keyboard event
	void key(char e){return;}
	// does nothing with mouse movement
	void motion(double x, double y){return;}
};

class BrickBreaker : public Game {
public:

	GrRect playerBrick;
	GrRect playerBall;

	float velocityX;
	float velocityY;
	float miliseconds;
	float frames;
	int BRICKS;
	GrRect bricks[35];
	GrRect background;
	GLuint paddle;

	BrickBreaker() {
		BRICKS = 35;
		velocityX = 0.025;
		velocityY = 0.025;
		frames = 0.03;

		playerBrick = GrRect(-0.18, -0.91, 0.3, 0.060, 0.0, 0.0, 1.0);
		playerBrick.zValue = 0.98;
		playerBrick.noBar = true;

		playerBall = GrRect(-0.7, -0.4, 0.08, 0.08, 1.0, 0.0, 0.0);
		playerBall.zValue = 0.98;
		playerBall.noBar = true;

		background = GrRect(-1.0, 1.0, 2.0, 2.0);
		background.noBar = true;
		background.zValue = 0.999;

		bg = SOIL_load_OGL_texture(
			"Hallow.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

		paddle = SOIL_load_OGL_texture(
			"img1.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);


		for (int i = 0, x = -98, y = 95; i < BRICKS; i++, x += 28) {
			if (x > 90) {
				x = -98;
				y -= 12;
			}
			bricks[i].upleftX = x / 100.0f;
			bricks[i].upleftY = y / 100.0f;
			bricks[i].width = 0.26;
			bricks[i].height = 0.1;
			bricks[i].r = 0.0;
			bricks[i].g = 1.0;
			bricks[i].b = 0.0;
			bricks[i].zValue = 0.98;
			bricks[i].noBar = true;
			bricks[i].displayBrick = true;

		}

		coin = '1';

	}



	void leftKey(bool check) {
		if (check) {
			playerBrick.upleftX -= 0.1;

		}
		if (playerBrick.upleftX < -1.0) {
			playerBrick.upleftX = -1.0;
		}

	}

	void rightKey(bool check) {
		if (check) {
			playerBrick.upleftX += 0.1;
		}
		if (playerBrick.upleftX + playerBrick.width > 1.0) {
			playerBrick.upleftX = 1.0 - playerBrick.width;
		}
	}

	void drawPlayerBrick() {
		playerBrick.draw();
	}

	void drawPlayerBall() {
		playerBall.draw();
	}

	void drawBricks() {
		for (int i = 0; i < BRICKS; i++) {
			if (bricks[i].displayBrick == true) {
				if (i % 2 == 0) {
					bricks[i].r = 0.2;
					bricks[i].g = 0.4;
					bricks[i].b = 0.0;
				}
				bricks[i].draw();
			}
		}
	}

	bool noBricks()
	{
		for (unsigned int i = 0; i < BRICKS; ++i)
		{
			if (bricks[i].displayBrick)
			{
				coin = '0';
				return false;
			}
		}
		coin = '1';
		return true;
	}

	bool checkCollision(float Ax, float Ay, float Aw, float Ah, float Bx, float By, float Bw, float Bh) {
		if (Ay + Ah < By) {
			return false;
		}
		if (Ay > By + Bh) {
			return false;
		}
		if (Ax + Aw < Bx) {
			return false;
		}
		if (Ax > Bx + Bw) {
			return false;
		}
		PlaySound("taiko-normal-hitwhistle.wav", NULL, SND_ASYNC); // SND_FILENAME
		return true;
	}
	void movePlayerBall() {
		playerBall.upleftX -= velocityX;			//check collision on x axis
		for (int i = 0; i < BRICKS; i++) {
			if (bricks[i].displayBrick == true) {
				if (checkCollision(playerBall.upleftX, playerBall.upleftY, playerBall.width, playerBall.height, bricks[i].upleftX, bricks[i].upleftY, bricks[i].width, bricks[i].height) == true) {
					velocityX = -velocityX;
					bricks[i].displayBrick = false;
					break;
				}
			}
		}

		playerBall.upleftY += velocityY;			//check collision on y axis
		for (int i = 0; i < BRICKS; i++) {
			if (bricks[i].displayBrick == true) {
				if (checkCollision(playerBall.upleftX, playerBall.upleftY, playerBall.width, playerBall.height, bricks[i].upleftX, bricks[i].upleftY, bricks[i].width, bricks[i].height) == true) {
					velocityY = -velocityY;
					bricks[i].displayBrick = false;
					break;
				}
			}
		}

		if (playerBall.upleftX < -1.0) {
			velocityX = -velocityX;
		}
		else if (playerBall.upleftX + playerBall.width > 1.0) {
			velocityX = -velocityX;
		}

		if (playerBall.upleftY < -0.91) {
			playCheck = false;
			coin = '0';
			PlaySound("Death.wav", NULL, SND_ASYNC);
			Sleep(4000);
			PlaySound("Runescape.wav", NULL, SND_ASYNC | SND_LOOP);
		}
		else if (playerBall.upleftY + playerBall.height > 1.0) {
			velocityY = -velocityY;
		}

		if (checkCollision(playerBrick.upleftX, playerBrick.upleftY, playerBrick.width, playerBrick.height, playerBall.upleftX, playerBall.upleftY, playerBall.width, playerBall.height) == true) {
			velocityY = -velocityY;
		}
	}

	char play() {

		background.draw(bg);

		playerBrick.draw(paddle);

		miliseconds = glutGet(GLUT_ELAPSED_TIME);
		miliseconds = miliseconds / 1000;
		drawPlayerBrick();

		drawPlayerBall();

		drawBricks();

		if (miliseconds <= msStart + 500) {
			if (miliseconds >= msStart + frames) {
				movePlayerBall();
				frames += 0.03;
			}
		}
		if (noBricks())
		{
			playCheck = false;
		}
		return coin;

	}

};

// Projectile class for Aliens and Players
class Projectile
{
	double x, y;
	bool up;
	Ticker timer;
public:
	// construct projectile with direction and coordinates
	Projectile(bool UpIfPlayer, double X, double Y = -1.5)
	{
		up = UpIfPlayer;
		x = X;
		y = Y;
		timer = Ticker();
		timer.durationMS(20);
	}
	// draw the projectile
	void draw()
	{
		if (up)
		{
			if (timer.passMS())
			{
				y += 0.01; // traverse distance 0.05
				timer.durationMS(20);
			}
			glColor3d(1,1,1);
			glBegin(GL_POLYGON); // circle of radius 0.05 ?
			for (double i = -0.025; i <= 0.025; i += (2*0.025/100))
			{
				glVertex2d(x+i, y+sqrt(0.025*0.025-i*i)); // top half 
				glVertex2d(x+i, y-sqrt(0.025*0.025-i*i)); // bot half
			}
			glEnd();
		}
		else
		{

			if (timer.passMS())
			{
				y -= 0.02; // traverse distance 0.05
				timer.durationMS(25);
			}
			glColor3d(1,0,0);
			glBegin(GL_POLYGON); // circle of radius 0.05 ?
			for (double i = -0.025; i <= 0.025; i += (2*0.025/100))
			{
				glVertex2d(x+i, y+sqrt(0.025*0.025-i*i)); // top half 
				glVertex2d(x+i, y-sqrt(0.025*0.025-i*i)); // bot half
			}
			glEnd();
		}
	}
	vector<Vec*> coords()
	{
		vector<Vec*> v;
			for (double i = -0.025; i <= 0.025; i += (2*0.025/25))
			{
				v.push_back(new Vec(x+i, y+sqrt(0.025*0.025-i*i)));
				v.push_back(new Vec(x+i, y-sqrt(0.025*0.025-i*i)));
			}
		return v;	
	}
	bool out()
	{
		if (y >= 0.85 || y <= -0.5)
		{
			return true;
		}
		return false;
	}
};
// Player class for Alien invaders
class Player
{
	Ticker timer;
	Ticker move;
public:
	double x; // y is -0.5
	vector<Projectile*> proj;
	Player(){
		timer = Ticker();
		x = 0;
		timer.durationMS(500);
		move = Ticker();
		move.durationMS(44);
	}
	bool contains(double X, double Y)
	{
		return (X >= x-0.2 && X <= x+0.2 && Y >= 0.5 && Y <= 0.2);
	}
	void keyboard(char e)
	{
		if (e == ' ')
		{
			shoot();
		}

		if (move.passMS())
		{
			if ((e == 'a' || e == 'A') && x >= -1)
			{
				x -= 0.04; // move left
			}
			else if ((e == 'd' || e == 'D') && x <= 1)
			{
				x += 0.04; // move right
			}
			move.durationMS(30);
		}
	}
	void shoot()
	{
		if (timer.passMS())
		{
			PlaySound("projectiles.wav", NULL, SND_ASYNC); // SND_FILENAME
			proj.push_back(new Projectile(true, x, -0.35));
			timer.durationMS(500);
		}
	}
	void draw()
	{
		glColor3d(1,0,0);
		glBegin(GL_POLYGON);
		glVertex2d(x-0.05, -0.4); // player height is 0.1
		glVertex2d(x-0.05, -0.5);
		glVertex2d(x+0.05, -0.5); ///////////// trying -1 as floor
		glVertex2d(x+0.05, -0.4);
		glEnd();
	}
	void projectiles()
	{
		for (unsigned int i = 0; i < proj.size(); ++i)
		{
			if (proj[i]->out())
			{
				proj.erase(proj.begin()+i);
			}
			else
			{
				proj[i]->draw();
			}
		}
	}
	bool contains(vector<Vec*> v)
	{
		for (unsigned int i = 0; i < v.size(); ++i)
		{
			if (v[i]->x <= x+0.05 && v[i]->x >= x-0.05 && v[i]->y <= -0.4 && v[i]->y >= -0.5)
			{
				return true;
			}
		}
		return false;
	}
};
// Alien class for Alien Invaders
class Alien
{
	double x, y, x1;
	bool right;
	Ticker timer;
	Ticker cooldown;
	Ticker invul;
	int health;
public:
	vector<Projectile*> proj;
	Alien(double X, double Y)
	{
		x = x1 = X;
		y = Y;
		health = 3;
		right = true;
		timer = Ticker();
		timer.durationMS(1);
		cooldown = Ticker();
		cooldown.durationMS(250);
		invul = Ticker();
		invul.durationMS(444);
	}
	void damage()
	{
		if (invul.passMS())
		{
			--health;
			invul.durationMS(444);
		}
	}
	void shoot()
	{
		if (cooldown.passMS())
		{
			proj.push_back(new Projectile(false, x+0.15, y-0.25));
			cooldown.durationMS(400);
		}
	}
	void shuffle()
	{
		if (timer.passMS()){
			if (right)
			{
				x += 0.01;
				if (x >= x1 + 0.3)
				{
					right = !right;
				}
			}
			else
			{
				x -= 0.01;
				if (x <= x1 - 0.3)
				{
					right = !right;
				}
			}
		timer.durationMS(33); // approx. 30 fps
		}
	}
	bool living(){
		if (health > 0){ return true;}
		return false;
	}
	void draw()
	{
		if (time(NULL)%2 == 0){glColor3d(0,1,0);}
		else{glColor3d(1,0,1);}
		glBegin(GL_POLYGON); // 0.3 x 0.3 ?
		glVertex2d(x, y);
		glVertex2d(x, y-0.3);
		glVertex2d(x+0.3, y-0.3);
		glVertex2d(x+0.3, y);
		glEnd();
		switch(health)
		{
			case 3:
				glColor3d(1,1,0);
				glBegin(GL_LINES);
				glVertex3d(x,y-0.3, -0.1);
				glVertex3d(x, y-0.3-0.2, -0.1);
				glEnd();
			case 2:
				glColor3d(1,1,0);
				glBegin(GL_LINES);
				glVertex3d(x+0.3,y-0.3, -0.1);
				glVertex3d(x+0.3, y-0.3-0.2, -0.1);
				glEnd();
			case 1:
				glColor3d(1,1,0);
				glBegin(GL_LINES);
				glVertex3d(x+0.15,y-0.3, -0.1);
				glVertex3d(x+0.15, y-0.3-0.2, -0.1);
				glEnd();
				break;
		}
		glColor3d(1,0,0);
			glBegin(GL_POLYGON); // circle of radius 0.05 ?
			for (double i = -0.05; i <= 0.05; i += (2*0.05/100))
			{
				glVertex3d(x+i+0.15, y+sqrt(0.05*0.05-i*i)-0.15,-0.1); // top half 
				glVertex3d(x+i+0.15, y-sqrt(0.05*0.05-i*i)-0.15,-0.1); // bot half
			}
			glEnd();
	}
	void projectiles()
	{
		for (unsigned int i = 0; i < proj.size(); ++i)
		{
			if (proj[i]->out())
			{
				proj.erase(proj.begin()+i);
			}
			else
			{
				proj[i]->draw();
			}
		}
	}
	bool contains(vector<Vec*> v)
	{
		for (unsigned int i = 0; i < v.size(); ++i)
		{
			if ( v[i]->x >= x && v[i]->x <= x+0.3 && v[i]->y >= y-0.3 && v[i]->y <= y)
			{
				return true;
			}
		}
		return false;
	}
	bool containsX(double X)
	{
		if (X >= x && X <= x+0.3)
		{
			return true;
		}
		return false;
	}
};
// Alien Invaders game class
class Invaders : public Game
{
	Player p1;
	vector<Alien> aliens;
	Ticker timer;
	Ticker combi;
public:
	Invaders()
	{
		p1 = Player();
		timer = Ticker();
		aliens.push_back(Alien(-0.75, 1));
		aliens.push_back(Alien(-0.35, 1));
		aliens.push_back(Alien(0.05, 1));
		aliens.push_back(Alien(0.45, 1));
		timer.durationMS(750);
		combi = Ticker();
		combi.durationMS(1000);
		playCheck = false;
		coin = '0';
	}
	bool win()
	{
		return aliens.empty();
	}
	void keyboard(char e)
	{
		p1.keyboard(e);
	}
	char play()
	{

		p1.draw();
		p1.projectiles();
	   for (unsigned int i = 0; i <aliens.size(); ++i){
		   if (aliens[i].containsX(p1.x)){
			aliens[i].shoot();
		   }
		   for (unsigned int j = 0; j < p1.proj.size(); ++j){
			   vector<Vec*> v = p1.proj[j]->coords();
			   if (aliens[i].contains(v)){
				   aliens[i].damage();
			   }
		   }
		   for (unsigned int k = 0; k < aliens[i].proj.size(); ++k){
			    vector<Vec*> v = aliens[i].proj[k]->coords();
				if (p1.contains(v)){
					playCheck = false;
					PlaySound("Death.wav", NULL, SND_ASYNC);
					Sleep(4000);
				}
		   }


		}
	   if (combi.passMS())
	   {
	   		for (unsigned int i = 0; i <aliens.size(); ++i)
	   		{
	   			aliens[i].shoot();
	   		}
	   		combi.durationMS(1000);
	   }
	   for (unsigned int i = 0; i < aliens.size(); ++i){
		   if (aliens[i].living()){
				aliens[i].shuffle();
				aliens[i].draw();
				aliens[i].projectiles();
		   }
		   else
		   {
		   		aliens.erase(aliens.begin()+i);
		   }
		}
		glColor3d(-0.6, 0.6, 0.6);
		glRasterPos2f(-0.75, -0.75);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("A = left\nD = right\nClick to shoot!"));
		if (win())
		{
			coin = '1';
			playCheck = false;
		}
		if (time(NULL) > endTime)
		{
			playCheck = false;
		}
		if(!playCheck)
		{
			PlaySound("Runescape.wav", NULL, SND_ASYNC | SND_LOOP);
		}
		glColor3d(0.6, 0.6, 0.6);
		glRasterPos2f(0.35, -0.9);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)("Time Remaining:"));

		glColor3d(0.6, 0.6, 0.6);
		glRasterPos2f(0.8, -0.9);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)(to_string(endTime - time(NULL)).c_str())); //Displays Remaining Time
		return coin;
	}
	void click(double x, double y) // for mouse click events
	{
		//p1.shoot();
	}
	void mousemove(double x, double y) // for mouse move events
	{
		return;
	}
};



#endif