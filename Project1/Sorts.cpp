#include "Sorts.h"
#include<string>
#include<glut.h>
#include "RGBA.h"
#include <windows.h>
#include "wav.h"
#include<time.h>

using namespace std;

Sorts::Sorts()
{
	//Sort and Hashing Algorithms
}


//Hashing (linear probing starts here)
void drawTextlp(int s1, int x, int y){

	string s = std::to_string(s1);
	glRasterPos2i(x, y);
	for (int i = 0; i < s.length(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s[i]);
	}
}

class Box
{
public:
	int s;
	float x, y, r, g, b;

	void draw()
	{
		glColor3f(r, g, b);
		glRectf(-90, -70, -70, -80);
		glColor3f(0.0, 0.0, 0.0);
		drawTextlp(s, -80, -76);
	}

	void set(int s1, float x1, float y1)
	{

		s = s1;
		x = x1;
		y = y1;
	}
	void setColor(float r1, float g1, float b1)
	{
		r = r1;
		g = g1;
		b = b1;
	}

	void render()
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
		glTranslatef(x, y, 0);
		draw();
		glPopMatrix();

	}


};
RGBApixmap pixlp[1];
int sWidthlp = 800;  int sHeightlp = 800;
float minX = -100.0, maxX = 100.0, minY = -100.0, maxY = 100.0;
float step = 50, angle = 50;
int screenWidth = 800, screenHeight = 800;


#define M_PI (4*atan(1.0f))




void circle(GLint res, GLfloat radius, float x, float y){

	int i;

	glBegin(GL_POLYGON);
	for (i = 0; i<res; i++)
		glVertex2f(radius * cos(2.0*M_PI*i / res) + x, radius * sin(2.0*M_PI*i / res) + y);
	glEnd();
}







void drawBar(int count){

	for (int i = 0; i < count; i++)
	{
		glColor3f(0.0, 0.0, 1.0);
		glRectf(-60.0, 76 - (12 * i), -50.0, 86.0 - (12 * i));
		glColor3f(0.0, 0.0, 0.0);
		circle(20, 3.0, -55, 81 - (12 * i));
		drawTextlp(i, -65, 81 - (12 * i));

	}


}
int nCount = 5;
int iCount = 0;
int t[5] = { 6, 16, 57, 19, 3 };
Box bx[5];
int iMod = 0;
int flagFw = 0;
int xInc = 55;
int xOffset = 60;
int yInc = 144;
int modArr[5];
int modRec[5];

void randomiselp()
{

	for (size_t inc = 0; inc < 5; inc++)
	{
		t[inc] = rand() % 999;

	}
}

int CheckM(int indx){
	int c = 0;
	for (int i = 0; i < nCount; i++)
	{
		bool chkI = true;
		for (int k = 0; k < nCount; k++)
		{
			if (modRec[k] == i){ chkI = false; }
		}
		if (modArr[i] == indx && chkI)
		{
			c = i;
			break;
		}

	}

	return c;
}



void CalculateHashing(){


	for (int i = 0; i < nCount; i++)
	{
		modArr[i] = -1;
	}
	for (int i = 0; i < nCount; i++)
	{
		modRec[i] = -2;
	}
	for (int i = 0; i < nCount; i++)
	{
		int mod = t[i] % nCount;
		int count = mod;
		if (modArr[mod] < 0){
			modArr[mod] = t[i];
		}
		else
		{
			int mCount = mod;
			while (modArr[mCount] > 0)
			{
				mCount++;
				mCount = mCount % nCount;

				if (mCount == mod - 1){ break; }
			}
			if (modArr[mCount] < 0){
				modArr[mCount] = t[i];
			}
		}

	}
}
void displayWinlp(void){


	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);

	pixlp[0].readBMPFile("backGround.bmp");
	glPixelZoom(1, 1);
	glRasterPos2i(-100, -100);
	pixlp[0].mDraw();
	glRasterPos2i(0, 0);





	int modeVal = CheckM(t[iMod]);


	modeVal *= 12;


	drawBar(nCount);

	if (iCount <= nCount){
		for (int i = 0; i < iCount; i++)
		{
			bx[i].setColor(0, 1, 1);
			bx[i].set(t[i], i * 25, 0);
		}
	}
	if (iCount > 2){
		for (int i = 0; i < nCount; i++)
		{
			bx[i].render();

		}
	}


	if (iCount == nCount + 3){

		bx[iMod].setColor(0, 1, 0);
	}
	else if (iCount == nCount + 4)
	{
		bx[iMod].setColor(0, 1, 1);
	}
	else if (iCount == nCount + 5)
	{
		bx[iMod].setColor(0, 1, 0);
	}
	else if (iCount == nCount + 6)
	{
		bx[iMod].setColor(0, 1, 1);
	}
	else if (iCount > nCount + 7 && iCount < nCount + 12)
	{
		bx[iMod].y += 3;
	}
	else if (iCount > nCount + 12 && bx[iMod].x <= xInc && flagFw == 0)
	{
		bx[iMod].x += 5;
	}
	else if (iCount > nCount + 12 && bx[iMod].x > xOffset && flagFw == 0)
	{
		bx[iMod].x -= 5;
	}
	else if (iCount > nCount + 12 && bx[iMod].x >= 55 && bx[iMod].y <= yInc - modeVal && flagFw == 0)
	{

		bx[iMod].y += 12;
	}

	else if (iCount > nCount + 12 && bx[iMod].y > yInc - modeVal){
		modRec[iMod] = CheckM(t[iMod]);
		iMod++; iCount = nCount + 2; flagFw = 0;

	}

	if (iCount < 1000)
		iCount++;


	glutSwapBuffers();
}


void movelp()
{


	glutPostRedisplay();

}



void myInitlp(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);       // background color is white
	glColor3f(0.0f, 0.0f, 0.0f);         // drawing color is black
	glPointSize(2.0);		          // a 'dot' is 2 by 2 pixels
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(minX, maxX, minY, maxY);

}





void menuControllp(int value){

	switch (value){
	case 1:
        glutIdleFunc(movelp);
		break;
	case 2:
		iCount = 0; iMod = 0; flagFw = 0;
		xInc = 55;
		xOffset = 60;
		yInc = 144;
		randomiselp();
		for (int i = 0; i < nCount; i++)
		{
			modRec[i] = -2;
		}
		for (int i = 0; i < nCount; i++)
		{
			modArr[i] = -1;
		}
		CalculateHashing();
		glutIdleFunc(movelp);
        break;
	case 101:
		glutHideWindow();
		break;
	}
}
void Sorts::playlinearprobing()
{
	char* argv[1];
	char ds[8];
	argv[0] = ds;
	int argc = 1;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(sWidthlp, sHeightlp);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Hashing (Linear Probing)");


	myInitlp();

	CalculateHashing();

	glutDisplayFunc(displayWinlp);


	glutCreateMenu(menuControllp);
	glutAddMenuEntry("Start", 1);
	glutAddMenuEntry("Restart", 2);
	glutAddMenuEntry("Exit", 101);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	glutMainLoop();

}
//Hashing (linear probing endsss here)







//Hashing (separate chaining starts here)

RGBApixmap pixsc[1];
int sWidthsc = 800;  int sHeightsc = 800;
float minXsc = -100.0, maxXsc = 100.0, minYsc = -100.0, maxYsc = 100.0;
float stepsc = 50, anglesc = 50;
int screenWidthsc = 800, screenHeightsc = 800;



void drawBarsc(int count){


	for (int i = 0; i < count; i++)
	{
		glColor3f(0.0, 0.0, 1.0);
		glRectf(-60.0, 76 - (12 * i), -50.0, 86.0 - (12 * i));
		glColor3f(0.0, 0.0, 0.0);
		circle(20, 3.0, -55, 81 - (12 * i));
		drawTextlp(i, -65, 81 - (12 * i));

	}


}

int nCountsc = 5;
int iCountsc = 0;
//int t[5] = {7,12,45,9,0}; 
int tsc[5] = { 6, 15, 56, 19, 1 };
Box bxsc[5];
int iModsc = 0;
int flagFwsc = 0;
int xIncsc = 55;
int xOffsetsc = 60;
int yIncsc = 144;
int ModArrsc[5];

int CheckMsc(){
	int c = 0;
	for (int i = 0; i < iModsc; i++)
	{
		int modeVal = tsc[iModsc] % nCountsc;
		if (ModArrsc[i] == modeVal)
			c += 35;

	}
	return c;
}

void randomisesc()
{
	for (size_t inc = 0; inc < 5; inc++)
	{
		tsc[inc] = rand() % 999;
	}

}

void displayWinsc(void){


	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);


	pixsc[0].readBMPFile("backGround2.bmp");
	glPixelZoom(1, 1);
	glRasterPos2i(-100, -100);
	pixsc[0].mDraw();
	glRasterPos2i(0, 0);


	int modeVal = tsc[iModsc] % nCountsc;

	modeVal *= 12;


	drawBarsc(nCountsc);

	if (iCountsc <= nCountsc){
		for (int i = 0; i < iCountsc; i++)
		{
			bxsc[i].setColor(0, 1, 1);
			bxsc[i].set(tsc[i], i * 25, 0);
		}
	}
	if (iCountsc > 2){
		for (int i = 0; i < nCountsc; i++)
		{
			bxsc[i].render();

		}
	}


	if (iCountsc == nCountsc + 3){

		bxsc[iModsc].setColor(0, 1, 0);
	}
	else if (iCountsc == nCountsc + 4)
	{
		bxsc[iModsc].setColor(0, 1, 1);
	}
	else if (iCountsc == nCountsc + 5)
	{
		bxsc[iModsc].setColor(0, 1, 0);
	}
	else if (iCountsc == nCountsc + 6)
	{
		bxsc[iModsc].setColor(0, 1, 1);
	}
	else if (iCountsc > nCountsc + 7 && iCountsc < nCountsc + 12)
	{
		bxsc[iModsc].y += 3;
	}
	else if (iCountsc > nCountsc + 12 && bxsc[iModsc].x <= xIncsc + CheckMsc() && flagFwsc == 0)
	{
		bxsc[iModsc].x += 5;
	}
	else if (iCountsc > nCountsc + 12 && bxsc[iModsc].x > xOffsetsc + CheckMsc() && flagFwsc == 0)
	{
		bxsc[iModsc].x -= 5;
	}
	else if (iCountsc > nCountsc + 12 && bxsc[iModsc].x >= 55 && bxsc[iModsc].y <= yIncsc - modeVal && flagFwsc == 0)
	{

		bxsc[iModsc].y += 12;
	}

	else if (iCountsc > nCountsc + 12 && bxsc[iModsc].y > yIncsc - modeVal){

		iModsc++; iCountsc = nCountsc + 2; flagFwsc = 0;
	}

	if (iCountsc < 1000)
		iCountsc++;
	ModArrsc[iModsc] = modeVal / 12;

	glutSwapBuffers();
}


void movesc()
{


	glutPostRedisplay();

}

void myInitsc(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);       // background color is white
	glColor3f(0.0f, 0.0f, 0.0f);         // drawing color is black
	glPointSize(2.0);		          // a 'dot' is 2 by 2 pixels
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(minXsc, maxXsc, minYsc, maxYsc);

}



void menuControlsc(int value){

	switch (value){
	case 1:
        glutIdleFunc(movesc);
		break;
	case 2:
		iCountsc = 0; iModsc = 0;
		flagFwsc = 0;
		xIncsc = 55;
		xOffsetsc = 60;
		yIncsc = 144;
		randomisesc();
		for (int i = 0; i < nCountsc; i++)
		{
			ModArrsc[i] = -1;
		}
		glutIdleFunc(movesc);
		break;
	case 101:
		glutHideWindow();
		break;
	}
}

void Sorts::playseparatechaining()
{
	char* argv[1];
	char ds[8];
	argv[0] = ds;
	int argc = 1;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(sWidthsc, sHeightsc);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Hashing (Saperate chaining)");

	myInitsc();
	/* the display function */
	glutDisplayFunc(displayWinsc);


	glutCreateMenu(menuControlsc);
	glutAddMenuEntry("Start", 1);
	glutAddMenuEntry("Restart", 2);
	glutAddMenuEntry("Exit", 101);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	glutMainLoop();
}

//Hashing (separate chaining endsss here)







//Radix sort starts here

int * output = new int[5];
int arr[5], arr1[5], arr2[5], arr3[5], arr4[5], arr5[5];
bool start = false;

int getMax(int arr[], int n)
{
	int max = arr[0];
	for (int i = 1; i < n; i++)
	if (arr[i] > max)
		max = arr[i];
	return max;
}

void countSort(int arr[], int n, int exp)
{

	int i, count[10] = { 0 };
	for (i = 0; i < n; i++)
	{
		count[(arr[i] / exp) % 10]++;
	}
	for (i = 1; i < 10; i++)
	{
		count[i] += count[i - 1];
	}
	for (i = n - 1; i >= 0; i--)
	{
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}

}

void radixsort(int arr[], int n, int exp)
{
	int m = getMax(arr, n);
	countSort(arr, n, exp);
}

void drawTextrs(string s, int x, int y)
{
	glRasterPos2i(x, y);
	for (int i = 0; i <s.length(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s[i]);
	}
}

class Car
{
public:
	int s;
	float x, y;
	RGBApixmap pix;

	void draw()
	{
		glRasterPos2i(0, 0);
		pix.mDraw();
		glTranslatef(16.5, 10.25, 0);
		drawTextrs(to_string(s), 0, 0);
		glTranslatef(-16.5, -10.25, 0);
	}

	void set(string n1, int s1, float x1, float y1)
	{
		s = s1;
		pix.readBMPFile(n1);
		x = x1;
		y = y1;
	}

	void render()
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
		glTranslatef(x, y, 0);
		glPixelZoom(0.8, 0.8);
		draw();
		glPopMatrix();

	}

};

Car c1[5];
int irs = 0;
int i = 0;
bool fb_sorted = false;

void myInitrs(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-150.0, 150.0, -50.0, 50.0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_EQUAL, 1);
}

void myDisplayrs(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0);

	c1[0].render();
	c1[1].render();
	c1[2].render();
	c1[3].render();
	c1[4].render();

	if (start == false)
	{
		if (i==30)
			drawTextrs("Sorted Sucessfully", -30, -40);
		glutSwapBuffers();
		return;
	}

	//Step 1
	if (i == 0)
	{

		drawTextrs("Sorting using least significant digit", -30, -40);
		for (int j = 0; j < 5; j++)
		{

			if (arr1[0] == (c1[j].s))
			{
				if (c1[j].y != -25)
				{
					c1[j].y -= 0.5;
				}
				else
				{
					if (c1[j].x != -125)
					{
						c1[j].x += (c1[j].x > -125) ? -0.5 : 0.5;
					}
					else
					{
						i++;
					}
				}
			}
		}
	}

	else if (i == 1)
	{
		drawTextrs("Sorting using least significant digit", -30, -40);
		for (int j = 0; j < 5; j++)
		{
			if (arr1[1] == (c1[j].s))
			{
				if (c1[j].y != -25)
				{
					c1[j].y -= 0.5;
				}
				else
				{
					if (c1[j].x != -75)
					{
						c1[j].x += (c1[j].x > -75) ? -0.5 : 0.5;
					}
					else
					{
						i++;
					}
				}
			}
		}
	}

	else if (i == 2)
	{
		drawTextrs("Sorting using least significant digit", -30, -40);
		for (int j = 0; j < 5; j++)
		{
			if (arr1[2] == (c1[j].s))
			{
				if (c1[j].y != -25)
				{
					c1[j].y -= 0.5;
				}
				else
				{
					if (c1[j].x != -25)
					{
						c1[j].x += (c1[j].x > -25) ? -0.5 : 0.5;
					}
					else
					{
						i++;
					}
				}
			}
		}
	}

	else if (i == 3)
	{
		drawTextrs("Sorting using least significant digit", -30, -40);
		for (int j = 0; j < 5; j++)
		{
			if (arr1[3] == (c1[j].s))
			{
				if (c1[j].y != -25)
				{
					c1[j].y -= 0.5;
				}
				else
				{
					if (c1[j].x != 25)
					{
						c1[j].x += (c1[j].x > 25) ? -0.5 : 0.5;
					}
					else
					{
						i++;
					}
				}
			}
		}
	}

	else if (i == 4)
	{
		drawTextrs("Sorting using least significant digit", -30, -40);
		for (int j = 0; j < 5; j++)
		{
			if (arr1[4] == (c1[j].s))
			{
				if (c1[j].y != -25)
				{
					c1[j].y -= 0.5;
				}
				else
				{
					if (c1[j].x != 75)
					{
						c1[j].x += (c1[j].x > 75) ? -0.5 : 0.5;
					}
					else
					{
						i++;
					}
				}
			}
		}
	}

	if (i == 5)
	{
		drawTextrs("Sorting using least significant digit", -30, -40);
		for (int j = 0; j < 5; j++)
		{
			if (c1[j].y != 15)
			{
				c1[j].y += 0.5;
			}
		}
		if ((c1[0].y == 15) && (c1[1].y == 15) && (c1[2].y == 15) && (c1[3].y == 15) && (c1[4].y == 15))
		{
			i++;
		}
	}
	//Step 2
	else if (i == 6)
	{
		drawTextrs("Sorting using second last digit", -30, -40);
		for (int j = 0; j < 5; j++)
		{
			if ((arr2[0]) == c1[j].s)
			{
				if (c1[j].y != -25)
				{
					c1[j].y -= 0.5;
				}
				else
				{
					if (c1[j].x != -125)
					{
						c1[j].x += (c1[j].x > -125) ? -0.5 : 0.5;
					}
					else
					{
						i++;
					}
				}
			}
		}
	}

	else if (i == 7)

	{
		drawTextrs("Sorting using second last digit", -30, -40);
		for (int j = 0; j < 5; j++)
		{
			if ((arr2[1]) == c1[j].s)
			{
				if (c1[j].y != -25)
				{
					c1[j].y -= 0.5;
				}
				else
				{
					if (c1[j].x != -75)
					{
						c1[j].x += (c1[j].x > -75) ? -0.5 : 0.5;
					}
					else
					{
						i++;
					}
				}
			}
		}
	}

	else if (i == 8)
	{
		drawTextrs("Sorting using second last digit", -30, -40);
		for (int j = 0; j < 5; j++)
		{
			if ((arr2[2]) == c1[j].s)
			{
				if (c1[j].y != -25)
				{
					c1[j].y -= 0.5;
				}
				else
				{
					if (c1[j].x != -25)
					{
						c1[j].x += (c1[j].x > -25) ? -0.5 : 0.5;
					}
					else
					{
						i++;
					}
				}
			}
		}
	}

	else if (i == 9)
	{
		drawTextrs("Sorting using second last digit", -30, -40);
		for (int j = 0; j < 5; j++)
		{
			if ((arr2[3]) == c1[j].s)
			{
				if (c1[j].y != -25)
				{
					c1[j].y -= 0.5;
				}
				else
				{
					if (c1[j].x != 25)
					{
						c1[j].x += (c1[j].x > 25) ? -0.5 : 0.5;
					}
					else
					{
						i++;
					}
				}
			}
		}
	}

	else if (i == 10)
	{
		drawTextrs("Sorting using second last digit", -30, -40);
		for (int j = 0; j < 5; j++)
		{
			if ((arr2[4]) == c1[j].s)
			{
				if (c1[j].y != -25)
				{
					c1[j].y -= 0.5;
				}
				else
				{
					if (c1[j].x != 75)
					{
						c1[j].x += (c1[j].x > 75) ? -0.5 : 0.5;
					}
					else
					{
						i++;
					}
				}
			}
		}
	}

	if (i == 11)
	{
		drawTextrs("Sorting using second last digit", -30, -40);
		for (int j = 0; j < 5; j++)
		{
			if (c1[j].y != 15)
			{
				c1[j].y += 0.5;
			}
		}
		if ((c1[0].y == 15) && (c1[1].y == 15) && (c1[2].y == 15) && (c1[3].y == 15) && (c1[4].y == 15))
		{
			i++;
		}
	}

	//Step 3
	else if (i == 12)
	{
		drawTextrs("Sorting using third digit", -30, -40);
		for (int j = 0; j < 5; j++)
		{
			if ((arr3[0]) == c1[j].s)
			{
				if (c1[j].y != -25)
				{
					c1[j].y -= 0.5;
				}
				else
				{
					if (c1[j].x != -125)
					{
						c1[j].x += (c1[j].x > -125) ? -0.5 : 0.5;
					}
					else
					{
						i++;
					}
				}
			}
		}
	}

	else if (i == 13)
	{
		drawTextrs("Sorting using third digit", -30, -40);
		for (int j = 0; j < 5; j++)
		{
			if ((arr3[1]) == c1[j].s)
			{
				if (c1[j].y != -25)
				{
					c1[j].y -= 0.5;
				}
				else
				{
					if (c1[j].x != -75)
					{
						c1[j].x += (c1[j].x > -75) ? -0.5 : 0.5;
					}
					else
					{
						i++;
					}
				}
			}
		}
	}

	else if (i == 14)
	{
		drawTextrs("Sorting using third digit", -30, -40);
		for (int j = 0; j < 5; j++)
		{
			if ((arr3[2]) == c1[j].s)
			{
				if (c1[j].y != -25)
				{
					c1[j].y -= 0.5;
				}
				else
				{
					if (c1[j].x != -25)
					{
						c1[j].x += (c1[j].x > -25) ? -0.5 : 0.5;
					}
					else
					{
						i++;
					}
				}
			}
		}
	}

	else if (i == 15)
	{
		drawTextrs("Sorting using third digit", -30, -40);
		for (int j = 0; j < 5; j++)
		{
			if ((arr3[3]) == c1[j].s)
			{
				if (c1[j].y != -25)
				{
					c1[j].y -= 0.5;
				}
				else
				{
					if (c1[j].x != 25)
					{
						c1[j].x += (c1[j].x > 25) ? -0.5 : 0.5;
					}
					else
					{
						i++;
					}
				}
			}
		}
	}

	else if (i == 16)
	{
		drawTextrs("Sorting using third digit", -30, -40);
		for (int j = 0; j < 5; j++)
		{
			if ((arr3[4]) == c1[j].s)
			{
				if (c1[j].y != -25)
				{
					c1[j].y -= 0.5;
				}
				else
				{
					if (c1[j].x != 75)
					{
						c1[j].x += (c1[j].x > 75) ? -0.5 : 0.5;
					}
					else
					{
						i++;
					}
				}
			}
		}
	}

	if (i == 17)
	{
		drawTextrs("Sorting using third digit", -30, -40);
		for (int j = 0; j < 5; j++)
		{
			if (c1[j].y != 15)
			{
				c1[j].y += 0.5;
			}
		}
		if ((c1[0].y == 15) && (c1[1].y == 15) && (c1[2].y == 15) && (c1[3].y == 15) && (c1[4].y == 15))
		{
			i++;
		}
	}

	//Step 4
	else if (i == 18)
	{
		drawTextrs("Sorting using second digit", -30, -40);
		for (int j = 0; j < 5; j++)
		{
			if ((arr4[0]) == c1[j].s)
			{
				if (c1[j].y != -25)
				{
					c1[j].y -= 0.5;
				}
				else
				{
					if (c1[j].x != -125)
					{
						c1[j].x += (c1[j].x > -125) ? -0.5 : 0.5;
					}
					else
					{
						i++;
					}
				}
			}
		}
	}

	else if (i == 19)
	{
		drawTextrs("Sorting using second digit", -30, -40);
		for (int j = 0; j < 5; j++)
		{
			if ((arr4[1]) == c1[j].s)
			{
				if (c1[j].y != -25)
				{
					c1[j].y -= 0.5;
				}
				else
				{
					if (c1[j].x != -75)
					{
						c1[j].x += (c1[j].x > -75) ? -0.5 : 0.5;
					}
					else
					{
						i++;
					}
				}
			}
		}
	}

	else if (i == 20)
	{
		drawTextrs("Sorting using second digit", -30, -40);
		for (int j = 0; j < 5; j++)
		{
			if ((arr4[2]) == c1[j].s)
			{
				if (c1[j].y != -25)
				{
					c1[j].y -= 0.5;
				}
				else
				{
					if (c1[j].x != -25)
					{
						c1[j].x += (c1[j].x > -25) ? -0.5 : 0.5;
					}
					else
					{
						i++;
					}
				}
			}
		}
	}

	else if (i == 21)

	{
		drawTextrs("Sorting using second digit", -30, -40);
		for (int j = 0; j < 5; j++)
		{
			if ((arr4[3]) == c1[j].s)
			{
				if (c1[j].y != -25)
				{
					c1[j].y -= 0.5;
				}
				else
				{
					if (c1[j].x != 25)
					{
						c1[j].x += (c1[j].x > 25) ? -0.5 : 0.5;
					}
					else
					{
						i++;
					}
				}
			}
		}
	}

	else if (i == 22)
	{
		drawTextrs("Sorting using second digit", -30, -40);
		for (int j = 0; j < 5; j++)
		{
			if ((arr4[4]) == c1[j].s)
			{
				if (c1[j].y != -25)
				{
					c1[j].y -= 0.5;
				}
				else
				{
					if (c1[j].x != 75)
					{
						c1[j].x += (c1[j].x > 75) ? -0.5 : 0.5;
					}
					else
					{
						i++;
					}
				}
			}
		}
	}

	if (i == 23)
	{
		drawTextrs("Sorting using second digit", -30, -40);
		for (int j = 0; j < 5; j++)
		{
			if (c1[j].y != 15)
			{
				c1[j].y += 0.5;
			}
		}
		if ((c1[0].y == 15) && (c1[1].y == 15) && (c1[2].y == 15) && (c1[3].y == 15) && (c1[4].y == 15))
		{
			i++;
		}
	}

	//Step 5
	else if (i == 24)
	{
		drawTextrs("Sorting using first digit", -30, -40);
		for (int j = 0; j < 5; j++)
		{
			if ((arr5[0]) == c1[j].s)
			{
				if (c1[j].y != -25)
				{
					c1[j].y -= 0.5;
				}
				else
				{
					if (c1[j].x != -125)
					{
						c1[j].x += (c1[j].x > -125) ? -0.5 : 0.5;
					}
					else
					{
						i++;
					}
				}
			}
		}
	}

	else if (i == 25)
	{
		drawTextrs("Sorting using first digit", -30, -40);
		for (int j = 0; j < 5; j++)
		{
			if ((arr5[1]) == c1[j].s)
			{
				if (c1[j].y != -25)
				{
					c1[j].y -= 0.5;
				}
				else
				{
					if (c1[j].x != -75)
					{
						c1[j].x += (c1[j].x > -75) ? -0.5 : 0.5;
					}
					else
					{
						i++;
					}
				}
			}
		}
	}

	else if (i == 26)
	{
		drawTextrs("Sorting using first digit", -30, -40);
		for (int j = 0; j < 5; j++)
		{
			if ((arr5[2]) == c1[j].s)
			{
				if (c1[j].y != -25)
				{
					c1[j].y -= 0.5;
				}
				else
				{
					if (c1[j].x != -25)
					{
						c1[j].x += (c1[j].x > -25) ? -0.5 : 0.5;
					}
					else
					{
						i++;
					}
				}
			}
		}
	}

	else if (i == 27)
	{
		drawTextrs("Sorting using first digit", -30, -40);
		for (int j = 0; j < 5; j++)
		{
			if ((arr5[3]) == c1[j].s)
			{
				if (c1[j].y != -25)
				{
					c1[j].y -= 0.5;
				}
				else
				{
					if (c1[j].x != 25)
					{
						c1[j].x += (c1[j].x > 25) ? -0.5 : 0.5;
					}
					else
					{
						i++;
					}
				}
			}
		}
	}

	else if (i == 28)
	{
		drawTextrs("Sorting using first digit", -30, -40);
		for (int j = 0; j < 5; j++)
		{
			if ((arr5[4]) == c1[j].s)
			{
				if (c1[j].y != -25)
				{
					c1[j].y -= 0.5;
				}
				else
				{
					if (c1[j].x != 75)
					{
						c1[j].x += (c1[j].x > 75) ? -0.5 : 0.5;
					}
					else
					{
						i++;
					}
				}
			}
		}
	}

	if (i == 29)
	{
		drawTextrs("Sorting using first digit", -30, -40);
		for (int j = 0; j < 5; j++)
		{
			if (c1[j].y != 15)
			{
				c1[j].y += 0.5;
			}
		}
		if ((c1[0].y == 15) && (c1[1].y == 15) && (c1[2].y == 15) && (c1[3].y == 15) && (c1[4].y == 15))
		{
			i=0;
			start = false;
		}
	}

	glutSwapBuffers();
}

void movers()
{
	glutPostRedisplay();
}

void menuControlrs(int value){

	switch (value){
	case 1:
		start = true;
		break;
	case 11:
		start = true;
		i = 0;
		int a;
		int num[5];
		srand(time(0));
		for (int i = 0; i < 5; i++)
		{
			a = (rand() % 90000) + 10000;
			num[i] = a;
		}
		arr[0] = num[0];
		arr[1] = num[1];
		arr[2] = num[2];
		arr[3] = num[3];
		arr[4] = num[4];
		radixsort(arr, 5, 1);
		for (int i = 0; i < 5; i++)
		{
			arr1[i] = output[i];
		}
		radixsort(arr1, 5, 10);
		for (int i = 0; i < 5; i++)
		{
			arr2[i] = output[i];
		}
		radixsort(arr2, 5, 100);
		for (int i = 0; i < 5; i++)
		{
			arr3[i] = output[i];
		}
		radixsort(arr3, 5, 1000);
		for (int i = 0; i < 5; i++)
		{
			arr4[i] = output[i];
		}
		radixsort(arr4, 5, 10000);
		for (int i = 0; i < 5; i++)
		{
			arr5[i] = output[i];
		}

		c1[0].set("car1.bmp", (num[0]), -125, 15);

		c1[1].set("car2.bmp", (num[1]), -75, 15);

		c1[2].set("car3.bmp", (num[2]), -25, 15);

		c1[3].set("car4.bmp", (num[3]), 25, 15);

		c1[4].set("car5.bmp", (num[4]), 75, 15);
		break;
	case 101:
		glutHideWindow();
		break;
	}
}

int screenWidthrs = 1200;
int screenHeightrs = 500;



void Sorts::playradixsort()
{

	char* argv[1];
	char ds[8];
	argv[0] = ds;
	int argc = 1;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(screenWidthrs, screenHeightrs);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Radix Sort");
	glutDisplayFunc(myDisplayrs);
	glutIdleFunc(movers);
	myInitrs();
	glutCreateMenu(menuControlrs);
	glutAddMenuEntry("Start", 1);
	glutAddMenuEntry("Restart", 11);
	glutAddMenuEntry("Exit", 101);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	int a;
	int num[5];
	srand(time(0));
	for (int i = 0; i < 5; i++)
	{
		a = (rand() % 90000) + 10000;
		num[i] = a;
	}

	int n = 5;
	arr[0] = num[0];
	arr[1] = num[1];
	arr[2] = num[2];
	arr[3] = num[3];
	arr[4] = num[4];

	radixsort(arr, n, 1);
	for (int i = 0; i < n; i++)
	{
		arr1[i] = output[i];
	}
	radixsort(arr1, n, 10);
	for (int i = 0; i < n; i++)
	{
		arr2[i] = output[i];
	}
	radixsort(arr2, n, 100);
	for (int i = 0; i < n; i++)
	{
		arr3[i] = output[i];
	}
	radixsort(arr3, n, 1000);
	for (int i = 0; i < n; i++)
	{
		arr4[i] = output[i];
	}
	radixsort(arr4, n, 10000);
	for (int i = 0; i < n; i++)
	{
		arr5[i] = output[i];
	}

	c1[0].set("car1.bmp", (num[0]), -125, 15);

	c1[1].set("car2.bmp", (num[1]), -75, 15);

	c1[2].set("car3.bmp", (num[2]), -25, 15);

	c1[3].set("car4.bmp", (num[3]), 25, 15);

	c1[4].set("car5.bmp", (num[4]), 75, 15);

	glutMainLoop();

}


//radix sort endssss here



//Merge Sort starts here


RGBApixmap back;
int ims = 0;
bool startms = false;
int a[4], b[4], c[8];
string bmps[8] = { "puzzle1.bmp", "puzzle2.bmp", "puzzle3.bmp", "puzzle4.bmp", "puzzle5.bmp", "puzzle6.bmp", "puzzle7.bmp", "puzzle8.bmp" };
int ai = 0, bi = 0, ci = 0, pos = 0;
int ys[8] = { 350, 311, 271, 233, 192, 154, 128, 87 };
int snums[8];

void drawTextms(float x, float y, int v)
{
	string s = std::to_string(v);
	glRasterPos2f(x, y);
	glColor3f(0, 0, 0);
	for (int i = 0; i < s.length(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
	}
}

class Puzzle
{
public:
	float x, y;
	RGBApixmap pic;
	int value;
	bool onleft;
	bool merged = false;
private:
	void draw()
	{
		glRasterPos2i(0, 0);
		glPixelZoom(0.5, 0.5);
		pic.mDraw();
		if (merged == false){
			glTranslatef(50, -30, 0);
			drawTextms(0, 0, value);
		}
	}
public:
	void render()
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
		glTranslatef(x, y, 0);
		draw();
		glPopMatrix();
	}

	void set(float x1, float y1, bool onl)
	{
		x = x1;
		y = y1;
		onleft = onl;
	}

	void setBitmap(string s)
	{
		pic.readBMPFile(s);
		pic.setChromaKey(255, 255, 255);
	}

};

Puzzle puzzle[8];
bool ftime;

void myInitms(void)
{
	glClearColor(1, 1, 1, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1000, 0, 500);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_EQUAL, 1.0);
}


void merge_sort()
{
	printf("here\n");
	while (ai <= 3 && bi <= 3)
	{
		if (a[ai] <= b[bi])
		{
			printf("%d ", a[ai]);
			snums[ci] = ai;
			ai++;

		}
		else
		{
			printf("%d ", b[bi]);
			snums[ci] = bi + 4;
			bi++;

		}
		ci++;
	}
	while (ai <= 3)
	{
		printf("%d ", a[ai]);
		snums[ci] = ai;
		ai++;
		ci++;
	}

	while (bi <= 3)
	{
		printf("%d ", b[bi]);
		snums[ci] = bi + 4;
		bi++;
		ci++;

	}
	ftime = false;
}


void myDisplayms(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 0);
	glRasterPos2i(0, 0);
	glPixelZoom(1, 1);
	back.mDraw();

	for (size_t y = 0; y < 8; y++)
	{
		puzzle[y].render();
	}


	if (startms == false)
	{
		glutSwapBuffers();
		return;
	}



	if (ims == pos&&ims != 8)
	{

		if (puzzle[snums[pos]].y != ys[ims] + 2)
		{

			puzzle[snums[pos]].y -= 1;
		}
		else
		{
			if (puzzle[snums[pos]].x != 450)
			{
				if (puzzle[snums[pos]].onleft)
					puzzle[snums[pos]].x += 1;
				else
				{
					puzzle[snums[pos]].x -= 1;
				}
			}
			else
			{
				puzzle[snums[pos]].merged = true;
				pos++;
				ims++;
			}
		}
	}


	glutSwapBuffers();
}

void movems()
{
	glutPostRedisplay();
}

void sortit(int k[], int length)
{
	int temp;
	for (int i = 0; i < length - 1; i++)
	{
		for (int j = i + 1; j < length; j++)
		{
			if (k[j]<k[i])
			{
				temp = k[i];
				k[i] = k[j];
				k[j] = temp;
			}
		}
	}

}

void randomisems()
{
	a[0] = rand() % 999;
	a[1] = rand() % 999;
	a[2] = rand() % 999;
	a[3] = rand() % 999;

	b[0] = rand() % 999;
	b[1] = rand() % 999;
	b[2] = rand() % 999;
	b[3] = rand() % 999;

	sortit(a, 4);
	sortit(b, 4);

	for (size_t p = 0; p < 4; p++)
	{
		c[p] = a[p];
		c[p + 4] = b[p];
		puzzle[p].value = a[p];
		puzzle[p + 4].value = b[p];
	}

	sortit(c, 8);

	for (size_t j = 0; j < 8; j++)
	{
		for (size_t k = 0; k < 8; k++)
		{
			if (c[j] == puzzle[k].value)
			{
				puzzle[k].setBitmap(bmps[j]);
				break;
			}
		}
	}
}

void menuControlms(int value){

	switch (value){
	case 1:
		startms = true;
		glutPostRedisplay();
		break;
	case 2:
		startms = true;
		puzzle[0].set(0, 425, true);
		puzzle[1].set(115, 425, true);
		puzzle[2].set(230, 425, true);
		puzzle[3].set(345, 425, true);
		puzzle[4].set(550, 425, false);
		puzzle[5].set(665, 425, false);
		puzzle[6].set(780, 425, false);
		puzzle[7].set(895, 425, false);
		for (size_t i = 0; i < 8; i++)
		{
			puzzle[i].merged = false;

		}
		ai = 0; bi = 0; ci = 0;  pos = 0; ims = 0;
		randomisems();
		merge_sort();
		glutPostRedisplay();
		break;
	case 101:
		glutHideWindow();
		break;
	}
}




int screenWidthms = 1000;
int screenHeightms = 600;

void Sorts::playmergesort()
{
	char* argv[1];
	char ds[8];
	argv[0] = ds;
	int argc = 1;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(screenWidthms, screenHeightms);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Merge Sort Merging");
	glutDisplayFunc(myDisplayms);
	myInitms();
	back.readBMPFile("back1.bmp");
	glutIdleFunc(movems);
	puzzle[0].set(0, 425, true);
	puzzle[1].set(115, 425, true);
	puzzle[2].set(230, 425, true);
	puzzle[3].set(345, 425, true);
	puzzle[4].set(550, 425, false);
	puzzle[5].set(665, 425, false);
	puzzle[6].set(780, 425, false);
	puzzle[7].set(895, 425, false);
	randomisems();
	merge_sort();
	glutCreateMenu(menuControlms);
	glutAddMenuEntry("Start", 1);
	glutAddMenuEntry("Restart", 2);
	glutAddMenuEntry("Exit", 101);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();

}
//merge sort endsss here



//Bucket Sort starts here
void drawtext(string s)
{
	glRasterPos2i(0, 0);
	for (int i = 0; i <s.length(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
	}
}

class Paper
{
public:
	string s;
	float x, y, r, g, b;

	void draw()
	{
		glColor3f(r, g, b);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_POLYGON);
		glVertex2f(6.0, 0.0);
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, 12.0);
		glVertex2f(9.0, 12.0);
		glVertex2f(9.0, 3.0);
		glVertex2f(6.0, 0.0);
		glVertex2f(6.0, 3.0);
		glVertex2f(9.0, 3.0);
		glEnd();

		glColor3f(0.0f, 0.0f, 0.0f);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_POLYGON);
		glVertex2f(6.0, 0.0);
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, 12.0);
		glVertex2f(9.0, 12.0);
		glVertex2f(9.0, 3.0);
		glVertex2f(6.0, 0.0);
		glVertex2f(6.0, 3.0);
		glVertex2f(9.0, 3.0);
		glEnd();

		glTranslatef(2, 5, 0);
		drawtext(s);
		glTranslatef(-2, -5, 0);
	}

	void set(string s1, float x1, float y1, float r1, float g1, float b1)
	{
		r = r1;
		g = g1;
		b = b1;
		s = s1;
		x = x1;
		y = y1;
	}

	void render()
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
		glTranslatef(x, y, 0);
		draw();
		glPopMatrix();

	}

	void movedown()
	{
		y -= 0.5;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
		glTranslatef(x, y, 0);
		draw();
		glPopMatrix();
	}
};


class Shelf
{
private:
	string s;
	float x, y;


public:
	void draw()
	{
		glColor3f(0.8, 0.5, 0.2);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_QUADS);
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, 10.0);
		glVertex2f(40.0, 10.0);
		glVertex2f(40.0, 0.0);
		glEnd();

		glColor3f(0.0f, 0.0f, 0.0f);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_QUADS);
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, 10.0);
		glVertex2f(40.0, 10.0);
		glVertex2f(40.0, 0.0);
		glEnd();

		glColor3f(1.0f, 1.0f, 1.0f);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_QUADS);
		glVertex2f(10.0, 0.0);
		glVertex2f(10.0, 10.0);
		glVertex2f(30.0, 10.0);
		glVertex2f(30.0, 0.0);
		glEnd();

		glColor3f(0.0f, 0.0f, 0.0f);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_QUADS);
		glVertex2f(10.0, 0.0);
		glVertex2f(10.0, 10.0);
		glVertex2f(30.0, 10.0);
		glVertex2f(30.0, 0.0);
		glEnd();

		glTranslatef(14, 4, 0);
		drawtext(s);
		glTranslatef(-14, -4, 0);
	}

	void render(string s1, float x1, float y1)
	{
		s = s1;
		x = x1;
		y = y1;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
		glTranslatef(x1, y1, 0);
		draw();
		glPopMatrix();
	}

};


RGBApixmap pix[1];
Paper p[10];
Shelf s1[4];
int i1 = 0;
bool rstart = false;

void menuControl1(int value){

	switch (value){
	case 1:
		rstart = true;
		break;
	case 2:
		rstart = true;

		i1 = 0;

		p[0].set("49", -95, 25, 0.5, 0.5, 0.5);

		p[1].set("91", -75, 25, 0.5, 0.4, 0.1);

		p[2].set("08", -55, 25, 0.8, 0.3, 0.3);

		p[3].set("53", -35, 25, 1, 1, 1);

		p[4].set("66", -15, 25, 1, 1, 0.2);

		p[5].set("61", 5, 25, 0.2, 0.6, 0.8);

		p[6].set("75", 25, 25, 0.7, 0.5, 0.3);

		p[7].set("24", 45, 25, 0, 0.7, 0.2);

		p[8].set("06", 65, 25, 0.8, 0.8, 0.8);

		p[9].set("30", 85, 25, 0.5, 1, 0.1);
		break;
	case 101:
		PlayBackgroundSound("music1.wav");
		glutHideWindow();
		break;
	}
}


void myInit2(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100.0, 100.0, -50.0, 50.0);
	glRasterPos2i(-100, -50);
	pix[0].mDraw();
	glRasterPos2i(0, 0);
}

void myDisplay2(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0);
	glRasterPos2i(-100, -50);
	pix[0].mDraw();
	glRasterPos2i(0, 0);

	p[0].render();

	p[1].render();

	p[2].render();

	p[3].render();

	p[4].render();

	p[5].render();

	p[6].render();

	p[7].render();

	p[8].render();

	p[9].render();

	s1[0].render("00-24", -92, -10);

	s1[1].render("25-49", -44, -10);

	s1[2].render("50-74", 4, -10);

	s1[3].render("75-99", 52, -10);

	if (rstart == false)
	{
		glutSwapBuffers();
		return;
	}

	if (i1 == 0)
	{
		if (p[0].y != 0)
			p[0].y -= 0.5;
		else
		{
			if (p[0].x != -44)
			{
				p[0].x += 0.5;

			}
			else
			{
				i1++;
			}

		}
	}

	else if (i1 == 1)
	{
		if (p[1].y != 0)
			p[1].y -= 0.5;
		else
		{
			if (p[1].x != 52)
			{
				p[1].x += 0.5;

			}
			else
			{
				i1++;
			}

		}

	}

	else if (i1 == 2)
	{
		if (p[2].y != 0)
			p[2].y -= 0.5;
		else
		{
			if (p[2].x != -92)
			{
				p[2].x -= 0.5;

			}
			else
			{
				i1++;
			}

		}

	}

	else if (i1 == 3)
	{
		if (p[3].y != 0)
			p[3].y -= 0.5;
		else
		{
			if (p[3].x != 4)
			{
				p[3].x += 0.5;

			}
			else
			{
				i1++;
			}

		}

	}

	else if (i1 == 4)
	{
		if (p[4].y != 0)
			p[4].y -= 0.5;
		else
		{
			if (p[4].x != 14)
			{
				p[4].x += 0.5;

			}
			else
			{
				i1++;
			}

		}

	}

	else if (i1 == 5)
	{
		if (p[5].y != 0)
			p[5].y -= 0.5;
		else
		{
			if (p[5].x != 24)
			{
				p[5].x += 0.5;

			}
			else
			{
				i1++;
			}

		}

	}


	else if (i1 == 6)
	{
		if (p[6].y != 0)
			p[6].y -= 0.5;
		else
		{
			if (p[6].x != 62)
			{
				p[6].x += 0.5;

			}
			else
			{
				i1++;
			}

		}

	}

	else if (i1 == 7)
	{
		if (p[7].y != 0)
			p[7].y -= 0.5;
		else
		{
			if (p[7].x != -82)
			{
				p[7].x -= 0.5;

			}
			else
			{
				i1++;
			}

		}

	}

	else if (i1 == 8)
	{
		if (p[8].y != 0)
			p[8].y -= 0.5;
		else
		{
			if (p[8].x != -72)
			{
				p[8].x -= 0.5;

			}
			else
			{
				i1++;
			}

		}

	}

	else if (i1 == 9)
	{
		if (p[9].y != 0)
			p[9].y -= 0.5;
		else
		{
			if (p[9].x != -34)
			{
				p[9].x -= 0.5;
			}
			else
			{
				i1++;
			}
		}
	}

	if (i1 == 10)
	{

		if (p[8].y != 15)
			p[8].y += 0.5;
		else
		{
			if (p[7].x != -72)
				p[7].x += 0.5;
			if (p[2].x != -82)
				p[2].x += 0.5;
			if (p[8].x != -92)
				p[8].x -= 0.5;

		}

		if (p[8].x == -92)
		{

			if (p[8].y != 0)
			{
				p[8].y--;
			}

			else
				i1++;

		}


	}


	if (i1 == 11)
	{

		if (p[9].x != -44)
			p[9].x -= 0.5;
		if (p[0].x != -34)
			p[0].x += 0.5;
		else
		{
			i1++;
		}

	}

	if (i1 == 12)
	{
		if (p[5].x != 14)
			p[5].x -= 0.5;
		if (p[4].x != 24)
			p[4].x += 0.5;
		else
		{
			i1++;
		}
	}


	if (i1 == 13)
	{
		if (p[6].x != 52)
			p[6].x -= 0.5;
		if (p[1].x != 62)
			p[1].x += 0.5;
		else
		{
			i1++;
		}
	}

	if (i1 == 14)
	{

		for (int j = 0; j < 10; j++)
		{
			if (p[j].y != 25)
				p[j].y++;
		}
		if ((p[0].y == 25) && (p[1].y == 25) && (p[2].y == 25) && (p[3].y == 25) && (p[4].y == 25) && (p[5].y == 25) && (p[6].y == 25) && (p[7].y == 25) && (p[8].y == 25) && (p[9].y == 25))
		{
			i1++;
		}
	}

	if (i1 == 15)
	{
		if (p[1].x != 85)
		{
			p[1].x += 0.5;
		}
		if (p[6].x != 65)
		{
			p[6].x += 0.5;
		}
		if (p[4].x != 45)
		{
			p[4].x += 0.5;
		}
		if (p[5].x != 25)
		{
			p[5].x += 0.5;
		}
		if (p[3].x != 5)
		{
			p[3].x += 0.5;
		}
		if (p[0].x != -15)
		{
			p[0].x += 0.5;
		}
		if (p[9].x != -35)
		{
			p[9].x += 0.5;
		}
		if (p[7].x != -55)
		{
			p[7].x += 0.5;
		}
		if (p[2].x != -75)
		{
			p[2].x += 0.5;
		}
		if (p[8].x != -95)
		{
			p[8].x -= 0.5;
		}
		
	}


	glutSwapBuffers();
}



void move2()
{
	glutPostRedisplay();
}

int sWidth = 1000;
int sHeight = 500;

void Sorts::playbucketsort()
{
	char* argv[1];
	char ds[8];
	argv[0] = ds;
	int argc = 1;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(sWidth, sHeight);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Bucket Sort");
	glutDisplayFunc(myDisplay2);
	glutIdleFunc(move2);
	pix[0].readBMPFile("back.bmp");
	myInit2();
	glutCreateMenu(menuControl1);
	glutAddMenuEntry("Start", 1);
	glutAddMenuEntry("Restart", 2);
	glutAddMenuEntry("Exit", 101);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	PlayBackgroundSound("music1.wav");
	p[0].set("49", -95, 25, 0.5, 0.5, 0.5);

	p[1].set("91", -75, 25, 0.5, 0.4, 0.1);

	p[2].set("08", -55, 25, 0.8, 0.3, 0.3);

	p[3].set("53", -35, 25, 1, 1, 1);

	p[4].set("66", -15, 25, 1, 1, 0.2);

	p[5].set("61", 5, 25, 0.2, 0.6, 0.8);

	p[6].set("75", 25, 25, 0.7, 0.5, 0.3);

	p[7].set("24", 45, 25, 0, 0.7, 0.2);

	p[8].set("06", 65, 25, 0.8, 0.8, 0.8);

	p[9].set("30", 85, 25, 0.5, 1, 0.1);

	glutMainLoop();


}
//Bucket sort ends here


