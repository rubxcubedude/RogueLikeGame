#include <string>
#include <vector>
#include <gl/freeglut.h>
using std::string;
#include "Entity.hpp"

std::vector<Entity*> vEntities;
Entity player(0.0f, 0.0f, '@', "BLACK");
Entity npc(0.5f, 0.5f, 'N', "BLACK");

void drawAllEntities(std::vector<Entity*> v)
{
	for(std::vector<Entity*>::iterator it= v.begin(); it != v.end(); ++it)
	{
		//set position to draw
		glRasterPos2d((*it)->getX(),(*it)->getY());
		//what we drawing has to be character
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, (*it)->getChar());
	}
}

void processKeyboardKeys(unsigned char key, int x, int y) {
	switch(toupper(key))
	{
		case 'A':
			player.move(-0.01, 0);
		  break;
		case 'D':
			player.move(0.01, 0);
		  break;
		case 'S':
			player.move(0, -0.01);
		  break;
		case 'W':
			player.move(0, 0.01);
		  break;			
	}
	glutPostRedisplay();
	if (key == 27)
		exit(0);
}

void processDirectionKeys(int key, int x, int y) {
	switch(key)
	{
		case GLUT_KEY_LEFT:
			player.move(-0.01, 0);
		  break;
	  case GLUT_KEY_RIGHT:
			player.move(0.01, 0);
		  break;
		case GLUT_KEY_DOWN:
			player.move(0, -0.01);
		  break;
		case GLUT_KEY_UP:
			player.move(0, 0.01);
		  break;			
	}
	glutPostRedisplay();
	if (key == 27)
		exit(0);
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawAllEntities(vEntities);

  glutSwapBuffers();
}

int main (int argc, char** argv)
{
	int screen_width = 800;
  int screen_height = 500;
	vEntities.push_back(&player);
	vEntities.push_back(&npc);
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