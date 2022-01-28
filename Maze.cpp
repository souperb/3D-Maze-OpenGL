/*
* Name: Ethan Campbell
* ID: 190057
* Class: CMPT315
* Assignment: Assignment 2
* Date: November 4, 2021
*/


#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
#include <windows.h>
#define M_PI 3.14159265358979323846
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <cmath>
#include<iostream>
using namespace std;


double angle = 0; // The angle of rotation for the cubes

// The user's position and viewing angle
double myx = -7.5;
double myz = -21.5;
double userAngle = 0;

bool opaque = true; // Determines whether to use GL_FILL or GL_LINE
bool projectileBool = false; // Determines if a box has been fired

// The projectiles Y and Z values
double projectileY = 0;
double projectileZ = 0;

double dY = 0; // The projectiles y direction for bouncing

bool collisonBool = true; // Toggles wall collision

int greenCubes = 0; // Counts the number of cubes that have been hit
bool greenWalls = false; // Turns all of the walls green

// Represents the maze. 'w' is a wall, 'r' is a red cube, 'g' is a green cube, and 'e' is an empty space
char maze[20][20] = {{'w', 'w', 'w', 'w', 'w', 'w', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'w', 'w', 'w', 'w', 'w', 'w'},
                     {'w', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'r', 'e', 'w', 'w', 'e', 'e', 'e', 'w'},
                     {'w', 'e', 'e', 'e', 'e', 'r', 'e', 'e', 'e', 'w', 'w', 'e', 'e', 'e', 'w', 'w', 'e', 'e', 'e', 'w'},
                     {'w', 'w', 'w', 'w', 'e', 'e', 'e', 'e', 'e', 'w', 'w', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'w'},
                     {'w', 'e', 'e', 'w', 'w', 'e', 'e', 'e', 'e', 'w', 'w', 'w', 'w', 'e', 'e', 'e', 'e', 'r', 'e', 'w'},
                     {'w', 'e', 'e', 'w', 'w', 'w', 'w', 'e', 'e', 'w', 'e', 'e', 'e', 'e', 'e', 'w', 'e', 'e', 'e', 'w'},
                     {'w', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'w', 'e', 'e', 'w', 'e', 'w', 'w', 'e', 'e', 'e', 'w'},
                     {'w', 'w', 'w', 'e', 'w', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'w', 'w', 'e', 'e', 'e', 'w'},
                     {'w', 'e', 'e', 'e', 'e', 'e', 'e', 'w', 'e', 'e', 'w', 'w', 'e', 'e', 'e', 'w', 'w', 'e', 'e', 'w'},
                     {'w', 'e', 'e', 'w', 'e', 'e', 'e', 'w', 'e', 'e', 'e', 'e', 'e', 'e', 'w', 'w', 'e', 'e', 'w', 'w'},
                     {'w', 'e', 'e', 'w', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'w', 'e', 'e', 'e', 'e', 'w'},
                     {'w', 'e', 'w', 'w', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'r', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'w'},
                     {'w', 'e', 'w', 'e', 'e', 'w', 'w', 'e', 'w', 'e', 'e', 'e', 'e', 'e', 'w', 'w', 'e', 'w', 'w', 'w'},
                     {'w', 'e', 'e', 'e', 'e', 'e', 'w', 'w', 'w', 'w', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'w', 'w', 'w'},
                     {'w', 'e', 'e', 'e', 'w', 'e', 'e', 'e', 'e', 'w', 'e', 'w', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'w'},
                     {'w', 'w', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'w', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'w'},
                     {'w', 'w', 'e', 'e', 'e', 'e', 'e', 'r', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'w', 'w', 'e', 'w'},
                     {'w', 'w', 'e', 'e', 'w', 'w', 'e', 'e', 'e', 'w', 'w', 'e', 'e', 'w', 'w', 'e', 'e', 'w', 'e', 'w'},
                     {'w', 'w', 'e', 'e', 'w', 'w', 'w', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'w', 'e', 'e', 'w', 'e', 'w'},
                     {'w', 'w', 'w', 'w', 'w', 'w', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'w', 'w', 'w', 'w', 'w', 'w'}};


void display(void) {
  if (opaque) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Determines whether to draw the world in outline view
  else glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  glClearColor (0.0, 0.0, 0.0, 0.0f); // Background colour
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the background

  // Define the world
  glMatrixMode(GL_MODELVIEW);

  // Draw the maze
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 20; j++) {

      // Translates to the users current position, builds according to the position in maze[],
      // and then rotates to match the user's current viewing angle
      glLoadIdentity();
      glRotatef(userAngle*180, 0, 1, 0);
      glTranslatef(myx, 0, myz);
      glTranslatef(i, 0, j);

      // Draw a yellow or wall
      if (maze[j][i] == 'w') {
        if (greenWalls)
          glColor3f(0.0, 1.0, 0.3);
        else
        glColor3f(0.4, 0.3, 0.0);
        glutSolidCube(1.0);

      // Draw a red spinning cube
      } else if (maze[j][i] == 'r') {
        glColor3f(1.0, 0.0, 0.0);
        glRotatef(angle, 0, 1, 0); // Roate the cube
        glutSolidCube(0.5); // Draw the cube

      // Draw a green spinning cube
      } else if (maze[j][i] == 'g') {
        glColor3f(0.0, 1.0, 0.0);
        glRotatef(angle, 0, 1, 0); // Roate the cube
        glutSolidCube(0.5); // Draw the cube
      }
    }
  }

  // Draws a blue spinning, bouncing cube that moves away from the user
  if (projectileBool) {
    glLoadIdentity();
    glTranslatef(0, projectileY, -projectileZ-3);
    glColor3f(0.0, 0.0, 1.0);
    glRotatef(angle*40, 1, 1, 1);
    glutSolidCube(0.25);
  }


  glFlush();
  glutSwapBuffers();
}

// Enables the necessary parameters to allows for lighting and perspective
void init(void) {
  glEnable(GL_DEPTH_TEST);

  glClearColor (0.0, 0.0, 0.0, 0.0f);
  glEnable(GL_COLOR_MATERIAL);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(45.5, 1.0, 1.0, 1000);
}


// Creates the light sources
void light(void) {
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  GLfloat lightPosition[] = {-0.5, 0.0, 5.0, 1.0};
  GLfloat ambientLight[] = {0.3, 0.3, 0.3, 1};
  GLfloat diffuseLight[] = {0.7, 0.7, 0.7, 1.0};
  GLfloat specularLight[] = {0.5, 0.5, 0.5, 1.0};

  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
}


// Determines if moving a user/projectile forward would result in collsion
bool collison(double x, double z) {
  if (!collisonBool)
    return false;
  else if (-abs(z) <= 0 && -abs(z) > -20 && -abs(x) <= 0 && -abs(x) > -20 && maze[int(round((-1*z)))][int(round(x*-1))] == 'w')
    return true;
  else
    return false;
}

// Determines if a firing cube hits a red cube or a wall
bool projectileCollision(double x, double z) {
  // If a cube is hit turn it green and return true
  if (-abs(z) <= 0 && -abs(z) > -20 && -abs(x) <= 0 && -abs(x) > -20 && maze[int(round((-1*z)))][int(round(x*-1))] == 'r') {
    maze[int(round((-1*z)))][int(round(x*-1))] = 'g';
    greenCubes++;

    // If all cubes have been hit, turn them red and the walls green
    if (greenCubes % 5 == 0) {
      for (int i = 0; i < 20; i++) {
        for(int j = 0; j< 20; j++) {
          if (maze[i][j] == 'g') maze[i][j] = 'r';
        }
      }
      greenWalls = true;
    }

    return true;

  // If a wall is hit return true
  } else if (-abs(z) <= 0 && -abs(z) > -20 && -abs(x) <= 0 && -abs(x) > -20 && maze[int(round((-1*z)))][int(round(x*-1))] == 'w')
    return true;
  else
    return false;
}


// Registers spacebar, 'w', and 'o' presses
void keyboardF(unsigned char key, int x, int y) {

  // If the user presses space then projectileBool is set true and the proectile will be drawn
  // This prevents multiple projectiles from being drawn at once
  if (key == ' ') {
    if (projectileBool == false)
      projectileBool = true;

  // If the user presses 'o' then the walls will be toggled between fill and line
  } else if (key == 'o') {
    if (opaque)
      opaque = false;
    else
      opaque = true;

  // If the user presses 'w' then wall collision is toggled on and off
  } else if (key == 'w') {
    if (collisonBool)
      collisonBool = false;
    else
      collisonBool = true;
  }
}



// Gets the direction the user press
void specialF(int key, int x, int y) {

  // Right and left presses rotates the angle the viewer is facing
  if (key == GLUT_KEY_RIGHT) {
    userAngle += 0.01;
    if (userAngle == 2.0) userAngle = 0;
    //cout << "userAngle: " << userAngle  << endl;
  } else if (key == GLUT_KEY_LEFT) {
    userAngle -= 0.01;
    if (userAngle < 0) userAngle = 1.999;
    //cout << "userAngle: " << userAngle << endl;

  // Up and down presses moves the user forwards or backwards in the direction they are facing
} else if (key == GLUT_KEY_DOWN && !collison(myx + sin(userAngle*M_PI), myz - cos(userAngle*M_PI))) {
    myx += sin(userAngle*M_PI)/5;
    myz -= cos(userAngle*M_PI)/5;
  } else if (key == GLUT_KEY_UP && !collison(myx - sin(userAngle*M_PI), myz + cos(userAngle*M_PI))) {
    myx -= sin(userAngle*M_PI)/5;
    myz += cos(userAngle*M_PI)/5;
  }
}



// Timer that determines what angle the cube is rotated at
// and moves the projectile forwards/up and down
void timer(int unused) {
  angle += 1; // Increases the angle of the cube's rotation
  if (angle == 360) angle = 0; // Reset the angle to 0 once it goes all the way around

  // If there is a projectile drawn, then it's z and y values are incremented
  // If the projectile collides with something, then it is removed
  if (projectileBool) {
    if (projectileCollision(myx - projectileZ*sin(userAngle*M_PI), myz + projectileZ*cos(userAngle*M_PI)) || projectileCollision(myx, myz + projectileZ)) {
      projectileBool = false;
    } else {
        projectileZ += 0.1; // Increase the z value of the projectile

      // If the projectile is at 0 then it moves down
      // If it is at -0.5, it starts to move back up
      if (projectileY >= 0) {
        dY = -0.05;
      } else if (projectileY <= -0.5) {
        dY = 0.05;
      }
      projectileY += dY; // Increment the y value appropriately

      // Once the projectile gets 5 units away from the user it disappears
      // The projectileBool is set back to false and it's coordinates are set back to 0
      if (projectileZ > 5.0) {
        projectileBool = false;
        projectileZ = 0;
        projectileY = 0;
      }
    }
  }

  glutTimerFunc(10, timer, 42);  // Recall the timer
  glutPostRedisplay(); // Redraw the screen
}

int main(int argc, char** argv) {
  // First set up GLUT
  glutInit( &argc, argv );
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  // Make the window
  int windowHandle = glutCreateWindow("Maze");
  glutSetWindow(windowHandle);

  // Place and size the window
  glutPositionWindow ( 100, 100 );
  glutReshapeWindow( 1000, 1000 );


  glutDisplayFunc(display); // Draw the display
  glutSpecialFunc(specialF); // Initialize the keyboard functions
  glutKeyboardFunc(keyboardF);
  init(); // Initialize the lighting
  light();

  glutTimerFunc(10, timer, 42);
  glutMainLoop();
  return 0;
}
