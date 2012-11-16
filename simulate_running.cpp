#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

//Skeleton Const
const double BASIC_SIZE = 0.25;
const double THIGH_SCALE_X = 0.6;
const double THIGH_SCALE_Y = 0.2;
const double THIGH_SCALE_Z = 0.2;
const double CALF_SCALE_X = 0.8;
const double CALF_SCALE_Y = 0.2;
const double CALF_SCALE_Z = 0.2;
const double FOOT_SCALE_X = 0.5;
const double FOOT_SCALE_Y = 0.15;
const double FOOT_SCALE_Z = 0.2;
const double BODY_SCALE_X = 0.25;
const double BODY_SCALE_Y = 1.25;
const double BODY_SCALE_Z = 0.75;

//Relative Const
const static double PI = acos(1.0);

//Skeleton Parameter
float spine[3] = {0.0f,BASIC_SIZE * BODY_SCALE_Y / 2,0.0f};
float thighL[3] = {BASIC_SIZE * THIGH_SCALE_X / 2,0.0f,BASIC_SIZE * THIGH_SCALE_Z};
float calfL[3] = {BASIC_SIZE * CALF_SCALE_X / 2,0.0f,0.0f};

//Relative Parameter
GLUquadricObj *quadric;
double lookatX;
double lookatY;
double lookatZ;
float centerX = 0;
float centerY = 0;
float centerZ = 0;
int scr_w;
int scr_h;
float vangle = 0;
float left_thigh_angle = -60;
float left_calf_angle = 60;
float left_foot_angle = 90;

void init()
{
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    quadric = gluNewQuadric();
    gluQuadricNormals(quadric,GLU_SMOOTH);
    gluQuadricTexture(quadric,GL_TRUE);
}

void drawSolidCircle(GLfloat x,GLfloat y,GLfloat r)
{
    int n = 128;
    GLfloat PI2 = 2.0f * PI;
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x,y);
        for (int i = 0;i < n;i++)
          glVertex2f(x + r * cos(i * PI2 / n),y + r * sin(i * PI2 / n));
    glEnd();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.9f,0.9f,0.9f);
    glPushMatrix();
    glTranslatef(centerX,centerY,centerZ);
    glRotatef(vangle,0.0f,1.0f,0.0f);
    //Body
    glPushMatrix();
        glTranslatef(spine[0],spine[1],spine[2]);
        glScalef(BODY_SCALE_X,BODY_SCALE_Y,BODY_SCALE_Z);
        glutSolidCube(BASIC_SIZE);
    glPopMatrix();
    //Left leg
    glPushMatrix();
        //Thigh
        glRotatef((GLfloat)left_thigh_angle,0.0f,0.0f,1.0f);
        glTranslatef(thighL[0],thighL[1],thighL[2]);
        glPushMatrix();
            glScalef(THIGH_SCALE_X,THIGH_SCALE_Y,THIGH_SCALE_Z);
            glutSolidCube(BASIC_SIZE);
        glPopMatrix();
        //Knee
        glTranslatef(BASIC_SIZE * THIGH_SCALE_X / 2,0.0f,0.0f);
        glPushMatrix();
            glTranslatef(0.0f,0.0f,-BASIC_SIZE * THIGH_SCALE_Z / 2);
            gluCylinder(quadric,BASIC_SIZE * THIGH_SCALE_Y / 2,BASIC_SIZE * THIGH_SCALE_Y / 2,BASIC_SIZE * THIGH_SCALE_Z,32,32);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.0f,0.0f,BASIC_SIZE * THIGH_SCALE_Z / 2);
            drawSolidCircle(0.0f,0.0f,BASIC_SIZE * THIGH_SCALE_Y / 2);
            glTranslatef(0.0f,0.0f,-BASIC_SIZE * THIGH_SCALE_Z);
            drawSolidCircle(0.0f,0.0f,BASIC_SIZE * THIGH_SCALE_Y / 2);
        glPopMatrix();
        //Calf
        glRotatef((GLfloat)left_calf_angle,0.0f,0.0f,1.0f);
        glTranslatef(calfL[0],calfL[1],calfL[2]);
        glPushMatrix();
            glScalef(CALF_SCALE_X,CALF_SCALE_Y,CALF_SCALE_Z);
            glutSolidCube(BASIC_SIZE);
        glPopMatrix();
        //Foot
        glTranslatef(BASIC_SIZE * THIGH_SCALE_X / 2,0.0f,0.0f);
        glTranslatef(BASIC_SIZE * FOOT_SCALE_X / 7,-BASIC_SIZE * THIGH_SCALE_Y * 7 / 10,0.0f);
        glRotatef((GLfloat)left_foot_angle,0.0f,0.0f,1.0f);
        glPushMatrix();
            glScalef(FOOT_SCALE_X,FOOT_SCALE_Y,FOOT_SCALE_Z);
            glutSolidCube(BASIC_SIZE);
        glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void reshape(int w,int h)
{
    scr_w = w;
    scr_h = h;
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0,(GLfloat)w / (GLfloat)h,1.0,1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(lookatX,lookatY,lookatZ,centerX,0.0f,centerZ,0.0f,1.0f,0.0f);
}

void mousemove(int x,int y)
{
    cout << x << " " << y << "\n";
}

int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(100,100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
//    glutPassiveMotionFunc(mousemove);
//    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
