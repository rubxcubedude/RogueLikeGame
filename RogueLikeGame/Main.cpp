#include <string>
#include <vector>
#include <gl/freeglut.h>
using std::string;

#include "Game.hpp"
#include "ColorConstants.hpp"

Game g;

void processKeyboardKeys(unsigned char key, int x, int y) {
  g.processKeyboardKeys(key, x, y);
}

void processDirectionKeys(int key, int x, int y) {
  g.processDirectionKeys(key,x,y);
}

void renderScene()
{
  g.update();
}

int main (int argc, char** argv)
{
  int screen_width = 800;
  int screen_height = 500;
  g.addNpc(25,25,'N', YELLOWF);
  glutInit(&argc, argv); // Start glut library, pass any extra command line commands to glut.
  glutInitWindowPosition(0,0);
  glutInitWindowSize(screen_width, screen_height);
  glutCreateWindow ("OpenGL window");
  // set up the OpenGL projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, (double)screen_width-1.0, 0.0, (double)screen_height-1.0, 0.0, 1.0);
  glViewport(0, 0, screen_width/100.0, screen_height/100.0);
  glShadeModel(GL_FLAT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  // register callbacks
  glutDisplayFunc(renderScene);
  
  //handle input from keyboard
  glutKeyboardFunc(processKeyboardKeys);
  glutSpecialFunc(processDirectionKeys);
  // enter GLUT event processing cycle
  glutMainLoop();
  return(0);
}