#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <string.h>

void characterStream();

void *currentfont;
GLchar randchar[5];
const char charset[] = "abcdefghijklmnopqrstuvwxyz";
GLint score;
GLint i;
GLint k, count=0,dec = 5;
GLint increment = 20 , initialStickman[2] = {10,70} , cpuinitialStickman[2] = {10,70} , stickmancount = 0, cpustickmancount = 0 ,small = 15, cpusmall = 20;
GLint x_step = 0;
void rand_string(size_t size)
{
    /*This function generates a string of five random characters each time it is called. These characters are furthur used in the program to match the mouse clicks of the user to decide whether the stickman should be tranlated forward or backward*/
    size_t n;
    if (size) {
        --size;
        for (n = 0; n < size; n++) {
            int key = rand() % (int) (sizeof charset - 1);
            randchar[n] = charset[key];
        }
        randchar[size] = '\0';
    }
    i=0;
    score = 0;
}

void setfont(void *font)
{
    /*Sets the current font to GLUT_BITMAP_9_BY_15*/
    currentfont=font;
}

void drawstring( int x, int y, char st) //this function will print the character
{
	/*This function displays the char passed to it at the position specified by the parameters x and y*/

	glRasterPos2i( x, y); // location to start printing text
	glutBitmapCharacter(currentfont, st);// Print a character on the screen
}

void youWin()
{
    /*This function is called when the user wins the game to render the image YouWin.jpg*/

    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    /* load an image file directly as a new OpenGL texture */
    GLuint tex_2d = SOIL_load_OGL_texture
	(
		"images/YouWin.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

/* check for an error during the load process */
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    glBindTexture(GL_TEXTURE_2D, tex_2d);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0);
        glVertex2f(0.0, 0.0);
        glTexCoord2f(1.0, 0.0);
        glVertex2f(1200.0, 0.0);
        glTexCoord2f(1.0, 1.0);
        glVertex2f(1200.0, 700.0);
        glTexCoord2f(0.0, 1.0);
        glVertex2f(0.0, 700.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glFlush();
}

void youLose()
{
    /*This function is called when the user loses the game to render the image YouLose.jpg*/	
	
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
    /* load an image file directly as a new OpenGL texture */
    GLuint tex_2d = SOIL_load_OGL_texture
	(
		"images/YouLose.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

/* check for an error during the load process */
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    glBindTexture(GL_TEXTURE_2D, tex_2d);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0);
        glVertex2f(0.0, 0.0);
        glTexCoord2f(1.0, 0.0);
        glVertex2f(1200.0, 0.0);
        glTexCoord2f(1.0, 1.0);
        glVertex2f(1200.0, 700.0);
        glTexCoord2f(0.0, 1.0);
        glVertex2f(0.0, 700.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glFlush();
}

void stickman1()
{
    /*This function renders the initial position of the user's stickman. Each time this function is called the value of stickmancount is incremented. The position of the stickman each time is function is called is based on the number of characters missed or matched by the user.*/
    
    stickmancount++;
    glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
    /* load an image file directly as a new OpenGL texture */
    GLuint tex_2d = SOIL_load_OGL_texture
	(
		"images/userStickman1.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

/* check for an error during the load process */
if( 0 == tex_2d )
{
	printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
}
    glBindTexture(GL_TEXTURE_2D, tex_2d);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0);
        glVertex2f(initialStickman[0] += small, 200.0);
        glTexCoord2f(1.0, 0.0);
        glVertex2f(initialStickman[1] += small, 200.0);
        glTexCoord2f(1.0, 1.0);
        glVertex2f(initialStickman[1] += small, 400.0);
        glTexCoord2f(0.0, 1.0);
        glVertex2f(initialStickman[0] += small, 400.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}


void stickman2()
{
    
    /*This function renders the second position of the user's stickman. Each time this function is called the value of stickmancount is decremented. The position of the stickman each time is function is called is based on the number of characters missed or matched by the user.*/
    stickmancount--;
    glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
    /* load an image file directly as a new OpenGL texture */
    GLuint tex_2d = SOIL_load_OGL_texture
	(
		"images/userStickman2.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

/* check for an error during the load process */
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    glBindTexture(GL_TEXTURE_2D, tex_2d);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0);
        glVertex2f(initialStickman[0] += small, 200.0);
        glTexCoord2f(1.0, 0.0);
        glVertex2f(initialStickman[1] += small, 200.0);
        glTexCoord2f(1.0, 1.0);
        glVertex2f(initialStickman[1] += small, 400.0);
        glTexCoord2f(0.0, 1.0);
        glVertex2f(initialStickman[0] += small, 400.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void cpuStickman1()
{
    
    /*This function renders the initial position of the cpu's stickman. Each time this function is called the value of cpustickmancount is incremented. Each time this function is called the stickman will translate forward by the specified number of units.*/
    cpustickmancount++;
    glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
    /* load an image file directly as a new OpenGL texture */
    GLuint tex_2d = SOIL_load_OGL_texture
	(
		"images/cpuStickman1.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

/* check for an error during the load process */
if( 0 == tex_2d )
{
	printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
}
    glBindTexture(GL_TEXTURE_2D, tex_2d);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0);
        glVertex2f(cpuinitialStickman[0] += cpusmall, 450.0);
        glTexCoord2f(1.0, 0.0);
        glVertex2f(cpuinitialStickman[1] += cpusmall, 450.0);
        glTexCoord2f(1.0, 1.0);
        glVertex2f(cpuinitialStickman[1] += cpusmall, 650.0);
        glTexCoord2f(0.0, 1.0);
        glVertex2f(cpuinitialStickman[0] += cpusmall, 650.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void cpuStickman2()
{
    
    /*This function renders the second position of the cpu's stickman. Each time this function is called the value of cpustickmancount is decremented. Each time this function is called the stickman will translate forward by the specified number of units.*/
    cpustickmancount--;
    glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
    /* load an image file directly as a new OpenGL texture */
    GLuint tex_2d = SOIL_load_OGL_texture
	(
		"images/cpuStickman2.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

/* check for an error during the load process */
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    glBindTexture(GL_TEXTURE_2D, tex_2d);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0);
        glVertex2f(cpuinitialStickman[0] += cpusmall, 450.0);
        glTexCoord2f(1.0, 0.0);
        glVertex2f(cpuinitialStickman[1] += cpusmall, 450.0);
        glTexCoord2f(1.0, 1.0);
        glVertex2f(cpuinitialStickman[1] += cpusmall, 650.0);
        glTexCoord2f(0.0, 1.0);
        glVertex2f(cpuinitialStickman[0] += cpusmall, 650.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void buttons()
{
	/*This function generates the 26 buttons displayed on the screen. Each of these buttons correspond to an alphabet.*/
	setfont(GLUT_BITMAP_9_BY_15);
   	glColor3f(1.0,1.0,1.0);
   	drawstring(50, 40, 'a');
   	glBegin(GL_LINE_LOOP);
   		glVertex2f(20, 20);
   		glVertex2f(90, 20);
   		glVertex2f(90, 70);
   		glVertex2f(20, 70);
   	glEnd();

   	drawstring(140, 40, 'b');
   	glBegin(GL_LINE_LOOP);
   		glVertex2f(110, 20);
   		glVertex2f(180, 20);
   		glVertex2f(180, 70);
   		glVertex2f(110, 70);
   	glEnd();

   	drawstring(230, 40, 'c');
   	glBegin(GL_LINE_LOOP);
   		glVertex2f(200, 20);
   		glVertex2f(270, 20);
   		glVertex2f(270, 70);
   		glVertex2f(200, 70);
   	glEnd();

   	drawstring(320, 40, 'd');
   	glBegin(GL_LINE_LOOP);
   		glVertex2f(290, 20);
   		glVertex2f(360, 20);
   		glVertex2f(360, 70);
   		glVertex2f(290, 70);
   	glEnd();

   	drawstring(410, 40, 'e');
   	glBegin(GL_LINE_LOOP);
   		glVertex2f(380, 20);
   		glVertex2f(450, 20);
   		glVertex2f(450, 70);
   		glVertex2f(380, 70);
   	glEnd();

   	drawstring(500, 40, 'f');
   	glBegin(GL_LINE_LOOP);
   		glVertex2f(470, 20);
   		glVertex2f(540, 20);
   		glVertex2f(540, 70);
   		glVertex2f(470, 70);
   	glEnd();

   	drawstring(590, 40, 'g');
   	glBegin(GL_LINE_LOOP);
   		glVertex2f(560, 20);
   		glVertex2f(630, 20);
   		glVertex2f(630, 70);
   		glVertex2f(560, 70);
   	glEnd();

   	drawstring(680, 40, 'h');
   	glBegin(GL_LINE_LOOP);
   		glVertex2f(650, 20);
   		glVertex2f(720, 20);
   		glVertex2f(720, 70);
   		glVertex2f(650, 70);
   	glEnd();

   	drawstring(770, 40, 'i');
   	glBegin(GL_LINE_LOOP);
   		glVertex2f(740, 20);
   		glVertex2f(810, 20);
   		glVertex2f(810, 70);
   		glVertex2f(740, 70);
   	glEnd();

   	drawstring(860, 40, 'j');
   	glBegin(GL_LINE_LOOP);
   		glVertex2f(830, 20);
   		glVertex2f(900, 20);
   		glVertex2f(900, 70);
   		glVertex2f(830, 70);
   	glEnd();

   	drawstring(950, 40, 'k');
   	glBegin(GL_LINE_LOOP);
   		glVertex2f(920, 20);
   		glVertex2f(990, 20);
   		glVertex2f(990, 70);
   		glVertex2f(920, 70);
   	glEnd();

   	drawstring(1040, 40, 'l');
   	glBegin(GL_LINE_LOOP);
   		glVertex2f(1010, 20);
   		glVertex2f(1080, 20);
   		glVertex2f(1080, 70);
   		glVertex2f(1010, 70);
   	glEnd();

   	drawstring(1130, 40, 'm');
   	glBegin(GL_LINE_LOOP);
   		glVertex2f(1100, 20);
   		glVertex2f(1170, 20);
   		glVertex2f(1170, 70);
   		glVertex2f(1100, 70);
   	glEnd();

   	drawstring(50, 100, 'n');
   	glBegin(GL_LINE_LOOP);
   		glVertex2f(20, 80);
   		glVertex2f(90, 80);
   		glVertex2f(90, 130);
   		glVertex2f(20, 130);
   	glEnd();

   	drawstring(140, 100, 'o');
   	glBegin(GL_LINE_LOOP);
   		glVertex2f(110, 80);
   		glVertex2f(180, 80);
   		glVertex2f(180, 130);
   		glVertex2f(110, 130);
   	glEnd();

   	drawstring(230, 100, 'p');
   	glBegin(GL_LINE_LOOP);
   		glVertex2f(200, 80);
   		glVertex2f(270, 80);
   		glVertex2f(270, 130);
   		glVertex2f(200, 130);
   	glEnd();

   	drawstring(320, 100, 'q');
   	glBegin(GL_LINE_LOOP);
   		glVertex2f(290, 80);
   		glVertex2f(360, 80);
   		glVertex2f(360, 130);
   		glVertex2f(290, 130);
   	glEnd();

   	drawstring(410, 100, 'r');
   	glBegin(GL_LINE_LOOP);
   		glVertex2f(380, 80);
   		glVertex2f(450, 80);
   		glVertex2f(450, 130);
   		glVertex2f(380, 130);
   	glEnd();

   	drawstring(500, 100, 's');
   	glBegin(GL_LINE_LOOP);
   		glVertex2f(470, 80);
   		glVertex2f(540, 80);
   		glVertex2f(540, 130);
   		glVertex2f(470, 130);
   	glEnd();

   	drawstring(590, 100, 't');
   	glBegin(GL_LINE_LOOP);
   		glVertex2f(560, 80);
   		glVertex2f(630, 80);
   		glVertex2f(630, 130);
   		glVertex2f(560, 130);
   	glEnd();

   	drawstring(680, 100, 'u');
   	glBegin(GL_LINE_LOOP);
   		glVertex2f(650, 80);
   		glVertex2f(720, 80);
   		glVertex2f(720, 130);
   		glVertex2f(650, 130);
   	glEnd();

   	drawstring(770, 100, 'v');
   	glBegin(GL_LINE_LOOP);
   		glVertex2f(740, 80);
   		glVertex2f(810, 80);
   		glVertex2f(810, 130);
   		glVertex2f(740, 130);
   	glEnd();

   	drawstring(860, 100, 'w');
   	glBegin(GL_LINE_LOOP);
   		glVertex2f(830, 80);
   		glVertex2f(900, 80);
   		glVertex2f(900, 130);
   		glVertex2f(830, 130);
   	glEnd();

   	drawstring(950, 100, 'x');
   	glBegin(GL_LINE_LOOP);
   		glVertex2f(920, 80);
   		glVertex2f(990, 80);
   		glVertex2f(990, 130);
   		glVertex2f(920, 130);
   	glEnd();

   	drawstring(1040, 100, 'y');
   	glBegin(GL_LINE_LOOP);
   		glVertex2f(1010, 80);
   		glVertex2f(1080, 80);
   		glVertex2f(1080, 130);
   		glVertex2f(1010, 130);
   	glEnd();

   	drawstring(1130, 100, 'z');
   	glBegin(GL_LINE_LOOP);
   		glVertex2f(1100, 80);
   		glVertex2f(1170, 80);
   		glVertex2f(1170, 130);
   		glVertex2f(1100, 130);
   	glEnd();
}

void operations(GLchar key)
{
    /*This function recognises the mouse clicks and matches the button pressed with the current character in the randomly generated string. If both of them are same, then the user's stickman gets an added bonus of 20 units for every character matched but if one character is missed, then the stickman is penalised with 20 units for each character. The function keeps the program in execution until one of the stickman has reached the finish. This function transfers the control back to the characterStream function if none of the stickmans have finished the race.*/
    if(key == randchar[i - dec])
    {
        initialStickman[0] += increment;
        initialStickman[1] += increment;
        score++;
        dec--;
    }
    else
    {
        initialStickman[0] -= 20;
        initialStickman[1] -= 20;
        score++;
        dec--;
    }

    if( score == 5 )
    {
        if(initialStickman[1] < 1100 && cpuinitialStickman[1] >= 1100)
        {
            youLose();
        }
        else if(initialStickman[1] >= 1100 && cpuinitialStickman[1] < 1100)
        {
            youWin();
        }
        else
        {
            score = 0;
            dec = 5;
            rand_string(6);
            characterStream();
        }
    }

}


void mousePressedCharacterStream(int btn, int state, int x, int y)
{
    /*This function recognises the mouse clicks and stores the value of the current click into key which is then compared with the current character in the operations functions and the control is transferred to the operations functions where furthur processing happens*/
    GLchar key;

	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if((x>=20 && x<=90) && (y>= 630 && y<= 680))
        {
            key = 'a';
        }
        else if((x>=110 && x<=180) && (y>= 630 && y<= 680))
        {
            key = 'b';
        }
        else if((x>=200 && x<=270) && (y>= 630 && y<= 680))
        {
            key = 'c';
        }
        else if((x>=290 && x<=360) && (y>= 630 && y<= 680))
        {
            key = 'd';
        }
        else if((x>=380 && x<=450) && (y>= 630 && y<= 680))
        {
            key = 'e';
        }
        else if((x>=470 && x<=540) && (y>= 630 && y<= 680))
        {
            key = 'f';
        }
        else if((x>=560 && x<=630) && (y>= 630 && y<= 680))
        {
            key = 'g';
        }
        else if((x>=650 && x<=720) && (y>= 630 && y<= 680))
        {
            key = 'h';
        }
        else if((x>=740 && x<=810) && (y>= 630 && y<= 680))
        {
            key = 'i';
        }
        else if((x>=830 && x<=900) && (y>= 630 && y<= 680))
        {
            key = 'j';
        }
        else if((x>=920 && x<=990) && (y>= 630 && y<= 680))
        {
            key = 'k';
        }
        else if((x>=1010 && x<=1080) && (y>= 630 && y<= 680))
        {
            key = 'l';
        }
        else if((x>=1100 && x<=1170) && (y>= 630 && y<= 680))
        {
            key = 'm';
        }
        if((x>=20 && x<=90) && (y>= 570 && y<= 620))
        {
            key = 'n';
        }
        else if((x>=110 && x<=180) && (y>= 570 && y<= 620))
        {
            key = 'o';
        }
        else if((x>=200 && x<=270) && (y>= 570 && y<= 620))
        {
            key = 'p';
        }
        else if((x>=290 && x<=360) && (y>= 570 && y<= 620))
        {
            key = 'q';
        }
        else if((x>=380 && x<=450) && (y>= 570 && y<= 620))
        {
            key = 'r';
        }
        else if((x>=470 && x<=540) && (y>= 570 && y<= 620))
        {
            key = 's';
        }
        else if((x>=560 && x<=630) && (y>= 570 && y<= 620))
        {
            key = 't';
        }
        else if((x>=650 && x<=720) && (y>= 570 && y<= 620))
        {
            key = 'u';
        }
        else if((x>=740 && x<=810) && (y>= 570 && y<= 620))
        {
            key = 'v';
        }
        else if((x>=830 && x<=900) && (y>= 570 && y<= 620))
        {
            key = 'w';
        }
        else if((x>=920 && x<=990) && (y>= 570 && y<= 620))
        {
            key = 'x';
        }
        else if((x>=1010 && x<=1080) && (y>= 570 && y<= 620))
        {
            key = 'y';
        }
        else if((x>=1100 && x<=1170) && (y>= 570 && y<= 620))
        {
            key = 'z';
        }
        operations(key);
    }
}

void characterStream()
{
    /*This function generates the square in which the user has to match the randomly generated characters of the string. Each character of the string is translated from the start position till it reaches the end of the box in this function. Every mouse click transfers the control to the mouse function.*/
    int j;
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    buttons();
    glutMouseFunc(mousePressedCharacterStream);


             if( !stickmancount )
            {
                    stickman1();
                    cpuStickman1();
                }
                else
                {
                    stickman2();
                    cpuStickman2();
                }

	if(randchar[i]!='\0')
        {
            k = 350;

            while(k<620)
            {
                //glClear(GL_COLOR_BUFFER_BIT);
                 k = k + increment;
                 glBegin(GL_LINE_LOOP);
                     glColor3f(1.0,0.0,0.0);
                     glVertex2i(600,150);
                     glVertex2i(640,150);
                     glVertex2i(640,190);
                     glVertex2i(600,190);
                 glEnd();
                 glRasterPos2d(k,165);
                 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,randchar[i]);
                 for(j=0;j<100000000;j++);
                 glFlush();

             }
            i++;
            if(i <= 5)
            {
                characterStream();
            }
        }
}

void loadingScreen()
{
    /* Tenders the image load.png. This function simulates the loading bar that is found in most of the games. Once the entire bar is filled, the control is transferred to the characterStream function through the mousePressedLoadScreen function*/
    int i;
	GLuint tex_2d_2, tex_2d_4;
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	tex_2d_4 = SOIL_load_OGL_texture
	(
		"images/load.png",
		SOIL_LOAD_RGBA,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_NTSC_SAFE_RGB
	);

	glBindTexture(GL_TEXTURE_2D, tex_2d_4);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 1.0);
		glVertex2f(0.0f, 0.0f);
		glTexCoord2f(1.0, 1.0);
		glVertex2f(1200.0f, 0.0f);
		glTexCoord2f(1.0, 0.0);
		glVertex2f(1200.0f, 700.0f);
		glTexCoord2f(0.0, 0.0);
		glVertex2f(0.0f, 700.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(57.0f+x_step, 345.3f);
	glVertex2f(59.0f, 345.3f);
	glVertex2f(59.0f, 351.0f);
	glVertex2f(57.0f+x_step, 351.0f);
	glEnd();
	glFlush();

	x_step += 40;

	if(x_step <= 1100)
	{
		for(i = 0; i<10000000;i++);
		{
			loadingScreen();
		}

	}
    	else
   	 {
        	characterStream();
   	 }
}

void mousePressedInstructionPage(int button, int state, int x, int y)
{
    /* If the user presses the left mouse button in instructionPage, then this function transfers the control to loadingScreen function once the mouse is released*/
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        glClear(GL_COLOR_BUFFER_BIT);
        loadingScreen();
    }
}
void instructionPage()
{	
	/*This function displays all the instructions of the game.*/
	int i;
	glClearColor(0.0,0.0,0.0,0.0);
	char instructions[] = "Instructions";
	char instruction1[] = "1. The blue stickman is the user and the red stickman is the cpu.";
	char instruction2[] = "2. User needs to match the characters being displayed on the screen before a new character is generated";
	char instruction21[] = "by clicking the corresponding button.";
	char instruction3[] = "3. The user and the cpu stickman translate by 5 and 10 units respectively throughout the game.";
	char instruction4[] = "4. For every string of five characters matched the user gets a bonus of 100 units.";
	char instruction5[] = "5. The user gets penalised by 20 units for every character missed.";
	char message[] = "Let's beat the Red Stickman, Click To Play.";

	
	glColor3f(1.0,0.0,1.0);
	glRasterPos2i(450, 600);
	for(i = 0; instructions[i]!='\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, instructions[i]);
	
	glColor3f(1.0,1.0,1.0);
	glRasterPos2i(100, 530);
	for(i = 0; instruction1[i]!='\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, instruction1[i]);

	glRasterPos2i(100, 500);
	for(i = 0; instruction2[i]!='\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, instruction2[i]);

	glRasterPos2i(125, 475);
	for(i = 0; instruction21[i]!='\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, instruction21[i]);


	glRasterPos2i(100, 445);
	for(i = 0; instruction3[i]!='\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, instruction3[i]);


	glRasterPos2i(100, 415);
	for(i = 0; instruction4[i]!='\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, instruction4[i]);

	glRasterPos2i(100, 385);
	for(i = 0; instruction5[i]!='\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, instruction5[i]);

	glColor3f(1.0,0.0,0.0);
	glRasterPos2i(500, 100);
	for(i = 0; message[i]!='\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
	
	glFlush();
	
	glutMouseFunc(mousePressedInstructionPage);
}

void mousePressed(int button, int state, int x, int y)
{
    /* If the user presses the left mouse button in frontPage, then this function transfers the control to instructionPage function once the mouse is released*/
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        glClear(GL_COLOR_BUFFER_BIT);
        instructionPage();
    }
}


void frontPage()
{
	/*Loads the image AlphaRun.jpg as the first page of the project. A left click on this page calls the mousePressed function which redirects the control to loadingScreen function which is the second page of the function*/

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
    /* load an image file directly as a new OpenGL texture */
	GLuint tex_2d = SOIL_load_OGL_texture
	(
		"images/AlphaRun.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	/* check for an error during the load process */
	if( 0 == tex_2d )
	{
		printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
	}

	glBindTexture(GL_TEXTURE_2D, tex_2d);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(0.0, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(1200.0, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(1200.0, 700.0);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(0.0, 700.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	glFlush();
	rand_string(6);
	glutMouseFunc(mousePressed);
}

void init()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glPointSize(5.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,1200.0,0.0,700.0);
}


int main(int argc, char**argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(1200,700);
    glutInitWindowPosition(0,0);
    glutCreateWindow("AlphaRun");
    glutDisplayFunc(frontPage);
    init();
    glutMainLoop();
}
