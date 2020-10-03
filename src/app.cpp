#include "glut_app.h"
// Your initialization code goes here.
MyApp *g_app_data = 0;
void initialize_app(int height, int width)
{
  g_app_data = new MyApp(height, width);
}
