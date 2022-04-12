// a and d to move right left trug
// space to /// J U M P /// yes you h eard it right, /// J U M P ///

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdbool.h>
#include <time.h>
#include "game_oop.h"
#include "game_oop.cpp"

int yaw = 0,  pitch = 90;
// movement position
float movex = 0, movez = 0; 
float x = 0., y = 1.75, z = 15.; // posisi awal kamera
float vx = 0., vy = 0., vz = 0.;
float dMove = 0, h, w;
int bitmapHeight = 12;
float mx=0, my=0;
float bruh0 = 0.1, bruh1 = 0, bruh2 = 0; // jangan pedulikan variabel ini

const GLfloat light_ambient[] = { 0.5f, 0.5f, 0.5f, 0.0f }; 
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
const GLfloat light_position[] = { 0.0f, 20.0f, 10.0f, 1.0f }; 
const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f }; 
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f }; 
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
const GLfloat high_shininess[] = { 100.0f }; 

Player player;

void timer(int millisec){
    glutTimerFunc(millisec, timer, millisec);
    glutPostRedisplay();
}

void init(){
    glClearColor(0, 0.2, 0.5, 0.8);
    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
 	glDepthFunc(GL_LESS); 
 	glEnable(GL_LIGHT0); 
 	glEnable(GL_NORMALIZE); 
 	glEnable(GL_COLOR_MATERIAL); 
 	glEnable(GL_LIGHTING); 
 	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient); 
 	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse); 
 	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular); 
 	glLightfv(GL_LIGHT0, GL_POSITION, light_position); 
 	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient); 
 	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse); 
 	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); 
 	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess); 
    timer(60);
}

void grid() {
    // Fungsi untuk membuat grid di "lantai"
    double i;
    const float Z_MIN = -50,
        Z_MAX = 50;
    const float X_MIN = -50,
        X_MAX = 50;
    const float gap = 1.5;
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINES);
    for (i = Z_MIN; i < Z_MAX; i += gap) {
        glVertex3f(i, 0, Z_MIN);
        glVertex3f(i, 0, Z_MAX);
    }
    for (i = X_MIN; i < X_MAX; i += gap) {
        glVertex3f(X_MIN, 0, i);
        glVertex3f(X_MAX, 0, i);
    }
    glEnd();
}

void orientCamera() {
    // float buff_pitch = pitch*PI/180.;
    // float buff_yaw = yaw*PI/180.;

    // vx = -sin(buff_pitch)*sin(buff_yaw);
    // vy = cos(buff_pitch);
    // vz = sin(buff_pitch)*cos(buff_yaw);

    glLoadIdentity();
    gluLookAt(0, 10, -16,
        0, 2, 3,
        0, (GLdouble)bruh0, (GLdouble)bruh1);
}

void pressKey(unsigned char key, int xn, int yn) {
    switch (key) {
        //testing purpose, jangan khawatirkan
        case 'W':
            bruh2+= .1;
        case 'w':
            bruh2+= .05;
            printf("%f", bruh2);
            break;
        case 'S':
            bruh2-= .1;
        case 's':
            bruh2-= .05;
            printf("%f", bruh2);
            break;
        // a and d to move right left trug
        case 'd':
            if(player.trugPosx>-5) player.trugPosx-=5;
            printf("%d\n", player.trugPosx);
            break;
        case 'a':
            if(player.trugPosx < 5) player.trugPosx += 5;
            printf("%d\n", player.trugPosx);
            break;
        // space to jump
        case 32:
            player.jump();
            break;
    }
}

void releaseKey(unsigned char key, int xn, int yn) {
    switch (key) {
        case 'W':
        case 'S':
        case 'w':
        case 's':
            movex= 0;
            break;
        case 'A':
        case 'D':
        case 'a':
        case 'd':
            movez= 0;
    }
}

void reshape(int w1, int h1) {
    // Fungsi reshape
    float ratio;
    if (h1 == 0) h1 = 1;
    w = w1;
    h = h1;
    ratio = w / (float)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45, ratio, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        x, y, z,
        x + vx, y + vy, z + vz,
        0., 1., 0.);
}

void display(){
    // call function to update pos and view every frame
    orientCamera();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    grid();
    // draw me a truck gandeng
    player.handleTrug();
    glutSwapBuffers();
}

int main(){
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("truk ga ndeng");
    glutIgnoreKeyRepeat(1);
    init();
    glutKeyboardFunc(pressKey);
    glutKeyboardUpFunc(releaseKey);
    glutSetCursor(GLUT_CURSOR_NONE);
    glutTimerFunc(50, timer, 50);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

