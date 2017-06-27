#include <string>
#include <vector>
#include <gl/freeglut.h>
using std::string;

#include "Game.hpp"

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
  g.addNpc(0.5,0.5,'N', "BLACK");
  glutInit(&argc, argv); // Start glut library, pass any extra command line commands to glut.
  glutInitWindowPosition(0,0);
  glutInitWindowSize(screen_width, screen_height);
  glutCreateWindow ("OpenGL window");
  // register callbacks
  glutDisplayFunc(renderScene);
  
  //handle input from keyboard
  glutKeyboardFunc(processKeyboardKeys);
  glutSpecialFunc(processDirectionKeys);
  // enter GLUT event processing cycle
  glutMainLoop();
  return(0);
}