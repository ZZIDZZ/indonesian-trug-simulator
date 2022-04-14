#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "game_oop.h"

bool GAME = true;
float WORLD_SPEED = 0.2;
float gravity = 7;

// float OBSTACLE_RENDER_DISTANCE = 
void drawMeAWheel(float radius, float height){
    GLfloat x              = 0.0;
    GLfloat y              = 0.0;
    GLfloat angle          = 0.0;
    GLfloat angle_stepsize = 0.1;

    /** Draw the tube */
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
        while( angle < 2*PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , height);
            glVertex3f(x, y , 0.0);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, height);
        glVertex3f(radius, 0.0, 0.0);
    glEnd();

    /** Draw the circle on top of cylinder */
    glBegin(GL_POLYGON);
    angle = 0.0;
        while( angle < 2*PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , height);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, height);
    glEnd();

    /** Draw the circle on top of cylinder */
    glBegin(GL_POLYGON);
    angle = 0.0;
        while( angle < 2*PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , 0);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, height);
    glEnd();
}

void drawMeABox(float w=1, float h=1, float l=1){
    //sisi kanan kiri
	glPushMatrix(); 
	 	glTranslatef(0,h+1,0); 
	 	glBegin(GL_QUADS); 
	 	glVertex3f(w,h,l); 
		glVertex3f(w,-h,l);
	 	glVertex3f(w,-h,-l);
	 	glVertex3f(w,h,-l);
	 	glEnd(); 
 	glPopMatrix();
 	
 	glPushMatrix(); 
        glTranslatef(0,h+1,0); 
	 	glBegin(GL_QUADS); 
	 	glVertex3f(-w,h,l); 
		glVertex3f(-w,-h,l);
	 	glVertex3f(-w,-h,-l);
	 	glVertex3f(-w,h,-l);
	 	glEnd(); 
 	glPopMatrix();
 	
 	//sisi depan belakang
 	glPushMatrix(); 
	 	glTranslatef(0,h+1,0); 
	 	glBegin(GL_QUADS); 
	 	glVertex3f(w,h,l); 
		glVertex3f(w,-h,l);
	 	glVertex3f(-w,-h,l);
	 	glVertex3f(-w,h,l);
	 	glEnd(); 
 	glPopMatrix();
 	
 	glPushMatrix(); 
	 	glTranslatef(0,h+1,0); 
	 	glBegin(GL_QUADS); 
	 	glVertex3f(w,h,-l); 
		glVertex3f(w,-h,-l);
	 	glVertex3f(-w,-h,-l);
	 	glVertex3f(-w,h,-l);
	 	glEnd(); 
 	glPopMatrix();
 	
 	glPushMatrix(); 
	 	glTranslatef(0,h+1,0); 
	 	glBegin(GL_QUADS); 
	 	glVertex3f(-w,h,l); 
		glVertex3f(-w,h,-l);
	 	glVertex3f(w,h,-l);
	 	glVertex3f(w,h,l);
	 	glEnd(); 
 	glPopMatrix();
 	
 	glPushMatrix(); 
	 	glTranslatef(0,h+1,0); 
	 	glBegin(GL_QUADS); 
	 	glVertex3f(-w,-h,l); 
		glVertex3f(-w,-h,-l);
	 	glVertex3f(w,-h,-l);
	 	glVertex3f(w,-h,l);
	 	glEnd(); 
 	glPopMatrix();
}


class Player{
    public:
        float trugPosx = 0, trugPosY = 0;
        float jumpSpeed = 2;
        float jumpSpeedBuffer = 0;
        float airTime = 0;
        bool onAir = false;
        void drawMeATruckGandeng(){
            //head
            glPushMatrix();
                glColor3f(0.7,0.1,0.8); drawMeABox(.8,.5,.2);
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.2,0.8,0.5); glTranslatef(0,0,-.8); drawMeABox(.8,.8,.6);
            glPopMatrix();

            // lamp
            glPushMatrix(); 
                glColor3f(1,1,1); glTranslatef(.5,.3,.2); drawMeABox(.1,.1,.05);
            glPopMatrix();

            glPushMatrix();
                glColor3f(1,1,1); glTranslatef(-.5,.3,.2); drawMeABox(.1,.1,.05);
            glPopMatrix();

            //hook 1
            glPushMatrix();
                glColor3f(.8,.3,.9); glTranslatef(0,.3,-1.5); drawMeABox(.1,.1,.3);
            glPopMatrix();

            //container 1
            glPushMatrix();
                glColor3f(0.2,0.8,0.5); glTranslatef(0,0,-2.8); drawMeABox(.8,.8,1);
            glPopMatrix();

            //hook 2
            glPushMatrix();
                glColor3f(.8,.3,.9); glTranslatef(0,.3,-4.0); drawMeABox(.1,.1,.3);
            glPopMatrix();

            //container 2
            glPushMatrix();
                glColor3f(0.2,0.8,0.5); glTranslatef(0,0,-5.2); drawMeABox(.8,.8,1);
            glPopMatrix();

            //roda depan
            glPushMatrix();
                glColor3f(0.2,0.1,0.3); glTranslatef(.6,1,-.6); glRotatef(90, 0,1,0); drawMeAWheel(.3,.3);
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.2,0.1,0.3); glTranslatef(-.9,1,-.6); glRotatef(90, 0,1,0); drawMeAWheel(.3,.3);
            glPopMatrix();

            //roda tengah
            glPushMatrix();
                glColor3f(0.2,0.1,0.3); glTranslatef(.6,1,-3.4); glRotatef(90, 0,1,0); drawMeAWheel(.3,.3);
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.2,0.1,0.3); glTranslatef(-.9,1,-3.4); glRotatef(90, 0,1,0); drawMeAWheel(.3,.3);
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.2,0.1,0.3); glTranslatef(.6,1,-2.2); glRotatef(90, 0,1,0); drawMeAWheel(.3,.3);
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.2,0.1,0.3); glTranslatef(-.9,1,-2.2); glRotatef(90, 0,1,0); drawMeAWheel(.3,.3);
            glPopMatrix();

            // roda belakang
            glPushMatrix();
                glColor3f(0.2,0.1,0.3); glTranslatef(.6,1,-5.8); glRotatef(90, 0,1,0); drawMeAWheel(.3,.3);
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.2,0.1,0.3); glTranslatef(-.9,1,-5.8); glRotatef(90, 0,1,0); drawMeAWheel(.3,.3);
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.2,0.1,0.3); glTranslatef(.6,1,-4.6); glRotatef(90, 0,1,0); drawMeAWheel(.3,.3);
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.2,0.1,0.3); glTranslatef(-.9,1,-4.6); glRotatef(90, 0,1,0); drawMeAWheel(.3,.3);
            glPopMatrix();
        }
        void handleTrug(){
            // jump logic memakai konsep percepatan gravitasi
            if(onAir){
                airTime += 0.04;
                trugPosY += jumpSpeedBuffer;
                if(jumpSpeed > (-jumpSpeedBuffer) && trugPosY > 0){
                    jumpSpeedBuffer = jumpSpeed - (gravity*airTime);
                } 
                else if(trugPosY <= 0) {
                    onAir = false; 
                    trugPosY = 0;
                }
                printf("trugPosY: %f\n", trugPosY);
                printf("jumpSpeedBuffer: %f\n", jumpSpeedBuffer);
                printf("airTime: %f\n", airTime);
                printf(onAir ? "onAir\n" : "notOnAir\n");
            }
            glPushMatrix();
                glTranslatef((GLfloat)trugPosx, trugPosY,0.0);
                drawMeATruckGandeng();
            glPopMatrix();
        }
        void jump(){
            if(!onAir){
                airTime = 0;
                onAir = true;
                jumpSpeedBuffer = jumpSpeed;
            }
        }
};

class Obstacle{
    public:
        Obstacle(){
            obsX = -5 + (rand() % 3) * 5;
            WORLD_SPEED += 0.01;
            R = 0.1 * (rand() % 10);
            G = 0.1 * (rand() % 10);
            B = 0.1 * (rand() % 10);
        }
        float obsX, obsY = 0, obsZ = 30;
        float R,G,B;
        void update(){
            obsZ -= WORLD_SPEED;
            printf("%f\n", obsZ);
        }
        void draw(){
            glPushMatrix();
                glColor3f(R,G,B);
                glTranslatef(obsX,obsY,obsZ);
                drawMeABox();
            glPopMatrix();
        }
        
};