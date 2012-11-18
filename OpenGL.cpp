#include <iostream>
#include <cmath>
#include <cstdio>

#ifdef _WIN32
#include <glut.h>
#define GLUT_DISABLE_ATEXIT_HACK
#define DELAY 12
#endif

#ifdef __linux
#include <GL/glut.h>
#define DELAY 1
#endif

#ifdef MACRO
#include <GL/glut.h>
#define DELAY 12
#endif
using namespace std;

//Skeleton Const
const double BASIC_SIZE = 0.25;
const double STRETCH_SCALE = 0.8;
const double JOINT_SPAN = 1.25;
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
const double ARM_SCALE_Z = 0.15;
const double FOREARM_SCALE_X = 0.65;
const double FOREARM_SCALE_Y = 0.15;
const double FOREARM_SCALE_Z = 0.15;

//Relative Const
const static double PI = acos(-1.0);
const double INCREMENT = 0.005;
const int NUM_OF_LINE = 32;
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
bool left_forward = true;
bool right_forward = false;
bool look_from_left = true;
double floor_move_x = 0.0;
double floor_move_y = 0.0;
double view_stretch = 1.0;
double near_sight = 1.0;
double far_sight = 200.0;
double lookatX = -1.06;
double lookatY = 0.5;
double lookatZ = 1.06;
double centerX = 0;
double centerY = 0;
double centerZ = 0;
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
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.3f,0.3f,0.3f);
	//Floor
    for (int i = 0;i < NUM_OF_LINE * 2;i++)
    {
        glBegin(GL_LINES);
            glVertex3f((NUM_OF_LINE - i) * BLOCK_SIZE + floor_move_x,-BASIC_SIZE * (BODY_SCALE_Y + THIGH_SCALE_X + CALF_SCALE_X + FOOT_SCALE_Z) / 2,NUM_OF_LINE * BLOCK_SIZE);
            glVertex3f((NUM_OF_LINE - i) * BLOCK_SIZE + floor_move_x,-BASIC_SIZE * (BODY_SCALE_Y + THIGH_SCALE_X + CALF_SCALE_X + FOOT_SCALE_Z) / 2,-NUM_OF_LINE * BLOCK_SIZE);
        glEnd();
        glBegin(GL_LINES);
            glVertex3f(NUM_OF_LINE * BLOCK_SIZE,-BASIC_SIZE * (BODY_SCALE_Y + THIGH_SCALE_X + CALF_SCALE_X + FOOT_SCALE_Z) / 2,(NUM_OF_LINE - i) * BLOCK_SIZE - floor_move_y);
            glVertex3f(-NUM_OF_LINE * BLOCK_SIZE,-BASIC_SIZE * (BODY_SCALE_Y + THIGH_SCALE_X + CALF_SCALE_X + FOOT_SCALE_Z) / 2,(NUM_OF_LINE - i) * BLOCK_SIZE - floor_move_y);
        glEnd();
    }
    floor_move_x += INCREMENT * cos((double)vangle / 180.0 * PI);
	floor_move_y += INCREMENT * sin((double)vangle / 180.0 * PI);
    if (floor_move_x >= BLOCK_SIZE)
      floor_move_x -= BLOCK_SIZE;
    else if (floor_move_x <= -BLOCK_SIZE)
      floor_move_x += BLOCK_SIZE;
	if (floor_move_y >= BLOCK_SIZE)
      floor_move_y -= BLOCK_SIZE;
    else if (floor_move_y <= -BLOCK_SIZE)
      floor_move_y += BLOCK_SIZE;
    glPushMatrix();
    glTranslatef(centerX,centerY,centerZ);
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
            glutSolidSphere(BASIC_SIZE * THIGH_SCALE_Y  / 2 * JOINT_SPAN,10,10);
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
        glutSolidSphere(BASIC_SIZE * THIGH_SCALE_Y / 2 * JOINT_SPAN,10,10);
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
        glutSolidSphere(BASIC_SIZE * ARM_SCALE_Y / 2 * JOINT_SPAN,10,10);
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
            glutSolidSphere(BASIC_SIZE * THIGH_SCALE_Y / 2 * JOINT_SPAN,10,10);
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
        glutSolidSphere(BASIC_SIZE * THIGH_SCALE_Y / 2 * JOINT_SPAN,10,10);
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
        glutSolidSphere(BASIC_SIZE * ARM_SCALE_Y / 2 * JOINT_SPAN,10,10);
        //Forearm
        glRotatef((GLfloat)right_forearm_angle,0.0f,0.0f,1.0f);
        glTranslatef(BASIC_SIZE * FOREARM_SCALE_X / 2,0.0f,0.0f);
        glPushMatrix();
            glScalef(FOREARM_SCALE_X,FOREARM_SCALE_Y,FOREARM_SCALE_Z);
            glutSolidCube(BASIC_SIZE);
        glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void refresh(int c)
{
    centerY = -(1 - sin(-left_thigh_angle / 180.0 * PI)) * BASIC_SIZE * THIGH_SCALE_X + BASIC_SIZE * FOOT_SCALE_Y / 2;
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
    glutTimerFunc(DELAY,refresh,0);
}

void reshape(int w,int h)
{
    scr_w = w;
    scr_h = h;
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75.0,(GLfloat)scr_w / (GLfloat)scr_h,near_sight * view_stretch,far_sight * view_stretch);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(lookatX,lookatY,lookatZ,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f);
}

void passiveMotion(int x,int y)
{
    lookatX = -1.5 + (double)x / scr_w * 3;
    lookatY = 1 - (double)y / scr_h * 2;
	if (look_from_left)
		lookatZ = sqrt(2.25 - lookatX * lookatX);
	else lookatZ = -sqrt(2.25 - lookatX * lookatX);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(lookatX * view_stretch,lookatY * view_stretch,lookatZ * view_stretch,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f);
}

void mouse(int button,int state,int x,int y)
{
	switch (button)
	{
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN)
			{
				if (near_sight * view_stretch > 0.5)
					view_stretch *= STRETCH_SCALE;
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				gluPerspective(75.0,(GLfloat)scr_w / (GLfloat)scr_h,near_sight * view_stretch,far_sight * view_stretch);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				gluLookAt(lookatX * view_stretch,lookatY * view_stretch,lookatZ * view_stretch,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f);
			}
			break;
		case GLUT_RIGHT_BUTTON:
			if (state == GLUT_DOWN)
			{
				if (far_sight * view_stretch < 1000.0)
					view_stretch /= STRETCH_SCALE;
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				gluPerspective(75.0,(GLfloat)scr_w / (GLfloat)scr_h,near_sight * view_stretch,far_sight * view_stretch);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				gluLookAt(lookatX * view_stretch,lookatY * view_stretch,lookatZ * view_stretch,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f);
			}
			break;
	}
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
        case 'w':
			vangle = -(180 - vangle) % 360;
			break;
        case 's':
            vangle = -(180 - vangle) % 360;
            break;
		case 32:
			look_from_left = !look_from_left;
			if (look_from_left)
				lookatZ = sqrt(2.25 - lookatX * lookatX);
			else lookatZ = -sqrt(2.25 - lookatX * lookatX);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(lookatX * view_stretch,lookatY * view_stretch,lookatZ * view_stretch,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f);
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
    glutCreateWindow("Simulate Human Walk");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(passiveMotion);
	glutMouseFunc(mouse);
    glutKeyboardFunc(control);
    refresh(0);
    glutMainLoop();
    return 0;
}
