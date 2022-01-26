#include<windows.h>
#include<bits/stdc++.h>
#include<sstream>
#include <string>
#include <sstream>
#include <stdexcept>
//#include<GL/glu.h>
#include<GL/glut.h>

#define ORTHO_LEFT -1000
#define ORTHO_RIGHT 1000
#define ORTHO_TOP 1000
#define ORTHO_BOTTOM -1000
#define ORTHO_NEAR 0
#define ORTHO_FAR 10000

#define C_WINDOW_WIDTH 750
#define C_WINDOW_HEIGHT 570

#define ENEMY_SIDE 200

int score = 0;

int playerX = 0;
int playerY = 0;
int enemyX = 300;
int enemyY = 300;

int gameOver = 0;
int playerSpeed = 17;
int enemySpeed = 5;
int directionOfEnemy = 1;
struct objectInfo{
  int top, bottom, right, left;
};

struct objectInfo playerInfo = {100, 100, 100, 100};
struct objectInfo enemyInfo = {ENEMY_SIDE, ENEMY_SIDE, ENEMY_SIDE, ENEMY_SIDE};

typedef struct Color{
    int r, g, b;
}Color;
Color color[] = {{1, 0.5, 0.5}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1}, {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {0, 0, 1} };

struct point{
    double x,y,z;
};
struct point eye= {100,100,100}; //Perspective Projection Parameter
struct point up = {0,0,1}; //Perspective Projection Parameter, change according id

void drawAxes()
{

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);{
        glColor3f(0.0f,1.0f,0.0f);
        glVertex3f( 1000,0,0);
        glVertex3f(-1000,0,0);

        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f(0,-1000,0);
        glVertex3f(0, 1000,0);

        glColor3f(0.0f,0.0f,1.0f);
        glVertex3f(0,0, 1000);
        glVertex3f(0,0,-1000);
    }glEnd();

}


void drawGrid()
{
	int i;

    glColor3f(0.6, 0.6, 0.6);	//grey
    glBegin(GL_LINES);{
        for(i=-8;i<=8;i++){

            if(i==0)
                continue;	//SKIP the MAIN axes

            //lines parallel to Y-axis
            glVertex3f(i*10, -90, 0);
            glVertex3f(i*10,  90, 0);

            //lines parallel to X-axis
            glVertex3f(-90, i*10, 0);
            glVertex3f( 90, i*10, 0);
        }
    }glEnd();

}


void createSquare(int x, int y, int side, float r, float g, float b){

    glBegin(GL_QUADS);
        glColor3f(r, g, b);
        glVertex3d(x, y, 0);
        glVertex3d(x + side, y, 0);
        glVertex3d(x + side, y + side, 0);
        glVertex3d(x, y + side, 0);
    glEnd();
}

void init(){



    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(ORTHO_LEFT, ORTHO_RIGHT, ORTHO_BOTTOM, ORTHO_TOP, ORTHO_NEAR, ORTHO_FAR);
//    gluPerspective(80, 1, 1, 5700);
}

void player(){
    glPushMatrix();
        glTranslated(playerX, playerY, 0);
         std::cout << "The enemy X, Y = (" << playerX << ", " << playerY << ")\n";
        createSquare(0, 0, 100, 1, 1, 1);
    glPopMatrix();
}

void enemy(){
    glPushMatrix();
        glTranslated(enemyX, enemyY, 0);
        //std::cout << "The enemy X, Y = (" << enemyX << ", " << enemyY << ")\n";
        createSquare(0, 0, ENEMY_SIDE, 1, 0, 0);
    glPopMatrix();
}

std::string toString(int n){
    std::ostringstream stm;
   stm << n;
   return stm.str();

}

printScore(){
    score++;
    glColor3d(0., 1., 0.);
    glPushMatrix();
        //glWindowPos2i( 10, 1014 );  // move in 10 pixels from the left and bottom edges
        std::string s = "High Score ";
        s += toString(score);
        std::cout << s;
        glRasterPos2f(-900, 900);

        int len = s.size();
        for (int i = 0; i < len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, s[i]);
        }
    glPopMatrix();

}

void display(){
 if(gameOver == 1){
    glColor3d(1., 0., 0.);
    glPushMatrix();
        //glWindowPos2i( 10, 1014 );  // move in 10 pixels from the left and bottom edges
        std::string s = "GAME OVER!!!";
        glRasterPos2f(-200, 0);

        int len = s.size();
        for (int i = 0; i < len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
        }
    glPopMatrix();
    glutSwapBuffers();
    return;
 }else{
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);	//color black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gluLookAt(0, 0, 1000, 0, 0, 0, 0, 1, 0);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glBegin(GL_LINES);
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(-1000, 0);
        glVertex2f(1000, 0);

        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(0, -1000);
        glVertex2f(0, 1000);
    glEnd();

    player();
    enemy();
    if(playerX + playerInfo.right > enemyX && playerY + playerInfo.top > enemyY && playerY < enemyY + enemyInfo.top && playerX < enemyX + enemyInfo.right){
        std::cout << "Player crashed!!!\n";
        gameOver = 1;
    }
    printScore();

    //glutPostRedisplay();
    //glFlush();
    glutSwapBuffers();
 }
}


void myKeyboard(unsigned char key, int x, int y){

}

void mySpecial(int key, int x, int y){
    if (key == GLUT_KEY_UP && playerY + playerInfo.top < 1000){
        playerY += playerSpeed;
    }
    else if(key == GLUT_KEY_DOWN && playerY > -1000){
        playerY -= playerSpeed;
    }
    else if(key == GLUT_KEY_LEFT && playerX > -1000){
        playerX -= playerSpeed;
    }
    else if(key == GLUT_KEY_RIGHT  && playerX + playerInfo.right < 1000){
        playerX += playerSpeed;
    }

}

void myMouse(int key, int state, int x, int y){

}

void timer(int x){
     directionOfEnemy =  rand()%8;
     //score++;
     enemySpeed++;
     glutTimerFunc(3000, timer, 1);
}

void animate(){
    //playerX += playerSpeed;
    if(enemyY + enemyInfo.top >= 1000){
        directionOfEnemy = 1;
    }
    if(enemyY  <= -1000){
        directionOfEnemy = 0;
    }
    if(enemyX + enemyInfo.right >= 1000){
        directionOfEnemy = 2;
    }
    if(enemyX <= -1000){
        directionOfEnemy = 3;
    }
    if(directionOfEnemy == 0){ //direction top
        enemyY += enemySpeed;
    }
    else if(directionOfEnemy == 1){ //direction bot
        enemyY -= enemySpeed;
    }
    else if(directionOfEnemy == 2){ //direction left
        enemyX -= enemySpeed;
    }
    else if(directionOfEnemy == 3){ //direction right
        enemyX += enemySpeed;
    }
    else if(directionOfEnemy == 4){
        enemyX += enemySpeed;
        enemyY += enemySpeed;
    }
    else if(directionOfEnemy == 5){
        enemyX -= enemySpeed;
        enemyY += enemySpeed;
    }
    else if(directionOfEnemy == 6){
        enemyX += enemySpeed;
        enemyY -= enemySpeed;
    }
    else if(directionOfEnemy == 7){
        enemyX -= enemySpeed;
        enemyY -= enemySpeed;
    }
    glutPostRedisplay();
}
void myMenu(int x){

}
int main(int argc, char** argv){
    glutInit( &argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Testing Area");
    init();
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecial);
    glutMouseFunc(myMouse);
    glutTimerFunc(3000, timer, 0);


    //glutCreateMenu(myMenu);
    glutMainLoop();

}
