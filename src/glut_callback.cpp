#include <iostream>
#include <cstdlib>
#include "glut_app.h"

//
// GLUT callback functions
//

// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  PPM &p = g_app_data->getDisplayPPM();

  double max = p.getMaxColorValue();
  double r, g, b;
  int row, column;
  glBegin(GL_POINTS);
  for (row = 0; row < p.getHeight(); row++)
  {
    for (column = 0; column < p.getWidth(); column++)
    {
      r = p.getChannel(row, column, 0) / max;
      g = p.getChannel(row, column, 1) / max;
      b = p.getChannel(row, column, 2) / max;
      glColor3d(r, g, b);
      glVertex2i(column, p.getHeight() - row - 1);
    }
  }
  glEnd();

  glutSwapBuffers();
}

// This callback function gets called by the Glut
// system whenever a key is pressed.
void keyboard(unsigned char c, int x, int y)
{
  std::cout << "key: " << (int)c << std::endl;
  switch (c)
  {
  case 'q':
  case 27: // escape character means to quit the program
    exit(0);
    break;
  case 'z':
    g_app_data->zoomIn();
    break;
  case 'Z':
    g_app_data->zoomOut();
    break;
  case 'j':
    g_app_data->julia();
    break;
  case 'm':
    g_app_data->mandelbrot();
    break;
  case 'J':
    g_app_data->setMode(g_app_data->MODE_JULIA_PARAMETERS);
    break;
  case 'w':
    g_app_data->writePPMFile();
    break;
  case 'a':
    g_app_data->toggleAntiAlias();
    break;
  case '0':
    g_app_data->setColorTable(0);
    break;
  case '1':
    g_app_data->setColorTable(1);
    break;
  case '2':
    g_app_data->setColorTable(2);
    break;
  case '3':
    g_app_data->setColorTable(3);
    break;
  default:
    return; // if we don't care, return without glutPostRedisplay()
  }

  glutPostRedisplay(); // tell glut to call display() as soon as possible.
}

void special(int c, int x, int y)
{
  std::cout << "special key: " << (int)c << std::endl;
  switch (c)
  {
  case GLUT_KEY_UP:
    // g_ry += 10;
    break;
  case GLUT_KEY_DOWN:
    // g_ry -= 10;
    break;
  case GLUT_KEY_LEFT:
    // g_rx -= 10;
    break;
  case GLUT_KEY_RIGHT:
    // g_rx += 10;
    break;
  default:
    return; // if we don't care, return without glutPostRedisplay()
  }
  glutPostRedisplay(); // tell glut to call display() as soon as possible.
}

// This callback function gets called by the Glut
// system whenever the window is resized by the user.
void reshape(int w, int h)
{
  // Reset our global variables to the new width and height.
  g_app_data->setSize(h, w);

  // Set the pixel resolution of the final picture (Screen coordinates).
  glViewport(0, 0, w, h);

  // Set the projection mode to 2D orthographic, and set the world coordinates:
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, w, 0, h);
  glMatrixMode(GL_MODELVIEW);
}

// This callback function gets called by the Glut
// system whenever any mouse button goes up or down.
void mouse(int mouse_button, int state, int x, int y)
{
  // translate pixel coordinates to display coordinates
  int xdisplay = x;
  int ydisplay = g_app_data->getHeight() - y;
  if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    std::cout << "Left Mouse Down. @" << xdisplay << "," << ydisplay << std::endl;
    g_app_data->getMode() == g_app_data->MODE_JULIA_PARAMETERS ? g_app_data->setJuliaParameters(x, y) : g_app_data->setCenter(x, y);
  }
  if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP)
  {
    std::cout << "Left Mouse Up. @" << xdisplay << "," << ydisplay << std::endl;
  }
  if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
  {
    std::cout << "Middle Mouse Down. @" << xdisplay << "," << ydisplay << std::endl;
  }
  if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_UP)
  {
    std::cout << "Middle Mouse Up. @" << xdisplay << "," << ydisplay << std::endl;
  }
  glutPostRedisplay();
}
