#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "game_oop.h"

bool GAME = true;
float WORLD_SPEED = 0.2;
float gravity = 7;

// float OBSTACLE_RENDER_DISTANCE = 
void renderCube(float w = 1, float l = 1, float h = 1) {
    float zVerts[4][3] = {
        {w, h, 0},
        {-w, h, 0},
        {-w, -h, 0},
        {w, -h, 0}
    };
    float xVerts[4][3] = {
        {l, h, 0},
        {-l, h, 0},
        {-l, -h, 0},
        {l, -h, 0}
    };
    float yVerts[4][3] = {
        {w, l, 0},
        {-w, l, 0},
        {-w, -l, 0},
        {w, -l, 0}
    };
    float zRot[6] = {0, -90, -180, 90, -90, 90};
    float zRotAxis[6][3] = {
        {0, 0, 0},
        {1, 0, 0},
        {1, 0, 0},
        {1, 0, 0},
        {0, 1, 0},
        {0, 1, 0}
    };
    glPushMatrix();
        glTranslatef(0, h, 0);
        for (int i = 0; i < 2; i++) {
            glPushMatrix();
                glRotatef(180-(i*180), 1, 0, 0);
                glTranslatef(0, 0, l);
                glBegin(GL_QUADS);
                glNormal3f(0, 0, 1);
                    for (auto v: zVerts) glVertex3fv(v);
                glEnd();
            glPopMatrix();
        };
        for (int i = -1; i < 2; i += 2) {
            glPushMatrix();
                glRotatef(i*90, 0, 1., 0.);
                glTranslatef(0, 0, w);
                glBegin(GL_QUADS);
                    for (auto v: xVerts) glVertex3fv(v);
                glEnd();
            glPopMatrix();
        }
        for (int i = -1; i < 2; i += 2) {
            glPushMatrix();
                glRotatef(i*90, 1, 0, 0.);
                glTranslatef(0, 0, h);
                glBegin(GL_QUADS);
                    for (auto v: yVerts) glVertex3fv(v);
                glEnd();
            glPopMatrix();
        }
    glPopMatrix();
}

void renderCylinder(float radius, float height) {
    float 
        x = 0.0,
        y = 0.0,
        angle = 0.0,
        angle_stepsize = 0.1;
    glPushMatrix();
        glTranslatef(-height/2, radius, 0);
        glRotatef(90, 0, 1, 0);
        glBegin(GL_QUAD_STRIP);
            angle = 0.0;
            while(angle < 2*PI) {
                x = radius * cos(angle);
                y = radius * sin(angle);
                glVertex3f(x, y , height);
                glVertex3f(x, y , 0.0);
                glNormal3f(cos(angle), sin(angle), 0);
                angle = angle + angle_stepsize;
            }
            glVertex3f(radius, 0.0, height);
            glVertex3f(radius, 0.0, 0.0);
        glEnd();

        glPushMatrix();
            glBegin(GL_POLYGON);
            angle = 0.0;
                while( angle < 2*PI ) {
                    x = radius * cos(angle);
                    y = radius * sin(angle);
                    glNormal3f(0, 0, 1);
                    glVertex3f(x, y , height);
                    angle = angle + angle_stepsize;
                }
                glNormal3f(0, 0, 1);
                glVertex3f(radius, 0.0, height);
            glEnd();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0, 0, -height);
            glBegin(GL_POLYGON);
            angle = 0.0;
                while (angle < 2*PI) {
                    x = radius * cos(angle);
                    y = radius * sin(angle);
                    glNormal3f(0, 0, -1);
                    glVertex3f(x, y , height);
                    angle = angle + angle_stepsize;
                }
                glNormal3f(0, 0, -1);
                glVertex3f(radius, 0.0, height);
            glEnd();
        glPopMatrix();
    glPopMatrix();
}

void renderAddContainer() {
    //2nd part
    glPushMatrix();
        //wheel back
        for (int i = -1; i <= 1; i += 2) {
            glPushMatrix();
                glTranslatef(0,0, -20);
                glTranslatef(i*2, 0, 0);
                glPushMatrix();
                    glColor3ub(16, 16, 16);
                    glTranslatef(0, 0, 8);
                    renderCylinder(1, 0.5);
                    glTranslatef(0, 0, 5);
                    glTranslatef(0, 0, (-6.25*2)-1);
                    renderCylinder(1, 0.5);
                    glTranslatef(0, 0, 2.2);
                    renderCylinder(1, 0.5);
                glPopMatrix();
            glPopMatrix();
        }

        //wheel deco back
        for (int i = -1; i <= 1; i += 2) {
            glPushMatrix();
                glTranslatef(0, 0.5, 0);
                glTranslatef(0,0, -20);
                glTranslatef(i*2, 0, 0);
                glPushMatrix();
                    glColor3ub(255, 255, 255);
                    glTranslatef(0, 0, 8);
                    renderCylinder(0.5, 0.6);
                    glTranslatef(0, 0, 5);
                    glTranslatef(0, 0, (-6.25*2)-1);
                    renderCylinder(0.5, 0.6);
                    glTranslatef(0, 0, 2.2);
                    renderCylinder(0.5, 0.6);
                glPopMatrix();
            glPopMatrix();
        }

        glTranslatef(0, 1, -16.35);
        glPushMatrix();
            glColor3ub(16, 16, 16);
            renderCube(2.15, 6.35, 0.1);

            glTranslatef(0, 0.2, 0);
            renderCube(2, 6.25, 0.1);
            glTranslatef(0, 0, -6.25);
        glPopMatrix();
        
        //connector
        glPushMatrix();
            glColor3ub(255, 255, 255);
            glTranslatef(0, 0, 6.75);
            renderCube(0.2, 0.4, 0.1);
        glPopMatrix();

        //container 2
        glPushMatrix();
            glColor3ub(225, 25, 25);
            glTranslatef(0, 0.4, 0);
            renderCube(1.8, 6, 2.5);
        glPopMatrix();
    glPopMatrix();
}

void renderTruckDeco() {

    //wheel deco front
    for (int i = -1; i <= 1; i += 2) {
        glPushMatrix();
            glTranslatef(0, 0.5, 0);
            glTranslatef(i*2, 0, 0);
            glPushMatrix();
                glColor3ub(255, 255, 255);
                glTranslatef(0, 0, 6.45);
                renderCylinder(0.5, 0.6);
                glTranslatef(0, 0, (-6.25*2)-1);
                renderCylinder(0.5, 0.6);
                glTranslatef(0, 0, 2.2);
                renderCylinder(0.5, 0.6);
            glPopMatrix();
        glPopMatrix();
    }

    //side panel
    for (int i = -1; i <= 1; i += 2) {
        //side panel 1
        glPushMatrix();
            glColor3ub(172, 172, 172);
            glTranslatef(i*2, 3.65, 5.15);
            renderCube(0.01, 0.2, 0.4);
        glPopMatrix();

        //side panel 2
        glPushMatrix();
            glColor3ub(172, 172, 172);
            glTranslatef(i*2, 3.65, 4.3);
            renderCube(0.01, 0.55, 0.6);
        glPopMatrix();
        
        //side door
        glPushMatrix();
            glColor3ub(114, 26, 24);
            glTranslatef(i*2, 1.5, 4.55);
            renderCube(0.01, 0.8, 1);
        glPopMatrix();

        // door handle
        glPushMatrix();
            glColor3ub(0, 0, 0);
            glTranslatef(i*2, 2.7, 4.1);
            renderCube(0.05, 0.2, 0.05);
        glPopMatrix();

        // door handle frame
        glPushMatrix();
            glColor3ub(128, 128, 128);
            glTranslatef(i*2, 2.65, 4.1);
            renderCube(0.02, 0.15, 0.1);
        glPopMatrix();
    }

    //front panel
    glPushMatrix();
        glColor3ub(172, 172, 172);
        glTranslatef(0, 3.7, 5.5);
        renderCube(1.8, 0.01, 0.6);
    glPopMatrix();

    //vent
    for (float i = 0; i <= 0.5; i += 0.1) {
        glPushMatrix();
            glColor3ub(0, 0, 0);
            glTranslatef(0, 1.5+(2*i), 9.1);
            renderCube(0.6+(i/2), 0.01, 0.05);
        glPopMatrix();
    }

    //headlamp
    for (int i = -1; i <= 1; i += 2) {
        glPushMatrix();
            glColor3ub(255, 255, 0);
            glTranslatef(i*1.4, 1.5, 9.1);
            renderCube(0.4, 0.01, 0.2);
        glPopMatrix();
    }
}



class Player{
    public:
        float trugPosx = 0, trugPosY = 0;
        float jumpSpeed = 2;
        float jumpSpeedBuffer = 0;
        float airTime = 0;
        bool onAir = false;
        void renderTruck() {
            //wheel front
            for (int i = -1; i <= 1; i += 2) {
                glPushMatrix();
                    glTranslatef(i*2, 0, 0);
                    glPushMatrix();
                        glColor3ub(16, 16, 16);
                        glTranslatef(0, 0, 6.45);
                        renderCylinder(1, 0.5);
                        glTranslatef(0, 0, (-6.25*2)-1);
                        renderCylinder(1, 0.5);
                        glTranslatef(0, 0, 2.2);
                        renderCylinder(1, 0.5);
                    glPopMatrix();
                glPopMatrix();
            }

            //truck and 1st container
            glPushMatrix();
                glTranslatef(0, 1, 0);
                glPushMatrix();
                    glColor3ub(16, 16, 16);
                    renderCube(2.15, 9.2, 0.1);
                    glTranslatef(0, 0.0, -9.1);

                    glTranslatef(0, 0.2, 6.25);
                    renderCube(2, 6.25, 0.1);
                    glTranslatef(0, 0, -6.25);

                    glPushMatrix();
                        glTranslatef(0, 0.2, 0);
                        //container1
                        glPushMatrix();
                            glColor3ub(225, 25, 25);
                            glTranslatef(0, 0, 6.35);
                            renderCube(1.8, 6, 2.5);
                            glTranslatef(0, 0, 3);
                            glTranslatef(0, 0, 0.2);
                        glPopMatrix();

                        //separator
                        glPushMatrix();
                            glColor3ub(16, 16, 16);
                            glTranslatef(0.0, 0.0, 12.45);
                            renderCube(2.0, 0.05, 2.4);
                            glTranslatef(0.0, 0.0, 0.05);
                        glPopMatrix();
                    glPopMatrix();

                    glPushMatrix();
                        glTranslatef(0, 0, 6.25*2+0.1);
                        //truckhead
                        glColor3ub(255, 59, 1);
                        glTranslatef(0.0, 0.0, 1.0);
                        renderCube(2.0, 1.0, 2.0);
                        glTranslatef(0.0, 0.0, 1.0);

                        //trucknose
                        glTranslatef(0, 0.0, 1.8);
                        renderCube(2.0, 1.8, 1.2);
                    glPopMatrix();
                glPopMatrix();
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
                renderTruck();
                renderTruckDeco();
                glTranslatef(0, 0, 13.5);
                for (int i = 0; i < 5; i++) {
                    glTranslatef(0, 0, -13.5);
                    renderAddContainer();
                }
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
        float obsX, obsY = 0, obsZ = 50;
        float R,G,B;
        void update(){
            obsZ -= WORLD_SPEED;
            printf("%f\n", obsZ);
        }
        void draw(){
            glPushMatrix();
                glColor3f(R,G,B);
                glTranslatef(obsX,obsY,obsZ);
                renderCube();
            glPopMatrix();
        }
};
        
class Gedung{
    public:
        Gedung(){
            obsX = -10 + (rand() % 2) * 20;
            WORLD_SPEED += 0.01;
        }
        float obsX, obsY = 0, obsZ = 30;
        void update(){
            obsZ -= WORLD_SPEED;
            printf("%f\n", obsZ);
        }
        void draw(){
            // TODO: gambar gedung disini
        }
};
