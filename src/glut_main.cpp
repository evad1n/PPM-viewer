#include "glut_app.h"

int main(int argc, char **argv)
{
  initialize_app(500, 700);

  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(g_app_data->getHeight(), g_app_data->getWidth());
  glutInitWindowPosition(50, 50);

  int fullscreen = 0;
  if (fullscreen)
  {
    glutGameModeString("800x600:32");
    glutEnterGameMode();
  }
  else
  {
    glutCreateWindow("This appears in the title bar");
  }

  // register event handlers
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);

  glColor3d(0, 0, 0);       // forground color
  glClearColor(1, 1, 1, 0); // background color

  glutMainLoop();

  return 0;
}
