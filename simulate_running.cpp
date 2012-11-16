#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

//Skeleton Const
const double BASIC_SIZE = 0.25;
const double HEAD_RADIUS = 0.05;
const double THIGH_SCALE_X = 0.7;
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
const double ARM_SCALE_X = 0.45;
const double ARM_SCALE_Y = 0.15;
const double ARM_SCALE_Z = 0.2;
const double FOREARM_SCALE_X = 0.65;
const double FOREARM_SCALE_Y = 0.15;
const double FOREARM_SCALE_Z = 0.2;

//Relative Const
const static double PI = acos(-1.0);
const int NUM_OF_LINE = 50;
const int BLOCK_SIZE = 1;

//Skeleton Parameter
float neck[3] = {0.0f,BASIC_SIZE * BODY_SCALE_Y + HEAD_RADIUS,0.0f};
float spine[3] = {0.0f,BASIC_SIZE * BODY_SCALE_Y / 2,0.0f};
float thighL[3] = {BASIC_SIZE * THIGH_SCALE_X / 2,0.0f,BASIC_SIZE * THIGH_SCALE_Z};
float calfL[3] = {BASIC_SIZE * CALF_SCALE_X / 2,0.0f,0.0f};
float thighR[3] = {BASIC_SIZE * THIGH_SCALE_X / 2,0.0f,-BASIC_SIZE * THIGH_SCALE_Z};
float calfR[3] = {BASIC_SIZE * CALF_SCALE_X / 2,0.0f,0.0f};
float armL[3] = {BASIC_SIZE * ARM_SCALE_X / 2,0.0f,BASIC_SIZE * (ARM_SCALE_Z + BODY_SCALE_Z) / 2};
float armR[3] = {BASIC_SIZE * ARM_SCALE_X / 2,0.0f,-BASIC_SIZE * (ARM_SCALE_Z + BODY_SCALE_Z) / 2};

//Relative Parameter
GLUquadricObj *quadric;
bool left_forward = true;
bool right_forward = false;
double floor_move;
double lookatX;
double lookatY;
double lookatZ;
int scr_w;
int scr_h;
int vangle = 0;
float left_thigh_angle = -60;
float left_calf_angle = 30;
float left_foot_angle = 90;
float right_thigh_angle = -120;
float right_calf_angle = 30;
float right_foot_angle = 90;
float left_arm_angle = -90;
float left_forearm_angle = -30;
float right_arm_angle = -75;
float right_forearm_angle = -15;

void init()
{
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    quadric = gluNewQuadric();
    gluQuadricNormals(quadric,GLU_SMOOTH);
    gluQuadricTexture(quadric,GL_TRUE);
    lookatX = -1.06;
    lookatY = 0.5;
    lookatZ = 1.06;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (int i = 0;i < NUM_OF_LINE;i++)
    {
        glBegin(GL_LINES);
            glVertex3f((NUM_OF_LINE / 2 - i) * BLOCK_SIZE + floor_move * cos((double)vangle / 180.0 * PI),-BASIC_SIZE * (BODY_SCALE_Y + THIGH_SCALE_X + CALF_SCALE_X + FOOT_SCALE_Z) / 2,NUM_OF_LINE * BLOCK_SIZE);
            glVertex3f((NUM_OF_LINE / 2 - i) * BLOCK_SIZE + floor_move * cos((double)vangle / 180.0 * PI),-BASIC_SIZE * (BODY_SCALE_Y + THIGH_SCALE_X + CALF_SCALE_X + FOOT_SCALE_Z) / 2,-NUM_OF_LINE * BLOCK_SIZE);
        glEnd();
        glBegin(GL_LINES);
            glVertex3f(NUM_OF_LINE * BLOCK_SIZE,-BASIC_SIZE * (BODY_SCALE_Y + THIGH_SCALE_X + CALF_SCALE_X + FOOT_SCALE_Z) / 2,(NUM_OF_LINE / 2 - i) * BLOCK_SIZE - floor_move * sin((double)vangle / 180.0 * PI));
            glVertex3f(-NUM_OF_LINE * BLOCK_SIZE,-BASIC_SIZE * (BODY_SCALE_Y + THIGH_SCALE_X + CALF_SCALE_X + FOOT_SCALE_Z) / 2,(NUM_OF_LINE / 2 - i) * BLOCK_SIZE - floor_move * sin((double)vangle / 180.0 * PI));
        glEnd();
    }
    floor_move += 0.005;
    if (floor_move >= BLOCK_SIZE)
      floor_move -= BLOCK_SIZE;
    glPushMatrix();
    glRotatef(vangle,0.0f,1.0f,0.0f);
    glColor3f(0.9f,0.9f,0.9f);
    //Head
    glPushMatrix();
        glTranslatef(neck[0],neck[1],neck[2]);
        glutSolidSphere(HEAD_RADIUS,10,10);
    glPopMatrix();
    //Body
    glPushMatrix();
        glTranslatef(spine[0],spine[1],spine[2]);
        glScalef(BODY_SCALE_X,BODY_SCALE_Y,BODY_SCALE_Z);
        glutSolidCube(BASIC_SIZE);
    glPopMatrix();
    glColor3f(0.5f,0.5f,0.5f);
    //Left leg
    glPushMatrix();
        //Hip
        glPushMatrix();
            glTranslatef(0.0f,0.0f,BASIC_SIZE * THIGH_SCALE_Z);
            glutSolidSphere(BASIC_SIZE * THIGH_SCALE_Y / 2,10,10);
        glPopMatrix();
        //Thigh
        glRotatef((GLfloat)left_thigh_angle,0.0f,0.0f,1.0f);
        glTranslatef(thighL[0],thighL[1],thighL[2]);
        glPushMatrix();
            glScalef(THIGH_SCALE_X,THIGH_SCALE_Y,THIGH_SCALE_Z);
            glutSolidCube(BASIC_SIZE);
        glPopMatrix();
        //Knee
        glTranslatef(BASIC_SIZE * THIGH_SCALE_X / 2,0.0f,0.0f);
        glutSolidSphere(BASIC_SIZE * THIGH_SCALE_Y / 2,10,10);
        //Calf
        glRotatef((GLfloat)left_calf_angle,0.0f,0.0f,1.0f);
        glTranslatef(calfL[0],calfL[1],calfL[2]);
        glPushMatrix();
            glScalef(CALF_SCALE_X,CALF_SCALE_Y,CALF_SCALE_Z);
            glutSolidCube(BASIC_SIZE);
        glPopMatrix();
        //Foot
        glTranslatef(BASIC_SIZE * CALF_SCALE_X / 2,0.0f,0.0f);
        glTranslatef(-BASIC_SIZE * FOOT_SCALE_X / 2 + BASIC_SIZE * THIGH_SCALE_Y,-BASIC_SIZE * CALF_SCALE_Y / 2,0.0f);
        glRotatef((GLfloat)left_foot_angle,0.0f,0.0f,1.0f);
        glPushMatrix();
            glScalef(FOOT_SCALE_X,FOOT_SCALE_Y,FOOT_SCALE_Z);
            glutSolidCube(BASIC_SIZE);
        glPopMatrix();
    glPopMatrix();
    //Left Arm
    glPushMatrix();
    glTranslatef(0.0f,BASIC_SIZE * BODY_SCALE_Y,0.0f);
        //Arm
        glRotatef((GLfloat)left_arm_angle,0.0f,0.0f,1.0f);
        glTranslatef(armL[0],armL[1],armL[2]);
        glPushMatrix();
            glScalef(ARM_SCALE_X,ARM_SCALE_Y,ARM_SCALE_Z);
            glutSolidCube(BASIC_SIZE);
        glPopMatrix();
        //Elbow
        glTranslatef(BASIC_SIZE * ARM_SCALE_X / 2,0.0f,0.0f);
        glutSolidSphere(BASIC_SIZE * ARM_SCALE_Y / 2,10,10);
        //Forearm
        glRotatef((GLfloat)left_forearm_angle,0.0f,0.0f,1.0f);
        glTranslatef(BASIC_SIZE * FOREARM_SCALE_X / 2,0.0f,0.0f);
        glPushMatrix();
            glScalef(FOREARM_SCALE_X,FOREARM_SCALE_Y,FOREARM_SCALE_Z);
            glutSolidCube(BASIC_SIZE);
        glPopMatrix();
    glPopMatrix();
    glColor3f(0.7f,0.7f,0.7f);
    //Right leg
    glPushMatrix();
        //Hip
        glPushMatrix();
            glTranslatef(0.0f,0.0f,-BASIC_SIZE * THIGH_SCALE_Z);
            glutSolidSphere(BASIC_SIZE * THIGH_SCALE_Y / 2,10,10);
        glPopMatrix();
        //Thigh
        glRotatef((GLfloat)right_thigh_angle,0.0f,0.0f,1.0f);
        glTranslatef(thighR[0],thighR[1],thighR[2]);
        glPushMatrix();
            glScalef(THIGH_SCALE_X,THIGH_SCALE_Y,THIGH_SCALE_Z);
            glutSolidCube(BASIC_SIZE);
        glPopMatrix();
        //Knee
        glTranslatef(BASIC_SIZE * THIGH_SCALE_X / 2,0.0f,0.0f);
        glutSolidSphere(BASIC_SIZE * THIGH_SCALE_Y / 2,10,10);
        //Calf
        glRotatef((GLfloat)right_calf_angle,0.0f,0.0f,1.0f);
        glTranslatef(calfR[0],calfR[1],calfR[2]);
        glPushMatrix();
            glScalef(CALF_SCALE_X,CALF_SCALE_Y,CALF_SCALE_Z);
            glutSolidCube(BASIC_SIZE);
        glPopMatrix();
        //Foot
        glTranslatef(BASIC_SIZE * CALF_SCALE_X / 2,0.0f,0.0f);
        glTranslatef(-BASIC_SIZE * FOOT_SCALE_X / 2 + BASIC_SIZE * THIGH_SCALE_Y,-BASIC_SIZE * CALF_SCALE_Y / 2,0.0f);
        glRotatef((GLfloat)right_foot_angle,0.0f,0.0f,1.0f);
        glPushMatrix();
            glScalef(FOOT_SCALE_X,FOOT_SCALE_Y,FOOT_SCALE_Z);
            glutSolidCube(BASIC_SIZE);
        glPopMatrix();
    glPopMatrix();
    //Right Arm
    glPushMatrix();
    glTranslatef(0.0f,BASIC_SIZE * BODY_SCALE_Y,0.0f);
        //Arm
        glRotatef((GLfloat)right_arm_angle,0.0f,0.0f,1.0f);
        glTranslatef(armR[0],armR[1],armR[2]);
        glPushMatrix();
            glScalef(ARM_SCALE_X,ARM_SCALE_Y,ARM_SCALE_Z);
            glutSolidCube(BASIC_SIZE);
        glPopMatrix();
        //Elbow
        glTranslatef(BASIC_SIZE * ARM_SCALE_X / 2,0.0f,0.0f);
        glutSolidSphere(BASIC_SIZE * ARM_SCALE_Y / 2,10,10);
        //Forearm
        glRotatef((GLfloat)right_forearm_angle,0.0f,0.0f,1.0f);
        glTranslatef(BASIC_SIZE * FOREARM_SCALE_X / 2,0.0f,0.0f);
        glPushMatrix();
            glScalef(FOREARM_SCALE_X,FOREARM_SCALE_Y,FOREARM_SCALE_Z);
            glutSolidCube(BASIC_SIZE);
        glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void refresh(int c)
{
    if (left_thigh_angle < -120)
    {
        left_forward = false;
    }
    else if (left_thigh_angle > -60)
    {
        left_forward = true;
    }
    if (right_thigh_angle < -120)
    {
        right_forward = false;
    }
    else if (right_thigh_angle > -60)
    {
        right_forward = true;
    }
    if (left_forward)
    {
        left_thigh_angle--;
        if (left_thigh_angle < -90)
            left_calf_angle++;
        else left_calf_angle--;
        left_arm_angle += 0.25;
        left_forearm_angle += 0.5;
    }
    else
    {
        left_thigh_angle++;
        if (left_thigh_angle <= -90)
          left_calf_angle--;
        else left_calf_angle++;
        left_arm_angle -= 0.25;
        left_forearm_angle -= 0.5;
    }
    if (right_forward)
    {
        right_thigh_angle--;
        if (right_thigh_angle < -90)
          right_calf_angle++;
        else right_calf_angle--;
        right_arm_angle += 0.25;
        right_forearm_angle += 0.5;
    }
    else
    {
        right_thigh_angle++;
        if (right_thigh_angle <= -90)
          right_calf_angle--;
        else right_calf_angle++;
        right_arm_angle -= 0.25;
        right_forearm_angle -= 0.5;
    }
    glutPostRedisplay();
    glutTimerFunc(1,refresh,0);
}

void reshape(int w,int h)
{
    scr_w = w;
    scr_h = h;
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0,(GLfloat)w / (GLfloat)h,1.0,200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(lookatX,lookatY,lookatZ,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f);
}

void mousemove(int x,int y)
{
    lookatX = -1.5 + (double)x / scr_w * 3;
    lookatY = 1 - (double)y / scr_h * 2;
    lookatZ = sqrt(2.25 - lookatX * lookatX);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(lookatX,lookatY,lookatZ,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f);
}

void control(unsigned char key,int x,int y)
{
    switch(key)
    {
        case 'a':
            vangle = (vangle + 1) % 360;
            break;
        case 'd':
            vangle = (vangle - 1) % 360;
            break;
        case 's':
            vangle = -(180 - vangle) % 360;
            break;
        case 27:
            exit(0);
        default:
            break;
    }
}

int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(100,100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(mousemove);
    glutKeyboardFunc(control);
    refresh(0);
    glutMainLoop();
    return 0;
}
