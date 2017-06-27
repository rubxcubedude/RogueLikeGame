#include <string>
#include <gl/freeglut.h>

using std::string;

float player_x=0.0f;
float player_y=0.0f;

void processKeyboardKeys(unsigned char key, int x, int y) {
	switch(toupper(key))
	{
		case 'A':
			player_x -=0.01;;
		  break;
		case 'D':
			player_x +=0.01;
		  break;
		case 'S':
			player_y -=0.01;
		  break;
		case 'W':
			player_y +=0.01;
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
			player_x -=0.01;
		  break;
	  case GLUT_KEY_RIGHT:
			player_x +=0.01;
		  break;
		case GLUT_KEY_DOWN:
			player_y -=0.01;
		  break;
		case GLUT_KEY_UP:
			player_y +=0.01;
		  break;			
	}
	glutPostRedisplay();
	if (key == 27)
		exit(0);
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//set position to draw
	glRasterPos2d(player_x, player_y);
	//what we drawing has to be character
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, '@');

  glutSwapBuffers();
}

int main (int argc, char** argv)
{
	int screen_width = 800;
  int screen_height = 500;
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